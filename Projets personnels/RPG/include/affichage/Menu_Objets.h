#ifndef MENU_OBJETS_AFFICHAGE_H_INCLUDED
#define MENU_OBJETS_AFFICHAGE_H_INCLUDED

#include <lib/Inventaire.h>
#include <lib/Equipe.h>

void AfficherObjetsAnimation(char animation); //Afficher ouverture du menu
void AfficherObjets(const Inventaire* inventaire, char choix, char choix2 = -1); //Afficher les objets de l'inventaire et leur nombre
void AfficherEquipe_Reduit(const Equipe* equipe, char choix, bool quantite, char x, char y); //Affiche les membres de l'équipe

#endif // MENU_OBJETS_AFFICHAGE_H_INCLUDED
