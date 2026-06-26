// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot1_interfaces/msg/detail/expected_model__rosidl_typesupport_introspection_c.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot1_interfaces/msg/detail/expected_model__functions.h"
#include "cobot1_interfaces/msg/detail/expected_model__struct.h"


// Include directives for member types
// Member `colors`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__msg__ExpectedModel__init(message_memory);
}

void cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_fini_function(void * message_memory)
{
  cobot1_interfaces__msg__ExpectedModel__fini(message_memory);
}

size_t cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__size_function__ExpectedModel__colors(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__get_const_function__ExpectedModel__colors(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__get_function__ExpectedModel__colors(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__fetch_function__ExpectedModel__colors(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__get_const_function__ExpectedModel__colors(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__assign_function__ExpectedModel__colors(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__get_function__ExpectedModel__colors(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__resize_function__ExpectedModel__colors(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_member_array[2] = {
  {
    "grid_size",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__msg__ExpectedModel, grid_size),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "colors",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__msg__ExpectedModel, colors),  // bytes offset in struct
    NULL,  // default value
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__size_function__ExpectedModel__colors,  // size() function pointer
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__get_const_function__ExpectedModel__colors,  // get_const(index) function pointer
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__get_function__ExpectedModel__colors,  // get(index) function pointer
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__fetch_function__ExpectedModel__colors,  // fetch(index, &value) function pointer
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__assign_function__ExpectedModel__colors,  // assign(index, value) function pointer
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__resize_function__ExpectedModel__colors  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_members = {
  "cobot1_interfaces__msg",  // message namespace
  "ExpectedModel",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__msg__ExpectedModel),
  cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_member_array,  // message members
  cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_type_support_handle = {
  0,
  &cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, msg, ExpectedModel)() {
  if (!cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__msg__ExpectedModel__rosidl_typesupport_introspection_c__ExpectedModel_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
