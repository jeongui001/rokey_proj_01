// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__TRAITS_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot1_interfaces/msg/detail/block_task__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cobot1_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const BlockTask & msg,
  std::ostream & out)
{
  out << "{";
  // member: y_position
  {
    out << "y_position: ";
    rosidl_generator_traits::value_to_yaml(msg.y_position, out);
    out << ", ";
  }

  // member: color
  {
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << ", ";
  }

  // member: block_type
  {
    out << "block_type: ";
    rosidl_generator_traits::value_to_yaml(msg.block_type, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BlockTask & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: y_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_position: ";
    rosidl_generator_traits::value_to_yaml(msg.y_position, out);
    out << "\n";
  }

  // member: color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << "\n";
  }

  // member: block_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "block_type: ";
    rosidl_generator_traits::value_to_yaml(msg.block_type, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BlockTask & msg, bool use_flow_style = false)
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
  const cobot1_interfaces::msg::BlockTask & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::msg::BlockTask & msg)
{
  return cobot1_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::msg::BlockTask>()
{
  return "cobot1_interfaces::msg::BlockTask";
}

template<>
inline const char * name<cobot1_interfaces::msg::BlockTask>()
{
  return "cobot1_interfaces/msg/BlockTask";
}

template<>
struct has_fixed_size<cobot1_interfaces::msg::BlockTask>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::msg::BlockTask>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::msg::BlockTask>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__TRAITS_HPP_
