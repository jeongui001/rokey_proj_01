// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot1_interfaces:srv/ProcessMosaic.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__TRAITS_HPP_
#define COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot1_interfaces/srv/detail/process_mosaic__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'input_image'
#include "sensor_msgs/msg/detail/image__traits.hpp"

namespace cobot1_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ProcessMosaic_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: input_image
  {
    out << "input_image: ";
    to_flow_style_yaml(msg.input_image, out);
    out << ", ";
  }

  // member: grid_rows
  {
    out << "grid_rows: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_rows, out);
    out << ", ";
  }

  // member: grid_cols
  {
    out << "grid_cols: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_cols, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ProcessMosaic_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: input_image
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "input_image:\n";
    to_block_style_yaml(msg.input_image, out, indentation + 2);
  }

  // member: grid_rows
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_rows: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_rows, out);
    out << "\n";
  }

  // member: grid_cols
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_cols: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_cols, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ProcessMosaic_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::srv::ProcessMosaic_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::srv::ProcessMosaic_Request & msg)
{
  return cobot1_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::srv::ProcessMosaic_Request>()
{
  return "cobot1_interfaces::srv::ProcessMosaic_Request";
}

template<>
inline const char * name<cobot1_interfaces::srv::ProcessMosaic_Request>()
{
  return "cobot1_interfaces/srv/ProcessMosaic_Request";
}

template<>
struct has_fixed_size<cobot1_interfaces::srv::ProcessMosaic_Request>
  : std::integral_constant<bool, has_fixed_size<sensor_msgs::msg::Image>::value> {};

template<>
struct has_bounded_size<cobot1_interfaces::srv::ProcessMosaic_Request>
  : std::integral_constant<bool, has_bounded_size<sensor_msgs::msg::Image>::value> {};

template<>
struct is_message<cobot1_interfaces::srv::ProcessMosaic_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace cobot1_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ProcessMosaic_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: colors
  {
    if (msg.colors.size() == 0) {
      out << "colors: []";
    } else {
      out << "colors: [";
      size_t pending_items = msg.colors.size();
      for (auto item : msg.colors) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ProcessMosaic_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: colors
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.colors.size() == 0) {
      out << "colors: []\n";
    } else {
      out << "colors:\n";
      for (auto item : msg.colors) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ProcessMosaic_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::srv::ProcessMosaic_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::srv::ProcessMosaic_Response & msg)
{
  return cobot1_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::srv::ProcessMosaic_Response>()
{
  return "cobot1_interfaces::srv::ProcessMosaic_Response";
}

template<>
inline const char * name<cobot1_interfaces::srv::ProcessMosaic_Response>()
{
  return "cobot1_interfaces/srv/ProcessMosaic_Response";
}

template<>
struct has_fixed_size<cobot1_interfaces::srv::ProcessMosaic_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::srv::ProcessMosaic_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::srv::ProcessMosaic_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<cobot1_interfaces::srv::ProcessMosaic>()
{
  return "cobot1_interfaces::srv::ProcessMosaic";
}

template<>
inline const char * name<cobot1_interfaces::srv::ProcessMosaic>()
{
  return "cobot1_interfaces/srv/ProcessMosaic";
}

template<>
struct has_fixed_size<cobot1_interfaces::srv::ProcessMosaic>
  : std::integral_constant<
    bool,
    has_fixed_size<cobot1_interfaces::srv::ProcessMosaic_Request>::value &&
    has_fixed_size<cobot1_interfaces::srv::ProcessMosaic_Response>::value
  >
{
};

template<>
struct has_bounded_size<cobot1_interfaces::srv::ProcessMosaic>
  : std::integral_constant<
    bool,
    has_bounded_size<cobot1_interfaces::srv::ProcessMosaic_Request>::value &&
    has_bounded_size<cobot1_interfaces::srv::ProcessMosaic_Response>::value
  >
{
};

template<>
struct is_service<cobot1_interfaces::srv::ProcessMosaic>
  : std::true_type
{
};

template<>
struct is_service_request<cobot1_interfaces::srv::ProcessMosaic_Request>
  : std::true_type
{
};

template<>
struct is_service_response<cobot1_interfaces::srv::ProcessMosaic_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__TRAITS_HPP_
