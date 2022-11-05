#include "OMOUSE.h"
#include <SDL.h>
#include "OVGA.h"
#include "OMOUSECR.h"

void Mouse::init()
{
    SDL_StopTextInput();
    SDL_ShowCursor(SDL_DISABLE);
    cur_x = 100;
    cur_y = 100;
}

void Mouse::process_mouse_motion(int x, int y)
{
    cur_x = x;
    cur_y = y;
    mouse_cursor.process(cur_x, cur_y);
}
