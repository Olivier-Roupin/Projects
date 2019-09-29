#ifndef MENU_COMPETENCES_H_INCLUDED
#define MENU_COMPETENCES_H_INCLUDED

#include <Partie.h>

#include <Menu_Objets.h>

int Competences(Equipe* equipe, Carte* carte);
void ChoixCompetences(Equipe* equipe, Carte* carte, int &choix_heros);

void AfficherCompetences(Equipe* equipe, int choix); //Afficher l'équipe
void AfficherChoixCompetences(Heros* heros, int choix = -1); //Afficher les compétences du héros

int PremiereCompetenceAffiche(int choix);

int UtiliserCompetence(Equipe* equipe, Carte* carte, Capacite* capacite, int choix_heros);
int UtiliserCompetence(Capacite* capacite, Personnage* cible);
int UtiliserCompetence(Capacite* capacite, Equipe* cible);

#endif // MENU_COMPETENCES_H_INCLUDED
