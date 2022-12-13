#include "height_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

HeightMap::HeightMap(short w, short h, Rand &rand_gen) : rand_gen(rand_gen)
{
    max_x = w;
    max_y = h;

    matrix = (short*)malloc((w + 1) * (h + 1) * sizeof(short));
    memset(matrix, 0, (w + 1) * (h + 1) * sizeof(short));
}

short HeightMap::get_pixel(short x, short y)
{
    return matrix[y * (max_x+1) + x];
}

void HeightMap::put_pixel(short x, short y, short value)
{
    matrix[y * (max_x+1) + x] = value;
}

void HeightMap::generate(int gen_method, int grain_factor, int random_seed)
{
    uint16_t rnd[4];

    iparmx = grain_factor * 8;

    for(int i = 0; i < 4; i++)
    {
        rnd[i] = 1 + (((rand_gen.get_rand() / 256) * (256 - 1)) >> 7);
    }

    memset(matrix, 0, (max_x + 1) * (max_y + 1) * sizeof(short));
    put_pixel(0, 0, rnd[0]);
    put_pixel(max_x, 0, rnd[1]);
    put_pixel(max_x, max_y, rnd[2]);
    put_pixel(0, max_y, rnd[3]);

    recur_level = 0;

    sub_divide(0, 0, max_x, max_y);
}

void HeightMap::sub_divide(int x1, int y1, int x2, int y2)
{
    int x, y;
    int32_t v, i;

    if(x2-x1<2 && y2-y1<2)
        return;

    recur_level++;
    recur1 = 320L >> recur_level;

    x = (x1+x2)>>1;
    y = (y1+y2)>>1;

    if((v=get_pixel(x,y1)) == 0)
        v=adjust(x1,y1,x ,y1,x2,y1);
    i=v;

    if((v=get_pixel(x2,y)) == 0)
        v=adjust(x2,y1,x2,y ,x2,y2);
    i+=v;

    if((v=get_pixel(x,y2)) == 0)
        v=adjust(x1,y2,x ,y2,x2,y2);
    i+=v;

    if((v=get_pixel(x1,y)) == 0)
        v=adjust(x1,y1,x1,y ,x1,y2);
    i+=v;

    if(get_pixel(x,y) == 0)
        put_pixel(x,y,(uint16_t)((i+2)>>2));

    sub_divide(x1,y1,x ,y);
    sub_divide(x ,y1,x2,y);
    sub_divide(x ,y ,x2,y2);
    sub_divide(x1,y ,x ,y2);
    recur_level--;
}


uint16_t HeightMap::adjust(int xa,int ya,int x,int y,int xb,int yb)
{
    int32_t pseudoRandom;

    pseudoRandom = ((int32_t)iparmx)*((rand_gen.get_rand()-16383));

    pseudoRandom = pseudoRandom * recur1;
    pseudoRandom = pseudoRandom >> 18;
    pseudoRandom = (((int32_t)get_pixel(xa,ya)+(int32_t)get_pixel(xb,yb)+1)>>1)+pseudoRandom;

    if (pseudoRandom >= 256)
        pseudoRandom = 256-1;

    if(pseudoRandom < 1)
        pseudoRandom = 1;

    put_pixel(x,y,(uint16_t)pseudoRandom);

    return((uint16_t)pseudoRandom);
}
