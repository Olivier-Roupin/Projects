#ifndef MOTEUR_GRAPHIQUE_H_INCLUDED
#define MOTEUR_GRAPHIQUE_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include <BoiteTexte.h>
#include <BlocAnime.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define TAILLE_BASIQUE 8
/*
#define NOMBRE_TEXTURES 3
#define LARGEUR_TEXTURE 16
#define TAILLE_TEXTURE 8*LARGEUR_TEXTURE

#define NOMBRE_BLOCS_GRAPHIQUES 256*/
#define NOMBRE_BLOCS_ANIMES 128
#define NOMBRE_TUILES 128
#define NOMBRE_SETS_TUILES 3
#define NOMBRE_SPRITES 16

extern SDL_Window *ecran;
extern SDL_Renderer *renderer;

extern SDL_Texture* textures[NOMBRE_TEXTURES];
//extern ElementGraphique* elements_graphiques[NOMBRE_TEXTURES*TAILLE_TEXTURE];
//extern BlocGraphique* blocs_graphiques[NOMBRE_BLOCS_GRAPHIQUES];
extern BlocAnime* blocs_animes[NOMBRE_BLOCS_ANIMES];
//extern ;


void init(char *titre);
void delay(unsigned int frameLimit);
SDL_Texture* ChargerImage(char* fichier);

#endif // MOTEUR_GRAPHIQUE_H_INCLUDED
