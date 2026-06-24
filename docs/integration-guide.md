# ws_cobot1 → rokey_project_01 통합 가이드

## 한 줄 요약

`ws_cobot1`의 5개 패키지(vision_core, vision_interfaces, image_processor_node, verify_node, vision_camera_bringup)를 `rokey_project_01` 단일 패키지로 통합했습니다.

---

## 디렉토리 구조

```
rokey_proj_01/                                        ← 워크스페이스 루트
└── rokey_project_01/
    ├── rokey_project_01_interfaces/                   ← 인터페이스 패키지 (CMake)
    │   ├── msg/
    │   │   ├── BlockCell.msg
    │   │   ├── BlockModel.msg
    │   │   ├── SegmentationInstance.msg
    │   │   ├── Mismatch.msg
    │   │   └── WebcamError.msg
    │   ├── srv/
    │   │   ├── ProcessMosaic.srv
    │   │   ├── VerifyAssembly.srv
    │   │   └── SequencePlan.srv
    │   ├── action/
    │   │   └── ExecuteQueue.action
    │   ├── CMakeLists.txt
    │   └── package.xml
    │
    ├── rokey_project_01/                              ← 노드 패키지 (ament_python)
    │   ├── rokey_project_01/                          ← Python 모듈
    │   │   ├── vision_core/                           ← 흡수된 라이브러리
    │   │   │   ├── segmentation/
    │   │   │   ├── config.py
    │   │   │   ├── geometry.py
    │   │   │   ├── grid_projection.py
    │   │   │   ├── models.py
    │   │   │   ├── mosaic.py
    │   │   │   ├── overlay.py
    │   │   │   ├── palette.py
    │   │   │   └── verification.py
    │   │   ├── bridge_node.py
    │   │   ├── image_processor_node.py
    │   │   ├── verify_node.py
    │   │   ├── sequencer_node.py
    │   │   ├── robot_controller_node.py
    │   │   ├── camera_node.py
    │   │   ├── webcam_node.py
    │   │   ├── process_mosaic_cli.py
    │   │   ├── verify_cli.py
    │   │   └── db.py
    │   ├── config/
    │   │   ├── vision.yaml
    │   │   ├── vision_ultralytics_template.yaml
    │   │   ├── image_processor.yaml
    │   │   ├── verify.yaml
    │   │   ├── front_camera_info.yaml
    │   │   └── usb_camera.yaml
    │   ├── launch/
    │   │   └── assembly.launch.py
    │   ├── setup.py
    │   └── package.xml
    │
    └── flask_app/                                     ← Flask 웹 앱
        ├── app.py
        ├── requirements.txt
        ├── templates/
        └── static/
```

---

## 파일 대응표

경로는 모두 `ws_cobot1/src/` 기준(좌) / `rokey_project_01/` 기준(우)으로 작성.

| ws_cobot1/src/ (기존)                                              | rokey_project_01/ (현재)                                                    |
|-------------------------------------------------------------------|----------------------------------------------------------------------------|
| `vision_core/vision_core/*.py`                                    | `rokey_project_01/rokey_project_01/vision_core/*.py`                       |
| `vision_core/vision_core/segmentation/*.py`                       | `rokey_project_01/rokey_project_01/vision_core/segmentation/*.py`          |
| `vision_interfaces/msg/*.msg`                                     | `rokey_project_01_interfaces/msg/*.msg`                                    |
| `vision_interfaces/srv/*.srv`                                     | `rokey_project_01_interfaces/srv/*.srv`                                    |
| `image_processor_node/image_processor_node/node.py`               | `rokey_project_01/rokey_project_01/image_processor_node.py`                |
| `image_processor_node/image_processor_node/process_mosaic_cli.py` | `rokey_project_01/rokey_project_01/process_mosaic_cli.py`                  |
| `verify_node/verify_node/node.py`                                 | `rokey_project_01/rokey_project_01/verify_node.py`                         |
| `verify_node/verify_node/verify_cli.py`                           | `rokey_project_01/rokey_project_01/verify_cli.py`                          |
| `vision_camera_bringup/config/vision.yaml`                        | `rokey_project_01/config/vision.yaml`                                      |
| `vision_camera_bringup/config/vision_ultralytics_template.yaml`   | `rokey_project_01/config/vision_ultralytics_template.yaml`                 |
| `vision_camera_bringup/config/front_camera_info.yaml`             | `rokey_project_01/config/front_camera_info.yaml`                           |
| `vision_camera_bringup/config/usb_camera.yaml`                    | `rokey_project_01/config/usb_camera.yaml`                                  |
| `image_processor_node/config/image_processor.yaml`                | `rokey_project_01/config/image_processor.yaml`                             |
| `verify_node/config/verify.yaml`                                  | `rokey_project_01/config/verify.yaml`                                      |

---

## import 변경 규칙

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

**vision_core 내부**는 상대 import(`from .models import ...`)를 사용하므로 수정 불필요.

---

## 인터페이스 목록

### msg

| 이름 | 출처 | 설명 |
|------|------|------|
| `BlockCell.msg` | vision_interfaces | 격자 셀 하나의 정보 (색상, 좌표, 신뢰도 등) |
| `BlockModel.msg` | vision_interfaces | N×N 격자 모델 전체 (셀 배열 + 세그멘테이션 정보) |
| `SegmentationInstance.msg` | vision_interfaces | 세그멘테이션 인스턴스 하나 (바운딩 박스, 마스크, 색상) |
| `Mismatch.msg` | vision_interfaces | 검증 시 불일치 항목 (기대 vs 관측) |
| `WebcamError.msg` | 기존 유지 | 실시간 모니터링 에러 |

### srv

| 이름 | 출처 | 설명 |
|------|------|------|
| `ProcessMosaic.srv` | vision_interfaces | 이미지 → 세그멘테이션 → N×N 블록 모델 생성 |
| `VerifyAssembly.srv` | vision_interfaces | 카메라 프레임과 기준 모델 비교 검증 |
| `SequencePlan.srv` | 기존 유지 | 격자 → 로봇 동작 큐 생성 |

### action

| 이름 | 출처 | 설명 |
|------|------|------|
| `ExecuteQueue.action` | 기존 유지 | 동작 큐 순차 실행 (피드백 포함) |

---

## 서비스/토픽 이름

| 기능 | 서비스/토픽 | 타입 | 노드 |
|------|------------|------|------|
| 이미지 분석 | `/image/analyze` (서비스) | `ProcessMosaic` | ImageProcessorNode |
| 조립 검증 | `/verify/assembly` (서비스) | `VerifyAssembly` | VerifyNode |
| 기준 모델 공유 | `/vision/expected_model` (토픽, TRANSIENT_LOCAL) | `BlockModel` | Bridge → Verify |
| 배치 계획 | `/sequence/plan` (서비스) | `SequencePlan` | SequencerNode |
| 로봇 실행 | `/execute_queue` (액션) | `ExecuteQueue` | RobotControllerNode |
| 카메라 영상 | `/front_camera/image_raw` (토픽) | `sensor_msgs/Image` | CameraNode |
| 카메라 정보 | `/front_camera/camera_info` (토픽) | `sensor_msgs/CameraInfo` | CameraNode |
| 웹캠 에러 | `/webcam/error` (토픽) | `WebcamError` | WebcamNode |

---

## 빌드

```bash
cd ~/rokey_proj_01_demo/rokey_proj_01
colcon build --packages-select rokey_project_01_interfaces rokey_project_01
source install/setup.bash
```

## 실행

```bash
# 전체 실행
ros2 launch rokey_project_01 assembly.launch.py

# 개별 노드 (image_processor는 vision_config_file 필수)
ros2 run rokey_project_01 image_processor_node \
  --ros-args -p vision_config_file:=$(ros2 pkg prefix rokey_project_01)/share/rokey_project_01/config/vision.yaml

# CLI 도구
ros2 run rokey_project_01 process_mosaic_cli --image photo.png --grid-size 8
ros2 run rokey_project_01 verify_cli
```

---

## 앞으로 작업할 때

- **ws_cobot1 디렉토리는 더 이상 사용하지 않음**
- 모든 수정은 `rokey_project_01/` 안에서 진행
- vision_core 수정: `rokey_project_01/rokey_project_01/rokey_project_01/vision_core/` 에서 직접 수정
- 새 msg/srv 추가 시: `rokey_project_01_interfaces/`에 파일 추가 후 `CMakeLists.txt` 업데이트
- config 수정: `rokey_project_01/rokey_project_01/config/` 의 yaml 파일 편집
