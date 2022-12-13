#include "world.h"
#include "location.h"
#include "height_map.h"
#include "rand.h"
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


World::World(Screen &scr) : screen(scr), rand_gen{}
{
    zoom_x_loc = 0;
    zoom_y_loc = 0;
    need_regenerate_flag = 0;
    step = GENERATE_STEP_HEIGHT;
    loc_matrix = NULL;
    height_map = NULL;

    char *data_dir;
    data_dir = getenv("DATA");

    if(data_dir)
        chdir(data_dir);

    terrain_bitmaps[TERRAIN_WATER] = IMG_Load("water.png");
    terrain_bitmaps[TERRAIN_GRASS] = IMG_Load("grass.png");
    terrain_bitmaps[TERRAIN_ROCK]  = IMG_Load("rock.png");

    tile_bitmap = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA8888);
}

void World::generate_map(void)
{
    if (loc_matrix == NULL)
        loc_matrix = (Location*)malloc(WORLD_WIDTH * WORLD_HEIGHT * sizeof(Location));

    if (height_map == NULL)
        height_map = new HeightMap(WORLD_WIDTH, WORLD_HEIGHT, rand_gen);

    height_map->generate(rand_gen.get_rand(), 5, rand_gen.get_rand()); // UB?

    for (int y = 0; y < WORLD_HEIGHT; y++)
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            short height = height_map->get_pixel(x, y);
            if (height < 80)
            {
                loc_matrix[x + y * WORLD_WIDTH].terrain_id = TERRAIN_WATER;
            }
            else if (height < 160)
            {
                loc_matrix[x + y * WORLD_WIDTH].terrain_id = TERRAIN_ROCK;
            }
            else
            {
                loc_matrix[x + y * WORLD_WIDTH].terrain_id = TERRAIN_GRASS;
            }
        }
    }

    need_regenerate_flag = 0;
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
            if (step == GENERATE_STEP_BITMAPS)
            {
                /* Terrain colors on the map */
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
            else if (step == GENERATE_STEP_HEIGHT)
            {
                /* Shades of gray of height on the map */
                short height = height_map->get_pixel(x - MAP_X1, y - MAP_Y1);
                r = height;
                g = height;
                b = height;
                screen.put_pixel(x, y, r, g, b);
            }
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
            if (step == GENERATE_STEP_BITMAPS)
            {
                int loc_index = x_tile + zoom_x_loc + (y_tile + zoom_y_loc) * WORLD_WIDTH;
                Location *loc = &loc_matrix[loc_index];
                SDL_Surface *bitmap = terrain_bitmaps[loc->terrain_id];
                screen.put_bitmap(x, y, bitmap);
            }
            else if (step == GENERATE_STEP_HEIGHT)
            {
                short height = height_map->get_pixel(x_tile + zoom_x_loc, y_tile + zoom_y_loc);
                unsigned char color_byte = height % 255;
                Uint32 color = (color_byte << 8) | (color_byte << 16) |
                               (color_byte << 24) | 0xFF;
                SDL_FillRect(tile_bitmap, NULL, color);
                screen.put_bitmap(x, y, tile_bitmap);
            }
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

int World::need_regenerate()
{
    return need_regenerate_flag;
}

void World::regenerate(void)
{
    need_regenerate_flag = 1;
}

void World::set_generate_step(Step s)
{
    step = s;
}
