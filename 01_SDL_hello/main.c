#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX 256

SDL_Window    *window;
SDL_Renderer  *renderer;
char          *images_path;

#define NUMBER_OF_TEXTURES 3
SDL_Texture   *textures[NUMBER_OF_TEXTURES];

int main(void)
{
    int res;
    int is_running;
    unsigned int clicks_counter = 0;
    SDL_Event event;
    char filename[NAME_MAX];

    images_path = getenv("IMG_PATH");
    if (images_path == NULL)
    {
        fprintf(stderr, "Error: IMG_PATH\n");
        return 1;
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("SDL hello",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               128,
                               128,
                               0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    res = SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // * Load Images
    strncpy(filename, images_path, NAME_MAX - 21);
    strncat(filename, "/one.png", 20);
    textures[0] = IMG_LoadTexture(renderer, filename);

    strncpy(filename, images_path, NAME_MAX - 21);
    strncat(filename, "/two.png", 20);
    textures[1] = IMG_LoadTexture(renderer, filename);

    strncpy(filename, images_path, NAME_MAX - 21);
    strncat(filename, "/three.png", 20);
    textures[2] = IMG_LoadTexture(renderer, filename);
    // *

    is_running = 1;
    while(is_running)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("Quit event\n");
                is_running = 0;
                break;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                clicks_counter++;
                printf("Mouse clicked. New texture index is %d\n", clicks_counter % NUMBER_OF_TEXTURES);
            }
        }
        res = SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textures[clicks_counter % NUMBER_OF_TEXTURES], NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();

    return 0;
}
