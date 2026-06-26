// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__STRUCT_H_
#define COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__STRUCT_H_

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

/// Struct defined in srv/SequencePlan in the package cobot1_interfaces.
typedef struct cobot1_interfaces__srv__SequencePlan_Request
{
  rosidl_runtime_c__String__Sequence colors;
  uint32_t grid_width;
  uint32_t grid_height;
} cobot1_interfaces__srv__SequencePlan_Request;

// Struct for a sequence of cobot1_interfaces__srv__SequencePlan_Request.
typedef struct cobot1_interfaces__srv__SequencePlan_Request__Sequence
{
  cobot1_interfaces__srv__SequencePlan_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__srv__SequencePlan_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'error_message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'tasks'
#include "cobot1_interfaces/msg/detail/block_task__struct.h"

/// Struct defined in srv/SequencePlan in the package cobot1_interfaces.
typedef struct cobot1_interfaces__srv__SequencePlan_Response
{
  rosidl_runtime_c__String error_message;
  cobot1_interfaces__msg__BlockTask__Sequence tasks;
} cobot1_interfaces__srv__SequencePlan_Response;

// Struct for a sequence of cobot1_interfaces__srv__SequencePlan_Response.
typedef struct cobot1_interfaces__srv__SequencePlan_Response__Sequence
{
  cobot1_interfaces__srv__SequencePlan_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__srv__SequencePlan_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__STRUCT_H_
