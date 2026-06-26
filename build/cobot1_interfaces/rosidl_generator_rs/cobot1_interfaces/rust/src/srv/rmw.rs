#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__ProcessMosaic_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__srv__ProcessMosaic_Request__init(msg: *mut ProcessMosaic_Request) -> bool;
    fn cobot1_interfaces__srv__ProcessMosaic_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ProcessMosaic_Request>, size: usize) -> bool;
    fn cobot1_interfaces__srv__ProcessMosaic_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ProcessMosaic_Request>);
    fn cobot1_interfaces__srv__ProcessMosaic_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ProcessMosaic_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ProcessMosaic_Request>) -> bool;
}

// Corresponds to cobot1_interfaces__srv__ProcessMosaic_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ProcessMosaic_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub input_image: sensor_msgs::msg::rmw::Image,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_rows: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_cols: u32,

}



impl Default for ProcessMosaic_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__srv__ProcessMosaic_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__srv__ProcessMosaic_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ProcessMosaic_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__ProcessMosaic_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__ProcessMosaic_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__ProcessMosaic_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ProcessMosaic_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ProcessMosaic_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/srv/ProcessMosaic_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__ProcessMosaic_Request() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__ProcessMosaic_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__srv__ProcessMosaic_Response__init(msg: *mut ProcessMosaic_Response) -> bool;
    fn cobot1_interfaces__srv__ProcessMosaic_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ProcessMosaic_Response>, size: usize) -> bool;
    fn cobot1_interfaces__srv__ProcessMosaic_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ProcessMosaic_Response>);
    fn cobot1_interfaces__srv__ProcessMosaic_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ProcessMosaic_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ProcessMosaic_Response>) -> bool;
}

// Corresponds to cobot1_interfaces__srv__ProcessMosaic_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ProcessMosaic_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub colors: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

}



impl Default for ProcessMosaic_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__srv__ProcessMosaic_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__srv__ProcessMosaic_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ProcessMosaic_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__ProcessMosaic_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__ProcessMosaic_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__ProcessMosaic_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ProcessMosaic_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ProcessMosaic_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/srv/ProcessMosaic_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__ProcessMosaic_Response() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__SequencePlan_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__srv__SequencePlan_Request__init(msg: *mut SequencePlan_Request) -> bool;
    fn cobot1_interfaces__srv__SequencePlan_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SequencePlan_Request>, size: usize) -> bool;
    fn cobot1_interfaces__srv__SequencePlan_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SequencePlan_Request>);
    fn cobot1_interfaces__srv__SequencePlan_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SequencePlan_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SequencePlan_Request>) -> bool;
}

// Corresponds to cobot1_interfaces__srv__SequencePlan_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SequencePlan_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub colors: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_width: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_height: u32,

}



impl Default for SequencePlan_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__srv__SequencePlan_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__srv__SequencePlan_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SequencePlan_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__SequencePlan_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__SequencePlan_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__SequencePlan_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SequencePlan_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SequencePlan_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/srv/SequencePlan_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__SequencePlan_Request() }
  }
}


#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__SequencePlan_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot1_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot1_interfaces__srv__SequencePlan_Response__init(msg: *mut SequencePlan_Response) -> bool;
    fn cobot1_interfaces__srv__SequencePlan_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SequencePlan_Response>, size: usize) -> bool;
    fn cobot1_interfaces__srv__SequencePlan_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SequencePlan_Response>);
    fn cobot1_interfaces__srv__SequencePlan_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SequencePlan_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SequencePlan_Response>) -> bool;
}

// Corresponds to cobot1_interfaces__srv__SequencePlan_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SequencePlan_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub error_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks: rosidl_runtime_rs::Sequence<super::super::msg::rmw::BlockTask>,

}



impl Default for SequencePlan_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot1_interfaces__srv__SequencePlan_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot1_interfaces__srv__SequencePlan_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SequencePlan_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__SequencePlan_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__SequencePlan_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot1_interfaces__srv__SequencePlan_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SequencePlan_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SequencePlan_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot1_interfaces/srv/SequencePlan_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot1_interfaces__srv__SequencePlan_Response() }
  }
}






#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__srv__ProcessMosaic() -> *const std::ffi::c_void;
}

// Corresponds to cobot1_interfaces__srv__ProcessMosaic
#[allow(missing_docs, non_camel_case_types)]
pub struct ProcessMosaic;

impl rosidl_runtime_rs::Service for ProcessMosaic {
    type Request = ProcessMosaic_Request;
    type Response = ProcessMosaic_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__srv__ProcessMosaic() }
    }
}




#[link(name = "cobot1_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__srv__SequencePlan() -> *const std::ffi::c_void;
}

// Corresponds to cobot1_interfaces__srv__SequencePlan
#[allow(missing_docs, non_camel_case_types)]
pub struct SequencePlan;

impl rosidl_runtime_rs::Service for SequencePlan {
    type Request = SequencePlan_Request;
    type Response = SequencePlan_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot1_interfaces__srv__SequencePlan() }
    }
}


