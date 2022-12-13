#ifndef _WORLD_H_
#define _WORLD_H_

#include "location.h"
#include "screen.h"
#include "height_map.h"
#include "rand.h"
#include <SDL.h>

class World
{
public:
    enum Step {
        GENERATE_STEP_HEIGHT,
        GENERATE_STEP_BITMAPS,
    };
private:
    Location *loc_matrix;
    Screen &screen;
    int zoom_x_loc;
    int zoom_y_loc;
    SDL_Surface *terrain_bitmaps[TERRAIN_MAX];
    SDL_Surface *tile_bitmap;
    int need_regenerate_flag;
    HeightMap *height_map;
    Rand rand_gen;
    Step step;
public:
    World(Screen &);
    void generate_map(void);
    void process(void);
    void scroll(int x, int y);
    int need_regenerate(void);
    void regenerate(void);
    void set_generate_step(Step s);
private:
};

#endif
