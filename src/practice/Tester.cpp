#include <ros/ros.h>
#include <vector>
#include <geometry_msgs/TransformStamped.h>
#include <cmath>
#include "Scan3.h"
#include "transformScan.h"
// This class is used to test to see if the code performs the Transform correctly
class TestTransform {
    private:
        ros::NodeHandle node;
        ros::Subscriber vrpn_sub;
        ros::Subscriber scan_sub;
        std::vector<double> current_pose;
    
    public:
        TestTransform(ros::NodeHandle n): node(n) {
            current_pose.resize(6);
            vrpn_sub = node.subscribe("Brain5/pose", 1000, &TestTransform::vrpn_callback, this);
            scan_sub = node.subscribe("scan", 1000, &TestTransform::scan_callback, this);
        }

        void vrpn_callback(const geometry_msgs::TransformStamped::ConstPtr &pose) {
            current_pose.at(0) = pose->transform.translation.x;
            current_pose.at(1) = pose->transform.translation.y;
            current_pose.at(2) = pose->transform.translation.z;
            double q1 = pose->transform.rotation.x;
            double q2 = pose->transform.rotation.y;
            double q3 = pose->transform.rotation.z;
            double q0 = pose->transform.rotation.w;
            double rolltop = 2 * (q0 * q1 + q2 * q3);
            double rollbot = 1 - 2 * (pow(q1, 2) + pow(q2, 2));
            double pitchnum = 2 * (q0 * q2 - q3 * q1);
            double yawtop = 2 * (q0 * q3 + q1 * q2);
            double yawbot = 1 - 2 * (pow(q2, 2) + pow(q3, 2));
            current_pose.at(3) = atan2(rolltop, rollbot);
            current_pose.at(4) = asin(pitchnum);
            current_pose.at(5) = atan2(yawtop, yawbot);
        }

        void scan_callback(const sensor_msgs::LaserScan::ConstPtr &scan) {
            Scan3 new_pose = transform::transform_scan(scan, current_pose);
            new_pose.print();
        }
};
// This class tests to see if the transform crashes when it's run
class TestCrash {
	private:
		ros::NodeHandle node;
		ros::Subscriber scan_sub;
		std::vector<double> const_pose;

	public:
		TestCrash(ros::NodeHandle n): node(n) {
		    const_pose.push_back(0);
            const_pose.push_back(1); 
            const_pose.push_back(2);
            const_pose.push_back(3);
            const_pose.push_back(4);
            const_pose.push_back(5);
			scan_sub = node.subscribe("scan", 1000, &TestCrash::callback, this);
		}
	
		void callback(const sensor_msgs::LaserScan::ConstPtr &scan) {
			Scan3 new_pose = transform::transform_scan(scan, const_pose);
			new_pose.print();
		}
};

int main(int argc, char** argv) {
    // It appears like the node name needs to match the file name, and the node needs to be linked to the ros libraries in the CMakeList (for future reference)
	ros::init(argc, argv, "Tester");
	ros::NodeHandle n;
	//TestTransform tc(n);
	TestCrash tc(n);
	ros::spin();
}
