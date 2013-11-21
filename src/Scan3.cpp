#include "Scan3.h"

Scan3::Scan3(int size) {
    x_coor = new double[size];
    y_coor = new double[size];
    z_coor = new double[size];
}

void Scan3::add_point(double x, double y, double z, int index) {
    x_coor[index] = x;
    y_coor[index] = y;
    z_coor[index] = z;
}

double* Scan3::get_end_point(int index) {
    double point[3];
    point[0] = x_coor[index];
    point[1] = y_coor[index];
    point[2] = z_coor[index];
}
