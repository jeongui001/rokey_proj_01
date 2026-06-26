#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to cobot1_interfaces__srv__ProcessMosaic_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ProcessMosaic_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub input_image: sensor_msgs::msg::Image,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_rows: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_cols: u32,

}



impl Default for ProcessMosaic_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ProcessMosaic_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ProcessMosaic_Request {
  type RmwMsg = super::srv::rmw::ProcessMosaic_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        input_image: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Owned(msg.input_image)).into_owned(),
        grid_rows: msg.grid_rows,
        grid_cols: msg.grid_cols,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        input_image: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Borrowed(&msg.input_image)).into_owned(),
      grid_rows: msg.grid_rows,
      grid_cols: msg.grid_cols,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      input_image: sensor_msgs::msg::Image::from_rmw_message(msg.input_image),
      grid_rows: msg.grid_rows,
      grid_cols: msg.grid_cols,
    }
  }
}


// Corresponds to cobot1_interfaces__srv__ProcessMosaic_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ProcessMosaic_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub colors: Vec<std::string::String>,

}



impl Default for ProcessMosaic_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ProcessMosaic_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ProcessMosaic_Response {
  type RmwMsg = super::srv::rmw::ProcessMosaic_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
        colors: msg.colors
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
        colors: msg.colors
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
      colors: msg.colors
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
    }
  }
}


// Corresponds to cobot1_interfaces__srv__SequencePlan_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SequencePlan_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub colors: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_width: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_height: u32,

}



impl Default for SequencePlan_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SequencePlan_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SequencePlan_Request {
  type RmwMsg = super::srv::rmw::SequencePlan_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        colors: msg.colors
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        grid_width: msg.grid_width,
        grid_height: msg.grid_height,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        colors: msg.colors
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      grid_width: msg.grid_width,
      grid_height: msg.grid_height,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      colors: msg.colors
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      grid_width: msg.grid_width,
      grid_height: msg.grid_height,
    }
  }
}


// Corresponds to cobot1_interfaces__srv__SequencePlan_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SequencePlan_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub error_message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks: Vec<super::msg::BlockTask>,

}



impl Default for SequencePlan_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SequencePlan_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SequencePlan_Response {
  type RmwMsg = super::srv::rmw::SequencePlan_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        error_message: msg.error_message.as_str().into(),
        tasks: msg.tasks
          .into_iter()
          .map(|elem| super::msg::BlockTask::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        error_message: msg.error_message.as_str().into(),
        tasks: msg.tasks
          .iter()
          .map(|elem| super::msg::BlockTask::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      error_message: msg.error_message.to_string(),
      tasks: msg.tasks
          .into_iter()
          .map(super::msg::BlockTask::from_rmw_message)
          .collect(),
    }
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


