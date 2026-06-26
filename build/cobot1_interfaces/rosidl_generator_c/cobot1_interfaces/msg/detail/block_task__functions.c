// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot1_interfaces:msg/BlockTask.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/msg/detail/block_task__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `color`
#include "rosidl_runtime_c/string_functions.h"

bool
cobot1_interfaces__msg__BlockTask__init(cobot1_interfaces__msg__BlockTask * msg)
{
  if (!msg) {
    return false;
  }
  // y_position
  // color
  if (!rosidl_runtime_c__String__init(&msg->color)) {
    cobot1_interfaces__msg__BlockTask__fini(msg);
    return false;
  }
  // block_type
  return true;
}

void
cobot1_interfaces__msg__BlockTask__fini(cobot1_interfaces__msg__BlockTask * msg)
{
  if (!msg) {
    return;
  }
  // y_position
  // color
  rosidl_runtime_c__String__fini(&msg->color);
  // block_type
}

bool
cobot1_interfaces__msg__BlockTask__are_equal(const cobot1_interfaces__msg__BlockTask * lhs, const cobot1_interfaces__msg__BlockTask * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // y_position
  if (lhs->y_position != rhs->y_position) {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->color), &(rhs->color)))
  {
    return false;
  }
  // block_type
  if (lhs->block_type != rhs->block_type) {
    return false;
  }
  return true;
}

bool
cobot1_interfaces__msg__BlockTask__copy(
  const cobot1_interfaces__msg__BlockTask * input,
  cobot1_interfaces__msg__BlockTask * output)
{
  if (!input || !output) {
    return false;
  }
  // y_position
  output->y_position = input->y_position;
  // color
  if (!rosidl_runtime_c__String__copy(
      &(input->color), &(output->color)))
  {
    return false;
  }
  // block_type
  output->block_type = input->block_type;
  return true;
}

cobot1_interfaces__msg__BlockTask *
cobot1_interfaces__msg__BlockTask__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__BlockTask * msg = (cobot1_interfaces__msg__BlockTask *)allocator.allocate(sizeof(cobot1_interfaces__msg__BlockTask), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot1_interfaces__msg__BlockTask));
  bool success = cobot1_interfaces__msg__BlockTask__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot1_interfaces__msg__BlockTask__destroy(cobot1_interfaces__msg__BlockTask * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot1_interfaces__msg__BlockTask__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot1_interfaces__msg__BlockTask__Sequence__init(cobot1_interfaces__msg__BlockTask__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__BlockTask * data = NULL;

  if (size) {
    data = (cobot1_interfaces__msg__BlockTask *)allocator.zero_allocate(size, sizeof(cobot1_interfaces__msg__BlockTask), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot1_interfaces__msg__BlockTask__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot1_interfaces__msg__BlockTask__fini(&data[i - 1]);
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
cobot1_interfaces__msg__BlockTask__Sequence__fini(cobot1_interfaces__msg__BlockTask__Sequence * array)
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
      cobot1_interfaces__msg__BlockTask__fini(&array->data[i]);
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

cobot1_interfaces__msg__BlockTask__Sequence *
cobot1_interfaces__msg__BlockTask__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__BlockTask__Sequence * array = (cobot1_interfaces__msg__BlockTask__Sequence *)allocator.allocate(sizeof(cobot1_interfaces__msg__BlockTask__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot1_interfaces__msg__BlockTask__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot1_interfaces__msg__BlockTask__Sequence__destroy(cobot1_interfaces__msg__BlockTask__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot1_interfaces__msg__BlockTask__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot1_interfaces__msg__BlockTask__Sequence__are_equal(const cobot1_interfaces__msg__BlockTask__Sequence * lhs, const cobot1_interfaces__msg__BlockTask__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot1_interfaces__msg__BlockTask__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot1_interfaces__msg__BlockTask__Sequence__copy(
  const cobot1_interfaces__msg__BlockTask__Sequence * input,
  cobot1_interfaces__msg__BlockTask__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cobot1_interfaces__msg__BlockTask);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot1_interfaces__msg__BlockTask * data =
      (cobot1_interfaces__msg__BlockTask *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot1_interfaces__msg__BlockTask__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot1_interfaces__msg__BlockTask__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot1_interfaces__msg__BlockTask__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
