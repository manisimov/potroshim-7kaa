#include <stdio.h>
#include <SDL.h>
#include "screen.h"
#include "world.h"
//#include "sys.h"

static Screen screen;
static World *world;

static void init(void);
static void run(void);
static int events(void);

int main(void)
{
    init();
    run();

    return 0;
}

void init(void)
{
    screen.clear(150, 150, 150);
    world = new World(screen);
    world->generate_map();
}

void run(void)
{
    while(events() == 0)
    {
        screen.flip();
        world->process();
    }
}

int events(void)
{
    SDL_Event event;
    int quit = 0;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                world->scroll(-1, 0);
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                world->scroll(0, -1);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                world->scroll(1, 0);
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                world->scroll(0, 1);
            }
            break;
        default:
            break;
        }
    }

    return quit;
}
