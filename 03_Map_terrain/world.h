#ifndef _WORLD_H_
#define _WORLD_H_

#include "location.h"
#include "screen.h"
#include <SDL.h>

class World
{
public:
private:
    Location *loc_matrix;
    Screen &screen;
    int zoom_x_loc;
    int zoom_y_loc;
    SDL_Surface *terrain_bitmaps[TERRAIN_MAX];
public:
    World(Screen &);
    void generate_map(void);
    void process(void);
    void scroll(int x, int y);
private:
};

#endif
