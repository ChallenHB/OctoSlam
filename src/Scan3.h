#ifndef SCAN3
#define SCAN3
// Scan3 is a a class that holds the endpoints of each incoming scan in 3D Cartesian coordinates. 
class Scan3 {
    private:
        // These are xyz arrays for the transformed scan
        int size;
        std::vector<float> x_coor;
        std::vector<float> y_coor;
        std::vecotr<float> z_coor;

    public:
        Scan3(int size);
        // adds a point into the scan
        void add_point(float x, float y, float z, int index);
        // returns a desired point from the
        std::vector<float> get_end_point(int index);
};
#endif
