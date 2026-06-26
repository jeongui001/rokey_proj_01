#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to cobot1_interfaces__msg__WebcamError

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub expected_color: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detected_color: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for WebcamError {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::WebcamError::default())
  }
}

impl rosidl_runtime_rs::Message for WebcamError {
  type RmwMsg = super::msg::rmw::WebcamError;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        step: msg.step,
        row: msg.row,
        col: msg.col,
        expected_color: msg.expected_color.as_str().into(),
        detected_color: msg.detected_color.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      step: msg.step,
      row: msg.row,
      col: msg.col,
        expected_color: msg.expected_color.as_str().into(),
        detected_color: msg.detected_color.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      step: msg.step,
      row: msg.row,
      col: msg.col,
      expected_color: msg.expected_color.to_string(),
      detected_color: msg.detected_color.to_string(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to cobot1_interfaces__msg__ExpectedModel

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExpectedModel {

    // This member is not documented.
    #[allow(missing_docs)]
    pub grid_size: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub colors: Vec<std::string::String>,

}



impl Default for ExpectedModel {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ExpectedModel::default())
  }
}

impl rosidl_runtime_rs::Message for ExpectedModel {
  type RmwMsg = super::msg::rmw::ExpectedModel;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        grid_size: msg.grid_size,
        colors: msg.colors
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      grid_size: msg.grid_size,
        colors: msg.colors
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      grid_size: msg.grid_size,
      colors: msg.colors
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
    }
  }
}


// Corresponds to cobot1_interfaces__msg__BlockTask

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockTask {

    // This member is not documented.
    #[allow(missing_docs)]
    pub y_position: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub color: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub block_type: u8,

}



impl Default for BlockTask {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BlockTask::default())
  }
}

impl rosidl_runtime_rs::Message for BlockTask {
  type RmwMsg = super::msg::rmw::BlockTask;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        y_position: msg.y_position,
        color: msg.color.as_str().into(),
        block_type: msg.block_type,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      y_position: msg.y_position,
        color: msg.color.as_str().into(),
      block_type: msg.block_type,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      y_position: msg.y_position,
      color: msg.color.to_string(),
      block_type: msg.block_type,
    }
  }
}


