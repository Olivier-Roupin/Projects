#include "affichage/Ecran_titre.h"
#include <moteur_graphique.h>
#include <lib/Partie.h> //NOMBRE_SAUVEGARDES

#define X_TEXTE_TITRE (LARGEUR_FENETRE/2-4) //12
#define Y_TEXTE_TITRE 2
#define Y_CHOIX_TITRE ((HAUTEUR_FENETRE+3)/4+1)//8
#define DY_CHOIX_TITRE 3

#define Y_PARTIE 4
#define DY_PARTIE 6
#define X_PARTIE_HEROS 2
#define X_PARTIE_LIEU 8
#define X_PARTIE_TEMPS (LARGEUR_FENETRE-17)//16

void AfficherEcran_Titre(char choix) {
    setCouleurEcran(32, 32, 32);
    effacerEcran();
    AfficherTexte("JeuOne",   X_TEXTE_TITRE+1, Y_TEXTE_TITRE);
    AfficherCadre(X_TEXTE_TITRE-1,Y_CHOIX_TITRE,10,1); //"Charger"
    AfficherTexte("Charger",  X_TEXTE_TITRE,   Y_CHOIX_TITRE);
    AfficherCadre(X_TEXTE_TITRE-1,Y_CHOIX_TITRE+DY_CHOIX_TITRE,10,1); //"Nouvelle"
    AfficherTexte("Nouvelle", X_TEXTE_TITRE,   Y_CHOIX_TITRE+DY_CHOIX_TITRE);
    AfficherCadre(X_TEXTE_TITRE-1,Y_CHOIX_TITRE+2*DY_CHOIX_TITRE,10,1); //"Quitter"
    AfficherTexte("Quitter",  X_TEXTE_TITRE,   Y_CHOIX_TITRE+2*DY_CHOIX_TITRE);
    if (choix >= 0 && choix < 3)
        AfficherCurseur(X_TEXTE_TITRE-1, Y_CHOIX_TITRE+DY_CHOIX_TITRE*choix);
}

void AfficherCharger(char** nom_heros, char** nom_cartes, char** temps,
                     unsigned char choix) {
    effacerEcran();
    unsigned char i;
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Charger",1,1); //7 caractères
    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
        const unsigned char couleur = choix == i ? COULEUR_BLANC : COULEUR_GRIS;
        AfficherCadre(1,Y_PARTIE+DY_PARTIE*i,-1,DY_PARTIE-2);
        if (temps[i]) {
            if (nom_heros[i])
                AfficherTexte(nom_heros[i], couleur, X_PARTIE_HEROS, Y_PARTIE+DY_PARTIE*i);
            else
                AfficherTexte("vide"      , couleur, X_PARTIE_HEROS, Y_PARTIE+DY_PARTIE*i);
            AfficherTexte("Temps:", couleur, X_PARTIE_TEMPS,   Y_PARTIE+DY_PARTIE*i); //6 caractères
            AfficherTexte(temps[i], couleur, X_PARTIE_TEMPS+7, Y_PARTIE+DY_PARTIE*i);
            AfficherTexte("Lieu:" , couleur, X_PARTIE_HEROS,   Y_PARTIE+DY_PARTIE*i+2);
            if (nom_cartes[i])
                AfficherTexte(nom_cartes[i], couleur, X_PARTIE_LIEU, Y_PARTIE+DY_PARTIE*i+2);
            else
                AfficherTexte("vide"       , couleur, X_PARTIE_LIEU, Y_PARTIE+DY_PARTIE*i+2);
        } else
            AfficherTexte("Vide", couleur, X_PARTIE_HEROS, Y_PARTIE+DY_PARTIE*i);
    }
    if (choix < NOMBRE_SAUVEGARDES)
        AfficherCurseur(1, Y_PARTIE+DY_PARTIE*choix);
}