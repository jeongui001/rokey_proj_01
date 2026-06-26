// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot1_interfaces:msg/WebcamError.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__TRAITS_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot1_interfaces/msg/detail/webcam_error__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cobot1_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const WebcamError & msg,
  std::ostream & out)
{
  out << "{";
  // member: step
  {
    out << "step: ";
    rosidl_generator_traits::value_to_yaml(msg.step, out);
    out << ", ";
  }

  // member: row
  {
    out << "row: ";
    rosidl_generator_traits::value_to_yaml(msg.row, out);
    out << ", ";
  }

  // member: col
  {
    out << "col: ";
    rosidl_generator_traits::value_to_yaml(msg.col, out);
    out << ", ";
  }

  // member: expected_color
  {
    out << "expected_color: ";
    rosidl_generator_traits::value_to_yaml(msg.expected_color, out);
    out << ", ";
  }

  // member: detected_color
  {
    out << "detected_color: ";
    rosidl_generator_traits::value_to_yaml(msg.detected_color, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WebcamError & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: step
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "step: ";
    rosidl_generator_traits::value_to_yaml(msg.step, out);
    out << "\n";
  }

  // member: row
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "row: ";
    rosidl_generator_traits::value_to_yaml(msg.row, out);
    out << "\n";
  }

  // member: col
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "col: ";
    rosidl_generator_traits::value_to_yaml(msg.col, out);
    out << "\n";
  }

  // member: expected_color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "expected_color: ";
    rosidl_generator_traits::value_to_yaml(msg.expected_color, out);
    out << "\n";
  }

  // member: detected_color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detected_color: ";
    rosidl_generator_traits::value_to_yaml(msg.detected_color, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WebcamError & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::msg::WebcamError & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::msg::WebcamError & msg)
{
  return cobot1_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::msg::WebcamError>()
{
  return "cobot1_interfaces::msg::WebcamError";
}

template<>
inline const char * name<cobot1_interfaces::msg::WebcamError>()
{
  return "cobot1_interfaces/msg/WebcamError";
}

template<>
struct has_fixed_size<cobot1_interfaces::msg::WebcamError>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::msg::WebcamError>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::msg::WebcamError>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__TRAITS_HPP_
