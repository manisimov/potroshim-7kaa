#include "screen.h"
#include <SDL.h>
#include <stdint.h>

Screen::Screen()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Map, generate",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               800,
                               600,
                               0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    surface =  SDL_CreateRGBSurfaceWithFormat(0, 800, 600, 32, SDL_PIXELFORMAT_RGBA8888);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                800, 600);
}

Screen::~Screen()
{
}

void Screen::flip(void)
{
    static Uint32 ticks = 0;
    Uint32 cur_ticks;

    cur_ticks = SDL_GetTicks();
    if (cur_ticks > ticks + 17 || cur_ticks < ticks)
    {
        ticks = cur_ticks;
        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

void Screen::clear(uint8_t r, uint8_t g, uint8_t b)
{
    int pitch = surface->pitch;
    char *pixels = (char*)surface->pixels;

    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            pixels[x * 4 + y * pitch] = 0;
            pixels[x * 4 + y * pitch + 1] = b;
            pixels[x * 4 + y * pitch + 2] = g;
            pixels[x * 4 + y * pitch + 3] = r;
        }
    }
}

void Screen::put_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    char *pixels = (char*)surface->pixels;
    int pitch = surface->pitch;

    pixels[x * 4 + y * pitch] = 0;
    pixels[x * 4 + y * pitch + 1] = b;
    pixels[x * 4 + y * pitch + 2] = g;
    pixels[x * 4 + y * pitch + 3] = r;
}

void Screen::put_rectangle(int x, int y, int w, int h, int r, int g, int b)
{
    char *pixels = (char*)surface->pixels;
    int pitch = surface->pitch;

    for (int x_cur = x; x_cur - x < w; x_cur++)
    {
        pixels[x_cur * 4 + y * pitch] = 0;
        pixels[x_cur * 4 + y * pitch + 1] = b;
        pixels[x_cur * 4 + y * pitch + 2] = g;
        pixels[x_cur * 4 + y * pitch + 3] = r;
        pixels[x_cur * 4 + (y + h) * pitch] = 0;
        pixels[x_cur * 4 + (y + h) * pitch + 1] = b;
        pixels[x_cur * 4 + (y + h) * pitch + 2] = g;
        pixels[x_cur * 4 + (y + h) * pitch + 3] = r;
    }

    for (int y_cur = y; y_cur - y < h; y_cur++)
    {
        pixels[x * 4 + y_cur * pitch] = 0;
        pixels[x * 4 + y_cur * pitch + 1] = b;
        pixels[x * 4 + y_cur * pitch + 2] = g;
        pixels[x * 4 + y_cur * pitch + 3] = r;
        pixels[(x + w) * 4 + y_cur * pitch] = 0;
        pixels[(x + w) * 4 + y_cur * pitch + 1] = b;
        pixels[(x + w) * 4 + y_cur * pitch + 2] = g;
        pixels[(x + w) * 4 + y_cur * pitch + 3] = r;
    }
}

void Screen::put_bitmap(int x, int y, SDL_Surface *bitmap)
{
    SDL_Rect src_rect;
    SDL_Rect dst_rect;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = bitmap->w;
    src_rect.h = bitmap->h;

    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.w = bitmap->w;
    dst_rect.h = bitmap->h;

    SDL_BlitSurface(bitmap, &src_rect, surface, &dst_rect);
}
