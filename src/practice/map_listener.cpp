#include <ros/ros.h>
#include <octomap/octomap.h>
#include <octomap_msgs/conversions.h>

class OctomapListener {
  private:
    ros::NodeHandle node;
    ros::Subscriber map_sub;
    octomap::OcTree* octo;

  public:
    OctomapListener(ros::NodeHandle n): node(n) {
      map_sub = node.subscribe("octomap_binary", 100, &OctomapListener::extractMap, this);
    }

    void extractMap(const octomap_msgs::OctomapBinary &map) {
      octo = octomap_msgs::binaryMsgDataToMap(map.data);\
    }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "making_octomap");
  ros::NodeHandle n;
  OctomapListener listener(n);
  ros::spin();
  return 1;
}
