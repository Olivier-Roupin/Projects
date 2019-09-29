#ifndef COMBAT_H_INCLUDED
#define COMBAT_H_INCLUDED

#include <Game_Over.h>
#include <Utilisable.h>
#include <controles.h>

#define NOMBRE_OBJETS_AFFICHES 5

int Combat(Partie* partie);
void AfficherCombat(Partie* partie); //Affiche l'écran de combat

void AfficherFond(Carte* carte, GroupeMonstres* groupe); //BETA Afficher le décor (selon où se trouve le joueur)

void AfficherEquipeCombat(Equipe* equipe, int cible, bool faction, bool quantite); //Afficher les héros de l'équipe
void AfficherHerosCombat(Heros* heros); //Afficher le héros
void AfficherJauge(int jauge); //Afficher la jauge d'action du héros

void AfficherMonstres(GroupeMonstres* groupe, int cible, bool faction, bool quantite); //Afficher les monstres ennemis
void AfficherCommandes(Heros* heros, int id); //BETA Afficher les actions exécutables par le héros (dont la jauge est pleine)
void AfficherObjetsCombat(Inventaire* inventaire, int choix);
void AfficherCompetencesCombat(Heros* heros, int choix);
int PremierObjetAfficheCombat(int choix);
int PremiereCompetenceAfficheCombat(int choix);

void ChoixHeros(Partie* partie, Input* input); //BETA Change le héros qui a ses actions affichées
void ChoixAction(Partie* partie, Input* input);
void ChoixCible(Partie* partie, Input* input);
void ChoixObjet(Partie* partie, Input* input);
void ChoixCapacite(Partie* partie, Input* input);

void ActionHeros(Partie* partie, int &combat);
void ActionMonstres(Partie* partie);

void ActualiserJauges(Equipe* equipe, GroupeMonstres* groupe); //BETA Actualise les jauges de tous les personnages en combat
void ViderJauges(Equipe* equipe); //BETA Vide les jauges de tous les héros

int CombatEnCours(int combat, Equipe* equipe, GroupeMonstres* groupe);

#endif // COMBAT_H_INCLUDED
