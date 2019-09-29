#ifndef DESSIN_H_INCLUDED
#define DESSIN_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Donnees.h"

void DessinerQuads(Donnees* sortie, int taille, int a);
void DessinerQuads(Donnees* sortie, int taille, int a, int RVBA);

#endif // DESSIN_H_INCLUDED
