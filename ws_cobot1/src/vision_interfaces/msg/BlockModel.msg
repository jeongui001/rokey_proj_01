# N x N block model generated from a segmented source image or observed camera frame.
std_msgs/Header header
string model_id

string segmentation_backend
string segmentation_model
uint32 source_width
uint32 source_height

uint32 grid_size
uint32 output_width
uint32 output_height
string fixed_axis
float64 fixed_axis_value

vision_interfaces/SegmentationInstance[] instances
vision_interfaces/BlockCell[] cells
