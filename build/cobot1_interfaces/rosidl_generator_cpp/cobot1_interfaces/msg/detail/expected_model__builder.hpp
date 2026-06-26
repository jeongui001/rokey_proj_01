// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__BUILDER_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot1_interfaces/msg/detail/expected_model__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot1_interfaces
{

namespace msg
{

namespace builder
{

class Init_ExpectedModel_colors
{
public:
  explicit Init_ExpectedModel_colors(::cobot1_interfaces::msg::ExpectedModel & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::msg::ExpectedModel colors(::cobot1_interfaces::msg::ExpectedModel::_colors_type arg)
  {
    msg_.colors = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::msg::ExpectedModel msg_;
};

class Init_ExpectedModel_grid_size
{
public:
  Init_ExpectedModel_grid_size()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExpectedModel_colors grid_size(::cobot1_interfaces::msg::ExpectedModel::_grid_size_type arg)
  {
    msg_.grid_size = std::move(arg);
    return Init_ExpectedModel_colors(msg_);
  }

private:
  ::cobot1_interfaces::msg::ExpectedModel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::msg::ExpectedModel>()
{
  return cobot1_interfaces::msg::builder::Init_ExpectedModel_grid_size();
}

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__BUILDER_HPP_
