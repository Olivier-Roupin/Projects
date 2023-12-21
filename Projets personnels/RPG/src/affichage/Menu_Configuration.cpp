#include "affichage/Menu_Configuration.h"
#include <moteur_graphique.h>
#include <conversions.h>

#include <affichage/Menu.h> //Y_INFOS, Y_TEMPS, X_EQUIPE, DY_EQUIPE, NOMBRE_MENUS

void AfficherConfigurationAnimation(char animation) {
    effacerEcran();
    AfficherCadre(
        X_EQUIPE  +(LARGEUR_FENETRE+1  -X_EQUIPE  )*animation/6,
        1,-1,
        NOMBRE_MENUS-6*animation/6+3+(HAUTEUR_FENETRE-2-3-3)*animation/6+2-2*animation/6+4);
        // MAX_HEROS_EQUIPE*DY_EQUIPE+(HAUTEUR_FENETRE-MAX_HEROS_EQUIPE*DY_EQUIPE)*animation/6); //Equipe (sortie)

    AfficherCadre(1,
        Y_INFOS   +(4                  -Y_INFOS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        3         +(HAUTEUR_FENETRE-2-3-3         )*animation/6); //Infos -> Configuation

    AfficherCadre(1,
        Y_TEMPS   +(HAUTEUR_FENETRE+1  -Y_TEMPS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        2-2*animation/6); //Temps (sortie)

    AfficherCadre(1,1,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        NOMBRE_MENUS-6*animation/6); //Menu -> Titre
    AfficherTexte("Configuration",1,5-4*animation/6);
}

void AfficherConfiguration(const Partie* partie, char choix) {
    unsigned char i;
    effacerEcran();
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Configuration",1,1); //13 caractères
    AfficherCadre(1,4,-1,-1);
    AfficherTexte("Vitesse:",2,4); //8 caractères
    for (i = MIN_VITESSE_COMBAT; i <= MAX_VITESSE_COMBAT; ++i) {
        AfficherCaractere('0'+i, partie->GetVitesseCombat() == i ?
            COULEUR_BLANC : COULEUR_GRIS,
            2*(i-MAX_VITESSE_COMBAT)+LARGEUR_FENETRE-3,4);
    }
    // AfficherCurseur(2*(partie->GetVitesseCombat()-MAX_VITESSE_COMBAT)+LARGEUR_FENETRE-4,4);

    AfficherTexte("Combat:",2,5); //7 caractères
    AfficherTexte("Actif" , partie->GetModeCombat()==MODE_ACTIF ?
        COULEUR_BLANC : COULEUR_GRIS, LARGEUR_FENETRE-20,5); //10
    AfficherTexte("Semi"  , partie->GetModeCombat()==MODE_SEMI_ACTIF ?
        COULEUR_BLANC : COULEUR_GRIS, LARGEUR_FENETRE-14,5); //16
    AfficherTexte("Passif", partie->GetModeCombat()==MODE_PASSIF ?
        COULEUR_BLANC : COULEUR_GRIS, LARGEUR_FENETRE-8 ,5); //22 //6 caractères
    // AfficherCurseur(LARGEUR_FENETRE-21+6*partie->GetModeCombat(),5); //9

    AfficherTexte("Memoriser curseur:",2,6); //18 caractères
    AfficherTexte("Non", partie->GetMemoriserCurseur() ?
        COULEUR_GRIS : COULEUR_BLANC, LARGEUR_FENETRE-9,6); //21
    AfficherTexte("Oui", partie->GetMemoriserCurseur() ?
        COULEUR_BLANC : COULEUR_GRIS, LARGEUR_FENETRE-5,6); //25
    // AfficherCurseur(LARGEUR_FENETRE-10+partie->GetMemoriserCurseur()*4,6); //20

    AfficherCurseur(1,4+choix);
}
