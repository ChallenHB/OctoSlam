#include <Eigen/Dense>
#include <sensor_msgs/LaserScan.h>

namespace scanTransform {
    transformScan (sensor_msgs::LaserScan::ConstPtr &scan, double[] current) {
        // change the points from polar to cartesian in the plane 3x1
        // rotate by the yaw angle 3x3 * 3x1
        // rotate by IMU angles (same as above)
        // translate by coordinates 3x1 = 3x4 * 4x1

