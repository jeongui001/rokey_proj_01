// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "cobot1_interfaces/action/detail/assembly__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_Goal_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_Goal(_init);
}

void Assembly_Goal_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_Goal *>(message_memory);
  typed_message->~Assembly_Goal();
}

size_t size_function__Assembly_Goal__tasks(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Assembly_Goal__tasks(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  return &member[index];
}

void * get_function__Assembly_Goal__tasks(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  return &member[index];
}

void fetch_function__Assembly_Goal__tasks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const cobot1_interfaces::msg::BlockTask *>(
    get_const_function__Assembly_Goal__tasks(untyped_member, index));
  auto & value = *reinterpret_cast<cobot1_interfaces::msg::BlockTask *>(untyped_value);
  value = item;
}

void assign_function__Assembly_Goal__tasks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<cobot1_interfaces::msg::BlockTask *>(
    get_function__Assembly_Goal__tasks(untyped_member, index));
  const auto & value = *reinterpret_cast<const cobot1_interfaces::msg::BlockTask *>(untyped_value);
  item = value;
}

void resize_function__Assembly_Goal__tasks(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_Goal_message_member_array[1] = {
  {
    "tasks",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<cobot1_interfaces::msg::BlockTask>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_Goal, tasks),  // bytes offset in struct
    nullptr,  // default value
    size_function__Assembly_Goal__tasks,  // size() function pointer
    get_const_function__Assembly_Goal__tasks,  // get_const(index) function pointer
    get_function__Assembly_Goal__tasks,  // get(index) function pointer
    fetch_function__Assembly_Goal__tasks,  // fetch(index, &value) function pointer
    assign_function__Assembly_Goal__tasks,  // assign(index, value) function pointer
    resize_function__Assembly_Goal__tasks  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_Goal_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_Goal",  // message name
  1,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_Goal),
  Assembly_Goal_message_member_array,  // message members
  Assembly_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_Goal_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_Goal_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_Goal_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_Goal>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_Goal_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_Goal)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_Result_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_Result(_init);
}

void Assembly_Result_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_Result *>(message_memory);
  typed_message->~Assembly_Result();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_Result_message_member_array[2] = {
  {
    "failed_step",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_Result, failed_step),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "error_message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_Result, error_message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_Result_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_Result",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_Result),
  Assembly_Result_message_member_array,  // message members
  Assembly_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_Result_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_Result_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_Result_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_Result>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_Result_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_Result)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_Feedback_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_Feedback(_init);
}

void Assembly_Feedback_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_Feedback *>(message_memory);
  typed_message->~Assembly_Feedback();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_Feedback_message_member_array[1] = {
  {
    "current_index",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_Feedback, current_index),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_Feedback_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_Feedback",  // message name
  1,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_Feedback),
  Assembly_Feedback_message_member_array,  // message members
  Assembly_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_Feedback_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_Feedback>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_Feedback_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_Feedback)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_SendGoal_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_SendGoal_Request(_init);
}

void Assembly_SendGoal_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_SendGoal_Request *>(message_memory);
  typed_message->~Assembly_SendGoal_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_SendGoal_Request, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "goal",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<cobot1_interfaces::action::Assembly_Goal>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_SendGoal_Request, goal),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_SendGoal_Request_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_SendGoal_Request),
  Assembly_SendGoal_Request_message_member_array,  // message members
  Assembly_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal_Request>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_SendGoal_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_SendGoal_Request)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_SendGoal_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_SendGoal_Response(_init);
}

void Assembly_SendGoal_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_SendGoal_Response *>(message_memory);
  typed_message->~Assembly_SendGoal_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_SendGoal_Response, accepted),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_SendGoal_Response, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_SendGoal_Response_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_SendGoal_Response),
  Assembly_SendGoal_Response_message_member_array,  // message members
  Assembly_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal_Response>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_SendGoal_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_SendGoal_Response)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers Assembly_SendGoal_service_members = {
  "cobot1_interfaces::action",  // service namespace
  "Assembly_SendGoal",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t Assembly_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_SendGoal_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::cobot1_interfaces::action::Assembly_SendGoal_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::cobot1_interfaces::action::Assembly_SendGoal_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_SendGoal)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_GetResult_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_GetResult_Request(_init);
}

void Assembly_GetResult_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_GetResult_Request *>(message_memory);
  typed_message->~Assembly_GetResult_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_GetResult_Request, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_GetResult_Request_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_GetResult_Request),
  Assembly_GetResult_Request_message_member_array,  // message members
  Assembly_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_GetResult_Request>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_GetResult_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_GetResult_Request)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_GetResult_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_GetResult_Response(_init);
}

void Assembly_GetResult_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_GetResult_Response *>(message_memory);
  typed_message->~Assembly_GetResult_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_GetResult_Response, status),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "result",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<cobot1_interfaces::action::Assembly_Result>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_GetResult_Response, result),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_GetResult_Response_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_GetResult_Response),
  Assembly_GetResult_Response_message_member_array,  // message members
  Assembly_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_GetResult_Response>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_GetResult_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_GetResult_Response)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers Assembly_GetResult_service_members = {
  "cobot1_interfaces::action",  // service namespace
  "Assembly_GetResult",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<cobot1_interfaces::action::Assembly_GetResult>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t Assembly_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_GetResult_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cobot1_interfaces::action::Assembly_GetResult>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_GetResult_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::cobot1_interfaces::action::Assembly_GetResult_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::cobot1_interfaces::action::Assembly_GetResult_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_GetResult)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<cobot1_interfaces::action::Assembly_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_introspection_cpp
{

void Assembly_FeedbackMessage_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::action::Assembly_FeedbackMessage(_init);
}

void Assembly_FeedbackMessage_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::action::Assembly_FeedbackMessage *>(message_memory);
  typed_message->~Assembly_FeedbackMessage();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Assembly_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_FeedbackMessage, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "feedback",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<cobot1_interfaces::action::Assembly_Feedback>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::action::Assembly_FeedbackMessage, feedback),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Assembly_FeedbackMessage_message_members = {
  "cobot1_interfaces::action",  // message namespace
  "Assembly_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces::action::Assembly_FeedbackMessage),
  Assembly_FeedbackMessage_message_member_array,  // message members
  Assembly_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  Assembly_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Assembly_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Assembly_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace action

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_FeedbackMessage>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_FeedbackMessage_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_FeedbackMessage)() {
  return &::cobot1_interfaces::action::rosidl_typesupport_introspection_cpp::Assembly_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
