#include "affichage/Menu_Magasin.h"
#include <moteur_graphique.h>
#include <affichage/Menu_Objets.h>
#include <conversions.h>
#include <macros.h> //MIN, MAX

#define MAGASIN_COL1 2
#define MAGASIN_COL2 (MAGASIN_COL1+TAILLE_NOM_OBJET+2)
#define MAGASIN_COL3 (LARGEUR_FENETRE-14) //(MAGASIN_COL2+5)
#define MAGASIN_DX 10

void AfficherMagasinsAnimation(char animation) {
    setCouleurEcran(0, 32, 32);
    effacerEcran();
    AfficherCadre(          1-8+8*animation/6,1,7,1); //"Magasin", 7 caractères
    AfficherTexte("Magasin",1-8+8*animation/6,1);
    AfficherCadre(       10+(LARGEUR_FENETRE-9-2)-(LARGEUR_FENETRE-9-2)*animation/6,1,LARGEUR_FENETRE-9-2,1); //"Or"
    AfficherTexte("Or: ",10+(LARGEUR_FENETRE-9-2)-(LARGEUR_FENETRE-9-2)*animation/6,1);
    AfficherCadre(          1-2*MAGASIN_DX+2*MAGASIN_DX*animation/6,4,8,1); //"Acheter", 7 caractères
    AfficherTexte("Acheter",2-2*MAGASIN_DX+2*MAGASIN_DX*animation/6,4);
    AfficherCadre(          1-2*MAGASIN_DX+2*MAGASIN_DX*animation/6+MAGASIN_DX,4,8,1); //"Vendre"
    AfficherTexte("Vendre" ,2-2*MAGASIN_DX+2*MAGASIN_DX*animation/6+MAGASIN_DX,4);
    AfficherCadre(          2*MAGASIN_DX+1+(LARGEUR_FENETRE-2*MAGASIN_DX-2)-(LARGEUR_FENETRE-2*MAGASIN_DX-2)*animation/6,4,LARGEUR_FENETRE-2*MAGASIN_DX-2,1); //"Quitter"
    AfficherTexte("Quitter",2*MAGASIN_DX+2+(LARGEUR_FENETRE-2*MAGASIN_DX-2)-(LARGEUR_FENETRE-2*MAGASIN_DX-2)*animation/6,4);
}

// Afficher le menu dans la fenêtre
void AfficherMagasins(char choix, unsigned int Or, bool choisi) {
    setCouleurEcran(0, 32, 32);
    effacerEcran();
    AfficherCadre(1,1,7,1); //"Magasin"
    AfficherTexte("Magasin",1,1);
    AfficherCadre(10,1,-1,1); //"Or"
    AfficherTexte("Or: ",10,1);
    char orT[10];
    EntierDroite(Or, orT, 10);
    AfficherTexte(orT,10+4,1);
    AfficherCadre(1,4,8,1); //"Acheter"
    AfficherTexte("Acheter",  choisi ? choix==MAGASIN_ACHETER ? COULEUR_BLANC : COULEUR_GRIS
        : COULEUR_BLANC, 2,4);
    AfficherCadre(1+MAGASIN_DX,4,8,1); //"Vendre"
    AfficherTexte("Vendre" , choisi ? choix==MAGASIN_VENDRE ? COULEUR_BLANC : COULEUR_GRIS 
        : COULEUR_BLANC, 2+MAGASIN_DX,4);
    AfficherCadre(1+MAGASIN_DX*2,4,-1,1); //"Quitter"
    AfficherTexte("Quitter", choisi ? COULEUR_GRIS
        : COULEUR_BLANC, 2+MAGASIN_DX*2,4);
    if (choix >= 0 && choix < 3)
        AfficherCurseur(1+MAGASIN_DX*choix,4);
}

void AfficherMagasins_AcheterAnimation(char animation) {
    AfficherCadre(1,7+(HAUTEUR_FENETRE-8)-(HAUTEUR_FENETRE-8)*animation/6,-1,HAUTEUR_FENETRE-8);
}

void AfficherMagasins_Acheter(const Magasin* magasin, const Inventaire* inventaire,
                              const Equipe* equipe, char choix, unsigned int Or) {
    char i;
    int hauteur = -1;
    AfficherCadre(1,7,-1,&hauteur);
    const int premier = premierElementListe(choix, hauteur-1, magasin->GetNombre());
    const int dernier = MIN(premier+hauteur,magasin->GetNombre());
    for (i = premier; i < dernier; ++i) {
        if (magasin->GetObjets(i)) {
            char couleur = magasin->GetPrix(i) <= Or ? COULEUR_BLANC
                                                     : COULEUR_GRIS;
            AfficherTexte(magasin->GetNom(i),couleur,MAGASIN_COL1,7+i-premier);
            char tbuf[5];
            EntierDroite(magasin->GetPrix(i), tbuf, 5);
            AfficherTexte(    tbuf, couleur, MAGASIN_COL2,7+i-premier);
            AfficherTexte("Stock:", MAGASIN_COL3,7+i-premier);
            EntierDroite(inventaire->GetNombre(magasin->GetObjets(i)),tbuf,5);
            AfficherTexte(    tbuf, MAGASIN_COL3+5,7+i-premier);
            //Objets equipés
            if (magasin->GetObjets(i)->EstEquipable()) {
                //1 caractère : 4 héros * 2 emplacements <= 8
                AfficherCaractere('(', MAGASIN_COL3+ 9,7+i-premier);
                AfficherCaractere(')', MAGASIN_COL3+11,7+i-premier);
                // EntierDroite(equipe->GetNombreObjets(magasin->GetObjets(i)),tbuf,5);
                // AfficherTexte(   tbuf, MAGASIN_COL3+8,7+i-premier);
                AfficherCaractere('0'+equipe->GetNombreObjets(magasin->GetObjets(i)), MAGASIN_COL3+10,7+i-premier);
            }
        }
    }
    if (choix >= 0 && choix < magasin->GetNombre())
        AfficherCurseur(1,7+choix-premier);
}

void AfficherMagasins_VendreAnimation(char animation) {
    AfficherCadre(1,7+(HAUTEUR_FENETRE-8)-(HAUTEUR_FENETRE-8)*animation/6,-1,HAUTEUR_FENETRE-8);
}

void AfficherMagasins_Vendre(const Inventaire* inventaire,
                             const Equipe* equipe, int choix) {
    int i, hauteur = -1;
    AfficherCadre(1,7,-1,&hauteur);
    const int premier = premierElementListe(choix, hauteur-1, MAX_OBJETS);
    for (i = premier; i < premier + hauteur; ++i) {
        if (inventaire->GetNombre(i) > 0) {
            AfficherTexte(inventaire->GetNom(i),MAGASIN_COL1,7+i-premier);
            char tbuf[5];
            EntierDroite(inventaire->GetPrix(i), tbuf, 5);
            AfficherTexte(    tbuf, MAGASIN_COL2  ,7+i-premier);
            AfficherTexte("Reste:", MAGASIN_COL3  ,7+i-premier);
            EntierDroite(inventaire->GetNombre(i), tbuf, 5);
            AfficherTexte(    tbuf, MAGASIN_COL3+5,7+i-premier);
            //Objets equipés
            if (inventaire->GetObjet(i)->EstEquipable()) {
                AfficherCaractere('(', MAGASIN_COL3+ 9,7+i-premier);
                AfficherCaractere(')', MAGASIN_COL3+11,7+i-premier);
                // EntierDroite(equipe->GetNombreObjets(inventaire->GetObjet(i)), tbuf, 5);
                // AfficherTexte(   tbuf, MAGASIN_COL3+ 8,7+i-premier);
                AfficherCaractere('0'+equipe->GetNombreObjets(inventaire->GetObjet(i)), MAGASIN_COL3+10,7+i-premier);
            }
        }
    }
    if (choix >= 0 && choix < MAX_OBJETS)
        AfficherCurseur(1,7+choix-premier);
}
