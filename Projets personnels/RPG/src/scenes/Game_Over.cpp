#include "scenes/Game_Over.h"
#include <affichage/Game_Over.h>
#include <moteur_graphique.h>

int Game_Over(Input* input) {
    while (!input->getA()) { //takeA ?
        AfficherGame_Over();
        input->Actualiser();
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}

