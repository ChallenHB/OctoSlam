#ifndef OCTOSLAM_CALCS
#define OCTOSLAM_CALCS

#include <Eigen/Dense>
#include <octomap/octomap.h>
#include <octomath/octomath.h>

namespace calculations {
    Eigen::Vector3f calc_det(float mv, float dx, float dy, float gammaP);

    Eigen::Matrix3f calc_hessian(float dx, float dy, float gammaP);
    
    float calc_gamma(float gamma, float x, float y, float dx, float dy);
   
    Vector3 calc_map_values(octomap::OcTree *map, octomath::Vector3 p,
                std::vector<octomath::Vector3> vectors, float mres); 
   
    float calc_mres(octomap::OcTree *map, octomath::Vector3 voxel);

    std::vector<octomath::Vector3> round_voxels(octomap::OcTree *map, octomath::Vector3 voxel
                float mres);
    
    std::vector<octomath::Vector3> transform_scan(const sensor_msgs::LaserScan::ConstPtr &scan,
                std::vector<double> current); 
}
#endif
