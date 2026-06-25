# 작업 유형 상수
uint8 PICK_PLACE=0
uint8 DETACH_DISCARD=1

# 작업 유형 (PICK_PLACE=0, DETACH_DISCARD=1)
uint8 task_type

# 작업 식별자 및 블록 색상
string task_id
string color

# source_pose: Pick 또는 Detach 좌표 [x_mm, y_mm, z_mm, a_deg, b_deg, c_deg]
float64[6] source_pose

# target_pose: Place(stack_index=0 기준) 또는 Basket 좌표 [x_mm, y_mm, z_mm, a_deg, b_deg, c_deg]
float64[6] target_pose

# Place 적층 인덱스 (PICK_PLACE 전용, 0부터 시작)
int32 stack_index
