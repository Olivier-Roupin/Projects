#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <Menu.h>
#include <Combat.h>
#include <Menu_Magasin.h>

#define LARGEUR_FENETRE 8
#define HAUTEUR_FENETRE 7

#define NOMBRE_CHOIX_TERRAIN 4

int Terrain(Partie* partie);

void AfficherTerrain(Partie* partie, int meneur); //BETA Afficher l'écran de terrain

void AfficherHeros(Partie* partie, int meneur); //BETA Afficher le heros (son nom et ses coordonnées)

void AfficherEvenements(Carte* carte, int X, int Y); //BETA Afficher les personnages non jouables
void ActualiserEvenements(Partie* partie);

void AfficherCarte(Carte* carte, int X, int Y, int Orientation); //BETA Afficher la carte (décor)
void AfficherTile(Carte* carte, int X, int Y, int Orientation, int j, int i);

int OrientationHeros(Input* input); //Donne l'orientation du héros en fonction de l'input
void DeplacementHeros(int &dX, int &dY, Input* input); //Donne les déplacements en fonction de l'input
bool DeplacerHeros(Partie* partie, int dX, int dY); //Teste les collisions et déplace le héros
int TestEvenement(Carte* carte, int X, int Y, int Z = -1); //Teste la présence d'un événement en X,Y(,Z) et retourne son indice
int TestContact(Partie* partie); //Teste si le héros est en contact avec un événement et retourne son indice
bool TestCollision(Carte* carte, int X, int Y, int Z);
int TestAutomatique(Carte* carte, int e); //Recherche des événements automatiques (d'indice plus grand que e)

//Commandes événements:
int AfficherMessage(Partie* partie, std::string val); //retourne 1 si validation
int AfficherChoix(Partie* partie, int nombre, std::string val1, std::string val2 = "", std::string val3 = "", std::string val4 = ""); //retourne 1 si validation
void TeleporterEquipe(Partie* partie, Carte* carte, int x, int y, int orientation);
int DeplacerEvenement(Carte* carte, int id, int dX, int dY, int Xheros, int Yheros); //retourne 1 si succès
void OuvrirMagasin(Partie* partie, Magasin* magasin);
void DemarrerCombat(Partie* partie, GroupeMonstres* groupe, bool gameover = 1);
#endif // TERRAIN_H_INCLUDED
