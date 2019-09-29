#ifndef MENU_OBJETS_H_INCLUDED
#define MENU_OBJETS_H_INCLUDED

#include <Partie.h>
#include <Utilisable.h>
#include <controles.h>

#include <moteur_graphique.h>
#include <Input.h>

#define NOMBRE_OBJETS_AFFICHES 5

int Objets(Inventaire* inventaire, Equipe* equipe, Carte* carte);
int Objets(Partie* partie);

int Equipe_Reduit(Equipe* equipe); //Permet de choisir un membre de l'équipe

void AfficherObjets(Inventaire* inventaire, int choix); //Afficher les objets de l'inventaire et leur nombre
//void AfficherObjets(Inventaire* inventaire, int choix, int type); //Affiche seulement les objets d'un type (accessoire arme etc...)
void AfficherEquipe_Reduit(Equipe* equipe, int choix); //Affiche les membres de l'équipe

int PremierObjetAffiche(int choix); //BETA Donne l'indice du premier objet affiché à l'écran
int ChercherObjetPrecedent(Inventaire* inventaire, int choix, int type1, int type2 = -1); //Cherche l'objet précédent du type1 ou type2
int ChercherObjetSuivant(Inventaire* inventaire, int choix, int type1, int type2 = -1);

int UtiliserObjet(Inventaire* inventaire, Equipe* equipe, Carte* carte, Utilisable* objet, int Situation = MENU);
int UtiliserObjet(Partie* partie, Utilisable* objet, int Situation = MENU);

int UtiliserObjet(Utilisable* objet, Personnage* cible);
int UtiliserObjet(Utilisable* objet, Equipe* cible);

//int EchangerObjets(Inventaire* inventaire, int objet1, int objet2);

#endif // MENU_OBJETS_H_INCLUDED
