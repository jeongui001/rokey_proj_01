// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot1_interfaces/msg/detail/block_task__rosidl_typesupport_introspection_c.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot1_interfaces/msg/detail/block_task__functions.h"
#include "cobot1_interfaces/msg/detail/block_task__struct.h"


// Include directives for member types
// Member `color`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__msg__BlockTask__init(message_memory);
}

void cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_fini_function(void * message_memory)
{
  cobot1_interfaces__msg__BlockTask__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_member_array[3] = {
  {
    "y_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__msg__BlockTask, y_position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "color",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__msg__BlockTask, color),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "block_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__msg__BlockTask, block_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_members = {
  "cobot1_interfaces__msg",  // message namespace
  "BlockTask",  // message name
  3,  // number of fields
  sizeof(cobot1_interfaces__msg__BlockTask),
  cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_member_array,  // message members
  cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_type_support_handle = {
  0,
  &cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, msg, BlockTask)() {
  if (!cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__msg__BlockTask__rosidl_typesupport_introspection_c__BlockTask_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
