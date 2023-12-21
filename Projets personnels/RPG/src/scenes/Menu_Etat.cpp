#include "scenes/Menu_Etat.h"
#include <affichage/Menu_Etat.h>
#include <moteur_graphique.h>
#include <scenes/Menu_Equipement.h> //ChercherHerosPrecedent, ChercherHerosSuivant

int Etat(Equipe* equipe, Input* input, char& choix_heros) {
    char animation;
    for (animation = 0; animation < 6; ++animation) {
        AfficherEtatAnimation(equipe->GetHeros(choix_heros), choix_heros, animation); //frames 0-5
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        AfficherEtat(equipe->GetHeros(choix_heros));
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeL()) {
            for (animation = 0; animation < 6; ++animation) {
                AfficherEtatTransition(animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            choix_heros = ChercherHerosPrecedent(equipe, choix_heros);
        }
        if (input->takeR()) {
            for (animation = 0; animation < 6; ++animation) {
                AfficherEtatTransition(5-animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            choix_heros = ChercherHerosSuivant(equipe, choix_heros);
        }
    }
    for (animation = 0; animation < 6; ++animation) {
        AfficherEtatAnimation(equipe->GetHeros(choix_heros), choix_heros, 6-animation); //frames 6-1
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}
