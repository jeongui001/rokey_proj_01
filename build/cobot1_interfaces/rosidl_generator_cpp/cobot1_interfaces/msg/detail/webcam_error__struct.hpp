// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot1_interfaces:msg/WebcamError.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__STRUCT_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__msg__WebcamError __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__msg__WebcamError __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WebcamError_
{
  using Type = WebcamError_<ContainerAllocator>;

  explicit WebcamError_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->step = 0l;
      this->row = 0l;
      this->col = 0l;
      this->expected_color = "";
      this->detected_color = "";
      this->message = "";
    }
  }

  explicit WebcamError_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : expected_color(_alloc),
    detected_color(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->step = 0l;
      this->row = 0l;
      this->col = 0l;
      this->expected_color = "";
      this->detected_color = "";
      this->message = "";
    }
  }

  // field types and members
  using _step_type =
    int32_t;
  _step_type step;
  using _row_type =
    int32_t;
  _row_type row;
  using _col_type =
    int32_t;
  _col_type col;
  using _expected_color_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _expected_color_type expected_color;
  using _detected_color_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _detected_color_type detected_color;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__step(
    const int32_t & _arg)
  {
    this->step = _arg;
    return *this;
  }
  Type & set__row(
    const int32_t & _arg)
  {
    this->row = _arg;
    return *this;
  }
  Type & set__col(
    const int32_t & _arg)
  {
    this->col = _arg;
    return *this;
  }
  Type & set__expected_color(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->expected_color = _arg;
    return *this;
  }
  Type & set__detected_color(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->detected_color = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::msg::WebcamError_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::msg::WebcamError_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::msg::WebcamError_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::msg::WebcamError_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__msg__WebcamError
    std::shared_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__msg__WebcamError
    std::shared_ptr<cobot1_interfaces::msg::WebcamError_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WebcamError_ & other) const
  {
    if (this->step != other.step) {
      return false;
    }
    if (this->row != other.row) {
      return false;
    }
    if (this->col != other.col) {
      return false;
    }
    if (this->expected_color != other.expected_color) {
      return false;
    }
    if (this->detected_color != other.detected_color) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const WebcamError_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WebcamError_

// alias to use template instance with default allocator
using WebcamError =
  cobot1_interfaces::msg::WebcamError_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__MSG__DETAIL__WEBCAM_ERROR__STRUCT_HPP_
