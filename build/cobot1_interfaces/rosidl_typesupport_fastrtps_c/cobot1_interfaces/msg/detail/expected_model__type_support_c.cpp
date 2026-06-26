// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/msg/detail/expected_model__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cobot1_interfaces/msg/detail/expected_model__struct.h"
#include "cobot1_interfaces/msg/detail/expected_model__functions.h"
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


using _ExpectedModel__ros_msg_type = cobot1_interfaces__msg__ExpectedModel;

static bool _ExpectedModel__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ExpectedModel__ros_msg_type * ros_message = static_cast<const _ExpectedModel__ros_msg_type *>(untyped_ros_message);
  // Field name: grid_size
  {
    cdr << ros_message->grid_size;
  }

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

  return true;
}

static bool _ExpectedModel__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ExpectedModel__ros_msg_type * ros_message = static_cast<_ExpectedModel__ros_msg_type *>(untyped_ros_message);
  // Field name: grid_size
  {
    cdr >> ros_message->grid_size;
  }

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

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t get_serialized_size_cobot1_interfaces__msg__ExpectedModel(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ExpectedModel__ros_msg_type * ros_message = static_cast<const _ExpectedModel__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name grid_size
  {
    size_t item_size = sizeof(ros_message->grid_size);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
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

  return current_alignment - initial_alignment;
}

static uint32_t _ExpectedModel__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_cobot1_interfaces__msg__ExpectedModel(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t max_serialized_size_cobot1_interfaces__msg__ExpectedModel(
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

  // member: grid_size
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
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

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = cobot1_interfaces__msg__ExpectedModel;
    is_plain =
      (
      offsetof(DataType, colors) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ExpectedModel__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_cobot1_interfaces__msg__ExpectedModel(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ExpectedModel = {
  "cobot1_interfaces::msg",
  "ExpectedModel",
  _ExpectedModel__cdr_serialize,
  _ExpectedModel__cdr_deserialize,
  _ExpectedModel__get_serialized_size,
  _ExpectedModel__max_serialized_size
};

static rosidl_message_type_support_t _ExpectedModel__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ExpectedModel,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, msg, ExpectedModel)() {
  return &_ExpectedModel__type_support;
}

#if defined(__cplusplus)
}
#endif
