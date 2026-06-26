// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__BUILDER_HPP_
#define COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot1_interfaces/srv/detail/sequence_plan__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot1_interfaces
{

namespace srv
{

namespace builder
{

class Init_SequencePlan_Request_grid_height
{
public:
  explicit Init_SequencePlan_Request_grid_height(::cobot1_interfaces::srv::SequencePlan_Request & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::srv::SequencePlan_Request grid_height(::cobot1_interfaces::srv::SequencePlan_Request::_grid_height_type arg)
  {
    msg_.grid_height = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::srv::SequencePlan_Request msg_;
};

class Init_SequencePlan_Request_grid_width
{
public:
  explicit Init_SequencePlan_Request_grid_width(::cobot1_interfaces::srv::SequencePlan_Request & msg)
  : msg_(msg)
  {}
  Init_SequencePlan_Request_grid_height grid_width(::cobot1_interfaces::srv::SequencePlan_Request::_grid_width_type arg)
  {
    msg_.grid_width = std::move(arg);
    return Init_SequencePlan_Request_grid_height(msg_);
  }

private:
  ::cobot1_interfaces::srv::SequencePlan_Request msg_;
};

class Init_SequencePlan_Request_colors
{
public:
  Init_SequencePlan_Request_colors()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SequencePlan_Request_grid_width colors(::cobot1_interfaces::srv::SequencePlan_Request::_colors_type arg)
  {
    msg_.colors = std::move(arg);
    return Init_SequencePlan_Request_grid_width(msg_);
  }

private:
  ::cobot1_interfaces::srv::SequencePlan_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::srv::SequencePlan_Request>()
{
  return cobot1_interfaces::srv::builder::Init_SequencePlan_Request_colors();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace srv
{

namespace builder
{

class Init_SequencePlan_Response_tasks
{
public:
  explicit Init_SequencePlan_Response_tasks(::cobot1_interfaces::srv::SequencePlan_Response & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::srv::SequencePlan_Response tasks(::cobot1_interfaces::srv::SequencePlan_Response::_tasks_type arg)
  {
    msg_.tasks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::srv::SequencePlan_Response msg_;
};

class Init_SequencePlan_Response_error_message
{
public:
  Init_SequencePlan_Response_error_message()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SequencePlan_Response_tasks error_message(::cobot1_interfaces::srv::SequencePlan_Response::_error_message_type arg)
  {
    msg_.error_message = std::move(arg);
    return Init_SequencePlan_Response_tasks(msg_);
  }

private:
  ::cobot1_interfaces::srv::SequencePlan_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::srv::SequencePlan_Response>()
{
  return cobot1_interfaces::srv::builder::Init_SequencePlan_Response_error_message();
}

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__BUILDER_HPP_
