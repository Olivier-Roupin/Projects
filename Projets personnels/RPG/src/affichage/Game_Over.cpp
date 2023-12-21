#include "affichage/Game_Over.h"
#include <moteur_graphique.h>

#define X_GAME_OVER (LARGEUR_FENETRE/2-5) //11
#define Y_GAME_OVER (HAUTEUR_FENETRE/2-1) //13

void AfficherGame_Over() {
    setCouleurEcran(32, 0, 0);
    effacerEcran();
    AfficherTexte("Game Over", X_GAME_OVER, Y_GAME_OVER);
}
