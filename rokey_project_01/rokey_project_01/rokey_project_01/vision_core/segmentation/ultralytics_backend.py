from __future__ import annotations

from pathlib import Path

import cv2
import numpy as np

from ..models import SegmentationResult
from ..mosaic import validate_bgr_image
from .base import InstanceSegmenter, make_instance


class UltralyticsInstanceSegmenter(InstanceSegmenter):
    backend_name = 'ultralytics'

    def __init__(self, config: dict):
        model_path = str(config.get('model_path', '')).strip()
        if not model_path:
            raise ValueError('Ultralytics backend requires a non-empty model_path.')
        if not Path(model_path).is_file():
            raise FileNotFoundError(f'Instance-segmentation model does not exist: {model_path}')
        try:
            from ultralytics import YOLO
        except ImportError as exc:
            raise RuntimeError(
                'Ultralytics backend selected but the ultralytics package is not installed. '
                'Install requirements-ml.txt in the Python environment used by ROS 2.'
            ) from exc

        self._model = YOLO(model_path)
        self.model_name = Path(model_path).name
        self._model_path = model_path
        self._confidence = float(config.get('confidence_threshold', 0.25))
        self._iou = float(config.get('iou_threshold', 0.7))
        self._image_size = int(config.get('image_size', 640))
        self._max_instances = int(config.get('max_instances', 200))
        self._mask_threshold = float(config.get('mask_threshold', 0.5))
        self._min_area = int(config.get('min_mask_area_px', 64))
        self._device = str(config.get('device', 'auto')).strip()
        self._half = bool(config.get('half', False))
        self._agnostic_nms = bool(config.get('agnostic_nms', False))
        self._allowed_names = {
            str(value).strip().lower() for value in config.get('allowed_classes', [])
            if str(value).strip()
        }
        self._allowed_ids = {int(value) for value in config.get('allowed_class_ids', [])}

    @staticmethod
    def _to_numpy(value) -> np.ndarray:
        if hasattr(value, 'detach'):
            value = value.detach()
        if hasattr(value, 'cpu'):
            value = value.cpu()
        if hasattr(value, 'numpy'):
            value = value.numpy()
        return np.asarray(value)

    @staticmethod
    def _class_name(names, class_id: int) -> str:
        if isinstance(names, dict):
            return str(names.get(class_id, class_id))
        if isinstance(names, (list, tuple)) and 0 <= class_id < len(names):
            return str(names[class_id])
        return str(class_id)

    def infer(self, image_bgr: np.ndarray) -> SegmentationResult:
        validate_bgr_image(image_bgr)
        kwargs = {
            'source': image_bgr,
            'conf': self._confidence,
            'iou': self._iou,
            'imgsz': self._image_size,
            'max_det': self._max_instances,
            'retina_masks': True,
            'verbose': False,
            'agnostic_nms': self._agnostic_nms,
        }
        if self._device and self._device.lower() != 'auto':
            kwargs['device'] = self._device
        if self._half:
            kwargs['half'] = True
        if self._allowed_ids:
            kwargs['classes'] = sorted(self._allowed_ids)

        predictions = self._model.predict(**kwargs)
        height, width = image_bgr.shape[:2]
        if not predictions:
            return SegmentationResult(self.backend_name, self.model_name, width, height, [])
        prediction = predictions[0]
        if prediction.masks is None or prediction.boxes is None:
            return SegmentationResult(self.backend_name, self.model_name, width, height, [])

        masks = self._to_numpy(prediction.masks.data)
        boxes = self._to_numpy(prediction.boxes.xyxy)
        scores = self._to_numpy(prediction.boxes.conf).reshape(-1)
        classes = self._to_numpy(prediction.boxes.cls).reshape(-1).astype(int)
        count = min(len(masks), len(boxes), len(scores), len(classes))
        names = getattr(prediction, 'names', getattr(self._model, 'names', {}))

        instances = []
        for source_index in range(count):
            class_id = int(classes[source_index])
            class_name = self._class_name(names, class_id)
            if self._allowed_names and class_name.strip().lower() not in self._allowed_names:
                continue
            mask_probability = np.asarray(masks[source_index], dtype=np.float32)
            if mask_probability.shape != (height, width):
                mask_probability = cv2.resize(
                    mask_probability,
                    (width, height),
                    interpolation=cv2.INTER_LINEAR,
                )
            mask = mask_probability >= self._mask_threshold
            if int(np.count_nonzero(mask)) < self._min_area:
                continue
            instances.append(
                make_instance(
                    len(instances),
                    class_id,
                    class_name,
                    float(scores[source_index]),
                    mask,
                    bbox_xyxy=boxes[source_index],
                )
            )

        return SegmentationResult(
            backend=self.backend_name,
            model_name=self.model_name,
            image_width=width,
            image_height=height,
            instances=instances,
        )

    def warmup(self) -> None:
        side = max(64, self._image_size)
        dummy = np.zeros((side, side, 3), dtype=np.uint8)
        self.infer(dummy)
