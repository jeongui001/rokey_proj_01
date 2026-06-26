// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot1_interfaces/srv/detail/sequence_plan__rosidl_typesupport_introspection_c.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot1_interfaces/srv/detail/sequence_plan__functions.h"
#include "cobot1_interfaces/srv/detail/sequence_plan__struct.h"


// Include directives for member types
// Member `colors`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__srv__SequencePlan_Request__init(message_memory);
}

void cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_fini_function(void * message_memory)
{
  cobot1_interfaces__srv__SequencePlan_Request__fini(message_memory);
}

size_t cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__size_function__SequencePlan_Request__colors(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__get_const_function__SequencePlan_Request__colors(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__get_function__SequencePlan_Request__colors(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__fetch_function__SequencePlan_Request__colors(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__get_const_function__SequencePlan_Request__colors(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__assign_function__SequencePlan_Request__colors(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__get_function__SequencePlan_Request__colors(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__resize_function__SequencePlan_Request__colors(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_member_array[3] = {
  {
    "colors",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__srv__SequencePlan_Request, colors),  // bytes offset in struct
    NULL,  // default value
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__size_function__SequencePlan_Request__colors,  // size() function pointer
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__get_const_function__SequencePlan_Request__colors,  // get_const(index) function pointer
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__get_function__SequencePlan_Request__colors,  // get(index) function pointer
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__fetch_function__SequencePlan_Request__colors,  // fetch(index, &value) function pointer
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__assign_function__SequencePlan_Request__colors,  // assign(index, value) function pointer
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__resize_function__SequencePlan_Request__colors  // resize(index) function pointer
  },
  {
    "grid_width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__srv__SequencePlan_Request, grid_width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grid_height",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__srv__SequencePlan_Request, grid_height),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_members = {
  "cobot1_interfaces__srv",  // message namespace
  "SequencePlan_Request",  // message name
  3,  // number of fields
  sizeof(cobot1_interfaces__srv__SequencePlan_Request),
  cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_member_array,  // message members
  cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_type_support_handle = {
  0,
  &cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan_Request)() {
  if (!cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__srv__SequencePlan_Request__rosidl_typesupport_introspection_c__SequencePlan_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__functions.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__struct.h"


// Include directives for member types
// Member `error_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `tasks`
#include "cobot1_interfaces/msg/block_task.h"
// Member `tasks`
#include "cobot1_interfaces/msg/detail/block_task__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot1_interfaces__srv__SequencePlan_Response__init(message_memory);
}

void cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_fini_function(void * message_memory)
{
  cobot1_interfaces__srv__SequencePlan_Response__fini(message_memory);
}

size_t cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__size_function__SequencePlan_Response__tasks(
  const void * untyped_member)
{
  const cobot1_interfaces__msg__BlockTask__Sequence * member =
    (const cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__get_const_function__SequencePlan_Response__tasks(
  const void * untyped_member, size_t index)
{
  const cobot1_interfaces__msg__BlockTask__Sequence * member =
    (const cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__get_function__SequencePlan_Response__tasks(
  void * untyped_member, size_t index)
{
  cobot1_interfaces__msg__BlockTask__Sequence * member =
    (cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__fetch_function__SequencePlan_Response__tasks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cobot1_interfaces__msg__BlockTask * item =
    ((const cobot1_interfaces__msg__BlockTask *)
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__get_const_function__SequencePlan_Response__tasks(untyped_member, index));
  cobot1_interfaces__msg__BlockTask * value =
    (cobot1_interfaces__msg__BlockTask *)(untyped_value);
  *value = *item;
}

void cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__assign_function__SequencePlan_Response__tasks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cobot1_interfaces__msg__BlockTask * item =
    ((cobot1_interfaces__msg__BlockTask *)
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__get_function__SequencePlan_Response__tasks(untyped_member, index));
  const cobot1_interfaces__msg__BlockTask * value =
    (const cobot1_interfaces__msg__BlockTask *)(untyped_value);
  *item = *value;
}

bool cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__resize_function__SequencePlan_Response__tasks(
  void * untyped_member, size_t size)
{
  cobot1_interfaces__msg__BlockTask__Sequence * member =
    (cobot1_interfaces__msg__BlockTask__Sequence *)(untyped_member);
  cobot1_interfaces__msg__BlockTask__Sequence__fini(member);
  return cobot1_interfaces__msg__BlockTask__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_member_array[2] = {
  {
    "error_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__srv__SequencePlan_Response, error_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tasks",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot1_interfaces__srv__SequencePlan_Response, tasks),  // bytes offset in struct
    NULL,  // default value
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__size_function__SequencePlan_Response__tasks,  // size() function pointer
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__get_const_function__SequencePlan_Response__tasks,  // get_const(index) function pointer
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__get_function__SequencePlan_Response__tasks,  // get(index) function pointer
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__fetch_function__SequencePlan_Response__tasks,  // fetch(index, &value) function pointer
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__assign_function__SequencePlan_Response__tasks,  // assign(index, value) function pointer
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__resize_function__SequencePlan_Response__tasks  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_members = {
  "cobot1_interfaces__srv",  // message namespace
  "SequencePlan_Response",  // message name
  2,  // number of fields
  sizeof(cobot1_interfaces__srv__SequencePlan_Response),
  cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_member_array,  // message members
  cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_type_support_handle = {
  0,
  &cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan_Response)() {
  cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, msg, BlockTask)();
  if (!cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot1_interfaces__srv__SequencePlan_Response__rosidl_typesupport_introspection_c__SequencePlan_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_members = {
  "cobot1_interfaces__srv",  // service namespace
  "SequencePlan",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_Request_message_type_support_handle,
  NULL  // response message
  // cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_Response_message_type_support_handle
};

static rosidl_service_type_support_t cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_type_support_handle = {
  0,
  &cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot1_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan)() {
  if (!cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_type_support_handle.typesupport_identifier) {
    cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot1_interfaces, srv, SequencePlan_Response)()->data;
  }

  return &cobot1_interfaces__srv__detail__sequence_plan__rosidl_typesupport_introspection_c__SequencePlan_service_type_support_handle;
}
