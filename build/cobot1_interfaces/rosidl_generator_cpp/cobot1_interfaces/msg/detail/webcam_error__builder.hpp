// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot1_interfaces:msg/WebcamError.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__BUILDER_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot1_interfaces/msg/detail/webcam_error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot1_interfaces
{

namespace msg
{

namespace builder
{

class Init_WebcamError_message
{
public:
  explicit Init_WebcamError_message(::cobot1_interfaces::msg::WebcamError & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::msg::WebcamError message(::cobot1_interfaces::msg::WebcamError::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::msg::WebcamError msg_;
};

class Init_WebcamError_detected_color
{
public:
  explicit Init_WebcamError_detected_color(::cobot1_interfaces::msg::WebcamError & msg)
  : msg_(msg)
  {}
  Init_WebcamError_message detected_color(::cobot1_interfaces::msg::WebcamError::_detected_color_type arg)
  {
    msg_.detected_color = std::move(arg);
    return Init_WebcamError_message(msg_);
  }

private:
  ::cobot1_interfaces::msg::WebcamError msg_;
};

class Init_WebcamError_expected_color
{
public:
  explicit Init_WebcamError_expected_color(::cobot1_interfaces::msg::WebcamError & msg)
  : msg_(msg)
  {}
  Init_WebcamError_detected_color expected_color(::cobot1_interfaces::msg::WebcamError::_expected_color_type arg)
  {
    msg_.expected_color = std::move(arg);
    return Init_WebcamError_detected_color(msg_);
  }

private:
  ::cobot1_interfaces::msg::WebcamError msg_;
};

class Init_WebcamError_col
{
public:
  explicit Init_WebcamError_col(::cobot1_interfaces::msg::WebcamError & msg)
  : msg_(msg)
  {}
  Init_WebcamError_expected_color col(::cobot1_interfaces::msg::WebcamError::_col_type arg)
  {
    msg_.col = std::move(arg);
    return Init_WebcamError_expected_color(msg_);
  }

private:
  ::cobot1_interfaces::msg::WebcamError msg_;
};

class Init_WebcamError_row
{
public:
  explicit Init_WebcamError_row(::cobot1_interfaces::msg::WebcamError & msg)
  : msg_(msg)
  {}
  Init_WebcamError_col row(::cobot1_interfaces::msg::WebcamError::_row_type arg)
  {
    msg_.row = std::move(arg);
    return Init_WebcamError_col(msg_);
  }

private:
  ::cobot1_interfaces::msg::WebcamError msg_;
};

class Init_WebcamError_step
{
public:
  Init_WebcamError_step()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WebcamError_row step(::cobot1_interfaces::msg::WebcamError::_step_type arg)
  {
    msg_.step = std::move(arg);
    return Init_WebcamError_row(msg_);
  }

private:
  ::cobot1_interfaces::msg::WebcamError msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::msg::WebcamError>()
{
  return cobot1_interfaces::msg::builder::Init_WebcamError_step();
}

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__BUILDER_HPP_
