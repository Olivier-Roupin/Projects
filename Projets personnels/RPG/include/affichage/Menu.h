#ifndef MENU_AFFICHAGE_H_INCLUDED
#define MENU_AFFICHAGE_H_INCLUDED

#include <lib/Partie.h>

#define X_EQUIPE 17
#define DY_EQUIPE 4
#define Y_INFOS 10
#define Y_TEMPS 15
#define NOMBRE_MENUS 7

void AfficherMenuAnimation(char animation);
void AfficherMenu(const Partie* partie, char choix, char choix2, char choix3);

#endif // MENU_AFFICHAGE_H_INCLUDED
