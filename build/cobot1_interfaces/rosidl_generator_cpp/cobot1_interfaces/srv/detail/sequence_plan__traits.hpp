// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__TRAITS_HPP_
#define COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cobot1_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SequencePlan_Request & msg,
  std::ostream & out)
{
  out << "{";
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
    out << ", ";
  }

  // member: grid_width
  {
    out << "grid_width: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_width, out);
    out << ", ";
  }

  // member: grid_height
  {
    out << "grid_height: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_height, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SequencePlan_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
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

  // member: grid_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_width: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_width, out);
    out << "\n";
  }

  // member: grid_height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_height: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_height, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SequencePlan_Request & msg, bool use_flow_style = false)
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
  const cobot1_interfaces::srv::SequencePlan_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::srv::SequencePlan_Request & msg)
{
  return cobot1_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::srv::SequencePlan_Request>()
{
  return "cobot1_interfaces::srv::SequencePlan_Request";
}

template<>
inline const char * name<cobot1_interfaces::srv::SequencePlan_Request>()
{
  return "cobot1_interfaces/srv/SequencePlan_Request";
}

template<>
struct has_fixed_size<cobot1_interfaces::srv::SequencePlan_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::srv::SequencePlan_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::srv::SequencePlan_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'tasks'
#include "cobot1_interfaces/msg/detail/block_task__traits.hpp"

namespace cobot1_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SequencePlan_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: error_message
  {
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << ", ";
  }

  // member: tasks
  {
    if (msg.tasks.size() == 0) {
      out << "tasks: []";
    } else {
      out << "tasks: [";
      size_t pending_items = msg.tasks.size();
      for (auto item : msg.tasks) {
        to_flow_style_yaml(item, out);
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
  const SequencePlan_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: error_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << "\n";
  }

  // member: tasks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tasks.size() == 0) {
      out << "tasks: []\n";
    } else {
      out << "tasks:\n";
      for (auto item : msg.tasks) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SequencePlan_Response & msg, bool use_flow_style = false)
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
  const cobot1_interfaces::srv::SequencePlan_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::srv::SequencePlan_Response & msg)
{
  return cobot1_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::srv::SequencePlan_Response>()
{
  return "cobot1_interfaces::srv::SequencePlan_Response";
}

template<>
inline const char * name<cobot1_interfaces::srv::SequencePlan_Response>()
{
  return "cobot1_interfaces/srv/SequencePlan_Response";
}

template<>
struct has_fixed_size<cobot1_interfaces::srv::SequencePlan_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::srv::SequencePlan_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::srv::SequencePlan_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<cobot1_interfaces::srv::SequencePlan>()
{
  return "cobot1_interfaces::srv::SequencePlan";
}

template<>
inline const char * name<cobot1_interfaces::srv::SequencePlan>()
{
  return "cobot1_interfaces/srv/SequencePlan";
}

template<>
struct has_fixed_size<cobot1_interfaces::srv::SequencePlan>
  : std::integral_constant<
    bool,
    has_fixed_size<cobot1_interfaces::srv::SequencePlan_Request>::value &&
    has_fixed_size<cobot1_interfaces::srv::SequencePlan_Response>::value
  >
{
};

template<>
struct has_bounded_size<cobot1_interfaces::srv::SequencePlan>
  : std::integral_constant<
    bool,
    has_bounded_size<cobot1_interfaces::srv::SequencePlan_Request>::value &&
    has_bounded_size<cobot1_interfaces::srv::SequencePlan_Response>::value
  >
{
};

template<>
struct is_service<cobot1_interfaces::srv::SequencePlan>
  : std::true_type
{
};

template<>
struct is_service_request<cobot1_interfaces::srv::SequencePlan_Request>
  : std::true_type
{
};

template<>
struct is_service_response<cobot1_interfaces::srv::SequencePlan_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__TRAITS_HPP_
