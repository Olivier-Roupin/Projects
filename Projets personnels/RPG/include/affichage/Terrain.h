#ifndef TERRAIN_H_SDL_INCLUDED
#define TERRAIN_H_SDL_INCLUDED

#include <lib/Partie.h>

void AfficherTerrain(const Partie* partie, int D, int dX, int dY);
//Commandes événements:
void AfficherMessage(const char* val);
// void AfficherMessageTransition(char animation);
void AfficherChoix(char choix, char nombre,
                   const char* val1, const char* val2,
                   const char* val3, const char* val4);
void AfficherDemarrerCombat(char animation);

#endif // TERRAIN_H_SDL_INCLUDED
