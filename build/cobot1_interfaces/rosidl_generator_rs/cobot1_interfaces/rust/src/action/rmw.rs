
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_Goal() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_Goal__init(msg: *mut Assembly_Goal) -> bool;
    fn cobot1_interfaces__action__Assembly_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_Goal>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_Goal>);
    fn cobot1_interfaces__action__Assembly_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_Goal>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks: rosidl_runtime_rs::Sequence<super::super::msg::rmw::BlockTask>,

}



impl Default for Assembly_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_Goal__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_Goal() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_Result() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_Result__init(msg: *mut Assembly_Result) -> bool;
    fn cobot1_interfaces__action__Assembly_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_Result>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_Result>);
    fn cobot1_interfaces__action__Assembly_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_Result>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_step: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_message: rosidl_runtime_rs::String,

}



impl Default for Assembly_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_Result__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_Result where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_Result() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_Feedback__init(msg: *mut Assembly_Feedback) -> bool;
    fn cobot1_interfaces__action__Assembly_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_Feedback>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_Feedback>);
    fn cobot1_interfaces__action__Assembly_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_Feedback>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub current_index: i32,

}



impl Default for Assembly_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_Feedback__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_Feedback() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_FeedbackMessage__init(msg: *mut Assembly_FeedbackMessage) -> bool;
    fn cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_FeedbackMessage>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_FeedbackMessage>);
    fn cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_FeedbackMessage>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::Assembly_Feedback,

}



impl Default for Assembly_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_FeedbackMessage() }
  }
}




#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_SendGoal_Request__init(msg: *mut Assembly_SendGoal_Request) -> bool;
    fn cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_SendGoal_Request>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_SendGoal_Request>);
    fn cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_SendGoal_Request>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::Assembly_Goal,

}



impl Default for Assembly_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_SendGoal_Request() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_SendGoal_Response__init(msg: *mut Assembly_SendGoal_Response) -> bool;
    fn cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_SendGoal_Response>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_SendGoal_Response>);
    fn cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_SendGoal_Response>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for Assembly_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_SendGoal_Response() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_GetResult_Request__init(msg: *mut Assembly_GetResult_Request) -> bool;
    fn cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_GetResult_Request>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_GetResult_Request>);
    fn cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_GetResult_Request>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for Assembly_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_GetResult_Request() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__action__Assembly_GetResult_Response__init(msg: *mut Assembly_GetResult_Response) -> bool;
    fn cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Assembly_GetResult_Response>, size: usize) -> bool;
    fn cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Assembly_GetResult_Response>);
    fn cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Assembly_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Assembly_GetResult_Response>) -> bool;
}

// Corresponds to cobot1_interfaces__action__Assembly_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Assembly_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::Assembly_Result,

}



impl Default for Assembly_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__action__Assembly_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__action__Assembly_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Assembly_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__action__Assembly_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Assembly_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Assembly_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/action/Assembly_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__action__Assembly_GetResult_Response() }
  }
}






#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__action__Assembly_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to cobot1_interfaces__action__Assembly_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct Assembly_SendGoal;

impl rosidl_runtime_rs::Service for Assembly_SendGoal {
    type Request = Assembly_SendGoal_Request;
    type Response = Assembly_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__action__Assembly_SendGoal() }
    }
}




#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__action__Assembly_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to cobot1_interfaces__action__Assembly_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct Assembly_GetResult;

impl rosidl_runtime_rs::Service for Assembly_GetResult {
    type Request = Assembly_GetResult_Request;
    type Response = Assembly_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__action__Assembly_GetResult() }
    }
}


