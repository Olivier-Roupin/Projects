#ifndef COMBAT_AFFICHAGE_H_INCLUDED
#define COMBAT_AFFICHAGE_H_INCLUDED

#include <lib/Partie.h>

void AfficherCombat(Partie* partie);
void AfficherFuite(int val);
void AfficherVictoireExp(int val);
void AfficherVictoireNiveau(const char* nom, int val);
void AfficherVictoireOr(int val);
void AfficherVictoireObjet(const char* nom);

#endif // COMBAT_AFFICHAGE_H_INCLUDED
