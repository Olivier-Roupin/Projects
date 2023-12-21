#ifndef MENU_ETAT_AFFICHAGE_H_INCLUDED
#define MENU_ETAT_AFFICHAGE_H_INCLUDED

#include <lib/Heros.h>

// void AfficherEtatAnimation(char animation);
void AfficherEtatAnimation(const Heros* heros, int choix_heros, char animation);
void AfficherEtatTransition(char animation);
void AfficherEtat(const Heros* heros); //BETA Affiche plein d'info sur le héros

#endif // MENU_ETAT_AFFICHAGE_H_INCLUDED
