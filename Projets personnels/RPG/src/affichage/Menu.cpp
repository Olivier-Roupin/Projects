#include "affichage/Menu.h"
#include <moteur_graphique.h>
#include <conversions.h>

#define DX_QUITTER 5
#define X_QUITTER (LARGEUR_FENETRE/2-8)
#define Y_QUITTER (Y_TEMPS/2) //15

void AfficherMenuAnimation(char animation) {
    setCouleurEcran(0, 32, 0);
    effacerEcran();
    AfficherCadre(                1-14+14*animation/6,Y_INFOS,X_EQUIPE-3,3);
    AfficherTexte("Or:"          ,1-14+14*animation/6,Y_INFOS);
    AfficherTexte("Pas:"         ,1-14+14*animation/6,Y_INFOS+1);
    AfficherTexte("Lieu:"        ,1-14+14*animation/6,Y_INFOS+2);
    AfficherCadre(                1-14+14*animation/6,Y_TEMPS,X_EQUIPE-3,2);
    AfficherTexte("Temps:"       ,1-14+14*animation/6,Y_TEMPS);
    AfficherCadre(                1-14+14*animation/6,1,X_EQUIPE-3,NOMBRE_MENUS);
    AfficherTexte("Objets"       ,1-14+14*animation/6,1);
    AfficherTexte("Equipement"   ,1-14+14*animation/6,2);
    AfficherTexte("Competences"  ,1-14+14*animation/6,3);
    AfficherTexte("Etat"         ,1-14+14*animation/6,4);
    AfficherTexte("Configuration",1-14+14*animation/6,5); //13 caractères
    AfficherTexte("Sauvegarder"  ,1-14+14*animation/6,6);
    AfficherTexte("Quitter"      ,1-14+14*animation/6,7);
    
    AfficherCadre(X_EQUIPE+(LARGEUR_FENETRE-16-2)-(LARGEUR_FENETRE-16-2)*animation/6,1,(LARGEUR_FENETRE-16-2),MAX_HEROS_EQUIPE*DY_EQUIPE); //Equipe
}

void AfficherEquipe(const Equipe* equipe, char choix, char choix2) {
    unsigned char i;
    AfficherCadre(X_EQUIPE,1,-1,MAX_HEROS_EQUIPE*DY_EQUIPE);
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i) {
        const Heros* heros = equipe->GetHeros(i);
        if (heros) {
            char image[2];
            heros->RenduCombat(image);
            if (heros->GetRang() == RANG_AVANT) {
                if (image[1] < 12)
                    AfficherHeros(image, X_EQUIPE+3, DY_EQUIPE*i+1);
                else
                    AfficherHeros(image, X_EQUIPE+3, DY_EQUIPE*i+2);
            } else {
                if (image[1] < 12)
                    AfficherHeros(image, X_EQUIPE+5, DY_EQUIPE*i+1);
                else
                    AfficherHeros(image, X_EQUIPE+5, DY_EQUIPE*i+2);
            }
            AfficherTexte(heros->GetNom(), X_EQUIPE, DY_EQUIPE*i+4);
            char vie[5];
            EntierDroite(heros->GetVie(),vie,5);
            AfficherTexte(vie, X_EQUIPE+3+TAILLE_NOM_PERSONNAGE, DY_EQUIPE*i+4);
        }
    }
    if (choix >= 0 && choix < MAX_HEROS_EQUIPE) {
        AfficherCurseur(X_EQUIPE-1, DY_EQUIPE*choix+2);
        if (choix2 >= 0 && choix2 < MAX_HEROS_EQUIPE)
            AfficherCurseur(X_EQUIPE-2, DY_EQUIPE*choix2+2);
    }
}

void AfficherQuitter(int choix) {
    AfficherCadre(X_QUITTER,Y_QUITTER,15,2);
    AfficherTexte("Etes vous sur ?",X_QUITTER,             Y_QUITTER  ); //15 caractères
    AfficherTexte("Non",            X_QUITTER+1,           Y_QUITTER+1);
    AfficherTexte("Oui",            X_QUITTER+1+DX_QUITTER,Y_QUITTER+1);
    AfficherCurseur(X_QUITTER+DX_QUITTER*choix, Y_QUITTER+1);
}

void AfficherMenu(const Partie* partie, char choix, char choix2, char choix3) {
    setCouleurEcran(0, 32, 0);
    effacerEcran();
    AfficherCadre(1,Y_INFOS,X_EQUIPE-3,3);
    AfficherTexte("Or:",          1,Y_INFOS);
    char orT[10];
    EntierDroite(partie->GetOr(),orT,Y_INFOS);
    AfficherTexte(orT,            6,Y_INFOS);
    AfficherTexte("Pas:",         1,Y_INFOS+1);
    char pas[9];
    EntierDroite(partie->GetPas(),pas,9);
    AfficherTexte(pas,            7,Y_INFOS+1);
    AfficherTexte("Lieu:",        1,Y_INFOS+2);
    AfficherTexte(partie->GetCarte()->GetNom(),8,Y_INFOS+2);
    AfficherCadre(1,Y_TEMPS,X_EQUIPE-3,2);
    AfficherTexte("Temps:",       1,Y_TEMPS); //6 caractères
    char temps[9];
    Int2Temps(partie->GetTempsJeu(), temps);
    AfficherTexte(temps,          X_EQUIPE-3-7,Y_TEMPS+1);
    const unsigned char couleur = choix2 == -1 && choix3 == -1 ? COULEUR_BLANC
                                                               : COULEUR_GRIS;
    AfficherCadre(1,1,14,NOMBRE_MENUS);
    AfficherTexte("Objets"       , couleur, 1, 1);
    AfficherTexte("Equipement"   , choix == 1 ? COULEUR_BLANC : couleur, 1, 2);
    AfficherTexte("Competences"  , choix == 2 ? COULEUR_BLANC : couleur, 1, 3);
    AfficherTexte("Etat"         , choix == 3 ? COULEUR_BLANC : couleur, 1, 4);
    AfficherTexte("Configuration", couleur, 1, 5); //13 caractères
    AfficherTexte("Sauvegarder"  , couleur, 1, 6);
    AfficherTexte("Quitter"      , choix == 6 ? COULEUR_BLANC : couleur, 1, 7);
    AfficherEquipe(partie->GetEquipe(), choix3, choix2); //affiché après pour curseur
    if (choix >= 0 && choix < NOMBRE_MENUS) {
        AfficherCurseur(0,1+choix);
        if (choix2 != -1)
            AfficherQuitter(choix2);
    }
}
