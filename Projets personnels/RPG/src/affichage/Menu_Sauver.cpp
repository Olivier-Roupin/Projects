#include "affichage/Menu_Sauver.h"
#include <moteur_graphique.h>
#include <lib/Partie.h> //NOMBRE_SAUVEGARDES

#include <affichage/Menu.h> //Y_INFOS, Y_TEMPS, X_EQUIPE, DY_EQUIPE, NOMBRE_MENUS
#define Y_PARTIE 4
#define DY_PARTIE 6
#define X_PARTIE_HEROS 2
#define X_PARTIE_LIEU 8
#define X_PARTIE_TEMPS (LARGEUR_FENETRE-17)//16
#define X_CONFIRMER (LARGEUR_FENETRE/2-1)//15
#define DX_CONFIRMER 5
#define Y_CONFIRMER 1//23

void AfficherSauverAnimation(char animation) {
    effacerEcran();
    AfficherCadre(
        X_EQUIPE  +(LARGEUR_FENETRE+1  -X_EQUIPE  )*animation/6,
        1,-1,
        MAX_HEROS_EQUIPE*DY_EQUIPE+(4*DY_PARTIE-2+2-MAX_HEROS_EQUIPE*DY_EQUIPE)*animation/6); //Equipe (sortie)

    AfficherCadre(1,
        Y_INFOS   +(Y_PARTIE            -Y_INFOS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2   -X_EQUIPE+3)*animation/6,
        3         +(2*DY_PARTIE-2       -3         )*animation/6); //Infos -> Sauvegardes (1/2)
        
    AfficherCadre(1,
        Y_TEMPS   +(Y_PARTIE+DY_PARTIE*2-Y_TEMPS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2   -X_EQUIPE+3)*animation/6,
        2         +(2*DY_PARTIE-2       -2         )*animation/6); //Temps -> Sauvegardes (2/2)

    AfficherCadre(1,1,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        NOMBRE_MENUS-6*animation/6); //Menu -> Titre
    AfficherTexte("Sauvegarder",1,5-4*animation/6);
}

void AfficherSauverChoix(char** nom_heros, char** nom_cartes, char** temps, unsigned char choix) {
    effacerEcran();
    unsigned char i;
    AfficherCadre(1,1,-1,1); //"Sauvegarder"
    AfficherTexte("Sauvegarder", 1, 1);
    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
        const unsigned char couleur = choix == i ? COULEUR_BLANC : COULEUR_GRIS;
        AfficherCadre(1,Y_PARTIE+DY_PARTIE*i,-1,DY_PARTIE-2);
        if (temps[i]) {
            if (nom_heros[i])
                AfficherTexte(nom_heros[i],couleur,X_PARTIE_HEROS,Y_PARTIE+DY_PARTIE*i);
            else
                AfficherTexte("vide"      ,couleur,X_PARTIE_HEROS,Y_PARTIE+DY_PARTIE*i);
            AfficherTexte("Temps:", couleur, X_PARTIE_TEMPS,   Y_PARTIE+DY_PARTIE*i);
            AfficherTexte(temps[i], couleur, X_PARTIE_TEMPS+7, Y_PARTIE+DY_PARTIE*i);
            AfficherTexte("Lieu:" , couleur, X_PARTIE_HEROS,   Y_PARTIE+DY_PARTIE*i+2);
            if (nom_cartes[i])
                AfficherTexte(nom_cartes[i],couleur,X_PARTIE_LIEU,Y_PARTIE+2+DY_PARTIE*i);
            else
                AfficherTexte("vide"       ,couleur,X_PARTIE_LIEU,Y_PARTIE+2+DY_PARTIE*i);
        } else
            AfficherTexte("Vide", couleur, X_PARTIE_HEROS, Y_PARTIE+DY_PARTIE*i);
    }
    if (choix < NOMBRE_SAUVEGARDES)
        AfficherCurseur(X_PARTIE_HEROS-1, Y_PARTIE+DY_PARTIE*choix);
}

void AfficherSauverValider(char choix) {
    // AfficherCadre(1,Y_PARTIE+1+NOMBRE_SAUVEGARDES*DY_PARTIE,15,2);
    AfficherCadre(X_CONFIRMER,Y_CONFIRMER,15,2);
    AfficherTexte("Etes vous sur ?", X_CONFIRMER, Y_CONFIRMER); //15 caractères
    AfficherTexte("Non", X_CONFIRMER+1, Y_CONFIRMER+1);
    AfficherTexte("Oui", X_CONFIRMER+1+DX_CONFIRMER, Y_CONFIRMER+1);
    AfficherCurseur(X_CONFIRMER+DX_CONFIRMER*choix, Y_CONFIRMER+1);
}
