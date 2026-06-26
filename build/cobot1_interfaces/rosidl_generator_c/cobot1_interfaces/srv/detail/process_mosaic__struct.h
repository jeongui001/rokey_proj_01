// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot1_interfaces:srv/ProcessMosaic.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__STRUCT_H_
#define COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'input_image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in srv/ProcessMosaic in the package cobot1_interfaces.
typedef struct cobot1_interfaces__srv__ProcessMosaic_Request
{
  sensor_msgs__msg__Image input_image;
  uint32_t grid_rows;
  uint32_t grid_cols;
} cobot1_interfaces__srv__ProcessMosaic_Request;

// Struct for a sequence of cobot1_interfaces__srv__ProcessMosaic_Request.
typedef struct cobot1_interfaces__srv__ProcessMosaic_Request__Sequence
{
  cobot1_interfaces__srv__ProcessMosaic_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__srv__ProcessMosaic_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// Member 'colors'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ProcessMosaic in the package cobot1_interfaces.
typedef struct cobot1_interfaces__srv__ProcessMosaic_Response
{
  bool success;
  rosidl_runtime_c__String message;
  rosidl_runtime_c__String__Sequence colors;
} cobot1_interfaces__srv__ProcessMosaic_Response;

// Struct for a sequence of cobot1_interfaces__srv__ProcessMosaic_Response.
typedef struct cobot1_interfaces__srv__ProcessMosaic_Response__Sequence
{
  cobot1_interfaces__srv__ProcessMosaic_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__srv__ProcessMosaic_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__STRUCT_H_
