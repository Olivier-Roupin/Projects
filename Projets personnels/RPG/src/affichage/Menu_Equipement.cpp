#include "affichage/Menu_Equipement.h"
#include <moteur_graphique.h>
#include <affichage/Menu_Objets.h>
#include <conversions.h>

#include <affichage/Menu.h> //Y_INFOS, Y_TEMPS, X_EQUIPE, DY_EQUIPE, NOMBRE_MENUS

#define EQUIPEMENT_COL 14
#define NOMBRE_OBJETS_EQUIPEMENT 5
#define X_OBJETS_EQUIPEMENT (LARGEUR_FENETRE-TAILLE_NOM_OBJET-4) //1
#define Y_OBJETS_EQUIPEMENT 8 //17
#define CATEGORIE_DX 10
#define CATEGORIE_X ((LARGEUR_FENETRE-3*CATEGORIE_DX)/2+1) //1
#define CATEGORIE_Y 4
#define X_CHOIX_EQUIPEMENT 2
#define Y_CHOIX_EQUIPEMENT (CATEGORIE_Y+3) //7
#define ATTRIBUTS_DX 9
#define ATTRIBUTS_X ((LARGEUR_FENETRE-3*ATTRIBUTS_DX)/2) //15
#define ATTRIBUTS_Y 15
#define ATTRIBUTS_DY 3

// const char* NOM_EQUIPEMENT = "Equipement";
#define NOM_EQUIPEMENT "Equipement"

void AfficherEquipementsAnimation(const Heros* heros, char choix_heros, char animation) {
    effacerEcran();
    AfficherCadre(1,
        Y_INFOS   +(4                  -Y_INFOS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        3         +(HAUTEUR_FENETRE-2-3-3         )*animation/6); //Infos -> Equipement

    AfficherCadre(1,
        Y_TEMPS   +(HAUTEUR_FENETRE+1  -Y_TEMPS   )*animation/6,
        X_EQUIPE-3+(LARGEUR_FENETRE-2  -X_EQUIPE+3)*animation/6,
        2-2*animation/6); //Temps (sortie)

    AfficherCadre(1,1,
        X_EQUIPE-3+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4-X_EQUIPE+3)*animation/6,
        NOMBRE_MENUS-6*animation/6); //Menu -> Titre
    AfficherTexte(NOM_EQUIPEMENT,1,2-1*(animation+3)/6);

    AfficherCadre(
        X_EQUIPE+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1 -X_EQUIPE)*animation/6,
        1,-1,
        MAX_HEROS_EQUIPE*DY_EQUIPE+(1-MAX_HEROS_EQUIPE*DY_EQUIPE)*animation/6); //Equipe -> Heros
    AfficherTexte(heros->GetNom(),
        X_EQUIPE+(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1 -X_EQUIPE)*animation/6,
        DY_EQUIPE*choix_heros+4 +(1-DY_EQUIPE*choix_heros-4)*animation/6);
}

void AfficherEquipementsTransition(char animation) {
    effacerEcran();
    AfficherCadre(1,1,LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4,1); //"Equipement"
    AfficherTexte(NOM_EQUIPEMENT,1,1); //10 caractères
    // AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1+(TAILLE_NOM_PERSONNAGE+2)*(animation+2)/6,1,TAILLE_NOM_PERSONNAGE,1); //Heros droite
    // AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1-3+3*(animation-2)/6,TAILLE_NOM_PERSONNAGE,1); //Heros gauche
    if (animation < 3)
        AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1+(TAILLE_NOM_PERSONNAGE+2)*animation/3,1,
            TAILLE_NOM_PERSONNAGE-TAILLE_NOM_PERSONNAGE*animation/3,1); //Heros droite
    else
        AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1-3+3*(animation-3)/3,TAILLE_NOM_PERSONNAGE,1); //Heros gauche
    
    const char droite = CATEGORIE_X+(LARGEUR_FENETRE-2)*animation/6;
    // AfficherCadre(1+(LARGEUR_FENETRE-2)*animation/6,4,LARGEUR_FENETRE-2,-1); //droite
    AfficherCadre(droite,4,LARGEUR_FENETRE-2-droite+2,-1); //droite (...+2) pour cropper
    AfficherTexte("Off:",    droite,               CATEGORIE_Y);
    AfficherCaractere('%', 7+droite,               CATEGORIE_Y);
    AfficherTexte("Def:",    droite+CATEGORIE_DX,  CATEGORIE_Y);
    AfficherCaractere('%', 7+droite+CATEGORIE_DX,  CATEGORIE_Y);
    AfficherTexte("Phy:",    droite+CATEGORIE_DX*2,CATEGORIE_Y);
    AfficherCaractere('%', 7+droite+CATEGORIE_DX*2,CATEGORIE_Y);

    const char droite2 = ATTRIBUTS_X+(LARGEUR_FENETRE-2)*animation/6;
    AfficherTexte("Vie",droite2               ,ATTRIBUTS_Y);
    AfficherTexte("AtP",droite2+ATTRIBUTS_DX  ,ATTRIBUTS_Y);
    AfficherTexte("DfP",droite2+ATTRIBUTS_DX*2,ATTRIBUTS_Y);
    AfficherTexte("Mag",droite2               ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("AtM",droite2+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("DfM",droite2+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("Vit",droite2               ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    AfficherTexte("Pre",droite2+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    AfficherTexte("Esq",droite2+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    
    const char gauche = droite-2-(LARGEUR_FENETRE-2);
    // AfficherCadre(1-2-(LARGEUR_FENETRE-2)+(LARGEUR_FENETRE-2)*animation/6,4,LARGEUR_FENETRE-2,-1); //gauche
    AfficherCadre(-1,4,LARGEUR_FENETRE-2+gauche+1,-1); //gauche (-1) pour cropper
    AfficherTexte("Off:",    gauche,               CATEGORIE_Y);
    AfficherCaractere('%', 7+gauche,               CATEGORIE_Y);
    AfficherTexte("Def:",    gauche+CATEGORIE_DX,  CATEGORIE_Y);
    AfficherCaractere('%', 7+gauche+CATEGORIE_DX,  CATEGORIE_Y);
    AfficherTexte("Phy:",    gauche+CATEGORIE_DX*2,CATEGORIE_Y);
    AfficherCaractere('%', 7+gauche+CATEGORIE_DX*2,CATEGORIE_Y);

    const char gauche2 = droite2-2-(LARGEUR_FENETRE-2);
    AfficherTexte("Vie",gauche2               ,ATTRIBUTS_Y);
    AfficherTexte("AtP",gauche2+ATTRIBUTS_DX  ,ATTRIBUTS_Y);
    AfficherTexte("DfP",gauche2+ATTRIBUTS_DX*2,ATTRIBUTS_Y);
    AfficherTexte("Mag",gauche2               ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("AtM",gauche2+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("DfM",gauche2+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("Vit",gauche2               ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    AfficherTexte("Pre",gauche2+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    AfficherTexte("Esq",gauche2+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
}

void AfficherEquipements(const Heros* heros) {
    effacerEcran();
    AfficherCadre(1,1,LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-4,1); //"Equipement"
    AfficherTexte(NOM_EQUIPEMENT,1,1); //10 caractères
    AfficherCadre(LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1,TAILLE_NOM_PERSONNAGE,1); //Heros
    AfficherTexte(heros->GetNom(),LARGEUR_FENETRE-TAILLE_NOM_PERSONNAGE-1,1);

    AfficherCadre(1,4,-1,-1);
    char sta[3];
    AfficherTexte("Off:", CATEGORIE_X,  CATEGORIE_Y);
    EntierDroite(heros->GetOffensif(), sta, 3);
    AfficherTexte(sta,    CATEGORIE_X+5,CATEGORIE_Y);
    AfficherCaractere('%',CATEGORIE_X+7,CATEGORIE_Y);

    AfficherTexte("Def:", CATEGORIE_X  +CATEGORIE_DX,CATEGORIE_Y);
    EntierDroite(heros->GetDefensif(), sta, 3);
    AfficherTexte(sta,    CATEGORIE_X+5+CATEGORIE_DX,CATEGORIE_Y);
    AfficherCaractere('%',CATEGORIE_X+7+CATEGORIE_DX,CATEGORIE_Y);

    AfficherTexte("Phy:", CATEGORIE_X  +CATEGORIE_DX*2,CATEGORIE_Y);
    EntierDroite(100-heros->GetOffensif()-heros->GetDefensif(), sta, 3);
    AfficherTexte(sta,    CATEGORIE_X+5+CATEGORIE_DX*2,CATEGORIE_Y);
    AfficherCaractere('%',CATEGORIE_X+7+CATEGORIE_DX*2,CATEGORIE_Y);
    
    char stt[5];
    AfficherTexte("Vie",ATTRIBUTS_X               ,ATTRIBUTS_Y);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_VIE), stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X               ,ATTRIBUTS_Y);
    AfficherTexte("AtP",ATTRIBUTS_X+ATTRIBUTS_DX  ,ATTRIBUTS_Y);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_ATKP),stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X+ATTRIBUTS_DX  ,ATTRIBUTS_Y);
    AfficherTexte("DfP",ATTRIBUTS_X+ATTRIBUTS_DX*2,ATTRIBUTS_Y);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_DEFP),stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X+ATTRIBUTS_DX*2,ATTRIBUTS_Y);
    AfficherTexte("Mag",ATTRIBUTS_X               ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_MAG), stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X               ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("AtM",ATTRIBUTS_X+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_ATKM),stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("DfM",ATTRIBUTS_X+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_DEFM),stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY);
    AfficherTexte("Vit",ATTRIBUTS_X               ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_VIT), stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X               ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    AfficherTexte("Pre",ATTRIBUTS_X+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_PRE), stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X+ATTRIBUTS_DX  ,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    AfficherTexte("Esq",ATTRIBUTS_X+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
    EntierDroite(heros->GetAttributTotal(ATTRIBUT_ESQ), stt, 6);
    AfficherTexte(stt,3+ATTRIBUTS_X+ATTRIBUTS_DX*2,ATTRIBUTS_Y+ATTRIBUTS_DY*2);
}

void AfficherChoixEquipementTransition(char animation) {
    const char droite = X_CHOIX_EQUIPEMENT+(LARGEUR_FENETRE-2)*animation/6;
    AfficherTexte("Main Gauche:" ,droite,Y_CHOIX_EQUIPEMENT); //droite
    AfficherTexte("Main Droite:" ,droite,Y_CHOIX_EQUIPEMENT+1);
    AfficherTexte("Tete:"        ,droite,Y_CHOIX_EQUIPEMENT+2);
    AfficherTexte("Corps:"       ,droite,Y_CHOIX_EQUIPEMENT+3);
    AfficherTexte("Accessoire 1:",droite,Y_CHOIX_EQUIPEMENT+4); //13 caractères
    AfficherTexte("Accessoire 2:",droite,Y_CHOIX_EQUIPEMENT+5);

    const char gauche = droite-2-(LARGEUR_FENETRE-2);
    AfficherTexte("Main Gauche:" ,gauche,Y_CHOIX_EQUIPEMENT); //gauche
    AfficherTexte("Main Droite:" ,gauche,Y_CHOIX_EQUIPEMENT+1);
    AfficherTexte("Tete:"        ,gauche,Y_CHOIX_EQUIPEMENT+2);
    AfficherTexte("Corps:"       ,gauche,Y_CHOIX_EQUIPEMENT+3);
    AfficherTexte("Accessoire 1:",gauche,Y_CHOIX_EQUIPEMENT+4); //13 caractères
    AfficherTexte("Accessoire 2:",gauche,Y_CHOIX_EQUIPEMENT+5);
}

void AfficherChoixEquipement(const Heros* heros, char choix) {
    AfficherTexte("Main Gauche:" ,X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT);
    if (heros->GetEquipement(EQUIPEMENT_MAINGAUCHE))
        AfficherTexte(heros->GetEquipement(EQUIPEMENT_MAINGAUCHE )->GetNom()
                  ,EQUIPEMENT_COL+X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT);

    AfficherTexte("Main Droite:" ,X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+1);
    if (heros->GetEquipement(EQUIPEMENT_MAINDROITE))
        AfficherTexte(heros->GetEquipement(EQUIPEMENT_MAINDROITE )->GetNom()
                  ,EQUIPEMENT_COL+X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+1);

    AfficherTexte("Tete:"        ,X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+2);
    if (heros->GetEquipement(EQUIPEMENT_TETE))
        AfficherTexte(heros->GetEquipement(EQUIPEMENT_TETE       )->GetNom()
                  ,EQUIPEMENT_COL+X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+2);

    AfficherTexte("Corps:"       ,X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+3);
    if (heros->GetEquipement(EQUIPEMENT_CORPS))
        AfficherTexte(heros->GetEquipement(EQUIPEMENT_CORPS      )->GetNom()
                  ,EQUIPEMENT_COL+X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+3);

    AfficherTexte("Accessoire 1:",X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+4); //13 caractères
    if (heros->GetEquipement(EQUIPEMENT_ACCESSOIRE1))
        AfficherTexte(heros->GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetNom()
                  ,EQUIPEMENT_COL+X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+4);

    AfficherTexte("Accessoire 2:",X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+5);
    if (heros->GetEquipement(EQUIPEMENT_ACCESSOIRE2))
        AfficherTexte(heros->GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetNom()
                  ,EQUIPEMENT_COL+X_CHOIX_EQUIPEMENT,Y_CHOIX_EQUIPEMENT+5);

    if (choix >= 0 && choix < NOMBRE_EQUIPEMENTS)
        AfficherCurseur(X_CHOIX_EQUIPEMENT-1,choix+Y_CHOIX_EQUIPEMENT);
}

int ChercherObjetPrecedent(const Inventaire* inventaire,
                           int choix, unsigned char type1, unsigned char type2) {
    int i = choix-1;
    while (i >= 0
          && inventaire->GetType(i) != type1
          && inventaire->GetType(i) != type2)
        i--;
    if (i < 0)
        return choix;
    return i;
}

int ChercherObjetSuivant(const Inventaire* inventaire,
                         int choix, unsigned char type1, unsigned char type2) {
    int i = choix+1;
    while (i < MAX_OBJETS
          && inventaire->GetType(i) != type1
          && inventaire->GetType(i) != type2)
        i++;
    if (i >= MAX_OBJETS)
        return choix;
    return i;
}

int PremierObjetAfficheFiltre(const Inventaire* inventaire, int choix,
                            int hauteur, unsigned char type1, unsigned char type2=0) {
    int i = choix, j;
    for (j = 0; j < hauteur/2; ++j)
        i = ChercherObjetSuivant(inventaire, i, type1, type2);
    for (j = 0; j < hauteur-1; ++j)
        i = ChercherObjetPrecedent(inventaire, i, type1, type2);
    return i;
}

void AfficherObjetsEquipement(const Inventaire* inventaire, const Equipable* equipe,
    int choix, unsigned char type1, unsigned char type2) {
    AfficherCadre(X_OBJETS_EQUIPEMENT,Y_OBJETS_EQUIPEMENT,TAILLE_NOM_OBJET+3,NOMBRE_OBJETS_EQUIPEMENT);
    if (inventaire == 0)
        return;
    const int premier = PremierObjetAfficheFiltre(inventaire, choix, NOMBRE_OBJETS_EQUIPEMENT, type1, type2);
    int i = premier;
    int j = 0;
    while (j < NOMBRE_OBJETS_EQUIPEMENT && i < MAX_OBJETS) {
        if (inventaire->GetObjets(i)
        && (inventaire->GetType(i) == type1
        ||  inventaire->GetType(i) == type2)) {
            if (choix == i)
                AfficherCurseur(X_OBJETS_EQUIPEMENT,Y_OBJETS_EQUIPEMENT+j);
            AfficherTexte(inventaire->GetNom(i),
                X_OBJETS_EQUIPEMENT+1,                 Y_OBJETS_EQUIPEMENT+j);
            char nombre[3];
            EntierDroite(inventaire->GetNombre(i), nombre, 3);
            AfficherTexte(nombre,
                X_OBJETS_EQUIPEMENT+1+TAILLE_NOM_OBJET,Y_OBJETS_EQUIPEMENT+j);
            ++j;
        }
        ++i;
    }
    if (inventaire->GetObjet(choix)) {
        const Equipable* equipable = (Equipable*)inventaire->GetObjet(choix);

        char sta[3];
        const char off = equipe != 0 ? equipe->GetOffensif() : 0;
        if (equipable->GetOffensif() > off) {
            EntierDroite((unsigned char)(equipable->GetOffensif()-off), sta, 3);
            AfficherCaractere('+', COULEUR_VERT,  CATEGORIE_X+4,CATEGORIE_Y+1);
            AfficherTexte(sta, COULEUR_VERT,  CATEGORIE_X+5,CATEGORIE_Y+1);
        } else if (equipable->GetOffensif() < off) {
            EntierDroite((unsigned char)(off-equipable->GetOffensif()), sta, 3);
            AfficherCaractere('-', COULEUR_ROUGE, CATEGORIE_X+4,CATEGORIE_Y+1);
            AfficherTexte(sta, COULEUR_ROUGE, CATEGORIE_X+5,CATEGORIE_Y+1);
        }
        const char def = equipe != 0 ? equipe->GetDefensif() : 0;
        if (equipable->GetDefensif() > def) {
            EntierDroite((unsigned char)(equipable->GetDefensif()-def), sta, 3);
            AfficherCaractere('+', COULEUR_VERT,  CATEGORIE_X+4+CATEGORIE_DX,CATEGORIE_Y+1);
            AfficherTexte(sta, COULEUR_VERT,  CATEGORIE_X+5+CATEGORIE_DX,CATEGORIE_Y+1);
        } else if (equipable->GetDefensif() < def) {
            EntierDroite((unsigned char)(def-equipable->GetDefensif()), sta, 3);
            AfficherCaractere('-', COULEUR_ROUGE, CATEGORIE_X+4+CATEGORIE_DX,CATEGORIE_Y+1);
            AfficherTexte(sta, COULEUR_ROUGE, CATEGORIE_X+5+CATEGORIE_DX,CATEGORIE_Y+1);
        }
        const char phy = equipe != 0 ? equipe->GetPhysionomique() : 16;
        if (equipable->GetPhysionomique() > phy) {
            EntierDroite((unsigned char)(equipable->GetPhysionomique()-phy), sta, 3);
            AfficherCaractere('+', COULEUR_VERT,  CATEGORIE_X+4+CATEGORIE_DX*2,CATEGORIE_Y+1);
            AfficherTexte(sta, COULEUR_VERT,  CATEGORIE_X+5+CATEGORIE_DX*2,CATEGORIE_Y+1);
        } else if (equipable->GetPhysionomique() < phy) {
            EntierDroite((unsigned char)(phy-equipable->GetPhysionomique()), sta, 3);
            AfficherCaractere('-', COULEUR_ROUGE, CATEGORIE_X+4+CATEGORIE_DX*2,CATEGORIE_Y+1);
            AfficherTexte(sta, COULEUR_ROUGE, CATEGORIE_X+5+CATEGORIE_DX*2,CATEGORIE_Y+1);
        }

        char stt[5];
        for (unsigned char k = 0; k < NOMBRE_ATTRIBUTS; ++k) {
            const char val = equipe != 0 ? equipe->GetAttribut(k) : 0;
            if (equipable->GetAttribut(k) > val) {
                EntierDroite((unsigned char)(equipable->GetAttribut(k)-val), stt, 5);
                AfficherCaractere('+',COULEUR_VERT,
                                4+ATTRIBUTS_X+ATTRIBUTS_DX*(k%3),
                                1+ATTRIBUTS_Y+ATTRIBUTS_DY*(k/3));
                AfficherTexte(stt, COULEUR_VERT,
                                4+ATTRIBUTS_X+ATTRIBUTS_DX*(k%3),
                                1+ATTRIBUTS_Y+ATTRIBUTS_DY*(k/3));
            } else if (equipable->GetAttribut(k) < val) {
                EntierDroite((unsigned char)(val-equipable->GetAttribut(k)), stt, 5);
                AfficherCaractere('-',COULEUR_ROUGE,
                                4+ATTRIBUTS_X+ATTRIBUTS_DX*(k%3),
                                1+ATTRIBUTS_Y+ATTRIBUTS_DY*(k/3));
                AfficherTexte(stt, COULEUR_ROUGE,
                                4+ATTRIBUTS_X+ATTRIBUTS_DX*(k%3),
                                1+ATTRIBUTS_Y+ATTRIBUTS_DY*(k/3));
            }
            // const char val = equipable->GetAttribut(k) - equipe->GetAttribut(k);
            // if (val != 0) {
            //     EntierDroite(val, stt, 5);
            //     AfficherTexte(stt, val > 0 ? COULEUR_VERT : COULEUR_ROUGE,
            //                     4+ATTRIBUTS_X+ATTRIBUTS_DX*(k%3),
            //                     1+ATTRIBUTS_Y+ATTRIBUTS_DY*(k/3));
            // }
        }
    }
}