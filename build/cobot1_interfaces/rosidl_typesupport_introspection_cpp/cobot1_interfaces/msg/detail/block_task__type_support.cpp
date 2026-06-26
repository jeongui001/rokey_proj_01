// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "cobot1_interfaces/msg/detail/block_task__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void BlockTask_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::msg::BlockTask(_init);
}

void BlockTask_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::msg::BlockTask *>(message_memory);
  typed_message->~BlockTask();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember BlockTask_message_member_array[3] = {
  {
    "y_position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::msg::BlockTask, y_position),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "color",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::msg::BlockTask, color),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "block_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::msg::BlockTask, block_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers BlockTask_message_members = {
  "cobot1_interfaces::msg",  // message namespace
  "BlockTask",  // message name
  3,  // number of fields
  sizeof(cobot1_interfaces::msg::BlockTask),
  BlockTask_message_member_array,  // message members
  BlockTask_init_function,  // function to initialize message memory (memory has to be allocated)
  BlockTask_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t BlockTask_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &BlockTask_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::msg::BlockTask>()
{
  return &::cobot1_interfaces::msg::rosidl_typesupport_introspection_cpp::BlockTask_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, msg, BlockTask)() {
  return &::cobot1_interfaces::msg::rosidl_typesupport_introspection_cpp::BlockTask_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
