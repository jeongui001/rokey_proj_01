// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from cobot1_interfaces:srv/ProcessMosaic.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/srv/detail/process_mosaic__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "cobot1_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cobot1_interfaces/srv/detail/process_mosaic__struct.h"
#include "cobot1_interfaces/srv/detail/process_mosaic__functions.h"
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

#include "sensor_msgs/msg/detail/image__functions.h"  // input_image

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_cobot1_interfaces
size_t get_serialized_size_sensor_msgs__msg__Image(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_cobot1_interfaces
size_t max_serialized_size_sensor_msgs__msg__Image(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_cobot1_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Image)();


using _ProcessMosaic_Request__ros_msg_type = cobot1_interfaces__srv__ProcessMosaic_Request;

static bool _ProcessMosaic_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ProcessMosaic_Request__ros_msg_type * ros_message = static_cast<const _ProcessMosaic_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: input_image
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Image
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->input_image, cdr))
    {
      return false;
    }
  }

  // Field name: grid_rows
  {
    cdr << ros_message->grid_rows;
  }

  // Field name: grid_cols
  {
    cdr << ros_message->grid_cols;
  }

  return true;
}

static bool _ProcessMosaic_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ProcessMosaic_Request__ros_msg_type * ros_message = static_cast<_ProcessMosaic_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: input_image
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Image
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->input_image))
    {
      return false;
    }
  }

  // Field name: grid_rows
  {
    cdr >> ros_message->grid_rows;
  }

  // Field name: grid_cols
  {
    cdr >> ros_message->grid_cols;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t get_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ProcessMosaic_Request__ros_msg_type * ros_message = static_cast<const _ProcessMosaic_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name input_image

  current_alignment += get_serialized_size_sensor_msgs__msg__Image(
    &(ros_message->input_image), current_alignment);
  // field.name grid_rows
  {
    size_t item_size = sizeof(ros_message->grid_rows);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name grid_cols
  {
    size_t item_size = sizeof(ros_message->grid_cols);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ProcessMosaic_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t max_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Request(
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

  // member: input_image
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_sensor_msgs__msg__Image(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: grid_rows
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: grid_cols
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
    using DataType = cobot1_interfaces__srv__ProcessMosaic_Request;
    is_plain =
      (
      offsetof(DataType, grid_cols) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ProcessMosaic_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ProcessMosaic_Request = {
  "cobot1_interfaces::srv",
  "ProcessMosaic_Request",
  _ProcessMosaic_Request__cdr_serialize,
  _ProcessMosaic_Request__cdr_deserialize,
  _ProcessMosaic_Request__get_serialized_size,
  _ProcessMosaic_Request__max_serialized_size
};

static rosidl_message_type_support_t _ProcessMosaic_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ProcessMosaic_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, ProcessMosaic_Request)() {
  return &_ProcessMosaic_Request__type_support;
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
// #include "cobot1_interfaces/srv/detail/process_mosaic__struct.h"
// already included above
// #include "cobot1_interfaces/srv/detail/process_mosaic__functions.h"
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

#include "rosidl_runtime_c/string.h"  // colors, message
#include "rosidl_runtime_c/string_functions.h"  // colors, message

// forward declare type support functions


using _ProcessMosaic_Response__ros_msg_type = cobot1_interfaces__srv__ProcessMosaic_Response;

static bool _ProcessMosaic_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ProcessMosaic_Response__ros_msg_type * ros_message = static_cast<const _ProcessMosaic_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    cdr << (ros_message->success ? true : false);
  }

  // Field name: message
  {
    const rosidl_runtime_c__String * str = &ros_message->message;
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

static bool _ProcessMosaic_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ProcessMosaic_Response__ros_msg_type * ros_message = static_cast<_ProcessMosaic_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->success = tmp ? true : false;
  }

  // Field name: message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->message.data) {
      rosidl_runtime_c__String__init(&ros_message->message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'message'\n");
      return false;
    }
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
size_t get_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ProcessMosaic_Response__ros_msg_type * ros_message = static_cast<const _ProcessMosaic_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name success
  {
    size_t item_size = sizeof(ros_message->success);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);
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

static uint32_t _ProcessMosaic_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot1_interfaces
size_t max_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Response(
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

  // member: success
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: message
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
    using DataType = cobot1_interfaces__srv__ProcessMosaic_Response;
    is_plain =
      (
      offsetof(DataType, colors) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ProcessMosaic_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_cobot1_interfaces__srv__ProcessMosaic_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ProcessMosaic_Response = {
  "cobot1_interfaces::srv",
  "ProcessMosaic_Response",
  _ProcessMosaic_Response__cdr_serialize,
  _ProcessMosaic_Response__cdr_deserialize,
  _ProcessMosaic_Response__get_serialized_size,
  _ProcessMosaic_Response__max_serialized_size
};

static rosidl_message_type_support_t _ProcessMosaic_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ProcessMosaic_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, ProcessMosaic_Response)() {
  return &_ProcessMosaic_Response__type_support;
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
#include "cobot1_interfaces/srv/process_mosaic.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t ProcessMosaic__callbacks = {
  "cobot1_interfaces::srv",
  "ProcessMosaic",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, ProcessMosaic_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, ProcessMosaic_Response)(),
};

static rosidl_service_type_support_t ProcessMosaic__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &ProcessMosaic__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot1_interfaces, srv, ProcessMosaic)() {
  return &ProcessMosaic__handle;
}

#if defined(__cplusplus)
}
#endif
