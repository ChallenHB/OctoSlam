#include "octoSlamCalcs.h"

Eigen::Matrix3f calculations::calc_hessian(float dx, float dy, float gammePrime) {
    Eigen::Matrix3f hessian;
    hessian(0, 0) = sqrt(dy);
    hessian(0, 1) = dy * dx;
    hessian(0, 2) = dy * gammaPrime;
    hessian(1, 0) = dy * dx;
    hessian(1, 1) = sqrt(dx);
    hessian(1, 2) = gammaPrime * dx;
    hessian(2, 0) = dy * gammaPrime;
    hessian(2, 1) = dy * dx;
    hessian(2, 2) = sqrt(gammePrime);
    return hessian.inverse();
}

