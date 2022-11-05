#include "OVGABUF.h"
#include <SDL.h>
#include "OVGA.h"

static SDL_Color colors[] = { {  0,   0,   0, 0},
                              {255,   0,   0, 0},
                              {  0, 255,   0, 0},
                              {  0,   0, 255, 0},
                              {100, 100, 100, 0},
                            };

int VgaBuf::init(char front, int w, int h)
{
    surface = SDL_CreateRGBSurface( 0, VGA_WIDTH, VGA_HEIGHT, VGA_BPP, 0, 0, 0, 0);
    SDL_SetPaletteColors(surface->format->palette, colors, 0, sizeof(colors) / sizeof(colors[0]));
    cur_buf_ptr = (char*)surface->pixels;

    return 1;
}
