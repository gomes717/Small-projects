#ifndef __LD19__
#define __LD19__
#include <string>
#include <stdint.h>
#include <termios.h>
#include <vector>

#define POINT_PER_PACK 12
#define HEADER 0x54

typedef struct __attribute__((__packed__))
{ 
    uint16_t distance;
    uint8_t intensity;
} LidarPointStructDef;


typedef union
{
    struct __attribute__((__packed__))
    {
        uint8_t header;
        uint8_t ver_len;
        uint16_t speed;
        uint16_t start_angle;
        LidarPointStructDef point[POINT_PER_PACK];
        uint16_t end_angle;
        uint16_t timestamp;
        uint8_t crc8;
    };
    uint8_t data[47];
} LiDARFrameTypeDef;

typedef struct 
{
    double x;
    double y;
} Point2D_t;

typedef struct 
{
    double dist;
    double theta;
} Polar_t;

class LD19
{
 public:
    LD19(std::string file);
    ~LD19();
    std::vector<Point2D_t> getPoints2D();
    std::vector<Polar_t> getPointsPolar();
    void getPointRaw();
 private:
    std::string file;
    int fd;
    termios tty;
    LiDARFrameTypeDef raw;
};

#endif