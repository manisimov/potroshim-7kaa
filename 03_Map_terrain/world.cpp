#include "world.h"
#include "location.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>

#define WORLD_WIDTH  200
#define WORLD_HEIGHT 200

#define MAP_X1 588
#define MAP_Y1 56
#define MAP_X2 788
#define MAP_Y2 256

#define ZOOM_WIDTH_IN_LOCS  18
#define ZOOM_HEIGHT_IN_LOCS 17

#define ZOOM_X1 0
#define ZOOM_Y1 56
#define ZOOM_X2 599
#define ZOOM_Y2 575

#define ZOOM_TILE_WIDTH  32
#define ZOOM_TILE_HEIGHT 32


World::World(Screen &scr) : screen(scr)
{
    zoom_x_loc = 0;
    zoom_y_loc = 0;

    char *data_dir;
    data_dir = getenv("DATA");

    if(data_dir)
        chdir(data_dir);

    terrain_bitmaps[TERRAIN_WATER] = IMG_Load("water.png");
    terrain_bitmaps[TERRAIN_GRASS] = IMG_Load("grass.png");
    terrain_bitmaps[TERRAIN_ROCK]  = IMG_Load("rock.png");
}

void World::generate_map(void)
{
    loc_matrix = (Location*)malloc(WORLD_WIDTH * WORLD_HEIGHT * sizeof(Location));

    for (int y = 0; y < WORLD_HEIGHT; y++)
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            loc_matrix[x + y * WORLD_WIDTH].terrain_id = rand() % (TERRAIN_MAX - 1) + 1;
            if (y < 10 || y > 150)
                loc_matrix[x + y * WORLD_WIDTH].terrain_id = TERRAIN_WATER;
        }
    }
}

void World::process(void)
{
    /* [1] Map */
    int loc_index = 0;

    /* 1a - terrain pixels */
    for (int y = MAP_Y1; y < MAP_Y1 + WORLD_HEIGHT; y++)
    {
        for (int x = MAP_X1; x < MAP_X1 + WORLD_WIDTH; x++, loc_index++)
        {
            uint8_t r, g, b;
            Location *loc = &loc_matrix[loc_index];
            r = 0;
            g = 0;
            b = 0;
            switch (loc->terrain_id)
            {
            case TERRAIN_WATER:
                b = 255;
                break;
            case TERRAIN_GRASS:
                g = 255;
                break;
            case TERRAIN_ROCK:
                r = 100;
                g = 100;
                b = 100;
                break;
            default:
                /* black */
                break;
            }
            screen.put_pixel(x, y, r, g, b);
        }
    }
    /* 1b - current position square */
    screen.put_rectangle(MAP_X1 + zoom_x_loc, MAP_Y1 + zoom_y_loc, 17, 16, 255, 255, 0);


    /* [2] Zoom */
    for (int y_tile = 0; y_tile < ZOOM_HEIGHT_IN_LOCS; y_tile++)
    {
        for (int x_tile = 0; x_tile < ZOOM_WIDTH_IN_LOCS; x_tile++)
        {
            int x = x_tile * ZOOM_TILE_WIDTH + ZOOM_X1;
            int y = y_tile * ZOOM_TILE_HEIGHT + ZOOM_Y1;
            int loc_index = x_tile + zoom_x_loc + (y_tile + zoom_y_loc) * WORLD_WIDTH;
            Location *loc = &loc_matrix[loc_index];
            SDL_Surface *bitmap = terrain_bitmaps[loc->terrain_id];

            screen.put_bitmap(x, y, bitmap);
        }
    }
}

void World::scroll(int x, int y)
{
    if (x == -1 && zoom_x_loc > 0)
        zoom_x_loc--;
    else if (x == 1 && zoom_x_loc + ZOOM_WIDTH_IN_LOCS < WORLD_WIDTH)
        zoom_x_loc++;

    if (y == -1 && zoom_y_loc > 0)
        zoom_y_loc--;
    else if (y == 1 && zoom_y_loc + ZOOM_HEIGHT_IN_LOCS < WORLD_HEIGHT)
        zoom_y_loc++;

    printf("x=%d y=%d\n", zoom_x_loc, zoom_y_loc);
}
