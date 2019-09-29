#ifndef TRACER_H_INCLUDED
#define TRACER_H_INCLUDED

#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <SDL/SDL.h>

#define TAILLE_ECRAN 768

long tracerLigne(SDL_Surface *ecran, long point1_X, long point1_Y, long point2_X, long point2_Y, long couleur_R, long couleur_G, long couleur_B, long epaisseur);
long tracerRayon(SDL_Surface *ecran, long point1_X, long point1_Y, long point2_X, long point2_Y, long couleur_R, long couleur_G, long couleur_B, long epaisseur);
void PutPixelColor(SDL_Surface *surface, int x, int y, SDL_Color couleur);

#endif // TRACER_H_INCLUDED
