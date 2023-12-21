#include "affichage/Menu_Nom.h"
#include <moteur_graphique.h>
#include <conversions.h>
#include <lib/Personnage.h> //TAILLE_NOM_PERSONNAGE

#define NOM_COL1 3
#define NOM_COL2 (LARGEUR_FENETRE-NOMBRE_COLONNES_CLAVIER*2-NOM_COL1+1) //20
#define NOM_X (LARGEUR_FENETRE/2-(TAILLE_NOM_PERSONNAGE+1)/2) //11
#define NOM_Y 4
#define NOM_COL_Y 6
#define HEROS_X (LARGEUR_FENETRE/2-1) //14
#define HEROS_Y 6
#define OPTIONS_Y (NOM_COL_Y+NOMBRE_LIGNES_CLAVIER+3)

void AfficherChoixNom(char* image, char* nom, unsigned char x, unsigned char y,
                                              unsigned char curseur) {
    unsigned char i, j;
    char c;
    effacerEcran();
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Changer nom", 1, 1); //11 caractères
    AfficherCadre(1,4,-1,-1);
    AfficherTexte(nom, NOM_X, NOM_Y);
    AfficherCaractere('?', NOM_X+curseur, 4);
    if (image[1] < 12)
        AfficherHeros(image, HEROS_X, HEROS_Y);
    else
        AfficherHeros(image, HEROS_X, HEROS_Y+1);
    // for (i = P_A; i <= P_Z; ++i) //on suppose une continuité de stockage
    const unsigned char couleur = curseur < TAILLE_NOM_PERSONNAGE ?
        COULEUR_BLANC : COULEUR_GRIS;
    i = j = 0;
    for (c = 'A'; c <= 'Z'; ++c) {
        AfficherCaractere(c, couleur, NOM_COL1+2*i, NOM_COL_Y+j);
        ++i;
        if (i == NOMBRE_COLONNES_CLAVIER) {
            i = 0;
            ++j;
        }
    }
    AfficherTexte("SPA", curseur > 0 && curseur < TAILLE_NOM_PERSONNAGE ?
        COULEUR_BLANC : COULEUR_GRIS, NOM_COL1+5, NOM_COL_Y+j);
    AfficherTexte("Defaut" , NOM_COL1, OPTIONS_Y);
    i = j = 0;
    for (c = 'a'; c <= 'z'; ++c) {
        AfficherCaractere(c, couleur, NOM_COL2+2*i, NOM_COL_Y+j);
        ++i;
        if (i == NOMBRE_COLONNES_CLAVIER) {
            i = 0;
            ++j;
        }
    }
    AfficherTexte("DEL",     curseur > 0 ? COULEUR_BLANC : COULEUR_GRIS,
        NOM_COL2+5, NOM_COL_Y+j);
    AfficherTexte("Valider", curseur > 0 ? COULEUR_BLANC : COULEUR_GRIS,
        NOM_COL2, OPTIONS_Y);
    if (y < NOMBRE_LIGNES_CLAVIER-1) {
        if (x < NOMBRE_COLONNES_CLAVIER)
            AfficherCurseur(NOM_COL1-1+2*x, NOM_COL_Y+y);
        else //if (x < 2*NOMBRE_COLONNES_CLAVIER)
            AfficherCurseur(NOM_COL2-1+2*(x-NOMBRE_COLONNES_CLAVIER), NOM_COL_Y+y);
    } else if (y == NOMBRE_LIGNES_CLAVIER-1) {
        if (x < NOMBRE_COLONNES_CLAVIER-2)
            AfficherCurseur(NOM_COL1-1+2*x, NOM_COL_Y+y);
        else if (x < NOMBRE_COLONNES_CLAVIER)
            AfficherCurseur(NOM_COL1-4+2*NOMBRE_COLONNES_CLAVIER, NOM_COL_Y+y);
        else if (x < 2*NOMBRE_COLONNES_CLAVIER-2)
            AfficherCurseur(NOM_COL2-1+2*(x-NOMBRE_COLONNES_CLAVIER), NOM_COL_Y+y);
        else //if (x < 2*NOMBRE_COLONNES_CLAVIER)
            AfficherCurseur(NOM_COL2-4+2*NOMBRE_COLONNES_CLAVIER, NOM_COL_Y+y);
    } else {
        if (x < NOMBRE_COLONNES_CLAVIER)
            AfficherCurseur(NOM_COL1-1, OPTIONS_Y);
        else
            AfficherCurseur(NOM_COL2-1, OPTIONS_Y);
    }
}
