#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <scenes/Menu.h>
#include <scenes/Combat.h>
#include <scenes/Menu_Magasin.h>

int Terrain(Partie* partie);

void ActualiserEvenements(Partie* partie);

bool DeplacerHeros(Partie* partie, int dX, int dY, bool fantome = false); //Teste les collisions et déplace le héros

//Commandes événements:
int Message(Partie* partie, const char* val); //retourne 1 si validation
// char MessageTransition(char animation); //retourne 0 si fini (<0 sinon)
int Choix(Partie* partie, char nombre, const char* val1, const char* val2 = "",
    const char* val3 = "", const char* val4 = ""); //retourne 1 si validation
int FonduSortant(int vitesse);
int FonduEntrant(int vitesse);
// void TeleporterEquipe(Partie* partie, int id, int x, int y, char orientation);
void TeleporterEquipe(Partie* partie, Carte* carte, int x, int y, char orientation);
int DeplacerEvenement(Carte* carte, unsigned char id, int dX, int dY, int Xheros, int Yheros, bool orienter=true, bool fantome=false, bool optionnel=false); //retourne 1 si succès
int OrienterEvenement(Carte* carte, unsigned char id, char orientation, int Xheros, int Yheros);
void OuvrirMagasin(Partie* partie, Magasin* magasin);
bool DemarrerCombat(Partie* partie, GroupeMonstres* groupe, bool gameover = true,
                    int D = 0, int dX = 0, int dY = 0);
unsigned char ChangerTuile(Partie* partie, unsigned char tuile, int X, int Y, int Z); //retourne la tuile précédente
#endif // TERRAIN_H_INCLUDED
