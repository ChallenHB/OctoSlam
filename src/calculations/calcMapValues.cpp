#include "OctoSlamCalcs.h"
#include <octomath/Vector3.h>

using namespace octomath {

Vector3 calculations::calc_map_values(octomap::OcTree *map, Vector3 p, 
std::vector<Vector3> vectors, float mres) {
    Vector3 v0 = vectors.at(0);
    Vector3 v1 = vectors.at(1);
    Vector3 v2 = vectors.at(2);
    Vector3 v3 = vectors.at(3);
    float Mv0 = tree->search(v0)->getOccupancy(); 
    float Mv1 = tree->search(v1)->getOccupancy();
    float Mv2 = tree->search(v2)->getOccupancy();
    float Mv3 = tree->search(v3)->getOccupancy();

    mvPart0 = (v3.y() - p.y())/mres * (v1.x() - p.x())/(v1.x() - v2.x()) * Mv0;
    mvPart1 = (v3.y() - p.y())/mres * (p.x() - v2.x())/(v1.x() - v2.x()) * Mv1;
    mvPart2 = (p.y() - v0.y())/mres * (v1.x() - p.x())/(v1.x() - v2.x()) * Mv2;
    mvPart3 = (p.y() - v0.y())/mres * (p.x() - v2.x())/(v1.x() - v2.x()) * Mv3;
    mv = mvPart0 + mvPart1 + mvPart2 + mvPart3;
    dx = (v3.y() - p.y())/mres * (Mv0 - Mv2) + (p.y() - v0.y())/mres * (Mv1 - Mv3);
    dy = (v1.x() - p.x())/mres * (Mv0 - Mv1) + (p.x() - v2.x())/mres * (Mv2 - Mv3);
    return Vector3(mv, dx, dy);
}

}
