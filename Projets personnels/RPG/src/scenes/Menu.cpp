#include "scenes/Menu.h"
#include <affichage/Menu.h>
#include <moteur_graphique.h> //horloge
#include <scenes/Menu_Objets.h> //Objets, Input
#include <scenes/Menu_Equipement.h> //Equipement
#include <scenes/Menu_Competences.h> //Competences
#include <scenes/Menu_Etat.h> //Etat
#include <scenes/Menu_Configuration.h> //Configuration
#include <scenes/Menu_Sauver.h> //Sauver

#define NOMBRE_CHOIX_MENU 7

int Menu(Partie* partie) {
    Input* input = partie->GetInput();
    char choix  =  0; // Menu principal
    char choix2 = -1; // Pour quitter ou pour échanger des héros
    char choix3 = -1; // Choix héros
    char animation;
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMenuAnimation(animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB() && !input->getX() && (choix != 6 || !input->getA())) {
        partie->SetTempsActif(horloge());
        AfficherMenu(partie, choix, choix2, choix3);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (choix2 == -1 && choix3 == -1) {
            if (input->takeHaut())
                choix = AVANT(choix, NOMBRE_CHOIX_MENU);
            if (input->takeBas())
                choix = APRES(choix, NOMBRE_CHOIX_MENU);
            if (input->takeDroite()) { //Equipe
                choix = -1;
                choix3 = 0;
            }
            if (input->takeA())
                switch (choix) {
                case 0:  //Objets
                    if (partie->GetInventaire())
                        Objets(partie);
                    break;
                case 1: //Equipements
                case 2: //Competences
                case 3: //Etat
                    // chercher le premier héros ? ou 0 ?
                    choix3 = ChercherHerosSuivant(partie->GetEquipe(), -1);
                    break;
                case 4: //Configuration
                    Configuration(partie);
                    break;
                case 5: //Sauver
                    Sauver(partie);
                    break;
                case 6: //Quitter
                    choix2 = 0;
                    break;
                default:
                    break;
                }
        } else if (choix3 == -1) { // "Quitter ?"
            if (input->takeGauche())
                choix2 = 1 - choix2;
            if (input->takeDroite())
                choix2 = 1 - choix2;
            if (input->takeA()) {
                if (choix2 == 1) {
                    for (animation = 0; animation <= 6; ++animation) {
                        AfficherMenuAnimation(6-animation);
                        afficherEcran();
                        syncEcran(frameLimit);
                    }
                    return 1;
                }
                choix2 = -1;
            }
            if (input->takeB())
                choix2 = -1;
        } else { // choix d'un héros
            if (partie->GetEquipe()) {
                if (input->takeHaut()) {
                    if (choix == -1)
                        choix3 = AVANT(choix3,MAX_HEROS_EQUIPE);
                    else
                        choix3 = ChercherHerosPrecedent(partie->GetEquipe(), choix3);
                }
                if (input->takeBas()) {
                    if (choix == -1)
                        choix3 = APRES(choix3,MAX_HEROS_EQUIPE);
                    else
                        choix3 = ChercherHerosSuivant(partie->GetEquipe(), choix3);
                }
                if (input->takeA()) {
                    if (choix == -1) { //Equipe
                        if (choix2 == -1)
                            choix2 = choix3;
                        else if (choix2 == choix3) {
                            partie->GetEquipe()->GetHeros(choix2)->ChangerRang();
                            choix2 = -1;
                        } else {
                            partie->GetEquipe()->EchangerHeros(choix2, choix3);
                            choix2 = -1;
                        }
                    } else if (partie->GetEquipe()->GetHeros(choix3)) {
                        switch (choix) {
                        case 1: //Equipements
                            Equipements(partie->GetInventaire(),
                                        partie->GetEquipe(),
                                        partie->GetInput(), choix3);
                            break;
                        case 2: //Competences
                            Competences(partie, choix3);
                            break;
                        case 3: //Etat
                            Etat(partie->GetEquipe(),partie->GetInput(),choix3);
                            break;
                        default:
                            break;
                        }
                        choix3 = -1; // retourne direct au menu principal
                    }
                }
            }
            if (input->takeB()) {
                if (choix2 != -1) //Equipe en changement
                    choix2 = -1;
                else if (choix != -1)
                    choix3 = -1;
                else { //Equipe
                    for (animation = 0; animation <= 6; ++animation) {
                        AfficherMenuAnimation(6-animation);
                        afficherEcran();
                        syncEcran(frameLimit);
                    }
                    return 0;
                }
            }
            if (input->takeGauche() && choix == -1 && choix2 == -1) { //Equipe
                choix3 = -1;
                choix = 0;
            }
        }
    }
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMenuAnimation(6-animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}
