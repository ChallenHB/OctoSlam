#include <ros/ros.h>
#include <octomap/octomap.h>
#include <iostream>
#include <fstream>

int main() {
    octomap::OcTree* ot = new octomap::OcTree("data/map_sept30.bt");
    octomap::OcTreeNode* node = (octomap::OcTreeNode *) ot->search(-1.1823, -1.72, .62);
    octomap::OcTreeKey pointKey, itKey;
    pointKey = ot->coordToKey(-1.1823, -1.72, .62);
    if (node == NULL) std::cout << "node is null" << std::endl;
    else{
        octomap::point3d p = ot->keyToCoord(pointKey);
        std::cout << "x: " << p.x() << " y: " << p.y()  << " z: " << p.z() << std::endl;
    }
    bool found = false;
    for (octomap::OcTree::leaf_iterator it = ot->begin_leafs(), end=ot->end_leafs(); it != end; ++it) {
        itKey = it.getIndexKey(); 
        if (itKey == pointKey) {
            std::cout << "Node center: " << it.getCoordinate() << std::endl;
            std::cout << "Node depth: " << it.getDepth() << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        printf("No match found");
    }
/*    octomap::OcTreeKey key = ot->coordToKey(.456, .5, .09 );
    octomap::point3d point = ot->keyToCoord(key);
    octomap::OcTreeNode* node = ot->search(point);
    if(node == NULL) {
        std::cout << "node is null" << std::endl;
    }
    else {
        std::cout << "node is not null" << std::endl;
        std::cout << "node value: " << node->getValue() << std::endl;
    }
    octomap::OcTreeNode* node1 = ot->search(0,1,0);
    if(node1 == NULL) {
        std::cout << "node1 is null" << std::endl;
    }
    else {
        std::cout << "node1 is not null" << std::endl;
        std::cout << "node1 value: " << node1->getValue() << std::endl;
    }*/
    
    return 1;
}
