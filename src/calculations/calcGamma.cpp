#include "octoSlamCalcs.h"

float calc_gamma(float gamma, float x, float y, float dx, float dy) {
    return (-sin(gamma) * x - cos(gamma) * y) * dy + (cos(gamma) * x - sin(gamma) * y) * dx;
}
