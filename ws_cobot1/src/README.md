# ROS 2 인스턴스 세그멘테이션 기반 블록 모자이크·검증 패키지

```text
ros2_ws/src/
├── vision_interfaces/
├── vision_core/
├── image_processor_node/
├── verify_node/
└── vision_camera_bringup/
```

`assembly_vision/` 같은 우산 디렉터리는 필요하지 않습니다. 단, `ament_python` 패키지 안의 같은 이름 디렉터리는 Python import를 위한 필수 모듈 디렉터리입니다.

```text
image_processor_node/          # ROS 패키지
└── image_processor_node/      # Python 모듈
```

### ImageProcessor 처리 순서

```text
입력 이미지
  → center crop / letterbox / stretch
  → 인스턴스 세그멘테이션
  → 각 N×N 셀과 모든 인스턴스 마스크의 겹침 계산
  → 셀별 dominant instance 선택
  → 선택된 마스크 내부 픽셀 또는 모델 클래스에서 블록 색 결정
  → N×N BlockModel + 모자이크 이미지
  → CameraInfo + TF + x/y 고정 평면으로 base 좌표 계산
```

### VerifyNode 처리 순서

```text
/front_camera/image_raw
  → 렌즈 왜곡 보정
  → 물리 작업 영역 ROI 원근 변환
  → 블록 인스턴스 세그멘테이션
  → 인스턴스 마스크를 기대 모델과 같은 N×N 격자로 투영
  → 색상·점유·마스크 겹침·중심 오차 비교
  → match_rate + Mismatch[] 반환
```

검증 오류 유형은 다음과 같습니다.

```text
MISSING             기대 블록이 검출되지 않음
WRONG_COLOR         기대 색상과 관측 색상이 다름
EXTRA               빈 셀에 블록이 검출됨
UNCERTAIN           기대 또는 관측 신뢰도가 기준 미만
MISALIGNED          마스크 면적 또는 중심 위치가 셀 기준을 벗어남
INSTANCE_CONFLICT   하나의 셀에 여러 인스턴스가 유의미하게 겹침
```

## 세그멘테이션 백엔드

### `opencv_components` — 모델 없는 실행·보정·테스트용

테두리 배경색을 Lab 공간에서 추정하고, 전경 색상 군집과 연결 성분을 이용해 인스턴스 마스크를 생성합니다. 전체 파이프라인은 실제 인스턴스 마스크를 사용하지만, **같은 색의 블록이 서로 붙어 있으면 분리하지 못할 수 있으므로 운영 검증에는 custom model 사용을 권장**합니다.

기본 `vision.yaml`은 모델 파일 없이 실행되도록 이 백엔드를 선택합니다. 운영 시 launch 인수만으로 두 노드를 `ultralytics`로 전환할 수 있습니다.

# 패키지 구성

```text
vision_interfaces/
├── msg/SegmentationInstance.msg
├── msg/BlockCell.msg
├── msg/BlockModel.msg
├── msg/Mismatch.msg
├── srv/ProcessMosaic.srv
└── srv/VerifyAssembly.srv

vision_core/vision_core/
├── config.py
├── geometry.py
├── grid_projection.py
├── models.py
├── mosaic.py
├── overlay.py
├── palette.py
├── verification.py
└── segmentation/
    ├── base.py
    ├── factory.py
    ├── opencv_components.py
    └── ultralytics_backend.py

image_processor_node/
├── image_processor_node/node.py
├── image_processor_node/process_mosaic_cli.py
└── config/image_processor.yaml

verify_node/
├── verify_node/node.py
├── verify_node/verify_cli.py
└── config/verify.yaml

vision_camera_bringup/
├── launch/vision_system.launch.py
├── launch/vision_nodes.launch.py
└── config/
    ├── vision.yaml
    ├── vision_ultralytics_template.yaml
    ├── usb_camera.yaml
    └── front_camera_info.yaml
```

# 주요 인터페이스

## `/vision/process_mosaic`

`vision_interfaces/srv/ProcessMosaic`

입력:

- `input_image`: 복사할 원본 이미지
- `grid_size`: N
- `output_width`, `output_height`: 반환 모자이크 크기, 0이면 기본값
- `fixed_axis`: `x` 또는 `y`, 빈 문자열이면 설정값
- `fixed_axis_value`: 고정 평면의 base-frame 좌표, 단위 m
- `compute_robot_coordinates`: 카메라 보정과 TF를 이용해 각 셀의 로봇 좌표 계산 여부

출력:

- `fitted_image`: 실제 세그멘테이션에 사용한 이미지
- `segmentation_overlay`: 인스턴스 ID·마스크·박스·클래스
- `mosaic_image`: N×N 블록 모자이크
- `model`: 인스턴스 목록, 셀별 dominant instance, 색상, 마스크 점유율, 카메라 픽셀, base 좌표

## `/vision/verify_assembly`

`vision_interfaces/srv/VerifyAssembly`

출력:

- `workspace_image`: 보정 후 물리 ROI를 정사각형으로 원근 변환한 영상
- `segmentation_overlay`: workspace 상의 블록 인스턴스 마스크
- `observed_mosaic`: 관측 N×N 모델
- `overlay_image`: 원 카메라 영상상의 검증 결과
- `observed_model`, `mismatches`, `match_rate`, `passed`

# 토픽

```text
입력
/front_camera/image_raw
/front_camera/camera_info
/vision/expected_model

ImageProcessor 출력
/vision/source/fitted
/vision/source/segmentation_overlay
/vision/mosaic
/vision/expected_model             transient-local

VerifyNode 출력
/vision/camera/rectified
/vision/camera/camera_info
/vision/verify/live_overlay
/vision/verify/workspace
/vision/verify/segmentation_overlay
/vision/verify/live_segmentation    선택 기능
/vision/verify/observed_mosaic
/vision/verify/overlay
/vision/observed_model              transient-local
```

## 실행

```bash
source /opt/ros/$ROS_DISTRO/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 launch vision_camera_bringup vision_system.launch.py \
  calibration_ready:=false \
  publish_static_tf:=false
```

다른 드라이버가 이미 동일한 토픽을 발행하면 공식 `usb_cam` 실행을 끕니다.

```bash
ros2 launch vision_camera_bringup vision_system.launch.py \
  use_camera_driver:=false \
  publish_static_tf:=false
```

# 사용 예

## 이미지 → 인스턴스 세그멘테이션 모자이크

좌표 계산 없이 8×8 모델 생성:

```bash
ros2 run image_processor_node process_mosaic_cli \
  --image ~/input.png \
  --grid-size 8 \
  --mosaic ~/mosaic.png \
  --segmentation ~/source_segmentation.png \
  --model-json ~/model.json
```

카메라/TF 보정 후 좌표도 계산:

```bash
ros2 run image_processor_node process_mosaic_cli \
  --image ~/input.png \
  --grid-size 8 \
  --fixed-axis x \
  --fixed-value 0.50 \
  --compute-coordinates
```

## 완성 조립물 검증

먼저 ProcessMosaic가 기대 모델을 `/vision/expected_model`에 발행한 상태여야 합니다.

```bash
ros2 run verify_node verify_cli \
  --threshold 95 \
  --timeout 3.0 \
  --overlay ~/verification_overlay.png \
  --segmentation ~/verification_segmentation.png
```

# 카메라와 좌표 보정

## 1. 내부 파라미터

`front_camera_info.yaml`은 의도적으로 미보정 상태입니다. 실제 카메라를 보정한 뒤 교체해야 합니다.

```bash
ros2 run camera_calibration cameracalibrator \
  --no-service-check \
  --size 8x6 \
  --square 0.025 \
  --ros-args -r image:=/front_camera/image_raw
```

해상도를 변경하면 내부 보정을 다시 수행합니다.

## 2. 카메라-베이스 외부 변환

다음 TF가 필요합니다.

```text
base_link -> front_camera_optical_frame
```

URDF나 별도 보정 노드가 이미 TF를 발행하면 `publish_static_tf:=false`를 사용하십시오. 임시 static TF는 launch 인수 `camera_x/y/z`, `camera_roll/pitch/yaw`로 지정할 수 있습니다.

## 3. 작업 영역 ROI

`vision.yaml`의 `workspace.roi_normalized`를 보정된 영상에서 다음 순서로 설정합니다.

```text
top-left → top-right → bottom-right → bottom-left
```

정규화 식:

```text
u_norm = pixel_x / (image_width - 1)
v_norm = pixel_y / (image_height - 1)
```

## 4. x/y 고정 평면 좌표

각 N×N 셀의 물리 카메라 픽셀 중심을 카메라 광선으로 역투영하고, base frame에서 다음 평면 중 하나와 교차시킵니다.

```text
fixed_axis=x → x=fixed_axis_value
fixed_axis=y → y=fixed_axis_value
```

반환 단위는 m입니다. DRL TCP에서 mm가 필요하면 RobotController 경계에서 변환하십시오.

이 계산은 블록 배치 중심들이 하나의 전면 평면에 놓인다는 가정입니다. 깊이가 다른 여러 평면을 동시에 처리하려면 요청별 고정값을 바꾸거나 깊이 카메라/3차원 캘리브레이션을 사용해야 합니다.

# 운영 튜닝 순서

1. 카메라 노출·화이트밸런스를 고정합니다.
2. 내부 보정과 `base_link -> camera` TF를 확정합니다.
3. 물리 ROI를 실제 작업대에 맞춥니다.
4. `palette.entries`를 실제 조명에서 촬영한 블록 RGB로 보정합니다.
5. Source model과 block model의 클래스 이름을 확인합니다.
6. 색상별 클래스를 쓰면 `class_to_palette`를 실제 클래스명과 맞춥니다.
7. `min_cell_coverage`, `min_alignment_coverage`, `max_centroid_offset_ratio`를 검증 데이터로 튜닝합니다.
8. 마지막으로 `pass_threshold`를 결정합니다.

# 중요한 제한사항

- 모델 가중치는 포함되어 있지 않습니다.
- 인스턴스 ID는 추론 1회 안에서만 유효하며 프레임 간 고정 ID가 아닙니다.
- 전면 카메라에서 가려진 블록은 검출할 수 없습니다.
- 같은 색의 맞닿은 블록을 모델 없는 OpenCV 백엔드가 항상 분리하지는 못합니다.
- 실시간 파지·낙하 감시는 별도의 실행 모니터 상태 머신과 시간 추적이 필요합니다. 이 패키지의 VerifyNode는 완성·복구 완료 시점의 구조 검증이 중심입니다.
- 사람·장비 안전 정지는 영상 추론만으로 구현하지 말고 로봇 안전 계층을 사용해야 합니다.

# 검증 상태

이 배포본에서 수행한 정적 검증:

- 모든 Python 파일 `compileall` 통과
- 모든 YAML 파싱 통과
- 모든 `package.xml` XML 파싱 통과
- `vision_core` 단위 테스트 6개 통과
