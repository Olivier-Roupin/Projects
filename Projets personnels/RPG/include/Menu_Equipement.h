#ifndef MENU_EQUIPEMENT_H_INCLUDED
#define MENU_EQUIPEMENT_H_INCLUDED

#include <Menu_Objets.h>

#define NOMBRE_CHOIX_EQUIPEMENT 6

int Equipements(Inventaire* inventaire, Equipe* equipe);
void ChoixEquipements(Inventaire *inventaire, Equipe* equipe, int &choix_heros);
int Objets_Reduit(Inventaire* inventaire, int type1, int type2 = -1); //C'est l'inventaire réduit aux objets du type1 ou type2, retourne l'indice de l'objet choisi

void AfficherEquipement(Equipe* equipe, int choix); //Afficher l'équipe
void AfficherChoixEquipement(Heros* heros, int choix = -1); //Afficher l'équipement du héros
void AfficherObjets_Reduit(Inventaire* inventaire, int choix, int type1, int type2 = -1); //Afficher seulement les objets du type1 ou du type2 (accessoire arme etc...)


#endif // MENU_EQUIPEMENT_H_INCLUDED
