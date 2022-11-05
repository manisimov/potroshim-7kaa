#ifndef __OVGA_H
#define __OVGA_H

#include <SDL.h>

#define VGA_WIDTH   800
#define VGA_HEIGHT  600
#define VGA_BPP     8

class Vga{
/* [1] - Fields */
private:
    SDL_Window    *window;
    SDL_Renderer  *renderer;
    SDL_Texture   *texture;
    SDL_Surface   *target;
public:
/* [2] - Methods */
private:

public:
    Vga();
    ~Vga();
    int init();
    void flip();
    void handle_messages();
};

extern Vga vga;

#endif
