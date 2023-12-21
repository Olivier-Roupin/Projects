#include "scenes/Terrain.h"
#include <affichage/Terrain.h>
#include <moteur_graphique.h>
#include <cstdlib> //rand
#include <scenes/Game_Over.h> //Game_Over pour les alterations/événements, Input

#define TAUX_RENCONTRE 10

void ActualiserEvenements(Partie* partie) {
    int i;
    const Carte* carte = partie->GetCarte();
    if (carte)
        for (i = 0; i < carte->GetNombre(); i++)
            partie->ExecuterEvenement(i, SCRIPT_CONTINU);
}

//Donne l'orientation du héros en fonction de l'input
char OrientationHeros(Input* input) {
    if (input->getBas())    return ORIENTATION_BAS;
    if (input->getDroite()) return ORIENTATION_DROITE;
    if (input->getGauche()) return ORIENTATION_GAUCHE;
    if (input->getHaut())   return ORIENTATION_HAUT;
    return -1;
}

//Donne les déplacements en fonction de l'input
void DeplacementHeros(int &dX, int &dY, Input* input) {
    dX = dY = 0;
    if (input->getBas()) {
        dY = 1;
        return;//input->Actualiser();//input->setBas(0); // mouvement fluide
    }
    if (input->getDroite()) {
        dX = 1;
        return;
    }
    if (input->getGauche()) {
        dX = -1;
        return;
    }
    if (input->getHaut()) {
        dY = -1;
        return;
    }
}

//Teste la présence d'un événement en X,Y(,Z) et retourne son indice
int TestEvenement(Carte* carte, int X, int Y, int Z = -1) {
    unsigned char k;
    if (carte == 0)
        return -1;
    carte->GetRepetition(X, Y);
    for (k = 0; k < carte->GetNombre(); ++k)
        if (carte->GetEvenements(k))
            if (X==carte->GetEvenements(k)->GetX()
             && Y==carte->GetEvenements(k)->GetY()
            && (Z==-1||Z==carte->GetEvenements(k)->GetZ()))
                return (int)k;
    return -1;
}

//Teste si le héros est en contact avec un événement et retourne son indice
int TestContact(Partie* partie) {
    int e = -1;
    if (partie->GetCarte() == 0)
        return -1;
    // TODO : test si héros fusionné avec événement au milieu ?
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),Z_BAS);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
        return e;
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),Z_HAUT);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
        return e;
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),
                      Z_MILIEU);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT)
    && partie->GetCarte()->GetEvenements(e)->GetTraversable())
        return e;
    // e = TestEvenement(partie->GetCarte(),
    //     partie->GetX()+partie->GetOrientationX(),
    //     partie->GetY()+partie->GetOrientationY(), Z_MILIEU);
    // if (partie->GetCarte()->GetEvenements(e)
    //  && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT)
    // )//&& !partie->GetCarte()->GetEvenements(e)->GetTraversable())
    //     return e;
    return -1;
}

//Teste si le héros est en contact avec un événement et retourne son indice
int TestContact2(Partie* partie) {
    int e = -1;
    if (partie->GetCarte() == 0)
        return -1;
    // TODO : test si héros fusionné avec événement au milieu ?
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),Z_BAS);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
        return e;
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),Z_HAUT);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
        return e;
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),
                      Z_MILIEU);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT)
    && partie->GetCarte()->GetEvenements(e)->GetTraversable())
        return e;
    e = TestEvenement(partie->GetCarte(),
        partie->GetX()+partie->GetOrientationX(),
        partie->GetY()+partie->GetOrientationY(), Z_MILIEU);
    if (e >= 0 && partie->GetCarte()->GetEvenements(e)
     && partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT)
    )//&& !partie->GetCarte()->GetEvenements(e)->GetTraversable())
        return e;
    return -1;
}

bool TestCollision(Carte* carte, int X, int Y, int Z) {
    int e;
    if (carte == 0)
        return false;
    carte->GetRepetition(X, Y);
    e = TestEvenement(carte,X,Y);
    if (e >= 0 && carte->GetEvenements(e))
        return carte->GetTraversable(X,Y) &&\
            (e==-1 || carte->GetEvenements(e)->GetZ()!=Z
            || carte->GetEvenements(e)->GetTraversable());
    return carte->GetTraversable(X,Y);
}

//Recherche des événements automatiques (d'indice plus grand que e)
int TestAutomatique(Carte* carte, int e) {
    int k;
    //on cherche les événements automatiques suivants (après e)
    if (carte)
        for (k = e+1; k < carte->GetNombre(); k++)
            if (k >= 0 && carte->GetEvenements(k)
            && carte->GetEvenements(k)->GetScripts(SCRIPT_AUTOMATIQUE))
                return k;
    //on retourne -1 si e est trop grand
    //ou si on ne trouve pas d'événement automatique
    return -1;
}

// void FondreVersTerrain(const Partie* partie, int D=0, int dX=0, int dY=0) {
void FondreVersTerrain(const Partie* partie) {
    ecran_fondu = 255;
    while (!FonduEntrant(16)) {
        AfficherTerrain(partie,0,0,0);
        setCouleurEcran(0, 0, 0, ecran_fondu);
        remplirEcran();
        afficherEcran();
        syncEcran(frameLimit);
    }
}

void FondreVersMenu(const Partie* partie, int D=0, int dX=0, int dY=0) {
    ecran_fondu = 0;
    while (!FonduSortant(16)) {
        if (D) D++;
        AfficherTerrain(partie,D,dX,dY);
        setCouleurEcran(0, 0, 0, ecran_fondu);
        remplirEcran();
        afficherEcran();
        syncEcran(frameLimit);
    }
}

//true == defaite, false == victoire
bool AppliquerAlterations(Partie* partie) {
    unsigned char i;
    Heros* heros;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i) {
        heros = partie->GetEquipe()->GetHeros(i);
        if (heros) {
            partie->SetLanceur((int)i);
            partie->SetFactionLanceur(FACTION_EQUIPE);
            int j;
            for (j = 0; j < MAX_ALTERATIONS; ++j)
                if (heros->GetAlterations(j))
                    if (heros->GetAlterations(j)->GetScriptTerrain()) {
                        heros->GetAlterations(j)->GetScriptTerrain(
                                                            )->Executer(partie);
                    }
        }
    }
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        if (partie->GetEquipe()->GetHeros(i)
         && partie->GetEquipe()->GetHeros(i)->GetVie())
            return false;
    return true;
}

int Terrain(Partie* partie) {
    Input* input = partie->GetInput();
    partie->SetTerrain(true);
    bool combat = false; //un combat se lance si vrai
    if (partie->GetEquipe() == 0)
        return -1;
    partie->ResetMeneur();
    partie->SetSituation(SITUATION_INITIALISATION);
    ecran_fondu = 255;
    bool init = true;
    int e = -1;
    int dX = 0, dY = 0; // à mettre dans initialisation ?

    while (partie->GetTerrain()) {
        AfficherTerrain(partie,partie->GetDeplace(),dX,dY);
        if (ecran_fondu > 0) {
            setCouleurEcran(0, 0, 0, ecran_fondu);
            remplirEcran();
        }
        input->Actualiser();
        ActualiserEvenements(partie);
        //afficherEcran();
        //syncEcran(frameLimit);
        switch (partie->GetSituation()) {
            case SITUATION_DEPLACEMENT:
                if (partie->GetDeplace() && input->getB()) partie->ChangerDeplace(1);
                if (partie->GetDeplace()) partie->ChangerDeplace(1);
                else {
                    partie->SetOrientation(OrientationHeros(input));
                    DeplacementHeros(dX,dY,input);
                    //si le personnage se déplace
                    if (DeplacerHeros(partie,dX,dY)) {
                        //appliquer les altérations
                        if (AppliquerAlterations(partie)) {
                            Game_Over(input);
                            partie->SetTerrain(false); //game over
                            break; //sortir du switch
                        }
                        partie->ResetMeneur(); //TODO: optimiser
                        e = TestContact(partie);
                        if (e != -1)
                            partie->SetSituation(SITUATION_CONTACT);
                        else if (partie->GetCarte()
                              && partie->GetCarte()->GetRencontres(
                                                partie->GetX(),partie->GetY()))
                            combat = !(rand() % TAUX_RENCONTRE);
                    //si le personnage essaie de se déplacer
                    } else if (dX || dY) {
                        e = TestContact2(partie);
                        if (e != -1)
                            partie->SetSituation(SITUATION_CONTACT);
                        // else if (partie->GetCarte()
                        //       && partie->GetCarte()->GetRencontres(
                        //                         partie->GetX(),partie->GetY()))
                        //     combat = !(rand() % TAUX_RENCONTRE);
                        else if (partie->GetDeplace() == 0)
                            partie->SetDeplace(-LARGEUR_TUILE);
                        dX = dY = 0;
                    }
                    if (combat) { //Combat aléatoire
                        combat = false;
                        if (partie->GetCarte() && partie->GetCarte()->GetRencontreset()) {
                            input->Vider();
                            unsigned char rencontre = partie->GetCarte(
                                )->GetRencontres(partie->GetX(),partie->GetY())-1;
                            unsigned char groupe_id = rand()%partie->GetCarte(
                                )->GetRencontreset()->GetNombreGroupes(rencontre);
                            GroupeMonstres* groupe(partie->GetCarte(
                                )->GetRencontreset(
                                )->GetGroupes(rencontre,groupe_id));
                            if (DemarrerCombat(partie, groupe, true, partie->GetDeplace(), dX, dY)) {
                                break;
                            }
                            partie->SetDeplace(0);
                            FondreVersTerrain(partie);
                        }
                    }
                    if (input->takeY()) //Changer Meneur
                        partie->IncMeneur();
                    if (input->getX()) { //Ouvrir Menu
                        input->Vider();
                        FondreVersMenu(partie, partie->GetDeplace(), dX, dY);
                        if (Menu(partie))
                            //Quitter la partie et retour à l'écran titre
                            return 0;
                        //Changer meneur si besoin
                        partie->ResetMeneur();
                        partie->SetDeplace(0);
                        FondreVersTerrain(partie); //GetDeplace()==0?
                    }
                    if (input->takeA()) { //Interagir
                        if (partie->GetCarte()) {
                            e = TestEvenement(partie->GetCarte(),
                                partie->GetX()+partie->GetOrientationX(),
                                partie->GetY()+partie->GetOrientationY());
                            if (e >= 0 && partie->GetCarte()->GetEvenements(e)
                            && partie->GetCarte()->GetEvenements(e)->GetScripts(
                                                    SCRIPT_INTERACTION)) //e!=-1 ?
                                partie->SetSituation(SITUATION_INTERACTION);
                        }
                    }
                }
                break;
            case SITUATION_INTERACTION: //Interaction avec événement
                if (partie->GetDeplace() && input->getB()) partie->ChangerDeplace(1);
                if (partie->GetDeplace()) partie->ChangerDeplace(1);
                else partie->ExecuterEvenement(e, SCRIPT_INTERACTION);
                break;
            case SITUATION_CONTACT: //Contact avec événement
                dX = partie->GetOrientationX();
                dY = partie->GetOrientationY();
                if (partie->GetDeplace() && input->getB()) partie->ChangerDeplace(1);
                if (partie->GetDeplace()) partie->ChangerDeplace(1);
                else partie->ExecuterEvenement(e, SCRIPT_CONTACT);
                break;
            case SITUATION_AUTOMATIQUE: //Evénement automatique
                if (partie->GetDeplace() && input->getB()) partie->ChangerDeplace(1);
                if (partie->GetDeplace()) partie->ChangerDeplace(1);
                else partie->ExecuterEvenement(e, SCRIPT_AUTOMATIQUE);
                break;
            case SITUATION_RECHERCHE: //Recherche d'événement automatique
                e = TestAutomatique(partie->GetCarte(), e);
                if (e == -1)
                    partie->SetSituation(SITUATION_DEPLACEMENT);
                else
                    partie->SetSituation(SITUATION_AUTOMATIQUE);
                break;
            case SITUATION_INITIALISATION: //Arrivée sur le terrain
                if (init) { //initialisation unique indépendante du fondu
                    e = -1;
                    dX = partie->GetOrientationX();
                    dY = partie->GetOrientationY();
                    if (partie->GetOrientation() == ORIENTATION_NEUTRE) {
                        partie->SetDeplace(0);
                        partie->SetOrientation(ORIENTATION_BAS);
                    }
                    input->Actualiser();
                    init = false;
                }
                if (partie->GetDeplace()) partie->ChangerDeplace(1);
                if (FonduEntrant(8)) {
                    partie->SetSituation(SITUATION_RECHERCHE);
                    init = true;
                }

                break;
        }
        afficherEcran(); //mis après pour garantir l'affichage
        syncEcran(frameLimit);
    }
    return 0;
}

bool DeplacerHeros(Partie* partie, int dX, int dY, bool fantome) {
    if (fantome || ((dX||dY)
    && TestCollision(partie->GetCarte(),partie->GetX()+dX,partie->GetY()+dY,
                     Z_MILIEU))) { //si le personnage se déplace
        //TODO: mettre tests répétition ici ?
        partie->ChangerX(dX);
        partie->ChangerY(dY);
        partie->SetDeplace(-LARGEUR_TUILE);
        partie->AjouterPas();
        return true;
    }
    return false;
}

int Message(Partie* partie, const char* val) {
    AfficherMessage(val);
    if (partie->GetInput()->takeA())
        return 1;
    return 0;
}

/*char MessageTransition(char animation) {
    AfficherMessageTransition(6+animation);
    return animation+1;
}*/

int Choix(Partie* partie, char nombre,
                  const char* val1, const char* val2,
                  const char* val3, const char* val4) {
    Input* input = partie->GetInput();
    AfficherChoix(partie->GetChoix(), nombre, val1, val2, val3, val4);
    if (input->takeBas())
        partie->SetChoix(AVANT(partie->GetChoix(),nombre));
    if (input->takeHaut())
        partie->SetChoix(APRES(partie->GetChoix(),nombre));
    if (input->takeA())
        return 1;
    return 0;
}

int FonduSortant(int vitesse) {
    ecran_fondu += vitesse;
    if (ecran_fondu > 255)
        ecran_fondu = 255; //écran noir
    return (ecran_fondu == 255);
}

int FonduEntrant(int vitesse) {
    ecran_fondu -= vitesse;
    if (ecran_fondu < 0)
        ecran_fondu = 0; //écran clair
    return (ecran_fondu == 0);
}

/*#include <fichierES.h>

void TeleporterEquipe(Partie* partie, int id,
                      int x, int y, char orientation) {
    if (id != partie->GetCarte()->GetId()) {
        char* fbuf = new char[8192];
        char fichier[] = "bdd/cartes/0.txt";
        fichier[11] += id;
        if (fichier_lire(fichier, fbuf)) {
            delete partie->GetCarte();
            int j = 0;
            partie->SetCarte(new Carte(id));
            partie->GetCarte()->Lire(j, fbuf);
        }
    }
    partie->SetX(x);
    partie->SetY(y);
    partie->SetOrientation(orientation);
}*/

void TeleporterEquipe(Partie* partie, Carte* carte,
                      int x, int y, char orientation) {
    partie->SetCarte(carte);
    //TODO: tester dimensions carte ?
    partie->SetX(x);
    partie->SetY(y);
    partie->SetOrientation(orientation);
}

int OrienterEvenement(Carte* carte, unsigned char id, char orientation, 
                      int Xheros, int Yheros) {
    if (carte == 0)
        return -1;
    Evenement* evenement = carte->GetEvenements(id);
    if (evenement == 0)
        return -1;
    if (orientation == -1) {
        if (evenement->GetY() > Yheros)
            evenement->SetOrientation(ORIENTATION_HAUT);
        else if (evenement->GetY() < Yheros)
            evenement->SetOrientation(ORIENTATION_BAS);
        else if (evenement->GetX() > Xheros)
            evenement->SetOrientation(ORIENTATION_GAUCHE);
        else if (evenement->GetX() < Xheros)
            evenement->SetOrientation(ORIENTATION_DROITE);
    } else
        evenement->SetOrientation(orientation);
    return 1;
}

int DeplacerEvenement(Carte* carte, unsigned char id, int dX, int dY,
                      int Xheros, int Yheros, bool orienter, bool fantome, bool optionnel) {
    if (carte == 0)
        return -1;
    Evenement* evenement = carte->GetEvenements(id);
    if (evenement == 0)
        return -1;
    if (evenement->GetDeplace()) {
        evenement->ChangerDeplace(1);
        if (evenement->GetDeplace() >= 0) {
            evenement->SetDx(0);
            evenement->SetDy(0);
            evenement->SetDeplace(0); //sécurité
            return 1;
        }
    } else {
        if (orienter) {
            if (dY < 0)
                evenement->SetOrientation(ORIENTATION_HAUT);
            else if (dY > 0)
                evenement->SetOrientation(ORIENTATION_BAS);
            else if (dX < 0)
                evenement->SetOrientation(ORIENTATION_GAUCHE);
            else if (dX > 0)
                evenement->SetOrientation(ORIENTATION_DROITE);
        }
        if (fantome || (TestCollision(carte, evenement->GetX()+dX,
                                     evenement->GetY()+dY, evenement->GetZ())
            && (evenement->GetX()+dX!=Xheros
            || evenement->GetY()+dY!=Yheros || evenement->GetZ()!=Z_MILIEU))) {
            evenement->ChangerX(dX);
            evenement->ChangerY(dY);
            evenement->SetDx(dX);
            evenement->SetDy(dY);
            if (carte->GetRepetition()) {
                evenement->SetX((evenement->GetX()+carte->GetLargeur())
                                % carte->GetLargeur());
                evenement->SetY((evenement->GetY()+carte->GetHauteur())
                                % carte->GetHauteur());
            }
            evenement->SetDeplace(-LARGEUR_TUILE);
            //return 1;
        } else if (optionnel)
            return 1;
    }
    return 0;
}

unsigned char ChangerTuile(Partie* partie, unsigned char tuile, int X, int Y, int Z) {
    if (partie->GetCarte()) {
        const unsigned char precedent = partie->GetCarte()->GetTuile(X,Y,Z);
        partie->GetCarte()->SetTuile(tuile,X,Y,Z);
        return precedent;
    }
    return 0;
}

void OuvrirMagasin(Partie* partie, Magasin* magasin) {
    if (magasin) {
        unsigned int Or = partie->GetOr();
        Magasins(partie->GetInventaire(), partie->GetEquipe(), magasin, partie->GetInput(), Or);
        partie->SetOr(Or);
    }
}

//true == defaite, false == victoire
bool DemarrerCombat(Partie* partie, GroupeMonstres* groupe, bool gameover,
                    int D, int dX, int dY) {
    if (groupe) {
        char animation;
        for (animation = 0; animation <= 6; ++animation) {
            if (D) D++;
            AfficherTerrain(partie,D,dX,dY);
            AfficherDemarrerCombat(animation);
            afficherEcran();
            syncEcran(frameLimit);
        }
        partie->SetGroupeCombat(groupe);
        //si on perd le combat et que ce n'est pas prévu, on perd le jeu
        if (Combat(partie) && gameover) {
            partie->SetTerrain(false);
            return true;
        }
    }
    return false;
}
