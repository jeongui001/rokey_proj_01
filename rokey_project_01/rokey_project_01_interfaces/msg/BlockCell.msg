# One logical block/cell in an N x N model.
uint32 index
uint32 row
uint32 col

string color
std_msgs/ColorRGBA rgba
bool occupied
float32 confidence

# Dominant instance assigned to this cell. -1 means no instance.
int32 instance_id
int32 class_id
string class_name
float32 instance_confidence

# Fraction of this cell covered by the dominant mask, in [0, 1].
float32 mask_coverage

# Number of instance masks that substantially overlap this cell.
uint32 overlapping_instances

# Cell centre in BlockModel source-image coordinates.
float32 source_u
float32 source_v

# Dominant instance centroid in BlockModel source-image coordinates.
# NaN when this cell is empty.
float32 instance_centroid_u
float32 instance_centroid_v

# Centroid distance from this cell centre, normalized by half-cell size.
# 0 means centred. NaN when this cell is empty.
float32 centroid_offset_ratio

# Pixel centre of the corresponding physical assembly cell in the rectified front-camera image.
float32 camera_u
float32 camera_v

# Pick/place centre represented in the robot base frame.
# frame_id is empty and coordinates are NaN when coordinate calculation was not requested.
geometry_msgs/PointStamped target
