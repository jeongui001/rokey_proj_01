// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__STRUCT_HPP_
#define COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'tasks'
#include "cobot1_interfaces/msg/detail/block_task__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_Goal __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_Goal __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_Goal_
{
  using Type = Assembly_Goal_<ContainerAllocator>;

  explicit Assembly_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Assembly_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _tasks_type =
    std::vector<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>>;
  _tasks_type tasks;

  // setters for named parameter idiom
  Type & set__tasks(
    const std::vector<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cobot1_interfaces::msg::BlockTask_<ContainerAllocator>>> & _arg)
  {
    this->tasks = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_Goal
    std::shared_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_Goal
    std::shared_ptr<cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_Goal_ & other) const
  {
    if (this->tasks != other.tasks) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_Goal_

// alias to use template instance with default allocator
using Assembly_Goal =
  cobot1_interfaces::action::Assembly_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_Result __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_Result __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_Result_
{
  using Type = Assembly_Result_<ContainerAllocator>;

  explicit Assembly_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->failed_step = 0l;
      this->error_message = "";
    }
  }

  explicit Assembly_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : error_message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->failed_step = 0l;
      this->error_message = "";
    }
  }

  // field types and members
  using _failed_step_type =
    int32_t;
  _failed_step_type failed_step;
  using _error_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _error_message_type error_message;

  // setters for named parameter idiom
  Type & set__failed_step(
    const int32_t & _arg)
  {
    this->failed_step = _arg;
    return *this;
  }
  Type & set__error_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->error_message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_Result
    std::shared_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_Result
    std::shared_ptr<cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_Result_ & other) const
  {
    if (this->failed_step != other.failed_step) {
      return false;
    }
    if (this->error_message != other.error_message) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_Result_

// alias to use template instance with default allocator
using Assembly_Result =
  cobot1_interfaces::action::Assembly_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces


#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_Feedback __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_Feedback_
{
  using Type = Assembly_Feedback_<ContainerAllocator>;

  explicit Assembly_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_index = 0l;
    }
  }

  explicit Assembly_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_index = 0l;
    }
  }

  // field types and members
  using _current_index_type =
    int32_t;
  _current_index_type current_index;

  // setters for named parameter idiom
  Type & set__current_index(
    const int32_t & _arg)
  {
    this->current_index = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_Feedback
    std::shared_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_Feedback
    std::shared_ptr<cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_Feedback_ & other) const
  {
    if (this->current_index != other.current_index) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_Feedback_

// alias to use template instance with default allocator
using Assembly_Feedback =
  cobot1_interfaces::action::Assembly_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "cobot1_interfaces/action/detail/assembly__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Request __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_SendGoal_Request_
{
  using Type = Assembly_SendGoal_Request_<ContainerAllocator>;

  explicit Assembly_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit Assembly_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const cobot1_interfaces::action::Assembly_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Request
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Request
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_SendGoal_Request_

// alias to use template instance with default allocator
using Assembly_SendGoal_Request =
  cobot1_interfaces::action::Assembly_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Response __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_SendGoal_Response_
{
  using Type = Assembly_SendGoal_Response_<ContainerAllocator>;

  explicit Assembly_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit Assembly_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Response
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_SendGoal_Response
    std::shared_ptr<cobot1_interfaces::action::Assembly_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_SendGoal_Response_

// alias to use template instance with default allocator
using Assembly_SendGoal_Response =
  cobot1_interfaces::action::Assembly_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces

namespace cobot1_interfaces
{

namespace action
{

struct Assembly_SendGoal
{
  using Request = cobot1_interfaces::action::Assembly_SendGoal_Request;
  using Response = cobot1_interfaces::action::Assembly_SendGoal_Response;
};

}  // namespace action

}  // namespace cobot1_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Request __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_GetResult_Request_
{
  using Type = Assembly_GetResult_Request_<ContainerAllocator>;

  explicit Assembly_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit Assembly_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Request
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Request
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_GetResult_Request_

// alias to use template instance with default allocator
using Assembly_GetResult_Request =
  cobot1_interfaces::action::Assembly_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Response __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_GetResult_Response_
{
  using Type = Assembly_GetResult_Response_<ContainerAllocator>;

  explicit Assembly_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit Assembly_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    cobot1_interfaces::action::Assembly_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const cobot1_interfaces::action::Assembly_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Response
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_GetResult_Response
    std::shared_ptr<cobot1_interfaces::action::Assembly_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_GetResult_Response_

// alias to use template instance with default allocator
using Assembly_GetResult_Response =
  cobot1_interfaces::action::Assembly_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces

namespace cobot1_interfaces
{

namespace action
{

struct Assembly_GetResult
{
  using Request = cobot1_interfaces::action::Assembly_GetResult_Request;
  using Response = cobot1_interfaces::action::Assembly_GetResult_Response;
};

}  // namespace action

}  // namespace cobot1_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "cobot1_interfaces/action/detail/assembly__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot1_interfaces__action__Assembly_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__cobot1_interfaces__action__Assembly_FeedbackMessage __declspec(deprecated)
#endif

namespace cobot1_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct Assembly_FeedbackMessage_
{
  using Type = Assembly_FeedbackMessage_<ContainerAllocator>;

  explicit Assembly_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit Assembly_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const cobot1_interfaces::action::Assembly_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_FeedbackMessage
    std::shared_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot1_interfaces__action__Assembly_FeedbackMessage
    std::shared_ptr<cobot1_interfaces::action::Assembly_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Assembly_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const Assembly_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Assembly_FeedbackMessage_

// alias to use template instance with default allocator
using Assembly_FeedbackMessage =
  cobot1_interfaces::action::Assembly_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace cobot1_interfaces

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace cobot1_interfaces
{

namespace action
{

struct Assembly
{
  /// The goal message defined in the action definition.
  using Goal = cobot1_interfaces::action::Assembly_Goal;
  /// The result message defined in the action definition.
  using Result = cobot1_interfaces::action::Assembly_Result;
  /// The feedback message defined in the action definition.
  using Feedback = cobot1_interfaces::action::Assembly_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = cobot1_interfaces::action::Assembly_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = cobot1_interfaces::action::Assembly_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = cobot1_interfaces::action::Assembly_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct Assembly Assembly;

}  // namespace action

}  // namespace cobot1_interfaces

#endif  // COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__STRUCT_HPP_
