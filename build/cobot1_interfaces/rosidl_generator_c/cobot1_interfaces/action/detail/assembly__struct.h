// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__STRUCT_H_
#define COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'tasks'
#include "cobot1_interfaces/msg/detail/block_task__struct.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_Goal
{
  cobot1_interfaces__msg__BlockTask__Sequence tasks;
} cobot1_interfaces__action__Assembly_Goal;

// Struct for a sequence of cobot1_interfaces__action__Assembly_Goal.
typedef struct cobot1_interfaces__action__Assembly_Goal__Sequence
{
  cobot1_interfaces__action__Assembly_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'error_message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_Result
{
  int32_t failed_step;
  rosidl_runtime_c__String error_message;
} cobot1_interfaces__action__Assembly_Result;

// Struct for a sequence of cobot1_interfaces__action__Assembly_Result.
typedef struct cobot1_interfaces__action__Assembly_Result__Sequence
{
  cobot1_interfaces__action__Assembly_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_Feedback
{
  int32_t current_index;
} cobot1_interfaces__action__Assembly_Feedback;

// Struct for a sequence of cobot1_interfaces__action__Assembly_Feedback.
typedef struct cobot1_interfaces__action__Assembly_Feedback__Sequence
{
  cobot1_interfaces__action__Assembly_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "cobot1_interfaces/action/detail/assembly__struct.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  cobot1_interfaces__action__Assembly_Goal goal;
} cobot1_interfaces__action__Assembly_SendGoal_Request;

// Struct for a sequence of cobot1_interfaces__action__Assembly_SendGoal_Request.
typedef struct cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence
{
  cobot1_interfaces__action__Assembly_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} cobot1_interfaces__action__Assembly_SendGoal_Response;

// Struct for a sequence of cobot1_interfaces__action__Assembly_SendGoal_Response.
typedef struct cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence
{
  cobot1_interfaces__action__Assembly_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} cobot1_interfaces__action__Assembly_GetResult_Request;

// Struct for a sequence of cobot1_interfaces__action__Assembly_GetResult_Request.
typedef struct cobot1_interfaces__action__Assembly_GetResult_Request__Sequence
{
  cobot1_interfaces__action__Assembly_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_GetResult_Response
{
  int8_t status;
  cobot1_interfaces__action__Assembly_Result result;
} cobot1_interfaces__action__Assembly_GetResult_Response;

// Struct for a sequence of cobot1_interfaces__action__Assembly_GetResult_Response.
typedef struct cobot1_interfaces__action__Assembly_GetResult_Response__Sequence
{
  cobot1_interfaces__action__Assembly_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"

/// Struct defined in action/Assembly in the package cobot1_interfaces.
typedef struct cobot1_interfaces__action__Assembly_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  cobot1_interfaces__action__Assembly_Feedback feedback;
} cobot1_interfaces__action__Assembly_FeedbackMessage;

// Struct for a sequence of cobot1_interfaces__action__Assembly_FeedbackMessage.
typedef struct cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence
{
  cobot1_interfaces__action__Assembly_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__STRUCT_H_
