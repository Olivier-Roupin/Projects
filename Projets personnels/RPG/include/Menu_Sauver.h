#ifndef MENU_SAUVER_H_INCLUDED
#define MENU_SAUVER_H_INCLUDED

#include <Partie.h>
#include "controles.h"

#include <moteur_graphique.h>
#include <Input.h>

#define NOMBRE_CHOIX_MENU_SAUVER 2

int Sauver(Partie* partie);
void AfficherSauverChoix(Partie** parties, int id);
void AfficherSauverValider(int choix);
void SauverInformations(Partie* partie, std::ofstream* flux); //Sauve diverses informations (or, nombre de pas etc...)
void SauverInventaire(Inventaire* inventaire, std::ofstream* flux); //Sauve les objets de l'inventaire (objet et quantité)
void SauverEquipe(Equipe* equipe, std::ofstream* flux); //Sauve les personnages de l'équipe
void SauverHeros(Heros* heros, std::ofstream* flux); //Sauve le héros (nom pv pm etc..)

#endif // MENU_SAUVER_H_INCLUDED
