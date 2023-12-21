#include "affichage/Combat.h"
#include <moteur_graphique.h>
#include <conversions.h>
#include <macros.h>

#define Y_FENETRE_COMBAT (HAUTEUR_FENETRE-7)  //21
#define LONGUEUR_JAUGE   8
#define  X_NOMS_COMBAT   (LARGEUR_FENETRE-13) //19
#define  X_HEROS_COMBAT  (LARGEUR_FENETRE-6)  //26
#define  Y_HEROS_COMBAT  4
#define DX_HEROS_COMBAT  2
#define DY_HEROS_COMBAT  4

void AfficherFond(const Carte* carte, const GroupeMonstres* groupe) {
    if (groupe && groupe->GetFond()) {
        for (int j = 0; j < LARGEUR_FENETRE; j+=2)
            AfficherTuile(groupe->GetFond(),j,0);
    } else if (carte && carte->GetFond())
        for (int j = 0; j < LARGEUR_FENETRE; j+=2)
            AfficherTuile(carte->GetFond(),j,0);
}

void AfficherMonstres(const GroupeMonstres* groupe, int cible, bool faction,
                      bool quantite) {
    unsigned char i;
    char image[1];
    for (i = 0; i < groupe->GetNombre(); ++i) {
        Monstre* monstre = groupe->GetMonstres(i);
        if (monstre) {
            if (!monstre->estEnVie()) {
                if (monstre->GetAnimation() == ANIMATION_MONSTRE_VISIBLE) {
                    monstre->SetAnimation(ANIMATION_MONSTRE_MORT);
                    if (monstre->GetId() < 3)
                        monstre->SetTempsAnimation((P_dither_4-P_dither_0+4+4-3));
                    else
                        monstre->SetTempsAnimation((P_dither_4-P_dither_0+4+6-3));
                }
            }
            if (monstre->GetAnimation() != ANIMATION_MONSTRE_CACHE) {
                image[0] = (char)(monstre->GetId() & 255);
                AfficherMonstre(image, groupe->GetX(i), groupe->GetY(i));
                if (monstre->GetAnimation() == ANIMATION_MONSTRE_MORT) {
                    if (monstre->GetId() < 3)
                        AfficherDithers(P_dither_4-P_dither_0-monstre->GetTempsAnimation(),
                            groupe->GetX(i), groupe->GetY(i), 4, 4);
                    else
                        AfficherDithers(P_dither_4-P_dither_0-monstre->GetTempsAnimation(),
                            groupe->GetX(i), groupe->GetY(i), 4, 6);
                }
            }
            if (monstre->GetTempsMessage()) {
                char degats[8];
                if (monstre->GetMessage() < 0) {
                    EntierGauche(-monstre->GetMessage(), degats, 7);
                    AfficherTexte(degats, COULEUR_ROUGE,
                        groupe->GetX(i), groupe->GetY(i)+2);
                } else if (monstre->GetMessage() > 0) {
                    EntierGauche( monstre->GetMessage(), degats, 7);
                    AfficherTexte(degats, COULEUR_VERT,
                        groupe->GetX(i), groupe->GetY(i)+2);
                } else { //0
                    EntierGauche(0, degats, 7);
                    AfficherTexte(degats, groupe->GetX(i), groupe->GetY(i)+2);
                }
                monstre->ActualiserMessage();
            }
            if (monstre->GetTempsAnimation())
                monstre->ActualiserAnimation();
        }
    }
    //Un monstre est sélectionné
    if (cible >= 0 && faction == FACTION_MONSTRES && quantite == QUANTITE_UNE) {
        //utile sinon on voit la flêche se déplacer
        if (groupe->GetMonstres(cible) && groupe->GetMonstres(cible)->estEnVie())
            AfficherCurseur(groupe->GetX(cible)-1, groupe->GetY(cible));
    } else if ((cible >= 0 && faction == FACTION_MONSTRES &&
        quantite == QUANTITE_FACTION) || cible == CIBLE_TOUS) {
        //Tous les monstres sont sélectionnés
        for (i = 0; i < groupe->GetNombre(); ++i)
            //utile sinon les monstres morts sont visuellement sélectionnés
            if (groupe->GetMonstres(cible) && groupe->GetMonstres(i)->estEnVie())
                AfficherCurseur(groupe->GetX(i)-1, groupe->GetY(i));
    }
}

void AfficherJauge(unsigned int jauge, int x, int y) {
    unsigned char i;
    AfficherElement(PAGE_POLICE, x, y, P_start);
    const unsigned char n = LONGUEUR_JAUGE*jauge/TAILLE_JAUGE;
    for (i = 0; i < n; ++i)
        AfficherElement(PAGE_POLICE, x+1+i, y, P_middle_8);
    for (i = n; i < LONGUEUR_JAUGE; ++i)
        AfficherElement(PAGE_POLICE, x+1+i, y, P_middle_0);
    AfficherElement(PAGE_POLICE, x+LONGUEUR_JAUGE+1, y, P_end);
}

void AfficherHerosCombat(Heros* heros, int x, int y) {
    char image[2];
    heros->RenduCombat(image);
    if (heros) {
        if (heros->GetRang() == RANG_AVANT) {
            if (image[1] < 12)
                AfficherHeros(image,x,y);
            else
                AfficherHeros(image,x,y+1);
        } else {
            if (image[1] < 12)
                AfficherHeros(image,x+DX_HEROS_COMBAT,y);
            else
                AfficherHeros(image,x+DX_HEROS_COMBAT,y+1);
        }
        if (heros->GetTempsMessage()) {
            char degats[8];
            if (heros->GetMessage() < 0) {
                EntierGauche(-heros->GetMessage(), degats, 7);
                AfficherTexte(degats,COULEUR_ROUGE,x,y+1);
            } else if (heros->GetMessage() > 0) {
                EntierGauche( heros->GetMessage(), degats, 7);
                AfficherTexte(degats,COULEUR_VERT,x,y+1);
            } else { //0
                EntierGauche(0, degats, 7);
                AfficherTexte(degats,x,y+1);
            }
            heros->ActualiserMessage();
        }
        if (heros->GetTempsAnimation())
            heros->ActualiserAnimation();
    }
}

void AfficherEquipeCombat(const Equipe* equipe, int cible, bool faction,
                          bool quantite) {
    unsigned char i;
    AfficherCadre(X_NOMS_COMBAT-LONGUEUR_JAUGE-3, Y_FENETRE_COMBAT, -1, 6);
    //LONGUEUR_JAUGE+TAILLE_NOM_PERSONNAGE+LARGEUR_FENETRE-X_NOMS_COMBAT-5, 6);
    for (i = 0; i < MAX_HEROS_EQUIPE; i++) {
        Heros* heros = equipe->GetHeros(i);
        if (heros) { // on veut quand même afficher les héros morts
            AfficherHerosCombat(heros, X_HEROS_COMBAT,
                                       Y_HEROS_COMBAT+DY_HEROS_COMBAT*i);
            AfficherTexte(heros->GetNom(), X_NOMS_COMBAT,Y_FENETRE_COMBAT+i);
            char vie[5];
            EntierDroite(heros->GetVie(), vie, 5);
            AfficherTexte(vie,
                X_NOMS_COMBAT+TAILLE_NOM_PERSONNAGE+1,Y_FENETRE_COMBAT+i);
            AfficherJauge(heros->GetJauge(),
                           X_NOMS_COMBAT-LONGUEUR_JAUGE-3,Y_FENETRE_COMBAT+i);
        }
    }
    if (cible >= 0 && faction == FACTION_EQUIPE
       && quantite == QUANTITE_UNE) {//Un héros est sélectionné
         if (equipe->GetHeros(cible))
            AfficherCurseur(X_HEROS_COMBAT-1,
                Y_HEROS_COMBAT+DY_HEROS_COMBAT*cible);
    } else if ((cible >= 0 && faction == FACTION_EQUIPE
             && quantite == QUANTITE_FACTION)
            || cible == CIBLE_TOUS) {//Tous les héros sont sélectionnés
        for (i = 0; i < MAX_HEROS_EQUIPE; i++)
            if (equipe->GetHeros(i))
                AfficherCurseur(X_HEROS_COMBAT-1,
                    Y_HEROS_COMBAT+DY_HEROS_COMBAT*i);
    }
}

void AfficherCommandes(const Heros *heros, int id) {
    AfficherCadre(1,Y_FENETRE_COMBAT,9,6);
    if (heros) {
        AfficherCurseur(1,Y_FENETRE_COMBAT+id);
        AfficherTexte("Attaquer",2,Y_FENETRE_COMBAT  ); //8 caractères
        AfficherTexte("Defense" ,2,Y_FENETRE_COMBAT+1);
        AfficherTexte("Rang"    ,2,Y_FENETRE_COMBAT+2);
        AfficherTexte("Objets"  ,2,Y_FENETRE_COMBAT+3);
        AfficherTexte("Capacite",2,Y_FENETRE_COMBAT+4);
        AfficherTexte("Fuite"   ,2,Y_FENETRE_COMBAT+5);
    }
}

void AfficherObjetsCombat(const Inventaire* inventaire, int choix) {
    int i, hauteur = -1;
    AfficherCadre(1,Y_FENETRE_COMBAT,TAILLE_NOM_OBJET+3,&hauteur);
    if (inventaire) {
        const int premier = premierElementListe(choix, hauteur-1, MAX_OBJETS);
        for (i = premier; i < premier + hauteur; ++i)
            if (inventaire->GetNombre(i) > 0) {
                char couleur = inventaire->GetType(i) == UTILISABLE ? COULEUR_BLANC
                                                                    : COULEUR_GRIS;
                AfficherTexte(inventaire->GetNom(i), couleur,
                    2,Y_FENETRE_COMBAT+i-premier);
                char nombre[3];
                EntierDroite(inventaire->GetNombre(i), nombre, 3);
                AfficherTexte(nombre, couleur,
                    2+TAILLE_NOM_OBJET,Y_FENETRE_COMBAT+i-premier);
            }
        if (choix >= 0 && choix < MAX_OBJETS) {
            AfficherCurseur(1,Y_FENETRE_COMBAT+choix-premier);
            if (inventaire->GetObjets(choix)) {
                if (inventaire->GetType(choix) == UTILISABLE) {
                    AfficherCadre(1,1,-1,1);
                    if (inventaire->GetObjet(choix))
                        AfficherTexte(
                            inventaire->GetObjet(choix)->GetDescription(),1,1);
                }
            }
        }
    }
}

void AfficherCompetencesCombat(const Heros* heros, int choix) {
    int i, hauteur = -1;
    AfficherCadre(1,Y_FENETRE_COMBAT,TAILLE_NOM_CAPACITE+4,&hauteur);
    if (heros) {
        const int premier = premierElementListe(choix, hauteur-1, MAX_SORTS);
        for (i = premier; i < premier + hauteur; ++i)
            if (heros->GetSorts(i)) {
                char couleur = heros->GetSorts(i)->GetCoutMagie()
                            <= heros->GetMagie() ? COULEUR_BLANC : COULEUR_GRIS;
                AfficherTexte(heros->GetSorts(i)->GetNom(), couleur,
                    2,Y_FENETRE_COMBAT+i-premier);
                char coutM[3];
                EntierDroite(heros->GetSorts(i)->GetCoutMagie(), coutM, 3);
                AfficherTexte(coutM, couleur,
                    3+TAILLE_NOM_CAPACITE,Y_FENETRE_COMBAT+i-premier);
            }
        char magie[4];
        EntierDroite(heros->GetMagie(), magie, 4);
        AfficherTexte(magie,  1,  Y_FENETRE_COMBAT-1);
        AfficherCaractere('/',1+3,Y_FENETRE_COMBAT-1);
        EntierDroite(heros->GetAttributTotal(ATTRIBUT_MAG), magie, 4);
        AfficherTexte(magie,  1+4,Y_FENETRE_COMBAT-1);
        if (choix >= 0 && choix < MAX_SORTS) {
            AfficherCurseur(1,Y_FENETRE_COMBAT+choix-premier);
            if (heros->GetSorts(choix)) {
                AfficherCadre(1,1,-1,1);
                AfficherTexte(heros->GetSorts(choix)->GetDescription(),1,1);
            }
        }
    }
}

void AfficherCombat(Partie* partie) {
    setCouleurEcran(32, 0, 0);
    effacerEcran();
    if (partie->GetCarte() && partie->GetGroupeCombat())
        AfficherFond(partie->GetCarte(), partie->GetGroupeCombat());
    if (partie->GetGroupeCombat())
        AfficherMonstres(partie->GetGroupeCombat(), partie->GetCible(),
                         partie->GetFaction(), partie->GetQuantite());
    if (partie->GetEquipe())
        AfficherEquipeCombat(partie->GetEquipe(), partie->GetCible(),
                             partie->GetFaction(), partie->GetQuantite());
    if (partie->GetHeros() != -1) // héros sélectionné
        AfficherCurseur(X_NOMS_COMBAT-1,Y_FENETRE_COMBAT+partie->GetHeros());
    switch (partie->GetMenu()) {
    case CHOIX_HEROS:
        break;
    case CHOIX_ACTION:
        if (partie->GetHeros() != -1)
            AfficherCommandes(partie->GetHeros_selection(),partie->GetAction());
        break;
    case CHOIX_OBJET:
        AfficherObjetsCombat(partie->GetInventaire(), partie->GetObjet());
        break;
    case CHOIX_CAPACITE:
        AfficherCompetencesCombat(partie->GetHeros_selection(),
                                  partie->GetCapacite());
        break;
    case CHOIX_CIBLE:
        break;
    default:
        break;
    }
}

void AfficherFuite(int val) {
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Fuite! Vous perdez:",1,1); //19 caractères
    char Or[5];
    EntierGauche(val, Or, 5);
    AfficherTexte(Or,20,1);
    AfficherTexte("or...",20+5+1,1);
}

void AfficherVictoireExp(int val) {
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Vous gagnez:",1,1); //12 caractères
    char exp[6];
    EntierGauche(val, exp, 6);
    AfficherTexte(exp,14,1);
    AfficherTexte("exp!",14+6+1,1);
}

void AfficherVictoireNiveau(const char* nom, int val) {
    AfficherCadre(1,1,-1,1);
    AfficherTexte(nom,1,1);
    AfficherTexte("passe",1+TAILLE_NOM_PERSONNAGE+1,1); //5 caractères
    if (val > 1) {
        char nombre[3];
        EntierDroite(val, nombre, 3);
        AfficherTexte(nombre,1+TAILLE_NOM_PERSONNAGE+1+7,1);
            AfficherTexte("niveaux!",1+TAILLE_NOM_PERSONNAGE+1+7+3,1);
    } else
        AfficherTexte("un niveau!",1+TAILLE_NOM_PERSONNAGE+1+7,1);
}

void AfficherVictoireOr(int val) {
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Vous gagnez:",1,1); //12 caractères
    char Or[6];
    EntierGauche(val, Or, 6);
    AfficherTexte(Or,14,1);
    AfficherTexte("or!",14+6+1,1);
}

void AfficherVictoireObjet(const char* nom) {
    AfficherCadre(1,1,-1,1);
    AfficherTexte("Vous obtenez:",1,1); //13 caractères
    AfficherTexte(nom,15,1);
    AfficherCaractere('!',15+TAILLE_NOM_OBJET,1);
}