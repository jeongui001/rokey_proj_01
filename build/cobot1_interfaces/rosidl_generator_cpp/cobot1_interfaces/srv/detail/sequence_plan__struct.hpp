// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__STRUCT_HPP_
#define COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__srv__SequencePlan_Request __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__srv__SequencePlan_Request __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SequencePlan_Request_
{
  using Type = SequencePlan_Request_<ContainerAllocator>;

  explicit SequencePlan_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_width = 0ul;
      this->grid_height = 0ul;
    }
  }

  explicit SequencePlan_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_width = 0ul;
      this->grid_height = 0ul;
    }
  }

  // field types and members
  using _colors_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _colors_type colors;
  using _grid_width_type =
    uint32_t;
  _grid_width_type grid_width;
  using _grid_height_type =
    uint32_t;
  _grid_height_type grid_height;

  // setters for named parameter idiom
  Type & set__colors(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->colors = _arg;
    return *this;
  }
  Type & set__grid_width(
    const uint32_t & _arg)
  {
    this->grid_width = _arg;
    return *this;
  }
  Type & set__grid_height(
    const uint32_t & _arg)
  {
    this->grid_height = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__srv__SequencePlan_Request
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__srv__SequencePlan_Request
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SequencePlan_Request_ & other) const
  {
    if (this->colors != other.colors) {
      return false;
    }
    if (this->grid_width != other.grid_width) {
      return false;
    }
    if (this->grid_height != other.grid_height) {
      return false;
    }
    return true;
  }
  bool operator!=(const SequencePlan_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SequencePlan_Request_

// alias to use template instance with default allocator
using SequencePlan_Request =
  cobot1_interfaces::srv::SequencePlan_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cobot1_interfaces


// Include directives for member types
// Member 'tasks'
#include "cobot1_interfaces/msg/detail/block_task__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__srv__SequencePlan_Response __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__srv__SequencePlan_Response __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SequencePlan_Response_
{
  using Type = SequencePlan_Response_<ContainerAllocator>;

  explicit SequencePlan_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_message = "";
    }
  }

  explicit SequencePlan_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : error_message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_message = "";
    }
  }

  // field types and members
  using _error_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _error_message_type error_message;
  using _tasks_type =
    std::vector<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>>;
  _tasks_type tasks;

  // setters for named parameter idiom
  Type & set__error_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->error_message = _arg;
    return *this;
  }
  Type & set__tasks(
    const std::vector<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>> & _arg)
  {
    this->tasks = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__srv__SequencePlan_Response
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__srv__SequencePlan_Response
    std::shared_ptr<cobot1_interfaces::srv::SequencePlan_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SequencePlan_Response_ & other) const
  {
    if (this->error_message != other.error_message) {
      return false;
    }
    if (this->tasks != other.tasks) {
      return false;
    }
    return true;
  }
  bool operator!=(const SequencePlan_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SequencePlan_Response_

// alias to use template instance with default allocator
using SequencePlan_Response =
  cobot1_interfaces::srv::SequencePlan_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cobot1_interfaces

namespace cobot1_interfaces
{

namespace srv
{

struct SequencePlan
{
  using Request = cobot1_interfaces::srv::SequencePlan_Request;
  using Response = cobot1_interfaces::srv::SequencePlan_Response;
};

}  // namespace srv

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__STRUCT_HPP_
