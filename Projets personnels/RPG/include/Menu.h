#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <Menu_Etat.h>
#include <Menu_Competences.h>
#include <Menu_Configuration.h>
#include <Menu_Sauver.h>

#define NOMBRE_CHOIX_MENU 7

int Menu(Partie* partie);
void AfficherMenu(Partie* partie, int choix, int choix2, int choix3); //Afficher le menu
void AfficherEquipe(Equipe* equipe, int choix); //Afficher les noms et rangs des membres de l'équipe
void AfficherQuitter(int choix);

#endif // MENU_H_INCLUDED
