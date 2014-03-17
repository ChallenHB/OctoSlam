#include "Localization.h"
#include <ros/ros.h>

int main(int argc, char** argv) {
    std::vector<float> init(6); // Need to figure out how to change this on the fly
    ros::init(argc, argv, "Localization");
    ros::NodeHandle n;
    Localization l(n, init);
    ros::spin();
}
