#ifndef MENU_EQUIPEMENT_H_INCLUDED
#define MENU_EQUIPEMENT_H_INCLUDED

#include <lib/Inventaire.h>
#include <lib/Equipe.h>
#include <Input.h>

void Equipements(Inventaire *inventaire, Equipe* equipe, Input* input, char &choix_heros);

char ChercherHerosPrecedent(const Equipe* equipe, char choix);
char ChercherHerosSuivant(const Equipe* equipe, char choix);
int ChercherObjetPrecedent(const Inventaire* inventaire, int choix, unsigned char type1, unsigned char type2 = 0); //Cherche l'objet précédent du type1 ou type2
int ChercherObjetSuivant(const Inventaire* inventaire, int choix, unsigned char type1, unsigned char type2 = 0);

#endif // MENU_EQUIPEMENT_H_INCLUDED
