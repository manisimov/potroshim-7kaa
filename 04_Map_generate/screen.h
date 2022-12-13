#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL.h>
#include <stdint.h>

class Screen
{
public:
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
public:
    Screen();
    ~Screen();
    void flip(void);
    void clear(uint8_t r, uint8_t g, uint8_t b);
    void put_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void put_bitmap(int x, int y, SDL_Surface *bitmap);
    void put_rectangle(int x, int y, int w, int h, int r, int g, int b);
private:
};

#endif
