// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/msg/detail/expected_model__rosidl_typesupport_fastrtps_cpp.hpp"
#include "cobot1_interfaces/msg/detail/expected_model__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace cobot1_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_cobot1_interfaces
cdr_serialize(
  const cobot1_interfaces::msg::ExpectedModel & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: grid_size
  cdr << ros_message.grid_size;
  // Member: colors
  {
    cdr << ros_message.colors;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_cobot1_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  cobot1_interfaces::msg::ExpectedModel & ros_message)
{
  // Member: grid_size
  cdr >> ros_message.grid_size;

  // Member: colors
  {
    cdr >> ros_message.colors;
  }

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_cobot1_interfaces
get_serialized_size(
  const cobot1_interfaces::msg::ExpectedModel & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: grid_size
  {
    size_t item_size = sizeof(ros_message.grid_size);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: colors
  {
    size_t array_size = ros_message.colors.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.colors[index].size() + 1);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_cobot1_interfaces
max_serialized_size_ExpectedModel(
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


  // Member: grid_size
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: colors
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
    using DataType = cobot1_interfaces::msg::ExpectedModel;
    is_plain =
      (
      offsetof(DataType, colors) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ExpectedModel__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const cobot1_interfaces::msg::ExpectedModel *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ExpectedModel__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<cobot1_interfaces::msg::ExpectedModel *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ExpectedModel__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const cobot1_interfaces::msg::ExpectedModel *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ExpectedModel__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ExpectedModel(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ExpectedModel__callbacks = {
  "cobot1_interfaces::msg",
  "ExpectedModel",
  _ExpectedModel__cdr_serialize,
  _ExpectedModel__cdr_deserialize,
  _ExpectedModel__get_serialized_size,
  _ExpectedModel__max_serialized_size
};

static rosidl_message_type_support_t _ExpectedModel__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ExpectedModel__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace cobot1_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_cobot1_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<cobot1_interfaces::msg::ExpectedModel>()
{
  return &cobot1_interfaces::msg::typesupport_fastrtps_cpp::_ExpectedModel__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cobot1_interfaces, msg, ExpectedModel)() {
  return &cobot1_interfaces::msg::typesupport_fastrtps_cpp::_ExpectedModel__handle;
}

#ifdef __cplusplus
}
#endif
