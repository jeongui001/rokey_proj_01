// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "cobot1_interfaces/action/detail/assembly__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_Goal_type_support_ids_t;

static const _Assembly_Goal_type_support_ids_t _Assembly_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_Goal_type_support_symbol_names_t _Assembly_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_Goal)),
  }
};

typedef struct _Assembly_Goal_type_support_data_t
{
  void * data[2];
} _Assembly_Goal_type_support_data_t;

static _Assembly_Goal_type_support_data_t _Assembly_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_Goal_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_Goal_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_Goal_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_Goal>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_Goal)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_Goal>();
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
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_Result_type_support_ids_t;

static const _Assembly_Result_type_support_ids_t _Assembly_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_Result_type_support_symbol_names_t _Assembly_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_Result)),
  }
};

typedef struct _Assembly_Result_type_support_data_t
{
  void * data[2];
} _Assembly_Result_type_support_data_t;

static _Assembly_Result_type_support_data_t _Assembly_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_Result_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_Result_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_Result_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_Result_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_Result_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_Result>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_Result)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_Result>();
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
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_Feedback_type_support_ids_t;

static const _Assembly_Feedback_type_support_ids_t _Assembly_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_Feedback_type_support_symbol_names_t _Assembly_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_Feedback)),
  }
};

typedef struct _Assembly_Feedback_type_support_data_t
{
  void * data[2];
} _Assembly_Feedback_type_support_data_t;

static _Assembly_Feedback_type_support_data_t _Assembly_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_Feedback_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_Feedback_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_Feedback>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_Feedback)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_Feedback>();
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
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_SendGoal_Request_type_support_ids_t;

static const _Assembly_SendGoal_Request_type_support_ids_t _Assembly_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_SendGoal_Request_type_support_symbol_names_t _Assembly_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_SendGoal_Request)),
  }
};

typedef struct _Assembly_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _Assembly_SendGoal_Request_type_support_data_t;

static _Assembly_SendGoal_Request_type_support_data_t _Assembly_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_SendGoal_Request_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_SendGoal_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal_Request>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_SendGoal_Request)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal_Request>();
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
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_SendGoal_Response_type_support_ids_t;

static const _Assembly_SendGoal_Response_type_support_ids_t _Assembly_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_SendGoal_Response_type_support_symbol_names_t _Assembly_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_SendGoal_Response)),
  }
};

typedef struct _Assembly_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _Assembly_SendGoal_Response_type_support_data_t;

static _Assembly_SendGoal_Response_type_support_data_t _Assembly_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_SendGoal_Response_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_SendGoal_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal_Response>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_SendGoal_Response)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_SendGoal_type_support_ids_t;

static const _Assembly_SendGoal_type_support_ids_t _Assembly_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_SendGoal_type_support_symbol_names_t _Assembly_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_SendGoal)),
  }
};

typedef struct _Assembly_SendGoal_type_support_data_t
{
  void * data[2];
} _Assembly_SendGoal_type_support_data_t;

static _Assembly_SendGoal_type_support_data_t _Assembly_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_SendGoal_service_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_Assembly_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_Assembly_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Assembly_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_SendGoal_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<cobot1_interfaces::action::Assembly_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_GetResult_Request_type_support_ids_t;

static const _Assembly_GetResult_Request_type_support_ids_t _Assembly_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_GetResult_Request_type_support_symbol_names_t _Assembly_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_GetResult_Request)),
  }
};

typedef struct _Assembly_GetResult_Request_type_support_data_t
{
  void * data[2];
} _Assembly_GetResult_Request_type_support_data_t;

static _Assembly_GetResult_Request_type_support_data_t _Assembly_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_GetResult_Request_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_GetResult_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_GetResult_Request>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_GetResult_Request)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_GetResult_Request>();
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
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_GetResult_Response_type_support_ids_t;

static const _Assembly_GetResult_Response_type_support_ids_t _Assembly_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_GetResult_Response_type_support_symbol_names_t _Assembly_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_GetResult_Response)),
  }
};

typedef struct _Assembly_GetResult_Response_type_support_data_t
{
  void * data[2];
} _Assembly_GetResult_Response_type_support_data_t;

static _Assembly_GetResult_Response_type_support_data_t _Assembly_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_GetResult_Response_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_GetResult_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_GetResult_Response>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_GetResult_Response)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_GetResult_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_GetResult_type_support_ids_t;

static const _Assembly_GetResult_type_support_ids_t _Assembly_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_GetResult_type_support_symbol_names_t _Assembly_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_GetResult)),
  }
};

typedef struct _Assembly_GetResult_type_support_data_t
{
  void * data[2];
} _Assembly_GetResult_type_support_data_t;

static _Assembly_GetResult_type_support_data_t _Assembly_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_GetResult_service_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_Assembly_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_Assembly_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Assembly_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_GetResult_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cobot1_interfaces::action::Assembly_GetResult>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<cobot1_interfaces::action::Assembly_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _Assembly_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Assembly_FeedbackMessage_type_support_ids_t;

static const _Assembly_FeedbackMessage_type_support_ids_t _Assembly_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Assembly_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Assembly_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Assembly_FeedbackMessage_type_support_symbol_names_t _Assembly_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, action, Assembly_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cobot1_interfaces, action, Assembly_FeedbackMessage)),
  }
};

typedef struct _Assembly_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _Assembly_FeedbackMessage_type_support_data_t;

static _Assembly_FeedbackMessage_type_support_data_t _Assembly_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Assembly_FeedbackMessage_message_typesupport_map = {
  2,
  "cobot1_interfaces",
  &_Assembly_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_Assembly_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_Assembly_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Assembly_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Assembly_FeedbackMessage_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::action::Assembly_FeedbackMessage>()
{
  return &::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly_FeedbackMessage)() {
  return get_message_type_support_handle<cobot1_interfaces::action::Assembly_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_typesupport_cpp/action_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace cobot1_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

static rosidl_action_type_support_t Assembly_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<cobot1_interfaces::action::Assembly>()
{
  using ::cobot1_interfaces::action::rosidl_typesupport_cpp::Assembly_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  Assembly_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::cobot1_interfaces::action::Assembly::Impl::SendGoalService>();
  Assembly_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::cobot1_interfaces::action::Assembly::Impl::GetResultService>();
  Assembly_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::cobot1_interfaces::action::Assembly::Impl::CancelGoalService>();
  Assembly_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::cobot1_interfaces::action::Assembly::Impl::FeedbackMessage>();
  Assembly_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::cobot1_interfaces::action::Assembly::Impl::GoalStatusMessage>();
  return &Assembly_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, cobot1_interfaces, action, Assembly)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<cobot1_interfaces::action::Assembly>();
}

#ifdef __cplusplus
}
#endif
