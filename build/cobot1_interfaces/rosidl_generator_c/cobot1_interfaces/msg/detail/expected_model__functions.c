// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot1_interfaces:msg/ExpectedModel.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/msg/detail/expected_model__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `colors`
#include "rosidl_runtime_c/string_functions.h"

bool
cobot1_interfaces__msg__ExpectedModel__init(cobot1_interfaces__msg__ExpectedModel * msg)
{
  if (!msg) {
    return false;
  }
  // grid_size
  // colors
  if (!rosidl_runtime_c__String__Sequence__init(&msg->colors, 0)) {
    cobot1_interfaces__msg__ExpectedModel__fini(msg);
    return false;
  }
  return true;
}

void
cobot1_interfaces__msg__ExpectedModel__fini(cobot1_interfaces__msg__ExpectedModel * msg)
{
  if (!msg) {
    return;
  }
  // grid_size
  // colors
  rosidl_runtime_c__String__Sequence__fini(&msg->colors);
}

bool
cobot1_interfaces__msg__ExpectedModel__are_equal(const cobot1_interfaces__msg__ExpectedModel * lhs, const cobot1_interfaces__msg__ExpectedModel * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // grid_size
  if (lhs->grid_size != rhs->grid_size) {
    return false;
  }
  // colors
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->colors), &(rhs->colors)))
  {
    return false;
  }
  return true;
}

bool
cobot1_interfaces__msg__ExpectedModel__copy(
  const cobot1_interfaces__msg__ExpectedModel * input,
  cobot1_interfaces__msg__ExpectedModel * output)
{
  if (!input || !output) {
    return false;
  }
  // grid_size
  output->grid_size = input->grid_size;
  // colors
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->colors), &(output->colors)))
  {
    return false;
  }
  return true;
}

cobot1_interfaces__msg__ExpectedModel *
cobot1_interfaces__msg__ExpectedModel__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__ExpectedModel * msg = (cobot1_interfaces__msg__ExpectedModel *)allocator.allocate(sizeof(cobot1_interfaces__msg__ExpectedModel), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot1_interfaces__msg__ExpectedModel));
  bool success = cobot1_interfaces__msg__ExpectedModel__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot1_interfaces__msg__ExpectedModel__destroy(cobot1_interfaces__msg__ExpectedModel * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot1_interfaces__msg__ExpectedModel__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot1_interfaces__msg__ExpectedModel__Sequence__init(cobot1_interfaces__msg__ExpectedModel__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__ExpectedModel * data = NULL;

  if (size) {
    data = (cobot1_interfaces__msg__ExpectedModel *)allocator.zero_allocate(size, sizeof(cobot1_interfaces__msg__ExpectedModel), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot1_interfaces__msg__ExpectedModel__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot1_interfaces__msg__ExpectedModel__fini(&data[i - 1]);
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
cobot1_interfaces__msg__ExpectedModel__Sequence__fini(cobot1_interfaces__msg__ExpectedModel__Sequence * array)
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
      cobot1_interfaces__msg__ExpectedModel__fini(&array->data[i]);
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

cobot1_interfaces__msg__ExpectedModel__Sequence *
cobot1_interfaces__msg__ExpectedModel__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__msg__ExpectedModel__Sequence * array = (cobot1_interfaces__msg__ExpectedModel__Sequence *)allocator.allocate(sizeof(cobot1_interfaces__msg__ExpectedModel__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot1_interfaces__msg__ExpectedModel__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot1_interfaces__msg__ExpectedModel__Sequence__destroy(cobot1_interfaces__msg__ExpectedModel__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot1_interfaces__msg__ExpectedModel__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot1_interfaces__msg__ExpectedModel__Sequence__are_equal(const cobot1_interfaces__msg__ExpectedModel__Sequence * lhs, const cobot1_interfaces__msg__ExpectedModel__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot1_interfaces__msg__ExpectedModel__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot1_interfaces__msg__ExpectedModel__Sequence__copy(
  const cobot1_interfaces__msg__ExpectedModel__Sequence * input,
  cobot1_interfaces__msg__ExpectedModel__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cobot1_interfaces__msg__ExpectedModel);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot1_interfaces__msg__ExpectedModel * data =
      (cobot1_interfaces__msg__ExpectedModel *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot1_interfaces__msg__ExpectedModel__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot1_interfaces__msg__ExpectedModel__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot1_interfaces__msg__ExpectedModel__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
