# One instance produced by the configured instance-segmentation backend.
uint32 instance_id
int32 class_id
string class_name
float32 confidence

# Bounding box and centroid are expressed in pixels of BlockModel.source_width/height.
sensor_msgs/RegionOfInterest roi
geometry_msgs/Point32 centroid
uint32 mask_area

# Largest approximated mask contour in source-image pixel coordinates.
geometry_msgs/Polygon contour

# Representative block colour assigned from class mapping or masked pixels.
string color
std_msgs/ColorRGBA rgba
float32 color_confidence
