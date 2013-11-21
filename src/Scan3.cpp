#include "Scan3.h"

Scan3::Scan3(int size) {
    x_coor = new float[size];
    y_coor = new float[size];
    z_coor = new float[size];
}

void Scan3::add_point(float x, float y, float z, int index) {
    x_coor[index] = x;
    y_coor[index] = y;
    z_coor[index] = z;
}

float* Scan3::get_end_point(int index) {
    double point[3];
    point[0] = x_coor[index];
    point[1] = y_coor[index];
    point[2] = z_coor[index];
}
