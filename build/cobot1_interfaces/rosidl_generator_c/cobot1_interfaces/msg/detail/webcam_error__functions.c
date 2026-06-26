// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot1_interfaces:msg/WebcamError.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/msg/detail/webcam_error__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `expected_color`
// Member `detected_color`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
cobot1_interfaces__msg__WebcamError__init(cobot1_interfaces__msg__WebcamError * msg)
{
  if (!msg) {
    return false;
  }
  // step
  // row
  // col
  // expected_color
  if (!rosidl_runtime_c__String__init(&msg->expected_color)) {
    cobot1_interfaces__msg__WebcamError__fini(msg);
    return false;
  }
  // detected_color
  if (!rosidl_runtime_c__String__init(&msg->detected_color)) {
    cobot1_interfaces__msg__WebcamError__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    cobot1_interfaces__msg__WebcamError__fini(msg);
    return false;
  }
  return true;
}

void
cobot1_interfaces__msg__WebcamError__fini(cobot1_interfaces__msg__WebcamError * msg)
{
  if (!msg) {
    return;
  }
  // step
  // row
  // col
  // expected_color
  rosidl_runtime_c__String__fini(&msg->expected_color);
  // detected_color
  rosidl_runtime_c__String__fini(&msg->detected_color);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
cobot1_interfaces__msg__WebcamError__are_equal(const cobot1_interfaces__msg__WebcamError * lhs, const cobot1_interfaces__msg__WebcamError * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // step
  if (lhs->step != rhs->step) {
    return false;
  }
  // row
  if (lhs->row != rhs->row) {
    return false;
  }
  // col
  if (lhs->col != rhs->col) {
    return false;
  }
  // expected_color
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->expected_color), &(rhs->expected_color)))
  {
    return false;
  }
  // detected_color
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->detected_color), &(rhs->detected_color)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
cobot1_interfaces__msg__WebcamError__copy(
  const cobot1_interfaces__msg__WebcamError * input,
  cobot1_interfaces__msg__WebcamError * output)
{
  if (!input || !output) {
    return false;
  }
  // step
  output->step = input->step;
  // row
  output->row = input->row;
  // col
  output->col = input->col;
  // expected_color
  if (!rosidl_runtime_c__String__copy(
      &(input->expected_color), &(output->expected_color)))
  {
    return false;
  }
  // detected_color
  if (!rosidl_runtime_c__String__copy(
      &(input->detected_color), &(output->detected_color)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

cobot1_interfaces__msg__WebcamError *
cobot1_interfaces__msg__WebcamError__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__WebcamError * msg = (cobot1_interfaces__msg__WebcamError *)allocator.allocate(sizeof(cobot1_interfaces__msg__WebcamError), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot1_interfaces__msg__WebcamError));
  bool success = cobot1_interfaces__msg__WebcamError__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot1_interfaces__msg__WebcamError__destroy(cobot1_interfaces__msg__WebcamError * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot1_interfaces__msg__WebcamError__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot1_interfaces__msg__WebcamError__Sequence__init(cobot1_interfaces__msg__WebcamError__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__WebcamError * data = NULL;

  if (size) {
    data = (cobot1_interfaces__msg__WebcamError *)allocator.zero_allocate(size, sizeof(cobot1_interfaces__msg__WebcamError), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot1_interfaces__msg__WebcamError__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot1_interfaces__msg__WebcamError__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cobot1_interfaces__msg__WebcamError__Sequence__fini(cobot1_interfaces__msg__WebcamError__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cobot1_interfaces__msg__WebcamError__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cobot1_interfaces__msg__WebcamError__Sequence *
cobot1_interfaces__msg__WebcamError__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__WebcamError__Sequence * array = (cobot1_interfaces__msg__WebcamError__Sequence *)allocator.allocate(sizeof(cobot1_interfaces__msg__WebcamError__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot1_interfaces__msg__WebcamError__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot1_interfaces__msg__WebcamError__Sequence__destroy(cobot1_interfaces__msg__WebcamError__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot1_interfaces__msg__WebcamError__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot1_interfaces__msg__WebcamError__Sequence__are_equal(const cobot1_interfaces__msg__WebcamError__Sequence * lhs, const cobot1_interfaces__msg__WebcamError__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot1_interfaces__msg__WebcamError__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot1_interfaces__msg__WebcamError__Sequence__copy(
  const cobot1_interfaces__msg__WebcamError__Sequence * input,
  cobot1_interfaces__msg__WebcamError__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cobot1_interfaces__msg__WebcamError);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot1_interfaces__msg__WebcamError * data =
      (cobot1_interfaces__msg__WebcamError *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot1_interfaces__msg__WebcamError__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot1_interfaces__msg__WebcamError__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot1_interfaces__msg__WebcamError__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
