// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot1_interfaces:srv/SequencePlan.idl
// generated code does not contain a copyright notice
#include "cobot1_interfaces/srv/detail/sequence_plan__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `colors`
#include "rosidl_runtime_c/string_functions.h"

bool
cobot1_interfaces__srv__SequencePlan_Request__init(cobot1_interfaces__srv__SequencePlan_Request * msg)
{
  if (!msg) {
    return false;
  }
  // colors
  if (!rosidl_runtime_c__String__Sequence__init(&msg->colors, 0)) {
    cobot1_interfaces__srv__SequencePlan_Request__fini(msg);
    return false;
  }
  // grid_width
  // grid_height
  return true;
}

void
cobot1_interfaces__srv__SequencePlan_Request__fini(cobot1_interfaces__srv__SequencePlan_Request * msg)
{
  if (!msg) {
    return;
  }
  // colors
  rosidl_runtime_c__String__Sequence__fini(&msg->colors);
  // grid_width
  // grid_height
}

bool
cobot1_interfaces__srv__SequencePlan_Request__are_equal(const cobot1_interfaces__srv__SequencePlan_Request * lhs, const cobot1_interfaces__srv__SequencePlan_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // colors
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->colors), &(rhs->colors)))
  {
    return false;
  }
  // grid_width
  if (lhs->grid_width != rhs->grid_width) {
    return false;
  }
  // grid_height
  if (lhs->grid_height != rhs->grid_height) {
    return false;
  }
  return true;
}

bool
cobot1_interfaces__srv__SequencePlan_Request__copy(
  const cobot1_interfaces__srv__SequencePlan_Request * input,
  cobot1_interfaces__srv__SequencePlan_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // colors
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->colors), &(output->colors)))
  {
    return false;
  }
  // grid_width
  output->grid_width = input->grid_width;
  // grid_height
  output->grid_height = input->grid_height;
  return true;
}

cobot1_interfaces__srv__SequencePlan_Request *
cobot1_interfaces__srv__SequencePlan_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__srv__SequencePlan_Request * msg = (cobot1_interfaces__srv__SequencePlan_Request *)allocator.allocate(sizeof(cobot1_interfaces__srv__SequencePlan_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot1_interfaces__srv__SequencePlan_Request));
  bool success = cobot1_interfaces__srv__SequencePlan_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot1_interfaces__srv__SequencePlan_Request__destroy(cobot1_interfaces__srv__SequencePlan_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot1_interfaces__srv__SequencePlan_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot1_interfaces__srv__SequencePlan_Request__Sequence__init(cobot1_interfaces__srv__SequencePlan_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__srv__SequencePlan_Request * data = NULL;

  if (size) {
    data = (cobot1_interfaces__srv__SequencePlan_Request *)allocator.zero_allocate(size, sizeof(cobot1_interfaces__srv__SequencePlan_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot1_interfaces__srv__SequencePlan_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot1_interfaces__srv__SequencePlan_Request__fini(&data[i - 1]);
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
cobot1_interfaces__srv__SequencePlan_Request__Sequence__fini(cobot1_interfaces__srv__SequencePlan_Request__Sequence * array)
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
      cobot1_interfaces__srv__SequencePlan_Request__fini(&array->data[i]);
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

cobot1_interfaces__srv__SequencePlan_Request__Sequence *
cobot1_interfaces__srv__SequencePlan_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__srv__SequencePlan_Request__Sequence * array = (cobot1_interfaces__srv__SequencePlan_Request__Sequence *)allocator.allocate(sizeof(cobot1_interfaces__srv__SequencePlan_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot1_interfaces__srv__SequencePlan_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot1_interfaces__srv__SequencePlan_Request__Sequence__destroy(cobot1_interfaces__srv__SequencePlan_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot1_interfaces__srv__SequencePlan_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot1_interfaces__srv__SequencePlan_Request__Sequence__are_equal(const cobot1_interfaces__srv__SequencePlan_Request__Sequence * lhs, const cobot1_interfaces__srv__SequencePlan_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot1_interfaces__srv__SequencePlan_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot1_interfaces__srv__SequencePlan_Request__Sequence__copy(
  const cobot1_interfaces__srv__SequencePlan_Request__Sequence * input,
  cobot1_interfaces__srv__SequencePlan_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cobot1_interfaces__srv__SequencePlan_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot1_interfaces__srv__SequencePlan_Request * data =
      (cobot1_interfaces__srv__SequencePlan_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot1_interfaces__srv__SequencePlan_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot1_interfaces__srv__SequencePlan_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot1_interfaces__srv__SequencePlan_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `error_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `tasks`
#include "cobot1_interfaces/msg/detail/block_task__functions.h"

bool
cobot1_interfaces__srv__SequencePlan_Response__init(cobot1_interfaces__srv__SequencePlan_Response * msg)
{
  if (!msg) {
    return false;
  }
  // error_message
  if (!rosidl_runtime_c__String__init(&msg->error_message)) {
    cobot1_interfaces__srv__SequencePlan_Response__fini(msg);
    return false;
  }
  // tasks
  if (!cobot1_interfaces__msg__BlockTask__Sequence__init(&msg->tasks, 0)) {
    cobot1_interfaces__srv__SequencePlan_Response__fini(msg);
    return false;
  }
  return true;
}

void
cobot1_interfaces__srv__SequencePlan_Response__fini(cobot1_interfaces__srv__SequencePlan_Response * msg)
{
  if (!msg) {
    return;
  }
  // error_message
  rosidl_runtime_c__String__fini(&msg->error_message);
  // tasks
  cobot1_interfaces__msg__BlockTask__Sequence__fini(&msg->tasks);
}

bool
cobot1_interfaces__srv__SequencePlan_Response__are_equal(const cobot1_interfaces__srv__SequencePlan_Response * lhs, const cobot1_interfaces__srv__SequencePlan_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // error_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->error_message), &(rhs->error_message)))
  {
    return false;
  }
  // tasks
  if (!cobot1_interfaces__msg__BlockTask__Sequence__are_equal(
      &(lhs->tasks), &(rhs->tasks)))
  {
    return false;
  }
  return true;
}

bool
cobot1_interfaces__srv__SequencePlan_Response__copy(
  const cobot1_interfaces__srv__SequencePlan_Response * input,
  cobot1_interfaces__srv__SequencePlan_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // error_message
  if (!rosidl_runtime_c__String__copy(
      &(input->error_message), &(output->error_message)))
  {
    return false;
  }
  // tasks
  if (!cobot1_interfaces__msg__BlockTask__Sequence__copy(
      &(input->tasks), &(output->tasks)))
  {
    return false;
  }
  return true;
}

cobot1_interfaces__srv__SequencePlan_Response *
cobot1_interfaces__srv__SequencePlan_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__srv__SequencePlan_Response * msg = (cobot1_interfaces__srv__SequencePlan_Response *)allocator.allocate(sizeof(cobot1_interfaces__srv__SequencePlan_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot1_interfaces__srv__SequencePlan_Response));
  bool success = cobot1_interfaces__srv__SequencePlan_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot1_interfaces__srv__SequencePlan_Response__destroy(cobot1_interfaces__srv__SequencePlan_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot1_interfaces__srv__SequencePlan_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot1_interfaces__srv__SequencePlan_Response__Sequence__init(cobot1_interfaces__srv__SequencePlan_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__srv__SequencePlan_Response * data = NULL;

  if (size) {
    data = (cobot1_interfaces__srv__SequencePlan_Response *)allocator.zero_allocate(size, sizeof(cobot1_interfaces__srv__SequencePlan_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot1_interfaces__srv__SequencePlan_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot1_interfaces__srv__SequencePlan_Response__fini(&data[i - 1]);
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
cobot1_interfaces__srv__SequencePlan_Response__Sequence__fini(cobot1_interfaces__srv__SequencePlan_Response__Sequence * array)
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
      cobot1_interfaces__srv__SequencePlan_Response__fini(&array->data[i]);
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

cobot1_interfaces__srv__SequencePlan_Response__Sequence *
cobot1_interfaces__srv__SequencePlan_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot1_interfaces__srv__SequencePlan_Response__Sequence * array = (cobot1_interfaces__srv__SequencePlan_Response__Sequence *)allocator.allocate(sizeof(cobot1_interfaces__srv__SequencePlan_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot1_interfaces__srv__SequencePlan_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot1_interfaces__srv__SequencePlan_Response__Sequence__destroy(cobot1_interfaces__srv__SequencePlan_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot1_interfaces__srv__SequencePlan_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot1_interfaces__srv__SequencePlan_Response__Sequence__are_equal(const cobot1_interfaces__srv__SequencePlan_Response__Sequence * lhs, const cobot1_interfaces__srv__SequencePlan_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot1_interfaces__srv__SequencePlan_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot1_interfaces__srv__SequencePlan_Response__Sequence__copy(
  const cobot1_interfaces__srv__SequencePlan_Response__Sequence * input,
  cobot1_interfaces__srv__SequencePlan_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cobot1_interfaces__srv__SequencePlan_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot1_interfaces__srv__SequencePlan_Response * data =
      (cobot1_interfaces__srv__SequencePlan_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot1_interfaces__srv__SequencePlan_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot1_interfaces__srv__SequencePlan_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot1_interfaces__srv__SequencePlan_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
