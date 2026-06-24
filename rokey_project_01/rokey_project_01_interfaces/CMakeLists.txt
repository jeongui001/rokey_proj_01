cmake_minimum_required(VERSION 3.8)
project(rokey_project_01_interfaces)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(action_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/BlockCell.msg"
  "msg/BlockModel.msg"
  "msg/SegmentationInstance.msg"
  "msg/Mismatch.msg"
  "msg/WebcamError.msg"
  "srv/ProcessMosaic.srv"
  "srv/VerifyAssembly.srv"
  "srv/SequencePlan.srv"
  "action/ExecuteQueue.action"
  DEPENDENCIES builtin_interfaces std_msgs sensor_msgs geometry_msgs
)

ament_package()
