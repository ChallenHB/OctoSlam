#ifndef TRANSFORM_SCAN
#define TRANSFORM_SCAN

#include <vector>
#include <sensor_msgs/LaserScan.h>
#include "Scan3.h"
namespace transform {

    Scan3* transform_scan(const sensor_msgs::LaserScan::ConstPtr &scan, std::vector<double> current);
}
#endif

