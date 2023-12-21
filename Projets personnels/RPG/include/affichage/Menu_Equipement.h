#ifndef MENU_EQUIPEMENT_AFFICHAGE_H_INCLUDED
#define MENU_EQUIPEMENT_AFFICHAGE_H_INCLUDED

#include <lib/Heros.h> //Equipable
#include <lib/Inventaire.h>

void AfficherEquipementsAnimation(const Heros* heros, char choix_heros, char animation);
void AfficherEquipementsTransition(char animation);
void AfficherEquipements(const Heros* heros); //Affiche le nom et stats du héros
void AfficherChoixEquipementTransition(char animation);
void AfficherChoixEquipement(const Heros* heros, char choix = -1); //Afficher l'équipement du héros
void AfficherObjetsEquipement(const Inventaire* inventaire, const Equipable* equipe, int choix, unsigned char type1, unsigned char type2 = 0); //Afficher seulement les objets du type1 ou du type2 (accessoire arme etc...)

#endif // MENU_EQUIPEMENT_AFFICHAGE_H_INCLUDED
