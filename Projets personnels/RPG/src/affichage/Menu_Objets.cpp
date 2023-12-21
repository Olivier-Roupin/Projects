#include "affichage/Menu_Objets.h"
#include <moteur_graphique.h>
#include <conversions.h>

#include <affichage/Menu.h> //Y_INFOS, Y_TEMPS, X_EQUIPE, DY_EQUIPE, NOMBRE_MENUS
#define OBJETS_COL1 2
#define OBJETS_COL2 (LARGEUR_FENETRE-13)//19

void AfficherObjetsAnimation(char animation) {
    effacerEcran();
    AfficherCadre(
        X_EQUIPE  +(LARGEUR_FENETRE+1  -X_EQUIPE  )*animation/6,
        1,-1,
        NOMBRE_MENUS-6*animation/6+3+(HAUTEUR_FENETRE-2-3-3)*animation/6+2-2*animation/6+4);
        // MAX_HEROS_EQUIPE*DY_EQUIPE+(HAUTEUR_FENETRE-MAX_HEROS_EQUIPE*DY_EQUIPE)*animation/6); //Equipe (sortie)

    AfficherCadre(1,
        Y_INFOS   +(4                  -Y_INFOS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        3         +(HAUTEUR_FENETRE-2-3-3         )*animation/6); //Infos -> Objets
        
    AfficherCadre(1,
        Y_TEMPS   +(HAUTEUR_FENETRE+1  -Y_TEMPS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        2-2*animation/6); //Temps (sortie)

    AfficherCadre(1,1,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        NOMBRE_MENUS-6*animation/6); //Menu -> Titre
    AfficherTexte("Objets",1,1);
}

void AfficherObjets(const Inventaire* inventaire, char choix, char choix2) {
    effacerEcran();
    AfficherCadre(1,1,-1,1); //"Objets"
    AfficherTexte("Objets",1,1);
    int i, hauteur = -1;
    AfficherCadre(1,4,-1,&hauteur);
    // const int premier = premierElementListe(choix, hauteur-1, MAX_OBJETS);
    // for (i = premier; i < premier + hauteur; i++) {
    //     if (inventaire->GetNombre(i) > 0) {
    //         AfficherTexte(inventaire->GetNom(i),OBJETS_COL1,i-premier+4);
    //         char nombre[3];
    //         EntierDroite(inventaire->GetNombre(i), nombre, 3);
    //         AfficherTexte(nombre,OBJETS_COL1+TAILLE_NOM_OBJET,i-premier+4);
    //     }
    // }
    const int premier = premierElementListe(choix/2, hauteur-1, MAX_OBJETS/2);
    for (i = 2*premier; i < 2*premier + 2*hauteur; ++i) {
        if (inventaire->GetNombre(i) > 0) {
            char couleur = inventaire->GetType(i) == UTILISABLE ? COULEUR_BLANC
                                                                : COULEUR_GRIS;
            AfficherTexte(inventaire->GetNom(i), couleur,
                OBJETS_COL1+OBJETS_COL2*(i%2),i/2-premier+4);
            char nombre[3];
            EntierDroite(inventaire->GetNombre(i), nombre, 3);
            AfficherTexte(nombre, couleur,
                OBJETS_COL1+TAILLE_NOM_OBJET+OBJETS_COL2*(i%2),i/2-premier+4);
        }
    }
    if (premier > 0)
        AfficherElement(PAGE_POLICE, LARGEUR_FENETRE-2, 4, P_up_arrow);
    if (premier < MAX_OBJETS/2 - hauteur)
        AfficherElement(PAGE_POLICE, LARGEUR_FENETRE-2, HAUTEUR_FENETRE-2, P_down_arrow);
    if (choix >= 0 && choix < MAX_OBJETS)
        // AfficherCurseur(OBJETS_COL1-1,choix -premier+4);
        AfficherCurseur(OBJETS_COL1-1+OBJETS_COL2*(choix %2), choix /2-premier+4);
    if (choix2 >= 0 && choix2 < MAX_OBJETS)
        // AfficherCurseur(OBJETS_COL1-2,choix2-premier+4);
        AfficherCurseur(OBJETS_COL1-2+OBJETS_COL2*(choix2%2), choix2/2-premier+4);
}

void AfficherEquipe_Reduit(const Equipe* equipe, char choix, bool quantite,
                           char x, char y) {
    unsigned char i;
    AfficherCadre(x,y,TAILLE_NOM_PERSONNAGE+5,MAX_HEROS_EQUIPE);
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        if (equipe->GetHeros(i)) {
            AfficherTexte(equipe->GetHeros(i)->GetNom(),x,y+i);
            char vie[5];
            EntierDroite(equipe->GetHeros(i)->GetVie(), vie, 5);
            AfficherTexte(vie,x+1+TAILLE_NOM_PERSONNAGE,y+i);
        }
    if (quantite)
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
            AfficherCurseur(0,0,x-1,y+i);
    else if (choix >= 0 && choix < MAX_HEROS_EQUIPE)
        AfficherCurseur(0,0,x-1,y+choix);
}
