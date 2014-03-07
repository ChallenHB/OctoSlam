#include "OctoSlamCalcs.h"
#include <math.h>

Eigen::Vector3f calculations::calc_det(float mv, float dx, float dy, float gammaP) {
    float coef = 1 - mv;
    Eigen::Vector3f ret;
    ret(0) = dy;
    ret(1) = dx;
    ret(2) = gammaP;
    return coef * ref;
}

Eigen::Matrix3f calculations::calc_hessian(float dx, float dy, float gammaP) {
    Eigen::Matrix3f hessian;
    hessian(0, 0) = sqrt(dy);
    hessian(0, 1) = dy * dx;
    hessian(0, 2) = dy * gammaP;
    hessian(1, 0) = dy * dx;
    hessian(1, 1) = sqrt(dx);
    hessian(1, 2) = gammaP * dx;
    hessian(2, 0) = dy * gammaP;
    hessian(2, 1) = dy * dx;
    hessian(2, 2) = sqrt(gammaP);
    return hessian.inverse();
}

float calculations::calc_gammaP(float gamma, float x, float y, float dx, float dy) {
    return (-sin(gamma) * x - cos(gamma) * y) * dy + (cos(gamma) * x - sin(gamma) * y) * dx;
}

octomath::Vector3 calculations::calc_map_values(octomap::OcTree *map, octomath::Vector3 p, 
            std::vector<octomath::Vector3> vectors, float mres) {
    octomath::Vector3 v0, v1, v2, v3;
    v0 = vectors.at(0);
    v1 = vectors.at(1);
    v2 = vectors.at(2);
    v3 = vectors.at(3);
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
    return octomath::Vector3(mv, dx, dy);
}

float calculations::calc_mres(octomap::ocTree *map, octomath::Vector3 endpoint) {
    octomap::OcTreeKey pointKey, itKey;
    pointKey = map->coordToKey(endpoint);
    if (pointKey == NULL) return 0; // This will be the error case
    for (octomap::OcTree::leaf_iterator = map->begin_leafs(), end = map->end_leafs();
            it != end; ++it) {
        itKey = it.getIndexKey();
        if (itKey == pointKey) {
            int dpeth = map->getTreeDepth() - itKey.getDepth(); // using n = 0 as the base level
            break;
        }
    }
    return pow(2, depth) * map->resolution;
}
