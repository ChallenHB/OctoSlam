#include <ros/ros.h>
#include <vector>
#include <geometry_msgs/TransformStamped.h>
#include <cmath>
#include "Scan3.h"
#include "transformScan.h"

class TestCode {
    private:
        ros::NodeHandle node;
        ros::Subscriber vrpn_sub;
        ros::Subscriber scan_sub;
        std::vector<double> current_pose;
    
    public:
        TestCode(ros::NodeHandle n): node(n) {
            vrpn_sub = node.subscribe("Brain5/pose", 1000, vrpn_callback);
            scan_sub = node.subscribe("scan", 1000, scan_callback);
        }

        void vrpn_callback(geometry_msgs::TransformStamped::ConstPtr &pose) {
            current_pose.at(0) = pose.transform.translation.x;
            current_pose.at(1) = pose.transform.translation.y;
            current_pose.at(2) = pose.transform.translation.z;
            double q1 = pose.transform.rotation.x;
            double q2 = pose.transform.rotation.y;
            double q3 = pose.transform.rotation.z;
            double q0 = pose.transform.rotation.w;
            double rolltop = 2 * (q0 * q1 + q2 * q3);
            double rollbot = 1 - 2 * (pow(q1, 2) + pow(q2, 2));
            double pitchnum = 2 * (q0 * q2 - q3 * q1);
            double yawtop = 2 * (q0 * q3 + q1 * q2);
            double yawbot = 1 - 2 * (pow(q2, 2) + pow(q3, 2));
            current_pose.at(3) = atan2(rolltop, rollbot);
            current_pose.at(4) = asin(pitchnum);
            current_pose.at(5) = atan(yawtop, yawbot);
        }

        void scan_callback(sensor_msgs::LaserScan::ConstPtr &scan) {
            Scan3* new_pose = transform::transform_scan(scan, current_pose);
            new_pose.print();
        }
    
int main(int argc, char** argv) {
    // subscriber code is now taken care of, now just need to write main code initalization TestCode    
}
