// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__STRUCT_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__msg__BlockTask __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__msg__BlockTask __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BlockTask_
{
  using Type = BlockTask_<ContainerAllocator>;

  explicit BlockTask_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->y_position = 0.0;
      this->color = "";
      this->block_type = 0;
    }
  }

  explicit BlockTask_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : color(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->y_position = 0.0;
      this->color = "";
      this->block_type = 0;
    }
  }

  // field types and members
  using _y_position_type =
    double;
  _y_position_type y_position;
  using _color_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _color_type color;
  using _block_type_type =
    uint8_t;
  _block_type_type block_type;

  // setters for named parameter idiom
  Type & set__y_position(
    const double & _arg)
  {
    this->y_position = _arg;
    return *this;
  }
  Type & set__color(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->color = _arg;
    return *this;
  }
  Type & set__block_type(
    const uint8_t & _arg)
  {
    this->block_type = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::msg::BlockTask_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::msg::BlockTask_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__msg__BlockTask
    std::shared_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__msg__BlockTask
    std::shared_ptr<cobot1_interfaces::msg::BlockTask_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BlockTask_ & other) const
  {
    if (this->y_position != other.y_position) {
      return false;
    }
    if (this->color != other.color) {
      return false;
    }
    if (this->block_type != other.block_type) {
      return false;
    }
    return true;
  }
  bool operator!=(const BlockTask_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BlockTask_

// alias to use template instance with default allocator
using BlockTask =
  cobot1_interfaces::msg::BlockTask_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__MSG__DETAIL__BLOCK_TASK__STRUCT_HPP_
