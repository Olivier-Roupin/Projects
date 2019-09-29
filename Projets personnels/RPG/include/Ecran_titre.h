#ifndef ECRAN_TITRE_H_INCLUDED
#define ECRAN_TITRE_H_INCLUDED

#include <Partie.h>
#include <controles.h>

#include <moteur_graphique.h>
#include <Input.h>

//#define QUITTER 2
#define NOMBRE_CHOIX_ECRAN_TITRE 3

int Ecran_titre();
void AfficherEcran_Titre(int choix); //Affiche l'écran de titre
void AfficherCharger(Partie** parties, int id);

#endif // ECRAN_TITRE_H_INCLUDED
