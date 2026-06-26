// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__TRAITS_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot1_interfaces/msg/detail/expected_model__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cobot1_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ExpectedModel & msg,
  std::ostream & out)
{
  out << "{";
  // member: grid_size
  {
    out << "grid_size: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_size, out);
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
  const ExpectedModel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: grid_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_size: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_size, out);
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

inline std::string to_yaml(const ExpectedModel & msg, bool use_flow_style = false)
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
  const cobot1_interfaces::msg::ExpectedModel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::msg::ExpectedModel & msg)
{
  return cobot1_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::msg::ExpectedModel>()
{
  return "cobot1_interfaces::msg::ExpectedModel";
}

template<>
inline const char * name<cobot1_interfaces::msg::ExpectedModel>()
{
  return "cobot1_interfaces/msg/ExpectedModel";
}

template<>
struct has_fixed_size<cobot1_interfaces::msg::ExpectedModel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::msg::ExpectedModel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::msg::ExpectedModel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__TRAITS_HPP_
