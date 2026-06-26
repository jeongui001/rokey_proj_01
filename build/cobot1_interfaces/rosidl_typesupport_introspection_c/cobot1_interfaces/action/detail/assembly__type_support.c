// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot1_interfaces/action/detail/assembly__functions.h"
#include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `tasks`
#include "cobot1_interfaces/msg/block_task.h"
// Member `tasks`
#include "cobot1_interfaces/msg/detail/block_task__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_Goal__init(message_memory);
}

void cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_Goal__fini(message_memory);
}

size_t cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__size_function__Assembly_Goal__tasks(
  const void * untyped_member)
{
  const cobot1_interfaces__msg__BlockTask__Sequence * member =
    (const cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__get_const_function__Assembly_Goal__tasks(
  const void * untyped_member, size_t index)
{
  const cobot1_interfaces__msg__BlockTask__Sequence * member =
    (const cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__get_function__Assembly_Goal__tasks(
  void * untyped_member, size_t index)
{
  cobot1_interfaces__msg__BlockTask__Sequence * member =
    (cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__fetch_function__Assembly_Goal__tasks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cobot1_interfaces__msg__BlockTask * item =
    ((const cobot1_interfaces__msg__BlockTask *)
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__get_const_function__Assembly_Goal__tasks(untyped_member, index));
  cobot1_interfaces__msg__BlockTask * value =
    (cobot1_interfaces__msg__BlockTask *)(untyped_value);
  *value = *item;
}

void cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__assign_function__Assembly_Goal__tasks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cobot1_interfaces__msg__BlockTask * item =
    ((cobot1_interfaces__msg__BlockTask *)
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__get_function__Assembly_Goal__tasks(untyped_member, index));
  const cobot1_interfaces__msg__BlockTask * value =
    (const cobot1_interfaces__msg__BlockTask *)(untyped_value);
  *item = *value;
}

bool cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__resize_function__Assembly_Goal__tasks(
  void * untyped_member, size_t size)
{
  cobot1_interfaces__msg__BlockTask__Sequence * member =
    (cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  cobot1_interfaces__msg__BlockTask__Sequence__fini(member);
  return cobot1_interfaces__msg__BlockTask__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_member_array[1] = {
  {
    "tasks",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_Goal, tasks),  // bytes offset in struct
    NULL,  // default value
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__size_function__Assembly_Goal__tasks,  // size() function pointer
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__get_const_function__Assembly_Goal__tasks,  // get_const(index) function pointer
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__get_function__Assembly_Goal__tasks,  // get(index) function pointer
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__fetch_function__Assembly_Goal__tasks,  // fetch(index, &value) function pointer
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__assign_function__Assembly_Goal__tasks,  // assign(index, value) function pointer
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__resize_function__Assembly_Goal__tasks  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_Goal",  // message name
  1,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_Goal),
  cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_Goal)() {
  cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, msg, BlockTask)();
  if (!cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_Goal__rosidl_typesupport_introspection_c__Assembly_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `error_message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_Result__init(message_memory);
}

void cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_member_array[2] = {
  {
    "failed_step",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_Result, failed_step),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_Result, error_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_Result",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_Result),
  cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_Result)() {
  if (!cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_Result__rosidl_typesupport_introspection_c__Assembly_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_Feedback__init(message_memory);
}

void cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_member_array[1] = {
  {
    "current_index",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_Feedback, current_index),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_Feedback",  // message name
  1,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_Feedback),
  cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_Feedback)() {
  if (!cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_Feedback__rosidl_typesupport_introspection_c__Assembly_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "cobot1_interfaces/action/assembly.h"
// Member `goal`
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_SendGoal_Request__init(message_memory);
}

void cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_SendGoal_Request),
  cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal_Request)() {
  cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_Goal)();
  if (!cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_SendGoal_Request__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_SendGoal_Response__init(message_memory);
}

void cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_SendGoal_Response),
  cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal_Response)() {
  cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_SendGoal_Response__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_members = {
  "cobot1_interfaces__action",  // service namespace
  "Assembly_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_type_support_handle = {
  0,
  &cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal)() {
  if (!cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_SendGoal_Response)()->data;
  }

  return &cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_GetResult_Request__init(message_memory);
}

void cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_GetResult_Request),
  cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult_Request)() {
  cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_GetResult_Request__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "cobot1_interfaces/action/assembly.h"
// Member `result`
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_GetResult_Response__init(message_memory);
}

void cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_GetResult_Response),
  cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult_Response)() {
  cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_Result)();
  if (!cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_GetResult_Response__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_members = {
  "cobot1_interfaces__action",  // service namespace
  "Assembly_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_type_support_handle = {
  0,
  &cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult)() {
  if (!cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_GetResult_Response)()->data;
  }

  return &cobot1_interfaces__action__detail__assembly__rosidl_typesupport_introspection_c__Assembly_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__functions.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "cobot1_interfaces/action/assembly.h"
// Member `feedback`
// already included above
// #include "cobot1_interfaces/action/detail/assembly__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__action__Assembly_FeedbackMessage__init(message_memory);
}

void cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_fini_function(void * message_memory)
{
  cobot1_interfaces__action__Assembly_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__action__Assembly_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_members = {
  "cobot1_interfaces__action",  // message namespace
  "Assembly_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__action__Assembly_FeedbackMessage),
  cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_member_array,  // message members
  cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_type_support_handle = {
  0,
  &cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_FeedbackMessage)() {
  cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, action, Assembly_Feedback)();
  if (!cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__action__Assembly_FeedbackMessage__rosidl_typesupport_introspection_c__Assembly_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
