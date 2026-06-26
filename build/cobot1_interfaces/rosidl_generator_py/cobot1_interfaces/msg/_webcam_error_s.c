// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from cobot1_interfaces:msg/WebcamError.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "cobot1_interfaces/msg/detail/webcam_error__struct.h"
#include "cobot1_interfaces/msg/detail/webcam_error__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool cobot1_interfaces__msg__webcam_error__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[48];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("cobot1_interfaces.msg._webcam_error.WebcamError", full_classname_dest, 47) == 0);
  }
  cobot1_interfaces__msg__WebcamError * ros_message = _ros_message;
  {  // step
    PyObject * field = PyObject_GetAttrString(_pymsg, "step");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->step = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // row
    PyObject * field = PyObject_GetAttrString(_pymsg, "row");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->row = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // col
    PyObject * field = PyObject_GetAttrString(_pymsg, "col");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->col = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // expected_color
    PyObject * field = PyObject_GetAttrString(_pymsg, "expected_color");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->expected_color, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // detected_color
    PyObject * field = PyObject_GetAttrString(_pymsg, "detected_color");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->detected_color, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // message
    PyObject * field = PyObject_GetAttrString(_pymsg, "message");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->message, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * cobot1_interfaces__msg__webcam_error__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of WebcamError */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("cobot1_interfaces.msg._webcam_error");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "WebcamError");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  cobot1_interfaces__msg__WebcamError * ros_message = (cobot1_interfaces__msg__WebcamError *)raw_ros_message;
  {  // step
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->step);
    {
      int rc = PyObject_SetAttrString(_pymessage, "step", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // row
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->row);
    {
      int rc = PyObject_SetAttrString(_pymessage, "row", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // col
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->col);
    {
      int rc = PyObject_SetAttrString(_pymessage, "col", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // expected_color
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->expected_color.data,
      strlen(ros_message->expected_color.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "expected_color", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // detected_color
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->detected_color.data,
      strlen(ros_message->detected_color.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "detected_color", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // message
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->message.data,
      strlen(ros_message->message.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "message", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
