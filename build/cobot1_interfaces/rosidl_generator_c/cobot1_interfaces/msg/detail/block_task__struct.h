// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__STRUCT_H_
#define COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'color'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/BlockTask in the package cobot1_interfaces.
typedef struct cobot1_interfaces__msg__BlockTask
{
  double y_position;
  rosidl_runtime_c__String color;
  uint8_t block_type;
} cobot1_interfaces__msg__BlockTask;

// Struct for a sequence of cobot1_interfaces__msg__BlockTask.
typedef struct cobot1_interfaces__msg__BlockTask__Sequence
{
  cobot1_interfaces__msg__BlockTask * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__msg__BlockTask__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__STRUCT_H_
