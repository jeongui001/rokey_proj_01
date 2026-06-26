// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__STRUCT_H_
#define COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'colors'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ExpectedModel in the package cobot1_interfaces.
typedef struct cobot1_interfaces__msg__ExpectedModel
{
  uint32_t grid_size;
  rosidl_runtime_c__String__Sequence colors;
} cobot1_interfaces__msg__ExpectedModel;

// Struct for a sequence of cobot1_interfaces__msg__ExpectedModel.
typedef struct cobot1_interfaces__msg__ExpectedModel__Sequence
{
  cobot1_interfaces__msg__ExpectedModel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__msg__ExpectedModel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__STRUCT_H_
