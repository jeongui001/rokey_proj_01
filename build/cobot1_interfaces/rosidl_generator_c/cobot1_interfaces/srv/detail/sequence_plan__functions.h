// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__FUNCTIONS_H_
#define COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "cobot1_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "cobot1_interfaces/srv/detail/sequence_plan__struct.h"

/// Initialize srv/SequencePlan message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__srv__SequencePlan_Request
 * )) before or use
 * cobot1_interfaces__srv__SequencePlan_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Request__init(cobot1_interfaces__srv__SequencePlan_Request * msg);

/// Finalize srv/SequencePlan message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Request__fini(cobot1_interfaces__srv__SequencePlan_Request * msg);

/// Create srv/SequencePlan message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__srv__SequencePlan_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__srv__SequencePlan_Request *
cobot1_interfaces__srv__SequencePlan_Request__create();

/// Destroy srv/SequencePlan message.
/**
 * It calls
 * cobot1_interfaces__srv__SequencePlan_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Request__destroy(cobot1_interfaces__srv__SequencePlan_Request * msg);

/// Check for srv/SequencePlan message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Request__are_equal(const cobot1_interfaces__srv__SequencePlan_Request * lhs, const cobot1_interfaces__srv__SequencePlan_Request * rhs);

/// Copy a srv/SequencePlan message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Request__copy(
  const cobot1_interfaces__srv__SequencePlan_Request * input,
  cobot1_interfaces__srv__SequencePlan_Request * output);

/// Initialize array of srv/SequencePlan messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__srv__SequencePlan_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Request__Sequence__init(cobot1_interfaces__srv__SequencePlan_Request__Sequence * array, size_t size);

/// Finalize array of srv/SequencePlan messages.
/**
 * It calls
 * cobot1_interfaces__srv__SequencePlan_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Request__Sequence__fini(cobot1_interfaces__srv__SequencePlan_Request__Sequence * array);

/// Create array of srv/SequencePlan messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__srv__SequencePlan_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__srv__SequencePlan_Request__Sequence *
cobot1_interfaces__srv__SequencePlan_Request__Sequence__create(size_t size);

/// Destroy array of srv/SequencePlan messages.
/**
 * It calls
 * cobot1_interfaces__srv__SequencePlan_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Request__Sequence__destroy(cobot1_interfaces__srv__SequencePlan_Request__Sequence * array);

/// Check for srv/SequencePlan message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Request__Sequence__are_equal(const cobot1_interfaces__srv__SequencePlan_Request__Sequence * lhs, const cobot1_interfaces__srv__SequencePlan_Request__Sequence * rhs);

/// Copy an array of srv/SequencePlan messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Request__Sequence__copy(
  const cobot1_interfaces__srv__SequencePlan_Request__Sequence * input,
  cobot1_interfaces__srv__SequencePlan_Request__Sequence * output);

/// Initialize srv/SequencePlan message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__srv__SequencePlan_Response
 * )) before or use
 * cobot1_interfaces__srv__SequencePlan_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Response__init(cobot1_interfaces__srv__SequencePlan_Response * msg);

/// Finalize srv/SequencePlan message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Response__fini(cobot1_interfaces__srv__SequencePlan_Response * msg);

/// Create srv/SequencePlan message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__srv__SequencePlan_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__srv__SequencePlan_Response *
cobot1_interfaces__srv__SequencePlan_Response__create();

/// Destroy srv/SequencePlan message.
/**
 * It calls
 * cobot1_interfaces__srv__SequencePlan_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Response__destroy(cobot1_interfaces__srv__SequencePlan_Response * msg);

/// Check for srv/SequencePlan message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Response__are_equal(const cobot1_interfaces__srv__SequencePlan_Response * lhs, const cobot1_interfaces__srv__SequencePlan_Response * rhs);

/// Copy a srv/SequencePlan message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Response__copy(
  const cobot1_interfaces__srv__SequencePlan_Response * input,
  cobot1_interfaces__srv__SequencePlan_Response * output);

/// Initialize array of srv/SequencePlan messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__srv__SequencePlan_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Response__Sequence__init(cobot1_interfaces__srv__SequencePlan_Response__Sequence * array, size_t size);

/// Finalize array of srv/SequencePlan messages.
/**
 * It calls
 * cobot1_interfaces__srv__SequencePlan_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Response__Sequence__fini(cobot1_interfaces__srv__SequencePlan_Response__Sequence * array);

/// Create array of srv/SequencePlan messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__srv__SequencePlan_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__srv__SequencePlan_Response__Sequence *
cobot1_interfaces__srv__SequencePlan_Response__Sequence__create(size_t size);

/// Destroy array of srv/SequencePlan messages.
/**
 * It calls
 * cobot1_interfaces__srv__SequencePlan_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__srv__SequencePlan_Response__Sequence__destroy(cobot1_interfaces__srv__SequencePlan_Response__Sequence * array);

/// Check for srv/SequencePlan message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Response__Sequence__are_equal(const cobot1_interfaces__srv__SequencePlan_Response__Sequence * lhs, const cobot1_interfaces__srv__SequencePlan_Response__Sequence * rhs);

/// Copy an array of srv/SequencePlan messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__srv__SequencePlan_Response__Sequence__copy(
  const cobot1_interfaces__srv__SequencePlan_Response__Sequence * input,
  cobot1_interfaces__srv__SequencePlan_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__SRV__DETAIL__SEQUENCE_PLAN__FUNCTIONS_H_
