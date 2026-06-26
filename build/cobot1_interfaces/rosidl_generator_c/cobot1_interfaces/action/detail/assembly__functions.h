// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cobot1_interfaces:action/Assembly.idl
// generated code does not contain a copyright notice

#ifndef COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__FUNCTIONS_H_
#define COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "cobot1_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "cobot1_interfaces/action/detail/assembly__struct.h"

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_Goal
 * )) before or use
 * cobot1_interfaces__action__Assembly_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Goal__init(cobot1_interfaces__action__Assembly_Goal * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Goal__fini(cobot1_interfaces__action__Assembly_Goal * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_Goal *
cobot1_interfaces__action__Assembly_Goal__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Goal__destroy(cobot1_interfaces__action__Assembly_Goal * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Goal__are_equal(const cobot1_interfaces__action__Assembly_Goal * lhs, const cobot1_interfaces__action__Assembly_Goal * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_Goal__copy(
  const cobot1_interfaces__action__Assembly_Goal * input,
  cobot1_interfaces__action__Assembly_Goal * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Goal__Sequence__init(cobot1_interfaces__action__Assembly_Goal__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Goal__Sequence__fini(cobot1_interfaces__action__Assembly_Goal__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_Goal__Sequence *
cobot1_interfaces__action__Assembly_Goal__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Goal__Sequence__destroy(cobot1_interfaces__action__Assembly_Goal__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Goal__Sequence__are_equal(const cobot1_interfaces__action__Assembly_Goal__Sequence * lhs, const cobot1_interfaces__action__Assembly_Goal__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_Goal__Sequence__copy(
  const cobot1_interfaces__action__Assembly_Goal__Sequence * input,
  cobot1_interfaces__action__Assembly_Goal__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_Result
 * )) before or use
 * cobot1_interfaces__action__Assembly_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Result__init(cobot1_interfaces__action__Assembly_Result * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Result__fini(cobot1_interfaces__action__Assembly_Result * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_Result *
cobot1_interfaces__action__Assembly_Result__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Result__destroy(cobot1_interfaces__action__Assembly_Result * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Result__are_equal(const cobot1_interfaces__action__Assembly_Result * lhs, const cobot1_interfaces__action__Assembly_Result * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_Result__copy(
  const cobot1_interfaces__action__Assembly_Result * input,
  cobot1_interfaces__action__Assembly_Result * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Result__Sequence__init(cobot1_interfaces__action__Assembly_Result__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Result__Sequence__fini(cobot1_interfaces__action__Assembly_Result__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_Result__Sequence *
cobot1_interfaces__action__Assembly_Result__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Result__Sequence__destroy(cobot1_interfaces__action__Assembly_Result__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Result__Sequence__are_equal(const cobot1_interfaces__action__Assembly_Result__Sequence * lhs, const cobot1_interfaces__action__Assembly_Result__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_Result__Sequence__copy(
  const cobot1_interfaces__action__Assembly_Result__Sequence * input,
  cobot1_interfaces__action__Assembly_Result__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_Feedback
 * )) before or use
 * cobot1_interfaces__action__Assembly_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Feedback__init(cobot1_interfaces__action__Assembly_Feedback * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Feedback__fini(cobot1_interfaces__action__Assembly_Feedback * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_Feedback *
cobot1_interfaces__action__Assembly_Feedback__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Feedback__destroy(cobot1_interfaces__action__Assembly_Feedback * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Feedback__are_equal(const cobot1_interfaces__action__Assembly_Feedback * lhs, const cobot1_interfaces__action__Assembly_Feedback * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_Feedback__copy(
  const cobot1_interfaces__action__Assembly_Feedback * input,
  cobot1_interfaces__action__Assembly_Feedback * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Feedback__Sequence__init(cobot1_interfaces__action__Assembly_Feedback__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Feedback__Sequence__fini(cobot1_interfaces__action__Assembly_Feedback__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_Feedback__Sequence *
cobot1_interfaces__action__Assembly_Feedback__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_Feedback__Sequence__destroy(cobot1_interfaces__action__Assembly_Feedback__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_Feedback__Sequence__are_equal(const cobot1_interfaces__action__Assembly_Feedback__Sequence * lhs, const cobot1_interfaces__action__Assembly_Feedback__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_Feedback__Sequence__copy(
  const cobot1_interfaces__action__Assembly_Feedback__Sequence * input,
  cobot1_interfaces__action__Assembly_Feedback__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_SendGoal_Request
 * )) before or use
 * cobot1_interfaces__action__Assembly_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Request__init(cobot1_interfaces__action__Assembly_SendGoal_Request * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Request__fini(cobot1_interfaces__action__Assembly_SendGoal_Request * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_SendGoal_Request *
cobot1_interfaces__action__Assembly_SendGoal_Request__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Request__destroy(cobot1_interfaces__action__Assembly_SendGoal_Request * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Request__are_equal(const cobot1_interfaces__action__Assembly_SendGoal_Request * lhs, const cobot1_interfaces__action__Assembly_SendGoal_Request * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_SendGoal_Request__copy(
  const cobot1_interfaces__action__Assembly_SendGoal_Request * input,
  cobot1_interfaces__action__Assembly_SendGoal_Request * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__init(cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__fini(cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence *
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__destroy(cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__are_equal(const cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * lhs, const cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__copy(
  const cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * input,
  cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_SendGoal_Response
 * )) before or use
 * cobot1_interfaces__action__Assembly_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Response__init(cobot1_interfaces__action__Assembly_SendGoal_Response * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Response__fini(cobot1_interfaces__action__Assembly_SendGoal_Response * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_SendGoal_Response *
cobot1_interfaces__action__Assembly_SendGoal_Response__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Response__destroy(cobot1_interfaces__action__Assembly_SendGoal_Response * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Response__are_equal(const cobot1_interfaces__action__Assembly_SendGoal_Response * lhs, const cobot1_interfaces__action__Assembly_SendGoal_Response * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_SendGoal_Response__copy(
  const cobot1_interfaces__action__Assembly_SendGoal_Response * input,
  cobot1_interfaces__action__Assembly_SendGoal_Response * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__init(cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__fini(cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence *
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__destroy(cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__are_equal(const cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * lhs, const cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__copy(
  const cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * input,
  cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_GetResult_Request
 * )) before or use
 * cobot1_interfaces__action__Assembly_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Request__init(cobot1_interfaces__action__Assembly_GetResult_Request * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Request__fini(cobot1_interfaces__action__Assembly_GetResult_Request * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_GetResult_Request *
cobot1_interfaces__action__Assembly_GetResult_Request__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Request__destroy(cobot1_interfaces__action__Assembly_GetResult_Request * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Request__are_equal(const cobot1_interfaces__action__Assembly_GetResult_Request * lhs, const cobot1_interfaces__action__Assembly_GetResult_Request * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_GetResult_Request__copy(
  const cobot1_interfaces__action__Assembly_GetResult_Request * input,
  cobot1_interfaces__action__Assembly_GetResult_Request * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__init(cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__fini(cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence *
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__destroy(cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__are_equal(const cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * lhs, const cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__copy(
  const cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * input,
  cobot1_interfaces__action__Assembly_GetResult_Request__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_GetResult_Response
 * )) before or use
 * cobot1_interfaces__action__Assembly_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Response__init(cobot1_interfaces__action__Assembly_GetResult_Response * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Response__fini(cobot1_interfaces__action__Assembly_GetResult_Response * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_GetResult_Response *
cobot1_interfaces__action__Assembly_GetResult_Response__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Response__destroy(cobot1_interfaces__action__Assembly_GetResult_Response * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Response__are_equal(const cobot1_interfaces__action__Assembly_GetResult_Response * lhs, const cobot1_interfaces__action__Assembly_GetResult_Response * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_GetResult_Response__copy(
  const cobot1_interfaces__action__Assembly_GetResult_Response * input,
  cobot1_interfaces__action__Assembly_GetResult_Response * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__init(cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__fini(cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence *
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__destroy(cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__are_equal(const cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * lhs, const cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__copy(
  const cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * input,
  cobot1_interfaces__action__Assembly_GetResult_Response__Sequence * output);

/// Initialize action/Assembly message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cobot1_interfaces__action__Assembly_FeedbackMessage
 * )) before or use
 * cobot1_interfaces__action__Assembly_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_FeedbackMessage__init(cobot1_interfaces__action__Assembly_FeedbackMessage * msg);

/// Finalize action/Assembly message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_FeedbackMessage__fini(cobot1_interfaces__action__Assembly_FeedbackMessage * msg);

/// Create action/Assembly message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cobot1_interfaces__action__Assembly_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_FeedbackMessage *
cobot1_interfaces__action__Assembly_FeedbackMessage__create();

/// Destroy action/Assembly message.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_FeedbackMessage__destroy(cobot1_interfaces__action__Assembly_FeedbackMessage * msg);

/// Check for action/Assembly message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_FeedbackMessage__are_equal(const cobot1_interfaces__action__Assembly_FeedbackMessage * lhs, const cobot1_interfaces__action__Assembly_FeedbackMessage * rhs);

/// Copy a action/Assembly message.
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
cobot1_interfaces__action__Assembly_FeedbackMessage__copy(
  const cobot1_interfaces__action__Assembly_FeedbackMessage * input,
  cobot1_interfaces__action__Assembly_FeedbackMessage * output);

/// Initialize array of action/Assembly messages.
/**
 * It allocates the memory for the number of elements and calls
 * cobot1_interfaces__action__Assembly_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__init(cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__fini(cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * array);

/// Create array of action/Assembly messages.
/**
 * It allocates the memory for the array and calls
 * cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence *
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/Assembly messages.
/**
 * It calls
 * cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
void
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__destroy(cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * array);

/// Check for action/Assembly message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cobot1_interfaces
bool
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__are_equal(const cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * lhs, const cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/Assembly messages.
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
cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__copy(
  const cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * input,
  cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // COBOT1_INTERFACES__ACTION__DETAIL__ASSEMBLY__FUNCTIONS_H_
