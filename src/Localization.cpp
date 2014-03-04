#include "Localization.h"
#include "OctoSlamCalcs.h"

Localization::Localization(ros::NodeHandle n, std::vector<float> init_pose): node(n) {
    if (init_pose.size() != 6) printf("Length of init_pose is incorrect");
    current_pose = init_pose;
    scan_sub = node.subscribe("Brain5/pose", 1000, &Localization::scan_callback, this);
    aux_sub = node.subscribe("sensor_data", 1000, &Localization::sensor_callback, this);
    // Will need to initialize the octomap once I know whether I'll be building the map
    // on the go (actual SLAM) vs. loading a known map
    // Also goes with how does the Localization, mapping go together?
}

void Localization:data_callback(geometry_msgs::Point pose) {
    current_pose.at(PHI) = pose.x;
    current_pose.at(PSI) = pose.y;
    current_pose.at(Z) = pose.z;
}

void Localization::scan_sub(const sensor_msgs::LaserScan::ConstPtr &scan) {
    // Everything is being done in floats, because that's what the scan comes as :)
    Eigen::Vector3f T(current_pose.at(X), current_pose.at(Y), current_pose.at(GAMMA));
    std::vector<octomath::Vector3> t_scan = calculations::transform_scan(scan, current);
    Eigen::Matrix3f Hessian;
    Eigen::Vector3f det;
    octomath::Vector3 voxel;
    octomath::Vector3 map_values;
    std::vector<octomath::Vector3> closest; // Rounded voxels
    float mv, dx, dy, gammaP, mres;
    for (int n = 0; n < ITERATIONS; ++n) {
        Hessian.setZero();
        det.setZero();
        for (int i = 0; i < t_scan.size(); ++i) {
            voxel = t_scan.at(i);
            mres = calculations::calc_mres(map, voxel);
            closest = calculations::round_voxels(map, voxel, mres);
            map_values = calculations::calc_map_values(map, voxel, closest, mres);
            mv = map_values.x(); dx = map_values.y(); dy = map_values.z();
            gammaP = calculations::calc_gamma(current.at(GAMMA), voxel.x(), voxel.y(), 
                    dx, dy);
            Hessian = Hessian + calculations::calc_hessian(dx, dy, gammaP);
            det = det + calculations::calc_det(mv, dx, dy, gammaP);
        }
        T = T + (Hessian * det);
    }
    current_pose.at(X) = T(0);
    current_pose.at(Y) = T(1);
    current_pose.at(GAMMA) = T(2);
}
