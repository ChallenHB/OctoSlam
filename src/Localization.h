#ifndef LOCALIZATION
#define LOCALIZATION

#include <geometry_msgs/Point.h>
#include <octomap/octomap.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>

class Localization {
    private:
        static const int X = 0; // Not known
        static const int Y = 1; // Not known
        static const int Z = 2; // Known from altitude data
        static const int PHI = 3; // Known from roll data
        static const int PSI = 4; // Known from pitch data
        static const int GAMMA = 5;  // Not known
        static const int ITERATIONS = 5; // Eventually will be passed in as a param
        ros::NodeHandle node;
        ros::Subscriber scan_sub;
        ros::Subscriber aux_sub; // For known position values
        std::vector<float> current_pose;
        octomap::OcTree* map;

    public:
        Localization(ros::NodeHandle n, std::vector<float> init_pose);
        void data_callback(geometry_msgs::Point pose);
        void scan_callback(const sensor_msgs::LaserScan::ConstPtr &scan);
};
#endif
