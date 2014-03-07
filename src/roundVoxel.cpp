#include "OctoSlamCalcs.h"

float round(float in, float mres) {
    float mod = in % res;
    if (mod > mres/2) return in + mres/2 - mod;
    return in - mod - mres/2;
}

std::vector<octomath::Vector3> calculations::round_voxels(octomath::Vector3 endpoint, float mres) {
    float v0x, v0y, v0z, v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
    v0x = round(endpoint.x(), mres);
    v0y = round(endpoint.y(), mres);
    v0z = round(endpoint.z(), mres);
    v1x = v0x + mres;
    v1y = v0y;
    v1z = v0z;
    v2x = v1x;
    v2y = v1y + mres;
    v2z = v1z;
    v3x = v2x + mres;
    v3y = v2y;
    v3z = v2z;
    octomath::Vector3 v0(v0x, v0y, v0z);
    octomath::Vector3 v1(v1x, v1y, v1z);
    octomath::Vector3 v2(v2x, v2y, v2z);
    octomath::Vector3 v3(v3x, v3y, v3z);
    std::vector<octomath::Vector3> ret;
    ret.push_back(v0);
    ret.push_back(v1);
    ret.push_back(v2);
    ret.push_back(v3);
    return ret;
}
