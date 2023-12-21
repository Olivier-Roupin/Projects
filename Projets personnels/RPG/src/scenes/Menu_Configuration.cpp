#include "scenes/Menu_Configuration.h"
#include <affichage/Menu_Configuration.h>
#include <moteur_graphique.h>
#include <Input.h>

#define NOMBRE_CHOIX_CONFIGURATION 3

int Configuration(Partie* partie) {
    Input* input = partie->GetInput();
    char choix = 0;
    char animation;
    for (animation = 0; animation < 6; ++animation) {
        AfficherConfigurationAnimation(animation); //frames 0-5
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        AfficherConfiguration(partie, choix);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeHaut())
            choix = AVANT(choix,NOMBRE_CHOIX_CONFIGURATION);
        if (input->takeBas())
            choix = APRES(choix,NOMBRE_CHOIX_CONFIGURATION);
        switch (choix) {
        case 0:
            if (input->takeGauche())
                partie->ChangerVitesseCombat(-1);
            if (input->takeDroite())
                partie->ChangerVitesseCombat(+1);
            break;
        case 1:
            if (input->takeGauche())
                partie->ChangerModeCombat(-1);
            if (input->takeDroite())
                partie->ChangerModeCombat(+1);
            break;
        case 2:
            if (input->takeGauche())
                partie->ChangerMemoriserCurseur();
            if (input->takeDroite())
                partie->ChangerMemoriserCurseur();
            break;
        default:
            break;
        }
    }
    input->setB(0);
    for (animation = 0; animation < 6; ++animation) {
        AfficherConfigurationAnimation(6-animation); //frames 6-1
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}
