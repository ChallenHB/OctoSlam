#include "octoSlamCalcs.h"

Eigen::Vector3f calculations::calc_det(float mv, float dx, float dy, float gammaP) {
    float coef = 1 - mv;
    Eigen::Vector3f ret;
    ret(0) = dy;
    ret(1) = dx;
    ret(2) = gammaPrime;
    return coef * ret;
}
