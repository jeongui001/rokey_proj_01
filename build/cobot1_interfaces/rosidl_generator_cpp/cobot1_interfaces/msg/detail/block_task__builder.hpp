// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__BUILDER_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot1_interfaces/msg/detail/block_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot1_interfaces
{

namespace msg
{

namespace builder
{

class Init_BlockTask_block_type
{
public:
  explicit Init_BlockTask_block_type(::cobot1_interfaces::msg::BlockTask & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::msg::BlockTask block_type(::cobot1_interfaces::msg::BlockTask::_block_type_type arg)
  {
    msg_.block_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::msg::BlockTask msg_;
};

class Init_BlockTask_color
{
public:
  explicit Init_BlockTask_color(::cobot1_interfaces::msg::BlockTask & msg)
  : msg_(msg)
  {}
  Init_BlockTask_block_type color(::cobot1_interfaces::msg::BlockTask::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_BlockTask_block_type(msg_);
  }

private:
  ::cobot1_interfaces::msg::BlockTask msg_;
};

class Init_BlockTask_y_position
{
public:
  Init_BlockTask_y_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BlockTask_color y_position(::cobot1_interfaces::msg::BlockTask::_y_position_type arg)
  {
    msg_.y_position = std::move(arg);
    return Init_BlockTask_color(msg_);
  }

private:
  ::cobot1_interfaces::msg::BlockTask msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::msg::BlockTask>()
{
  return cobot1_interfaces::msg::builder::Init_BlockTask_y_position();
}

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__BUILDER_HPP_
