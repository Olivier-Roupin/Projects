#include "affichage/Terrain.h"
#include <moteur_graphique.h>
#include <macros.h> //MIN, MAX

#define Y_SPRITE 2

#define NOMBRE_CHOIX_TERRAIN 4

//Seulement en version SDL : affiche les événements sur une couche
//la logique d'affichage est bien correcte pour les modulo?
//TODO: vérifier l'affichage en dehors de l'écran
//TODO: dupliquer sprites quand Repetition sur petite carte
//TODO: affichage de demi sprites incorrect
void AfficherEvenements(const Carte* carte, int X, int Y, int z, int D,
                        int dX, int dY, bool z_test) {
    unsigned char k;
    int dx, dy, i, j;
    char d;
    //Cherche un événement sur la couche z
    char image[3];
    for (k = 0; k < carte->GetNombre(); ++k)
        if (carte->GetEvenements(k))
            if (carte->GetEvenements(k)->GetZ() == z) {
                d  = carte->GetEvenements(k)->GetDeplace();
                dx = carte->GetEvenements(k)->GetDx();
                dy = carte->GetEvenements(k)->GetDy();
                j  = carte->GetEvenements(k)->GetX();
                i  = carte->GetEvenements(k)->GetY();
                //Surtout utile pour les sprites qui se déplacent
                if (carte->GetRepetition(j,i)) {
                    if (j-X+LARGEUR_FENETRE/4 < -MAX(0,dX))
                        j += carte->GetLargeur();
                    if (i-Y+HAUTEUR_FENETRE/4 < -MAX(0,dY))
                        i += carte->GetHauteur();
                }
                if (z != Z_MILIEU
                || (z == Z_MILIEU && i <  Y+dY && !z_test)
                || (z == Z_MILIEU && i >= Y+dY &&  z_test)) { //test profondeur
                    carte->GetEvenements(k)->RenduTerrain(image, LARGEUR_TUILE);
                    AfficherSprite(image, -D*dX+d*dx,
                                          -D*dY+d*dy-Y_SPRITE,
                                        //   2*(j-X+LARGEUR_FENETRE/4),
                                        //   2*(i-Y+HAUTEUR_FENETRE/4),
                                          2*(j-X)+LARGEUR_FENETRE/2,
                                          2*(i-Y)+HAUTEUR_FENETRE/2,
                                          image[2]==1, false);
                }
            }
}

/*void AfficherImage(const char* image, int j, int i) {
}*/

void AfficherCouche(const Carte* carte, int X, int Y, int z, int D,
                    int dX, int dY) {
    int i0,j0,i,j;
    // for (i0 = Y-HAUTEUR_FENETRE/4-MAX(0,dY);
    for (i0 = Y-(HAUTEUR_FENETRE+2)/4-MAX(0,dY);
         i0 < HAUTEUR_FENETRE/2+Y-HAUTEUR_FENETRE/4-MIN(0,dY); ++i0)
        for (j0 = X-LARGEUR_FENETRE/4-MAX(0,dX);
             j0 < LARGEUR_FENETRE/2+X-LARGEUR_FENETRE/4-MIN(0,dX); ++j0) {
            i=i0; //pour le modulo
            j=j0;
            carte->GetRepetition(j,i);
            if ((unsigned int)j < carte->GetLargeur() && j >= 0
             && (unsigned int)i < carte->GetHauteur() && i >= 0 && z >= 0 && z < NOMBRE_Z)
                if (z == Z_BAS || carte->GetTuile(j,i,z))
                    AfficherTuile(carte->GetImageTuile(j,i,z),
                                        -D*dX, -D*dY,
                                        // 2*(j0-X+LARGEUR_FENETRE/4),
                                        // 2*(i0-Y+HAUTEUR_FENETRE/4));
                                        2*(j0-X)+LARGEUR_FENETRE/2,
                                        2*(i0-Y)+HAUTEUR_FENETRE/2);
        }
}

void AfficherHeros(char Orientation, bool step, int id) {
    char image[2];
    image[0] = (char)(id & 255);
    switch (Orientation) {
        case ORIENTATION_DROITE:
            image[1] = step ? 5 : 4;
            AfficherHeros(image, 0,-Y_SPRITE,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2,true,false);
            break;
        case ORIENTATION_HAUT:
            image[1] = step ? 3 : 2;
            AfficherHeros(image, 0,-Y_SPRITE,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2);
            break;
        case ORIENTATION_GAUCHE:
            image[1] = step ? 5 : 4;
            AfficherHeros(image, 0,-Y_SPRITE,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2);
            break;
        case ORIENTATION_BAS:
        default:
            image[1] = step ? 1 : 0;
            AfficherHeros(image, 0,-Y_SPRITE,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2);
    }
}

//affiche le monde ET les sprites
void AfficherCarte(const Carte* carte, int X, int Y, char Orientation, int D,
                   int dX, int dY, int id) {
    AfficherCouche(    carte, X, Y, Z_BAS,    D, dX, dY);
    AfficherEvenements(carte, X, Y, Z_BAS,    D, dX, dY, false);
    AfficherCouche(    carte, X, Y, Z_MILIEU, D, dX, dY);
    AfficherEvenements(carte, X, Y, Z_MILIEU, D, dX, dY, true);
    AfficherHeros(Orientation, D<=-LARGEUR_TUILE/2, id);
    AfficherEvenements(carte, X, Y, Z_MILIEU, D, dX, dY, false);
    AfficherEvenements(carte, X, Y, Z_HAUT,   D, dX, dY, false);
    AfficherCouche(    carte, X, Y, Z_HAUT,   D, dX, dY);
}

void AfficherTerrain(const Partie* partie, int D, int dX, int dY) {
    setCouleurEcran(0, 0, 32);
    effacerEcran();
    if (partie->GetCarte() && partie->GetEquipe()->GetHeros(partie->GetMeneur()))
        AfficherCarte(partie->GetCarte(), partie->GetX(), partie->GetY(),
                    partie->GetOrientation(), D, dX, dY, partie->GetEquipe()->GetHeros(partie->GetMeneur())->GetId());
}

void AfficherMessage(const char* val) {
    AfficherCadre(1,1,-1,6);
    AfficherTexte(val,1,1);
}

/*void AfficherMessageTransition(char animation) {
    AfficherCadre(1,1,-1,animation);
}*/

void AfficherChoix(char choix, char nombre,
                  const char* val1, const char* val2,
                  const char* val3, const char* val4) {
    int i;
    const char* val[NOMBRE_CHOIX_TERRAIN] = {val1, val2, val3, val4};
    AfficherCadre(1,1,-1,6);
    for (i = 0; i < nombre; i++)
        AfficherTexte(val[i],2,1+i);
    if (choix >= 0 && choix < nombre)
        AfficherCurseur(1,1+choix);
}

void AfficherDemarrerCombat(char animation) {
    // AfficherDithers((HAUTEUR_FENETRE+LARGEUR_FENETRE)*animation/6-(HAUTEUR_FENETRE+LARGEUR_FENETRE), 0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    AfficherDithers((HAUTEUR_FENETRE+LARGEUR_FENETRE)*animation/6-(HAUTEUR_FENETRE-1+LARGEUR_FENETRE-1), 0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
}