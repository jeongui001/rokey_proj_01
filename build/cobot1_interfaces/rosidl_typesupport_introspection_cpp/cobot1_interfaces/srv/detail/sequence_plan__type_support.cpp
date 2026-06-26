// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cobot1_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SequencePlan_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::srv::SequencePlan_Request(_init);
}

void SequencePlan_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::srv::SequencePlan_Request *>(message_memory);
  typed_message->~SequencePlan_Request();
}

size_t size_function__SequencePlan_Request__colors(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SequencePlan_Request__colors(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__SequencePlan_Request__colors(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__SequencePlan_Request__colors(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__SequencePlan_Request__colors(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__SequencePlan_Request__colors(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__SequencePlan_Request__colors(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__SequencePlan_Request__colors(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SequencePlan_Request_message_member_array[3] = {
  {
    "colors",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::srv::SequencePlan_Request, colors),  // bytes offset in struct
    nullptr,  // default value
    size_function__SequencePlan_Request__colors,  // size() function pointer
    get_const_function__SequencePlan_Request__colors,  // get_const(index) function pointer
    get_function__SequencePlan_Request__colors,  // get(index) function pointer
    fetch_function__SequencePlan_Request__colors,  // fetch(index, &value) function pointer
    assign_function__SequencePlan_Request__colors,  // assign(index, value) function pointer
    resize_function__SequencePlan_Request__colors  // resize(index) function pointer
  },
  {
    "grid_width",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::srv::SequencePlan_Request, grid_width),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "grid_height",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::srv::SequencePlan_Request, grid_height),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SequencePlan_Request_message_members = {
  "cobot1_interfaces::srv",  // message namespace
  "SequencePlan_Request",  // message name
  3,  // number of fields
  sizeof(cobot1_interfaces::srv::SequencePlan_Request),
  SequencePlan_Request_message_member_array,  // message members
  SequencePlan_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  SequencePlan_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SequencePlan_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SequencePlan_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::srv::SequencePlan_Request>()
{
  return &::cobot1_interfaces::srv::rosidl_typesupport_introspection_cpp::SequencePlan_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, srv, SequencePlan_Request)() {
  return &::cobot1_interfaces::srv::rosidl_typesupport_introspection_cpp::SequencePlan_Request_message_type_support_handle;
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
// #include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
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

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SequencePlan_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cobot1_interfaces::srv::SequencePlan_Response(_init);
}

void SequencePlan_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cobot1_interfaces::srv::SequencePlan_Response *>(message_memory);
  typed_message->~SequencePlan_Response();
}

size_t size_function__SequencePlan_Response__tasks(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SequencePlan_Response__tasks(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  return &member[index];
}

void * get_function__SequencePlan_Response__tasks(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  return &member[index];
}

void fetch_function__SequencePlan_Response__tasks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const cobot1_interfaces::msg::BlockTask *>(
    get_const_function__SequencePlan_Response__tasks(untyped_member, index));
  auto & value = *reinterpret_cast<cobot1_interfaces::msg::BlockTask *>(untyped_value);
  value = item;
}

void assign_function__SequencePlan_Response__tasks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<cobot1_interfaces::msg::BlockTask *>(
    get_function__SequencePlan_Response__tasks(untyped_member, index));
  const auto & value = *reinterpret_cast<const cobot1_interfaces::msg::BlockTask *>(untyped_value);
  item = value;
}

void resize_function__SequencePlan_Response__tasks(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<cobot1_interfaces::msg::BlockTask> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SequencePlan_Response_message_member_array[2] = {
  {
    "error_message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::srv::SequencePlan_Response, error_message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "tasks",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<cobot1_interfaces::msg::BlockTask>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces::srv::SequencePlan_Response, tasks),  // bytes offset in struct
    nullptr,  // default value
    size_function__SequencePlan_Response__tasks,  // size() function pointer
    get_const_function__SequencePlan_Response__tasks,  // get_const(index) function pointer
    get_function__SequencePlan_Response__tasks,  // get(index) function pointer
    fetch_function__SequencePlan_Response__tasks,  // fetch(index, &value) function pointer
    assign_function__SequencePlan_Response__tasks,  // assign(index, value) function pointer
    resize_function__SequencePlan_Response__tasks  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SequencePlan_Response_message_members = {
  "cobot1_interfaces::srv",  // message namespace
  "SequencePlan_Response",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces::srv::SequencePlan_Response),
  SequencePlan_Response_message_member_array,  // message members
  SequencePlan_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  SequencePlan_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SequencePlan_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SequencePlan_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::srv::SequencePlan_Response>()
{
  return &::cobot1_interfaces::srv::rosidl_typesupport_introspection_cpp::SequencePlan_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, srv, SequencePlan_Response)() {
  return &::cobot1_interfaces::srv::rosidl_typesupport_introspection_cpp::SequencePlan_Response_message_type_support_handle;
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
// #include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace cobot1_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers SequencePlan_service_members = {
  "cobot1_interfaces::srv",  // service namespace
  "SequencePlan",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<cobot1_interfaces::srv::SequencePlan>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t SequencePlan_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SequencePlan_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace cobot1_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cobot1_interfaces::srv::SequencePlan>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::cobot1_interfaces::srv::rosidl_typesupport_introspection_cpp::SequencePlan_service_type_support_handle;
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
        ::cobot1_interfaces::srv::SequencePlan_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::cobot1_interfaces::srv::SequencePlan_Response
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
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, srv, SequencePlan)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<cobot1_interfaces::srv::SequencePlan>();
}

#ifdef __cplusplus
}
#endif
