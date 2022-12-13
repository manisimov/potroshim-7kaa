#ifndef _HEIGHT_MAP_H_
#define _HEIGHT_MAP_H_

#include "rand.h"
#include <stdint.h>

class HeightMap {
public:
private:
    short *matrix;
    short max_x;
    short max_y;
    Rand &rand_gen;
    int recur_level;
    int recur1;
    int iparmx;
public:
    HeightMap() = delete;
    HeightMap(short w, short h, Rand &rand_gen);
    short get_pixel(short x, short y);
    void put_pixel(short x, short y, short value);
    void generate(int gen_method, int grain_factor, int random_seed);
private:
    void sub_divide(int x1, int y1, int x2, int y2);
    uint16_t adjust(int xa,int ya,int x,int y,int xb,int yb);
};

#endif
