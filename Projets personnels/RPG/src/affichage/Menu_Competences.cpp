#include "affichage/Menu_Competences.h"
#include <moteur_graphique.h>
#include <conversions.h>

#include <affichage/Menu.h> //Y_INFOS, Y_TEMPS, X_EQUIPE, DY_EQUIPE, NOMBRE_MENUS
#define HAUTEUR_COMPETENCES 14

void AfficherCompetencesAnimation(const Heros* heros, char choix_heros, char animation) {
    effacerEcran();
    AfficherCadre(1,
        Y_INFOS   +(4                    -Y_INFOS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2    -X_EQUIPE+3)*animation/6,
        3         +(HAUTEUR_COMPETENCES-3         )*animation/6); //Infos -> Competences

    AfficherCadre(1,
        Y_TEMPS   +(HAUTEUR_COMPETENCES+4+2                -Y_TEMPS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2                      -X_EQUIPE+3)*animation/6,
        2         +(HAUTEUR_FENETRE-3-HAUTEUR_COMPETENCES-4-2         )*animation/6); //Temps -> Description

    AfficherCadre(1,1,
        X_EQUIPE-3+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-4-X_EQUIPE+3)*animation/6,
        NOMBRE_MENUS-6*animation/6); //Menu -> Titre
    AfficherTexte("Competences",1,3-2*(animation+2)/6);

    AfficherCadre(
        X_EQUIPE+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1 -X_EQUIPE)*animation/6,
        1,-1,
        MAX_HEROS_EQUIPE*DY_EQUIPE+(1-MAX_HEROS_EQUIPE*DY_EQUIPE)*animation/6); //Equipe -> Heros
    AfficherTexte(heros->GetNom(),
        X_EQUIPE + (LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1-X_EQUIPE)*animation/6,
        DY_EQUIPE*choix_heros+4 +(1-DY_EQUIPE*choix_heros-4)*animation/6);
}

void AfficherCompetencesTransition(char animation) {
    effacerEcran();
    AfficherCadre(1,1,LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-4,1); //"Competences"
    AfficherTexte("Competences",1,1); //11 caractères

    // AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1+(TAILLE_NOM_PERSONNAGE+4+4+2)*(animation+2)/6,1,TAILLE_NOM_PERSONNAGE+4+4,1); //Heros droite
    // AfficherCaractere('/',LARGEUR_FENETRE-4-1+(TAILLE_NOM_PERSONNAGE+4+4+2)*(animation+2)/6,1);
    // AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1,1-3+3*(animation-2)/6,TAILLE_NOM_PERSONNAGE+4+4,1); //Heros gauche
    // AfficherCaractere('/',LARGEUR_FENETRE-4-1+(TAILLE_NOM_PERSONNAGE+4+4+2)*(animation+2)/6,1-3+3*(animation-2)/6);
    if (animation < 3)
        AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1+(TAILLE_NOM_PERSONNAGE+4+4+2)*animation/3,1,
            TAILLE_NOM_PERSONNAGE+4+4-(TAILLE_NOM_PERSONNAGE+4+4)*animation/3,1); //Heros droite
    else
        AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1,1-3+3*(animation-3)/3,TAILLE_NOM_PERSONNAGE,1); //Heros gauche

    // AfficherCadre(1+(LARGEUR_FENETRE-2)*animation/6,4,LARGEUR_FENETRE-2,HAUTEUR_COMPETENCES); //droite
    AfficherCadre(1+(LARGEUR_FENETRE-2)*animation/6,4,LARGEUR_FENETRE-2-1+(LARGEUR_FENETRE-2)*animation/6+2,HAUTEUR_COMPETENCES); //droite (...+2) pour cropper
    // AfficherCadre(1-2-(LARGEUR_FENETRE-2)+(LARGEUR_FENETRE-2)*animation/6,4,LARGEUR_FENETRE-2,HAUTEUR_COMPETENCES); //gauche
    AfficherCadre(-1,4,LARGEUR_FENETRE-2+1+(LARGEUR_FENETRE-2)*animation/6-2-(LARGEUR_FENETRE-2)+1,HAUTEUR_COMPETENCES); //gauche (-1) pour cropper

    AfficherCadre(1,4+HAUTEUR_COMPETENCES+2,-1,-1); //Description
}

void AfficherCompetences(const Heros* heros, char choix) {
    effacerEcran();
    AfficherCadre(1,1,LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-4,1); //"Competences"
    AfficherTexte("Competences",1,1); //11 caractères
    AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1,1,TAILLE_NOM_PERSONNAGE+4+4,1); //Heros
    AfficherTexte(heros->GetNom(),LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-4-1,1);
    char nombre[4];
    EntierDroite(heros->GetMagie(), nombre, 4);
    AfficherTexte(nombre,LARGEUR_FENETRE-4-4,1);
    AfficherCaractere('/',LARGEUR_FENETRE-4-1,1);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_MAG), nombre, 4);
    AfficherTexte(nombre,LARGEUR_FENETRE-4,1);
    
    int i, longueur = -1, hauteur = HAUTEUR_COMPETENCES;
    AfficherCadre(1, 4, &longueur, hauteur);
    const int premier = premierElementListe(choix, hauteur-1, MAX_SORTS);
    for (i = premier; i < premier + hauteur-1; i++) {
        if (heros->GetSorts(i)) {
            char couleur = heros->estEnVie() && heros->GetSorts(i)->GetCoutMagie()
                        <= heros->GetMagie() ? COULEUR_BLANC : COULEUR_GRIS;
            AfficherTexte(heros->GetSorts(i)->GetNom(),couleur,2,i-premier+4);
            EntierDroite(heros->GetSorts(i)->GetCoutMagie(), nombre, 4);
            AfficherTexte(nombre,couleur,longueur-3,i-premier+4);
        }
    }
    AfficherCadre(1,4+hauteur+2,-1,-1); //Description
    if (choix >= 0 && choix < MAX_SORTS) {
        AfficherCurseur(1,choix-premier+4);
        if (heros->GetSorts(choix))
            AfficherTexte(heros->GetSorts(choix)->GetDescription(),1,4+hauteur+2);
    }
}
