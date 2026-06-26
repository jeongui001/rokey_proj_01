// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__BUILDER_HPP_
#define COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot1_interfaces/action/detail/assembly__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_Goal_tasks
{
public:
  Init_Assembly_Goal_tasks()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cobot1_interfaces::action::Assembly_Goal tasks(::cobot1_interfaces::action::Assembly_Goal::_tasks_type arg)
  {
    msg_.tasks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_Goal>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_Goal_tasks();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_Result_error_message
{
public:
  explicit Init_Assembly_Result_error_message(::cobot1_interfaces::action::Assembly_Result & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::action::Assembly_Result error_message(::cobot1_interfaces::action::Assembly_Result::_error_message_type arg)
  {
    msg_.error_message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_Result msg_;
};

class Init_Assembly_Result_failed_step
{
public:
  Init_Assembly_Result_failed_step()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Assembly_Result_error_message failed_step(::cobot1_interfaces::action::Assembly_Result::_failed_step_type arg)
  {
    msg_.failed_step = std::move(arg);
    return Init_Assembly_Result_error_message(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_Result>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_Result_failed_step();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_Feedback_current_index
{
public:
  Init_Assembly_Feedback_current_index()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cobot1_interfaces::action::Assembly_Feedback current_index(::cobot1_interfaces::action::Assembly_Feedback::_current_index_type arg)
  {
    msg_.current_index = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_Feedback>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_Feedback_current_index();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_SendGoal_Request_goal
{
public:
  explicit Init_Assembly_SendGoal_Request_goal(::cobot1_interfaces::action::Assembly_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::action::Assembly_SendGoal_Request goal(::cobot1_interfaces::action::Assembly_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_SendGoal_Request msg_;
};

class Init_Assembly_SendGoal_Request_goal_id
{
public:
  Init_Assembly_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Assembly_SendGoal_Request_goal goal_id(::cobot1_interfaces::action::Assembly_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Assembly_SendGoal_Request_goal(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_SendGoal_Request>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_SendGoal_Request_goal_id();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_SendGoal_Response_stamp
{
public:
  explicit Init_Assembly_SendGoal_Response_stamp(::cobot1_interfaces::action::Assembly_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::action::Assembly_SendGoal_Response stamp(::cobot1_interfaces::action::Assembly_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_SendGoal_Response msg_;
};

class Init_Assembly_SendGoal_Response_accepted
{
public:
  Init_Assembly_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Assembly_SendGoal_Response_stamp accepted(::cobot1_interfaces::action::Assembly_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Assembly_SendGoal_Response_stamp(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_SendGoal_Response>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_SendGoal_Response_accepted();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_GetResult_Request_goal_id
{
public:
  Init_Assembly_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cobot1_interfaces::action::Assembly_GetResult_Request goal_id(::cobot1_interfaces::action::Assembly_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_GetResult_Request>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_GetResult_Request_goal_id();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_GetResult_Response_result
{
public:
  explicit Init_Assembly_GetResult_Response_result(::cobot1_interfaces::action::Assembly_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::action::Assembly_GetResult_Response result(::cobot1_interfaces::action::Assembly_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_GetResult_Response msg_;
};

class Init_Assembly_GetResult_Response_status
{
public:
  Init_Assembly_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Assembly_GetResult_Response_result status(::cobot1_interfaces::action::Assembly_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Assembly_GetResult_Response_result(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_GetResult_Response>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_GetResult_Response_status();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace action
{

namespace builder
{

class Init_Assembly_FeedbackMessage_feedback
{
public:
  explicit Init_Assembly_FeedbackMessage_feedback(::cobot1_interfaces::action::Assembly_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::action::Assembly_FeedbackMessage feedback(::cobot1_interfaces::action::Assembly_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_FeedbackMessage msg_;
};

class Init_Assembly_FeedbackMessage_goal_id
{
public:
  Init_Assembly_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Assembly_FeedbackMessage_feedback goal_id(::cobot1_interfaces::action::Assembly_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Assembly_FeedbackMessage_feedback(msg_);
  }

private:
  ::cobot1_interfaces::action::Assembly_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::action::Assembly_FeedbackMessage>()
{
  return cobot1_interfaces::action::builder::Init_Assembly_FeedbackMessage_goal_id();
}

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__BUILDER_HPP_
