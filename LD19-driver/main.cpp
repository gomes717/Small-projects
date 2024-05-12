#include "Driver/include/LD19.hpp"

int main()
{
    LD19 lidar = LD19("/dev/ttyUSB0");
    while(true)
    {
        std::vector<Point2D_t> pontos = lidar.getPoints2D();
    }
    return 0;
}