// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace cobot1_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SequencePlan_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SequencePlan_Request_type_support_ids_t;

static const _SequencePlan_Request_type_support_ids_t _SequencePlan_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SequencePlan_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SequencePlan_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SequencePlan_Request_type_support_symbol_names_t _SequencePlan_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, srv, SequencePlan_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, srv, SequencePlan_Request)),
  }
};

typedef struct _SequencePlan_Request_type_support_data_t
{
  void * data[2];
} _SequencePlan_Request_type_support_data_t;

static _SequencePlan_Request_type_support_data_t _SequencePlan_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SequencePlan_Request_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_SequencePlan_Request_message_typesupport_ids.typesupport_identifier[0],
  &_SequencePlan_Request_message_typesupport_symbol_names.symbol_name[0],
  &_SequencePlan_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SequencePlan_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SequencePlan_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::srv::SequencePlan_Request>()
{
  return &::cobot1_interfaces::srv::rosidl_typesupport_cpp::SequencePlan_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, srv, SequencePlan_Request)() {
  return get_message_type_support_handle<cobot1_interfaces::srv::SequencePlan_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cobot1_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SequencePlan_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SequencePlan_Response_type_support_ids_t;

static const _SequencePlan_Response_type_support_ids_t _SequencePlan_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SequencePlan_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SequencePlan_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SequencePlan_Response_type_support_symbol_names_t _SequencePlan_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, srv, SequencePlan_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, srv, SequencePlan_Response)),
  }
};

typedef struct _SequencePlan_Response_type_support_data_t
{
  void * data[2];
} _SequencePlan_Response_type_support_data_t;

static _SequencePlan_Response_type_support_data_t _SequencePlan_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SequencePlan_Response_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_SequencePlan_Response_message_typesupport_ids.typesupport_identifier[0],
  &_SequencePlan_Response_message_typesupport_symbol_names.symbol_name[0],
  &_SequencePlan_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SequencePlan_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SequencePlan_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::srv::SequencePlan_Response>()
{
  return &::cobot1_interfaces::srv::rosidl_typesupport_cpp::SequencePlan_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, srv, SequencePlan_Response)() {
  return get_message_type_support_handle<cobot1_interfaces::srv::SequencePlan_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cobot1_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SequencePlan_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SequencePlan_type_support_ids_t;

static const _SequencePlan_type_support_ids_t _SequencePlan_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SequencePlan_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SequencePlan_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SequencePlan_type_support_symbol_names_t _SequencePlan_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, srv, SequencePlan)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, srv, SequencePlan)),
  }
};

typedef struct _SequencePlan_type_support_data_t
{
  void * data[2];
} _SequencePlan_type_support_data_t;

static _SequencePlan_type_support_data_t _SequencePlan_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SequencePlan_service_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_SequencePlan_service_typesupport_ids.typesupport_identifier[0],
  &_SequencePlan_service_typesupport_symbol_names.symbol_name[0],
  &_SequencePlan_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t SequencePlan_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SequencePlan_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cobot1_interfaces::srv::SequencePlan>()
{
  return &::cobot1_interfaces::srv::rosidl_typesupport_cpp::SequencePlan_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, srv, SequencePlan)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<cobot1_interfaces::srv::SequencePlan>();
}

#ifdef __cplusplus
}
#endif
