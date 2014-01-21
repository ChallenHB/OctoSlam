// I have not run this program to check if it crashes
// I have not test to see if the output is correct
#include <Eigen/Dense>
#include <math.h>
#include "transformScan.h"

void set_yaw_rot(Eigen::Matrix3d yaw_rot, double yaw) {
	yaw_rot(0, 0) = cos(yaw);
	yaw_rot(0, 1) = -sin(yaw);
	yaw_rot(0, 2) = 0;
	yaw_rot(1, 0) = sin(yaw);
	yaw_rot(1, 1) = cos(yaw);
	yaw_rot(1, 2) = 0;
	yaw_rot(2, 0) = 0;
	yaw_rot(2, 1) = 0; 
	yaw_rot(2, 2) = 1;
}
	
void set_roll_rot(Eigen::Matrix3d roll_rot, double roll) {
	roll_rot(0, 0) = cos(roll);
	roll_rot(0, 1) = 0;
	roll_rot(0, 2) = sin(roll);
	roll_rot(1, 0) = 0;
	roll_rot(1, 1) = 1;
	roll_rot(1, 2) = 0;
	roll_rot(2, 0) = -sin(roll);
	roll_rot(2, 1) = 0;
	roll_rot(2, 2) = cos(roll);
}
	
void set_pitch_rot(Eigen::Matrix3d pitch_rot, double pitch) {
	pitch_rot(0, 0) = cos(pitch);
	pitch_rot(0, 1) = -sin(pitch);
	pitch_rot(0, 2) = 0;
	pitch_rot(1, 0) = sin(pitch);
	pitch_rot(1, 1) = cos(pitch);
	pitch_rot(1, 2) = 0;
	pitch_rot(2, 0) = 0;
	pitch_rot(2, 1) = 0;
	pitch_rot(2, 2) = 1;
}
	
void set_translate(Eigen::Matrix<double, 3, 4> translate, double x, double y, double z) {
	translate(0, 0) = 1;
	translate(0, 1) = 0;
	translate(0, 2) = 0;
	translate(0, 3) = x;
	translate(1, 0) = 0;
	translate(1, 1) = 1;
	translate(1, 2) = 0;
	translate(1, 3) = y;
	translate(2, 0) = 0;
	translate(2, 1) = 0;
	translate(2, 2) = 1;
	translate(2, 3) = z;
}

Scan3* transform::transform_scan(const sensor_msgs::LaserScan::ConstPtr &scan, std::vector<double> current) {
	float diff = scan->angle_max - scan->angle_min;
	float sizef = diff / scan->angle_increment;
	float angle =  scan->angle_min;
	int size = int(sizef);
	Scan3* ret = new Scan3(size);
	Eigen::Matrix3d roll_rot;
	Eigen::Matrix3d pitch_rot;
	Eigen::Matrix3d yaw_rot;
	Eigen::Matrix<double, 3, 4> translate; 
	set_roll_rot(roll_rot, current.at(3));// roll angle is third index
	set_pitch_rot(pitch_rot, current.at(4));// rot "  "  "  " "
	set_yaw_rot(yaw_rot, current[5]);
	set_translate(translate, current.at(0), current.at(1), current.at(2));
	for (int i = 0; i < size; i++) {
		if (scan->ranges[i] < scan->range_min || scan->ranges[i] > scan->range_max) {
			continue;
		}
		float range = scan->ranges[i];
		Eigen::Vector3d endpoints;
		endpoints(0) = range * cos(angle);
		endpoints(1) = range * sin(angle);
		endpoints(2) = 0;
		endpoints = yaw_rot * endpoints;
		endpoints = roll_rot * endpoints;
		endpoints = pitch_rot * endpoints;
		Eigen::Vector4d addon;
		addon(0) = endpoints(0);
		addon(1) = endpoints(1);
		addon(2) = endpoints(2);
		addon(3) = 1;
		endpoints = translate * addon;
		ret->add_point(endpoints(0), endpoints(1), endpoints(2), i);
		angle += scan->angle_increment;
	}
	return ret;
}
