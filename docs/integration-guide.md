# ws_cobot1 → rokey_project_01 통합 가이드

## 한 줄 요약

`ws_cobot1`의 5개 패키지(vision_core, vision_interfaces, image_processor_node, verify_node, vision_camera_bringup)를 `rokey_project_01` 단일 패키지로 통합했습니다.

---

## 무엇이 바뀌었나

### 패키지 구조 변경

```
[Before] ws_cobot1/src/                    [After] rokey_project_01/
├── vision_core/                    →       rokey_project_01/vision_core/  (내부 모듈)
├── vision_interfaces/              →       rokey_project_01_interfaces/   (기존 인터페이스 패키지에 흡수)
├── image_processor_node/           →       rokey_project_01/image_processor_node.py
├── verify_node/                    →       rokey_project_01/verify_node.py
└── vision_camera_bringup/          →       rokey_project_01/config/ + launch/
```

### 파일 대응표

| ws_cobot1 (기존)                                  | rokey_project_01 (현재)                                |
|--------------------------------------------------|-------------------------------------------------------|
| `vision_core/vision_core/*.py`                   | `rokey_project_01/vision_core/*.py`                   |
| `vision_core/vision_core/segmentation/*.py`      | `rokey_project_01/vision_core/segmentation/*.py`      |
| `vision_interfaces/msg/*.msg`                    | `rokey_project_01_interfaces/msg/*.msg`               |
| `vision_interfaces/srv/*.srv`                    | `rokey_project_01_interfaces/srv/*.srv`               |
| `image_processor_node/node.py`                   | `rokey_project_01/image_processor_node.py`            |
| `image_processor_node/process_mosaic_cli.py`     | `rokey_project_01/process_mosaic_cli.py`              |
| `verify_node/node.py`                            | `rokey_project_01/verify_node.py`                     |
| `verify_node/verify_cli.py`                      | `rokey_project_01/verify_cli.py`                      |
| `vision_camera_bringup/config/vision.yaml`       | `rokey_project_01/config/vision.yaml`                 |
| `image_processor_node/config/image_processor.yaml`| `rokey_project_01/config/image_processor.yaml`       |
| `verify_node/config/verify.yaml`                 | `rokey_project_01/config/verify.yaml`                 |

---

## import 경로 변경

코드 수정 시 아래 규칙만 기억하면 됩니다.

```python
# Before (ws_cobot1)
from vision_core.config import load_vision_config
from vision_core.segmentation import create_segmenter
from vision_interfaces.srv import ProcessMosaic
from vision_interfaces.msg import BlockModel

# After (rokey_project_01)
from rokey_project_01.vision_core.config import load_vision_config
from rokey_project_01.vision_core.segmentation import create_segmenter
from rokey_project_01_interfaces.srv import ProcessMosaic
from rokey_project_01_interfaces.msg import BlockModel
```

**vision_core 내부**는 상대 import(`from .models import ...`)를 사용하므로 수정 불필요합니다.

---

## 인터페이스 변경

### 삭제된 타입 (rokey_project_01 구형)

| 타입 | 대체 |
|------|------|
| `ImageAnalyze.srv` | `ProcessMosaic.srv` |
| `VerifyImage.msg` | `BlockModel` 토픽 발행 |
| `CalibratedImage.msg` | `sensor_msgs/Image` + `sensor_msgs/CameraInfo` |

### 현재 인터페이스 목록

```
rokey_project_01_interfaces/
├── msg/
│   ├── BlockCell.msg              ← vision_interfaces에서 이관
│   ├── BlockModel.msg             ← vision_interfaces에서 이관
│   ├── SegmentationInstance.msg   ← vision_interfaces에서 이관
│   ├── Mismatch.msg              ← vision_interfaces에서 이관
│   └── WebcamError.msg           ← 기존 유지
├── srv/
│   ├── ProcessMosaic.srv         ← vision_interfaces에서 이관 (구 ImageAnalyze 대체)
│   ├── VerifyAssembly.srv        ← vision_interfaces에서 이관
│   └── SequencePlan.srv          ← 기존 유지
└── action/
    └── ExecuteQueue.action       ← 기존 유지
```

---

## 서비스/토픽 이름

| 기능 | 서비스/토픽 | 타입 |
|------|------------|------|
| 이미지 분석 | `/image/analyze` (서비스) | `ProcessMosaic` |
| 조립 검증 | `/verify/assembly` (서비스) | `VerifyAssembly` |
| 기준 모델 공유 | `/vision/expected_model` (토픽, TRANSIENT_LOCAL) | `BlockModel` |
| 배치 계획 | `/sequence/plan` (서비스) | `SequencePlan` |
| 로봇 실행 | `/execute_queue` (액션) | `ExecuteQueue` |
| 카메라 영상 | `/front_camera/image_raw` (토픽) | `sensor_msgs/Image` |
| 카메라 정보 | `/front_camera/camera_info` (토픽) | `sensor_msgs/CameraInfo` |
| 웹캠 에러 | `/webcam/error` (토픽) | `WebcamError` |

---

## 빌드 방법

```bash
cd ~/rokey_proj_01_demo/rokey_proj_01
colcon build --packages-select rokey_project_01_interfaces rokey_project_01
source install/setup.bash
```

## 실행 방법

```bash
# 전체 실행
ros2 launch rokey_project_01 assembly.launch.py

# 개별 노드 실행 (image_processor는 vision_config_file 필수)
ros2 run rokey_project_01 image_processor_node \
  --ros-args -p vision_config_file:=$(ros2 pkg prefix rokey_project_01)/share/rokey_project_01/config/vision.yaml

# CLI 도구
ros2 run rokey_project_01 process_mosaic_cli --image photo.png --grid-size 8
ros2 run rokey_project_01 verify_cli
```

---

## 앞으로 작업할 때

- `ws_cobot1` 디렉토리는 더 이상 사용하지 않습니다
- 모든 수정은 `rokey_project_01/` 안에서 합니다
- vision_core 수정 시 `rokey_project_01/rokey_project_01/vision_core/` 에서 직접 수정
- 새 msg/srv 추가 시 `rokey_project_01_interfaces/`에 추가하고 `CMakeLists.txt` 업데이트
