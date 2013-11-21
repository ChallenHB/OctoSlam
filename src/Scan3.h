#ifndef SCAN3
#define SCAN3

class Scan3 {
    private:
        float* x_coor;
        float* y_coor;
        float* z_coor;

    public:
        Scan3(int size);
        void add_point(float x, float y, float z, int index);
        double* get_end_point(int index);
};
#endif
