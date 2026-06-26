// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/srv/detail/sequence_plan__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cobot1_interfaces/srv/detail/sequence_plan__struct.h"
#include "cobot1_interfaces/srv/detail/sequence_plan__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // colors
#include "rosidl_runtime_c/string_functions.h"  // colors

// forward declare type support functions


using _SequencePlan_Request__ros_msg_type = cobot1_interfaces__srv__SequencePlan_Request;

static bool _SequencePlan_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SequencePlan_Request__ros_msg_type * ros_message = static_cast<const _SequencePlan_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: colors
  {
    size_t size = ros_message->colors.size;
    auto array_ptr = ros_message->colors.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: grid_width
  {
    cdr << ros_message->grid_width;
  }

  // Field name: grid_height
  {
    cdr << ros_message->grid_height;
  }

  return true;
}

static bool _SequencePlan_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SequencePlan_Request__ros_msg_type * ros_message = static_cast<_SequencePlan_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: colors
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->colors.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->colors);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->colors, size)) {
      fprintf(stderr, "failed to create array for field 'colors'");
      return false;
    }
    auto array_ptr = ros_message->colors.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'colors'\n");
        return false;
      }
    }
  }

  // Field name: grid_width
  {
    cdr >> ros_message->grid_width;
  }

  // Field name: grid_height
  {
    cdr >> ros_message->grid_height;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t get_serialized_size_cobot1_interfaces__srv__SequencePlan_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SequencePlan_Request__ros_msg_type * ros_message = static_cast<const _SequencePlan_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name colors
  {
    size_t array_size = ros_message->colors.size;
    auto array_ptr = ros_message->colors.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name grid_width
  {
    size_t item_size = sizeof(ros_message->grid_width);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name grid_height
  {
    size_t item_size = sizeof(ros_message->grid_height);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SequencePlan_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_cobot1_interfaces__srv__SequencePlan_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t max_serialized_size_cobot1_interfaces__srv__SequencePlan_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: colors
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: grid_width
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: grid_height
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = cobot1_interfaces__srv__SequencePlan_Request;
    is_plain =
      (
      offsetof(DataType, grid_height) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SequencePlan_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_cobot1_interfaces__srv__SequencePlan_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SequencePlan_Request = {
  "cobot1_interfaces::srv",
  "SequencePlan_Request",
  _SequencePlan_Request__cdr_serialize,
  _SequencePlan_Request__cdr_deserialize,
  _SequencePlan_Request__get_serialized_size,
  _SequencePlan_Request__max_serialized_size
};

static rosidl_message_type_support_t _SequencePlan_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SequencePlan_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, SequencePlan_Request)() {
  return &_SequencePlan_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__struct.h"
// already included above
// #include "cobot1_interfaces/srv/detail/sequence_plan__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "cobot1_interfaces/msg/detail/block_task__functions.h"  // tasks
// already included above
// #include "rosidl_runtime_c/string.h"  // error_message
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // error_message

// forward declare type support functions
size_t get_serialized_size_cobot1_interfaces__msg__BlockTask(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_cobot1_interfaces__msg__BlockTask(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, msg, BlockTask)();


using _SequencePlan_Response__ros_msg_type = cobot1_interfaces__srv__SequencePlan_Response;

static bool _SequencePlan_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SequencePlan_Response__ros_msg_type * ros_message = static_cast<const _SequencePlan_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: error_message
  {
    const rosidl_runtime_c__String * str = &ros_message->error_message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: tasks
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, cobot1_interfaces, msg, BlockTask
      )()->data);
    size_t size = ros_message->tasks.size;
    auto array_ptr = ros_message->tasks.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  return true;
}

static bool _SequencePlan_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SequencePlan_Response__ros_msg_type * ros_message = static_cast<_SequencePlan_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: error_message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->error_message.data) {
      rosidl_runtime_c__String__init(&ros_message->error_message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->error_message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'error_message'\n");
      return false;
    }
  }

  // Field name: tasks
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, cobot1_interfaces, msg, BlockTask
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->tasks.data) {
      cobot1_interfaces__msg__BlockTask__Sequence__fini(&ros_message->tasks);
    }
    if (!cobot1_interfaces__msg__BlockTask__Sequence__init(&ros_message->tasks, size)) {
      fprintf(stderr, "failed to create array for field 'tasks'");
      return false;
    }
    auto array_ptr = ros_message->tasks.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t get_serialized_size_cobot1_interfaces__srv__SequencePlan_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SequencePlan_Response__ros_msg_type * ros_message = static_cast<const _SequencePlan_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name error_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->error_message.size + 1);
  // field.name tasks
  {
    size_t array_size = ros_message->tasks.size;
    auto array_ptr = ros_message->tasks.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_cobot1_interfaces__msg__BlockTask(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SequencePlan_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_cobot1_interfaces__srv__SequencePlan_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t max_serialized_size_cobot1_interfaces__srv__SequencePlan_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: error_message
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: tasks
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_cobot1_interfaces__msg__BlockTask(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = cobot1_interfaces__srv__SequencePlan_Response;
    is_plain =
      (
      offsetof(DataType, tasks) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SequencePlan_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_cobot1_interfaces__srv__SequencePlan_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SequencePlan_Response = {
  "cobot1_interfaces::srv",
  "SequencePlan_Response",
  _SequencePlan_Response__cdr_serialize,
  _SequencePlan_Response__cdr_deserialize,
  _SequencePlan_Response__get_serialized_size,
  _SequencePlan_Response__max_serialized_size
};

static rosidl_message_type_support_t _SequencePlan_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SequencePlan_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, SequencePlan_Response)() {
  return &_SequencePlan_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "cobot1_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cobot1_interfaces/srv/sequence_plan.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SequencePlan__callbacks = {
  "cobot1_interfaces::srv",
  "SequencePlan",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, SequencePlan_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, SequencePlan_Response)(),
};

static rosidl_service_type_support_t SequencePlan__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &SequencePlan__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, SequencePlan)() {
  return &SequencePlan__handle;
}

#if defined(__cplusplus)
}
#endif
