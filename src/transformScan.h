#ifndef TRANSFORM_SCAN
#define TRANSFORM_SCAN

#include <vector>
#include <sensor_msgs/LaserScan.h>
#include "Scan3.h"
using namespace transform {

Scan3* transform_scan(sensor_msgs::LaserScan::ConstPtr &scan, std::vector<float> current);
}
#endif

