// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot1_interfaces:msg/WebcamError.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__STRUCT_H_
#define COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'expected_color'
// Member 'detected_color'
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/WebcamError in the package cobot1_interfaces.
typedef struct cobot1_interfaces__msg__WebcamError
{
  int32_t step;
  int32_t row;
  int32_t col;
  rosidl_runtime_c__String expected_color;
  rosidl_runtime_c__String detected_color;
  rosidl_runtime_c__String message;
} cobot1_interfaces__msg__WebcamError;

// Struct for a sequence of cobot1_interfaces__msg__WebcamError.
typedef struct cobot1_interfaces__msg__WebcamError__Sequence
{
  cobot1_interfaces__msg__WebcamError * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__msg__WebcamError__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__STRUCT_H_
