#include "affichage/Menu_Etat.h"
#include <moteur_graphique.h>
#include <conversions.h>

#include <affichage/Menu.h> //Y_INFOS, Y_TEMPS, X_EQUIPE, DY_EQUIPE, NOMBRE_MENUS
#define ETAT_COL 12

void AfficherEtatAnimation(const Heros* heros, int choix_heros, char animation) {
    effacerEcran();
    AfficherCadre(1,
        Y_INFOS   +(4                  -Y_INFOS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        3         +(HAUTEUR_FENETRE-2-3-3         )*animation/6); //Infos -> Etat

    AfficherCadre(1,
        Y_TEMPS   +(HAUTEUR_FENETRE+1  -Y_TEMPS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        2-2*animation/6); //Temps (sortie)

    AfficherCadre(1,1,
        X_EQUIPE-3+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-X_EQUIPE+3)*animation/6,
        NOMBRE_MENUS-6*animation/6); //Menu -> Titre
    AfficherTexte("Etat",1,4-3*(animation+1)/6);

    AfficherCadre(
        X_EQUIPE+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1 -X_EQUIPE)*animation/6,
        1,-1,
        MAX_HEROS_EQUIPE*DY_EQUIPE+(1-MAX_HEROS_EQUIPE*DY_EQUIPE)*animation/6); //Equipe -> Heros
    AfficherTexte(heros->GetNom(),
        X_EQUIPE+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1 -X_EQUIPE)*animation/6,
        DY_EQUIPE*choix_heros+4 +(1-DY_EQUIPE*choix_heros-4)*animation/6);
}

void AfficherEtatTransition(char animation) {
    effacerEcran();
    AfficherCadre(1,1,LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4,1); //"Etat"
    AfficherTexte("Etat",1,1);
    // AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1+(TAILLE_NOM_PERSONNAGE+2)*(animation+2)/6,1,TAILLE_NOM_PERSONNAGE,1); //Heros droite
    // AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1-3+3*(animation-2)/6,TAILLE_NOM_PERSONNAGE,1); //Heros gauche
    if (animation < 3)
        AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1+(TAILLE_NOM_PERSONNAGE+2)*animation/3,1,
            TAILLE_NOM_PERSONNAGE-TAILLE_NOM_PERSONNAGE*animation/3,1); //Heros droite
    else
        AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1-3+3*(animation-3)/3,TAILLE_NOM_PERSONNAGE,1); //Heros gauche

    const char droite = 1+(LARGEUR_FENETRE-2)*animation/6;
    // AfficherCadre(droite,4,LARGEUR_FENETRE-2,-1); //droite
    AfficherCadre(droite,4,LARGEUR_FENETRE-2-droite+2,-1); //droite (...+2) pour cropper
    AfficherTexte("Vie:"        ,droite, 6);
    // AfficherCaractere('/'       ,droite+11,6);
    AfficherTexte("Magie:"      ,droite, 7);
    // AfficherCaractere('/'       ,droite+12,7);
    AfficherTexte("Vitesse:"    ,droite, 8);
    AfficherTexte("Attaque P:"  ,droite, 9);
    AfficherTexte("Attaque M:"  ,droite,10);
    AfficherTexte("Precision:"  ,droite,11);
    // AfficherCaractere('%'       ,droite+13,11);
    AfficherTexte("Defense P:"  ,droite,12);
    AfficherTexte("Defense M:"  ,droite,13);
    AfficherTexte("Esquive:"    ,droite,14);
    // AfficherCaractere('%'       ,droite+11,14);
    AfficherTexte("Niveau:"     ,droite,16);
    AfficherTexte("Experience:" ,droite-1+LARGEUR_FENETRE-5-ETAT_COL-3,16);
    AfficherTexte("Alterations:",droite,18);

    const char gauche = droite-2-(LARGEUR_FENETRE-2);
    // AfficherCadre(gauche,4,LARGEUR_FENETRE-2,-1); //gauche
    AfficherCadre(-1,4,LARGEUR_FENETRE-2+gauche+1,-1); //gauche (-1) pour cropper
    AfficherTexte("Vie:"        ,gauche, 6);
    // AfficherCaractere('/'       ,gauche+11,6);
    AfficherTexte("Magie:"      ,gauche, 7);
    // AfficherCaractere('/'       ,gauche+12,7);
    AfficherTexte("Vitesse:"    ,gauche, 8);
    AfficherTexte("Attaque P:"  ,gauche, 9);
    AfficherTexte("Attaque M:"  ,gauche,10);
    AfficherTexte("Precision:"  ,gauche,11);
    // AfficherCaractere('%'       ,gauche+13,11);
    AfficherTexte("Defense P:"  ,gauche,12);
    AfficherTexte("Defense M:"  ,gauche,13);
    AfficherTexte("Esquive:"    ,gauche,14);
    // AfficherCaractere('%'       ,gauche+11,14);
    AfficherTexte("Niveau:"     ,gauche,16);
    AfficherTexte("Experience:" ,gauche-1+LARGEUR_FENETRE-5-ETAT_COL-3,16);
    AfficherTexte("Alterations:",gauche,18);
}

void AfficherEtat(const Heros* heros) {
    effacerEcran();
    AfficherCadre(1,1,LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4,1); //"Etat"
    AfficherTexte("Etat",1,1);
    AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1,TAILLE_NOM_PERSONNAGE,1); //Heros
    AfficherTexte(heros->GetNom(),LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1);

    char entier[5];
    AfficherCadre(1,4,-1,-1);
    AfficherTexte("Vie:",1,6);
    EntierDroite(heros->GetVie(), entier, 5);
    AfficherTexte(entier,ETAT_COL-2,6);
    AfficherCaractere('/',ETAT_COL-2+4,6);
    EntierGauche(heros->GetAttributTotal(ATTRIBUT_VIE ), entier, 5);
    AfficherTexte(entier,ETAT_COL-2+5,6);
    AfficherTexte("Magie:",1,7);
    EntierDroite(heros->GetMagie(), entier, 4);
    AfficherTexte(entier,ETAT_COL-1,7);
    AfficherCaractere('/',ETAT_COL-1+3,7);
    EntierGauche(heros->GetAttributTotal(ATTRIBUT_MAG ), entier, 4);
    AfficherTexte(entier,ETAT_COL-1+4,7);
    AfficherTexte("Vitesse:",1,8);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_VIT ), entier, 3);
    AfficherTexte(entier,ETAT_COL,8);
    AfficherTexte("Attaque P:",1,9);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_ATKP), entier, 3);
    AfficherTexte(entier,ETAT_COL,9);
    AfficherTexte("Attaque M:",1,10);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_ATKM), entier, 3);
    AfficherTexte(entier,ETAT_COL,10);
    AfficherTexte("Precision:",1,11);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_PRE ), entier, 4);
    AfficherTexte(entier,ETAT_COL-1,11);
    AfficherCaractere('%',ETAT_COL-1+3,11);
    AfficherTexte("Defense P:",1,12);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_DEFP), entier, 3);
    AfficherTexte(entier,ETAT_COL,12);
    AfficherTexte("Defense M:",1,13);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_DEFM), entier, 3);
    AfficherTexte(entier,ETAT_COL,13);
    AfficherTexte("Esquive:",1,14);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_ESQ ), entier, 4);
    AfficherTexte(entier,ETAT_COL-1,14);
    AfficherCaractere('%',ETAT_COL-1+3,14);

    AfficherTexte("Niveau:",1,16);
    EntierDroite(heros->GetNiveau(), entier, 3);
    AfficherTexte(entier,ETAT_COL,16);

    AfficherTexte("Experience:",LARGEUR_FENETRE-5-ETAT_COL-3,16);
    EntierDroite(heros->GetExperience(), entier, 5);
    AfficherTexte(entier,LARGEUR_FENETRE-5,16);

    AfficherTexte("Alterations:",1,18);
    unsigned char j = 0;
    for (unsigned char i = 0; i < MAX_ALTERATIONS; ++i) {
        if (heros->GetAlterations(i)) {
            AfficherTexte(heros->GetAlterations(i)->GetNom(),1+13,18+j);
            ++j;
        }
    }
}
