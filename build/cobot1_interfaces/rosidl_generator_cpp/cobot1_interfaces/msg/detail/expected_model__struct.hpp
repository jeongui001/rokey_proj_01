// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__STRUCT_HPP_
#define COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__msg__ExpectedModel __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__msg__ExpectedModel __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ExpectedModel_
{
  using Type = ExpectedModel_<ContainerAllocator>;

  explicit ExpectedModel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_size = 0ul;
    }
  }

  explicit ExpectedModel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_size = 0ul;
    }
  }

  // field types and members
  using _grid_size_type =
    uint32_t;
  _grid_size_type grid_size;
  using _colors_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _colors_type colors;

  // setters for named parameter idiom
  Type & set__grid_size(
    const uint32_t & _arg)
  {
    this->grid_size = _arg;
    return *this;
  }
  Type & set__colors(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->colors = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__msg__ExpectedModel
    std::shared_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__msg__ExpectedModel
    std::shared_ptr<cobot1_interfaces::msg::ExpectedModel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExpectedModel_ & other) const
  {
    if (this->grid_size != other.grid_size) {
      return false;
    }
    if (this->colors != other.colors) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExpectedModel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExpectedModel_

// alias to use template instance with default allocator
using ExpectedModel =
  cobot1_interfaces::msg::ExpectedModel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__MSG__DETAIL__EXPECTED_MODEL__STRUCT_HPP_
