#include "Scan3.h"
#include <iostream>

Scan3::Scan3(int s) {
    size = s;
    x_coor.resize(s);
    y_coor.resize(s);
    z_coor.resize(s);
}

void Scan3::add_point(float x, float y, float z, int index) {
    x_coor[index] = x;
    y_coor[index] = y;
    z_coor[index] = z;
}

std::vector<float> Scan3::get_end_point(int index) {
    std::vector<float> point;
    point.push_back(x_coor.at(index));
    point.push_back(y_coor.at(index));
    point.push_back(z_coor.at(index));
}

void Scan3::print() {
    for (int i = 0; i < size; i++) {
        std::cout << "x: " << x_coor.at(i) << ", y: " << y_coor.at(i) << ", z: " << z_coor.at(i) << std::endl;
    }
}
