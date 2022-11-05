#include "OVGA.h"
#include <SDL.h>
#include "OVGABUF.h"
#include "OSYS.h"
#include "OMOUSE.h"

Vga::Vga()
{
}

int Vga::init()
{
    if(SDL_Init(SDL_INIT_VIDEO))
        return 0;

    int mouse_x, mouse_y;
    SDL_GetGlobalMouseState(&mouse_x, &mouse_y);

    window = SDL_CreateWindow( "Main loop and cursor",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
    SDL_RenderSetLogicalSize(renderer, VGA_WIDTH, VGA_HEIGHT);

    SDL_WarpMouseGlobal(mouse_x, mouse_y);

    Uint32 window_pixel_format = SDL_GetWindowPixelFormat(window);
    texture = SDL_CreateTexture( renderer,
                                 window_pixel_format,
                                 SDL_TEXTUREACCESS_STREAMING,
                                 VGA_WIDTH,
                                 VGA_HEIGHT);

    int desktop_bpp = 0;
    if (SDL_PIXELTYPE(window_pixel_format) == SDL_PIXELTYPE_PACKED32)
    {
        desktop_bpp = 32;
    }
    else if (SDL_PIXELTYPE(window_pixel_format) == SDL_PIXELTYPE_PACKED16)
    {
        desktop_bpp = 16;
    }
    else if (SDL_PIXELTYPE(window_pixel_format) == SDL_PIXELTYPE_PACKED8)
    {
        desktop_bpp = 8;
    }
    else
    {
        return 0;
    }

    target = SDL_CreateRGBSurface( 0,
                                   VGA_WIDTH,
                                   VGA_HEIGHT,
                                   desktop_bpp,
                                   0, 0, 0, 0);

    return 1;
}

void Vga::flip()
{
    static Uint32 ticks = 0;
    Uint32 cur_ticks;

    cur_ticks = SDL_GetTicks();
    if(cur_ticks > ticks + 17 || cur_ticks < ticks)
    {
        ticks = cur_ticks;
        SDL_BlitSurface(vga_front.surface, NULL, target, NULL);
        SDL_UpdateTexture(texture, NULL, target->pixels, target->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

void Vga::handle_messages()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            sys.signal_exit_flag = 1;
            break;
        case SDL_MOUSEMOTION:
            int logical_x, logical_y;
            logical_x = event.motion.x;
            logical_y = event.motion.y;
            mouse.process_mouse_motion(logical_x, logical_y);
            break;
        default:
            break;
        }
    }
}

Vga::~Vga()
{
}
