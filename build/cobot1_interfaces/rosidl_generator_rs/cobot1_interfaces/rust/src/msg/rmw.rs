#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__msg__WebcamError() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__msg__WebcamError__init(msg: *mut WebcamError) -> bool;
    fn cobot1_interfaces__msg__WebcamError__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<WebcamError>, size: usize) -> bool;
    fn cobot1_interfaces__msg__WebcamError__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<WebcamError>);
    fn cobot1_interfaces__msg__WebcamError__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<WebcamError>, out_seq: *mut rosidl_runtime_rs::Sequence<WebcamError>) -> bool;
}

// Corresponds to cobot1_interfaces__msg__WebcamError
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct WebcamError {

    // This member is not documented.
    #[allow(missing_docs)]
    pub step: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub row: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub col: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub expected_color: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detected_color: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for WebcamError {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__msg__WebcamError__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__msg__WebcamError__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for WebcamError {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__WebcamError__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__WebcamError__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__WebcamError__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for WebcamError {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for WebcamError where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/msg/WebcamError";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__msg__WebcamError() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__msg__ExpectedModel() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__msg__ExpectedModel__init(msg: *mut ExpectedModel) -> bool;
    fn cobot1_interfaces__msg__ExpectedModel__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExpectedModel>, size: usize) -> bool;
    fn cobot1_interfaces__msg__ExpectedModel__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExpectedModel>);
    fn cobot1_interfaces__msg__ExpectedModel__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExpectedModel>, out_seq: *mut rosidl_runtime_rs::Sequence<ExpectedModel>) -> bool;
}

// Corresponds to cobot1_interfaces__msg__ExpectedModel
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExpectedModel {

    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_size: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub colors: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

}



impl Default for ExpectedModel {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__msg__ExpectedModel__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__msg__ExpectedModel__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExpectedModel {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__ExpectedModel__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__ExpectedModel__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__ExpectedModel__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExpectedModel {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExpectedModel where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/msg/ExpectedModel";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__msg__ExpectedModel() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__msg__BlockTask() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__msg__BlockTask__init(msg: *mut BlockTask) -> bool;
    fn cobot1_interfaces__msg__BlockTask__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BlockTask>, size: usize) -> bool;
    fn cobot1_interfaces__msg__BlockTask__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BlockTask>);
    fn cobot1_interfaces__msg__BlockTask__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BlockTask>, out_seq: *mut rosidl_runtime_rs::Sequence<BlockTask>) -> bool;
}

// Corresponds to cobot1_interfaces__msg__BlockTask
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockTask {

    // This member is not documented.
    #[allow(missing_docs)]
    pub y_position: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub color: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub block_type: u8,

}



impl Default for BlockTask {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__msg__BlockTask__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__msg__BlockTask__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BlockTask {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__BlockTask__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__BlockTask__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__msg__BlockTask__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BlockTask {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BlockTask where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/msg/BlockTask";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__msg__BlockTask() }
  }
}


