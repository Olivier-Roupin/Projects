#include "moteur_graphique.h"

#include <iostream>

using namespace std;

SDL_Window *ecran;
SDL_Renderer *renderer;

SDL_Texture* textures[NOMBRE_TEXTURES];
ElementGraphique* elements_graphiques[NOMBRE_TEXTURES*TAILLE_TEXTURE];
BlocGraphique* blocs_graphiques[NOMBRE_BLOCS_GRAPHIQUES];
BlocAnime* blocs_animes[NOMBRE_BLOCS_ANIMES];

void init(char *titre)
{
    ecran = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_PRESENTVSYNC);

    if (ecran == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags ))
    {
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }

    SDL_ShowCursor(SDL_DISABLE);

    /*
    if (TTF_Init() < 0)
    {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
    */

    /*
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("Mix_Init: Failed to init SDL_Mixer\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_AllocateChannels(32);
    */
}

void delay(unsigned int frameLimit)
{
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }
    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }
    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

SDL_Texture* ChargerImage(char* fichier)
{
    SDL_Surface* image(0);
    SDL_Texture* texture(0);
    image = IMG_Load(fichier);
    if (image)
    {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
        image = 0;
    }
    return texture;
}
