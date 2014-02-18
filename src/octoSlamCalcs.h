#ifndef OCTOSLAM_CALCS
#define OCTOSLAM_CALCS

#include <Eigen/Dense>

namespace calculations {
    Eigen::Matrix3f calc_hessian(float dx, float dy, float gammePrime);
    Eigen::Vector3f calc_def(float mv, float dx, float dy, float gammaPrime);
}
