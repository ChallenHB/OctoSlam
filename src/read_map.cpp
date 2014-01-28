#include <ros/ros.h>
#include <octomap/octomap.h>
#include <iostream>
int main() {
    // How do I correctly open a octomap file
    octomap::OcTree* ot = new octomap::OcTree("data/map_sept30.bt");
    std::cout << "Print something" << std::endl;
    for(octomap::OcTree::leaf_iterator it = ot->begin_leafs(), end=ot->end_leafs(); it != end; ++it){
        std::cout << "Node center: " << it.getCoordinate() << std::endl;
        std::cout << "Node size: " << it.getSize() << std::endl;
        std::cout << "Node value: " << it->getValue() << std::endl;
    }
   /* octomap::OcTreeNode *node = (octomap::OcTreeNode *)  ot->search(0, 0, 0);
    if(node == NULL) {
        std::cout << "node is null" << std::endl;
    }
    else {
        std::cout << "node is not null" << std::endl;
    }
    std::cout << "node value: " << node->getValue() << std::endl;*/
    return 1;
}
