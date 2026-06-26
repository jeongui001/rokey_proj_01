// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot1_interfaces:srv/ProcessMosaic.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__STRUCT_HPP_
#define COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'input_image'
#include "sensor_msgs/msg/detail/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Request __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Request __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ProcessMosaic_Request_
{
  using Type = ProcessMosaic_Request_<ContainerAllocator>;

  explicit ProcessMosaic_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : input_image(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_rows = 0ul;
      this->grid_cols = 0ul;
    }
  }

  explicit ProcessMosaic_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : input_image(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_rows = 0ul;
      this->grid_cols = 0ul;
    }
  }

  // field types and members
  using _input_image_type =
    sensor_msgs::msg::Image_<ContainerAllocator>;
  _input_image_type input_image;
  using _grid_rows_type =
    uint32_t;
  _grid_rows_type grid_rows;
  using _grid_cols_type =
    uint32_t;
  _grid_cols_type grid_cols;

  // setters for named parameter idiom
  Type & set__input_image(
    const sensor_msgs::msg::Image_<ContainerAllocator> & _arg)
  {
    this->input_image = _arg;
    return *this;
  }
  Type & set__grid_rows(
    const uint32_t & _arg)
  {
    this->grid_rows = _arg;
    return *this;
  }
  Type & set__grid_cols(
    const uint32_t & _arg)
  {
    this->grid_cols = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Request
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Request
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ProcessMosaic_Request_ & other) const
  {
    if (this->input_image != other.input_image) {
      return false;
    }
    if (this->grid_rows != other.grid_rows) {
      return false;
    }
    if (this->grid_cols != other.grid_cols) {
      return false;
    }
    return true;
  }
  bool operator!=(const ProcessMosaic_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ProcessMosaic_Request_

// alias to use template instance with default allocator
using ProcessMosaic_Request =
  cobot1_interfaces::srv::ProcessMosaic_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cobot1_interfaces


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Response __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Response __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ProcessMosaic_Response_
{
  using Type = ProcessMosaic_Response_<ContainerAllocator>;

  explicit ProcessMosaic_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit ProcessMosaic_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _colors_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _colors_type colors;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
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
    cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Response
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__srv__ProcessMosaic_Response
    std::shared_ptr<cobot1_interfaces::srv::ProcessMosaic_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ProcessMosaic_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->colors != other.colors) {
      return false;
    }
    return true;
  }
  bool operator!=(const ProcessMosaic_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ProcessMosaic_Response_

// alias to use template instance with default allocator
using ProcessMosaic_Response =
  cobot1_interfaces::srv::ProcessMosaic_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cobot1_interfaces

namespace cobot1_interfaces
{

namespace srv
{

struct ProcessMosaic
{
  using Request = cobot1_interfaces::srv::ProcessMosaic_Request;
  using Response = cobot1_interfaces::srv::ProcessMosaic_Response;
};

}  // namespace srv

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__SRV__DETAIL__PROCESS_MOSAIC__STRUCT_HPP_
