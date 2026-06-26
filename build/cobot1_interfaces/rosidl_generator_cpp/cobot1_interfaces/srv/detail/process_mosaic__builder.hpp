// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot1_interfaces:srv/ProcessMosaic.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__BUILDER_HPP_
#define COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot1_interfaces/srv/detail/process_mosaic__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot1_interfaces
{

namespace srv
{

namespace builder
{

class Init_ProcessMosaic_Request_grid_cols
{
public:
  explicit Init_ProcessMosaic_Request_grid_cols(::cobot1_interfaces::srv::ProcessMosaic_Request & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::srv::ProcessMosaic_Request grid_cols(::cobot1_interfaces::srv::ProcessMosaic_Request::_grid_cols_type arg)
  {
    msg_.grid_cols = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::srv::ProcessMosaic_Request msg_;
};

class Init_ProcessMosaic_Request_grid_rows
{
public:
  explicit Init_ProcessMosaic_Request_grid_rows(::cobot1_interfaces::srv::ProcessMosaic_Request & msg)
  : msg_(msg)
  {}
  Init_ProcessMosaic_Request_grid_cols grid_rows(::cobot1_interfaces::srv::ProcessMosaic_Request::_grid_rows_type arg)
  {
    msg_.grid_rows = std::move(arg);
    return Init_ProcessMosaic_Request_grid_cols(msg_);
  }

private:
  ::cobot1_interfaces::srv::ProcessMosaic_Request msg_;
};

class Init_ProcessMosaic_Request_input_image
{
public:
  Init_ProcessMosaic_Request_input_image()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ProcessMosaic_Request_grid_rows input_image(::cobot1_interfaces::srv::ProcessMosaic_Request::_input_image_type arg)
  {
    msg_.input_image = std::move(arg);
    return Init_ProcessMosaic_Request_grid_rows(msg_);
  }

private:
  ::cobot1_interfaces::srv::ProcessMosaic_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::srv::ProcessMosaic_Request>()
{
  return cobot1_interfaces::srv::builder::Init_ProcessMosaic_Request_input_image();
}

}  // namespace cobot1_interfaces


namespace cobot1_interfaces
{

namespace srv
{

namespace builder
{

class Init_ProcessMosaic_Response_colors
{
public:
  explicit Init_ProcessMosaic_Response_colors(::cobot1_interfaces::srv::ProcessMosaic_Response & msg)
  : msg_(msg)
  {}
  ::cobot1_interfaces::srv::ProcessMosaic_Response colors(::cobot1_interfaces::srv::ProcessMosaic_Response::_colors_type arg)
  {
    msg_.colors = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot1_interfaces::srv::ProcessMosaic_Response msg_;
};

class Init_ProcessMosaic_Response_message
{
public:
  explicit Init_ProcessMosaic_Response_message(::cobot1_interfaces::srv::ProcessMosaic_Response & msg)
  : msg_(msg)
  {}
  Init_ProcessMosaic_Response_colors message(::cobot1_interfaces::srv::ProcessMosaic_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ProcessMosaic_Response_colors(msg_);
  }

private:
  ::cobot1_interfaces::srv::ProcessMosaic_Response msg_;
};

class Init_ProcessMosaic_Response_success
{
public:
  Init_ProcessMosaic_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ProcessMosaic_Response_message success(::cobot1_interfaces::srv::ProcessMosaic_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ProcessMosaic_Response_message(msg_);
  }

private:
  ::cobot1_interfaces::srv::ProcessMosaic_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot1_interfaces::srv::ProcessMosaic_Response>()
{
  return cobot1_interfaces::srv::builder::Init_ProcessMosaic_Response_success();
}

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__BUILDER_HPP_
