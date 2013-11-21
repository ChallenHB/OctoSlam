#ifndef SCAN3
#define SCAN3

class Scan3 {
    private:
        double* x_coor;
        double* y_coor;
        double* z_coor;

    public:
        Scan3(int size);
        void add_point(double x, double y, double z, int index);
        double* get_end_point(int index);
};
#endif
