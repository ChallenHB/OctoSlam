#include "Scan3.h"
#include "transformScan.cpp"

int main(int argc, char** argv) {
    Scan3* testing = new Scan3(3);
    testing->add_point(1, 3, 4, 0);
    testing->add_point(2,3,4,1);
    testing->add_point(1, 2,3, 2);
    testing->print();
}
