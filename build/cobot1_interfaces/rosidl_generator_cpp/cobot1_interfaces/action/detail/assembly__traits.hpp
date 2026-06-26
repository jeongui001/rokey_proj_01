// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__TRAITS_HPP_
#define COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot1_interfaces/action/detail/assembly__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'tasks'
#include "cobot1_interfaces/msg/detail/block_task__traits.hpp"

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_Goal & msg,
  std::ostream & out)
{
  out << "{";
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
  const Assembly_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
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

inline std::string to_yaml(const Assembly_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_Goal & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_Goal>()
{
  return "cobot1_interfaces::action::Assembly_Goal";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_Goal>()
{
  return "cobot1_interfaces/action/Assembly_Goal";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: failed_step
  {
    out << "failed_step: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_step, out);
    out << ", ";
  }

  // member: error_message
  {
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: failed_step
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failed_step: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_step, out);
    out << "\n";
  }

  // member: error_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_Result & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_Result>()
{
  return "cobot1_interfaces::action::Assembly_Result";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_Result>()
{
  return "cobot1_interfaces/action/Assembly_Result";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_index
  {
    out << "current_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_index, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_index, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_Feedback & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_Feedback>()
{
  return "cobot1_interfaces::action::Assembly_Feedback";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_Feedback>()
{
  return "cobot1_interfaces/action/Assembly_Feedback";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "cobot1_interfaces/action/detail/assembly__traits.hpp"

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_SendGoal_Request & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_SendGoal_Request>()
{
  return "cobot1_interfaces::action::Assembly_SendGoal_Request";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_SendGoal_Request>()
{
  return "cobot1_interfaces/action/Assembly_SendGoal_Request";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<cobot1_interfaces::action::Assembly_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<cobot1_interfaces::action::Assembly_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_SendGoal_Response & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_SendGoal_Response>()
{
  return "cobot1_interfaces::action::Assembly_SendGoal_Response";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_SendGoal_Response>()
{
  return "cobot1_interfaces/action/Assembly_SendGoal_Response";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_SendGoal>()
{
  return "cobot1_interfaces::action::Assembly_SendGoal";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_SendGoal>()
{
  return "cobot1_interfaces/action/Assembly_SendGoal";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<cobot1_interfaces::action::Assembly_SendGoal_Request>::value &&
    has_fixed_size<cobot1_interfaces::action::Assembly_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<cobot1_interfaces::action::Assembly_SendGoal_Request>::value &&
    has_bounded_size<cobot1_interfaces::action::Assembly_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<cobot1_interfaces::action::Assembly_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<cobot1_interfaces::action::Assembly_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<cobot1_interfaces::action::Assembly_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_GetResult_Request & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_GetResult_Request>()
{
  return "cobot1_interfaces::action::Assembly_GetResult_Request";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_GetResult_Request>()
{
  return "cobot1_interfaces/action/Assembly_GetResult_Request";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "cobot1_interfaces/action/detail/assembly__traits.hpp"

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_GetResult_Response & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_GetResult_Response>()
{
  return "cobot1_interfaces::action::Assembly_GetResult_Response";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_GetResult_Response>()
{
  return "cobot1_interfaces/action/Assembly_GetResult_Response";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<cobot1_interfaces::action::Assembly_Result>::value> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<cobot1_interfaces::action::Assembly_Result>::value> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_GetResult>()
{
  return "cobot1_interfaces::action::Assembly_GetResult";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_GetResult>()
{
  return "cobot1_interfaces/action/Assembly_GetResult";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<cobot1_interfaces::action::Assembly_GetResult_Request>::value &&
    has_fixed_size<cobot1_interfaces::action::Assembly_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<cobot1_interfaces::action::Assembly_GetResult_Request>::value &&
    has_bounded_size<cobot1_interfaces::action::Assembly_GetResult_Response>::value
  >
{
};

template<>
struct is_service<cobot1_interfaces::action::Assembly_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<cobot1_interfaces::action::Assembly_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<cobot1_interfaces::action::Assembly_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "cobot1_interfaces/action/detail/assembly__traits.hpp"

namespace cobot1_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Assembly_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Assembly_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Assembly_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace cobot1_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot1_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot1_interfaces::action::Assembly_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot1_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot1_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const cobot1_interfaces::action::Assembly_FeedbackMessage & msg)
{
  return cobot1_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<cobot1_interfaces::action::Assembly_FeedbackMessage>()
{
  return "cobot1_interfaces::action::Assembly_FeedbackMessage";
}

template<>
inline const char * name<cobot1_interfaces::action::Assembly_FeedbackMessage>()
{
  return "cobot1_interfaces/action/Assembly_FeedbackMessage";
}

template<>
struct has_fixed_size<cobot1_interfaces::action::Assembly_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<cobot1_interfaces::action::Assembly_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<cobot1_interfaces::action::Assembly_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<cobot1_interfaces::action::Assembly_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<cobot1_interfaces::action::Assembly_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<cobot1_interfaces::action::Assembly>
  : std::true_type
{
};

template<>
struct is_action_goal<cobot1_interfaces::action::Assembly_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<cobot1_interfaces::action::Assembly_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<cobot1_interfaces::action::Assembly_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__TRAITS_HPP_
