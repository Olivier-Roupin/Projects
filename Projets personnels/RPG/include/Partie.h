#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include <Input.h>
#include <Carte.h>
#include <Equipe.h>
#include <Inventaire.h>
    #include <Utilisable.h>
#include <GroupeMonstres.h>
    #include <Magasin.h>
#define QUITTER -2
#define NOUVELLE_PARTIE -1
#define CHARGER_PARTIE 0
#define MAX_OR 999999999
//Options
#define MIN_VITESSE_COMBAT 1
#define MAX_VITESSE_COMBAT 8
#define MODE_ACTIF 0
#define MODE_SEMI_ACTIF 1
#define MODE_PASSIF 2

#define NOMBRE_CAPACITES 100
#define NOMBRE_OBJETS 100
#define NOMBRE_CARTES 100
#define NOMBRE_MONSTRES 100
#define NOMBRE_GROUPES_MONSTRES 100
#define NOMBRE_HEROS 8
#define NOMBRE_TILESETS 100
#define NOMBRE_MAGASINS 50
#define NOMBRE_ALTERATIONS 20

extern Capacite *capacites[NOMBRE_CAPACITES+1];
extern Objet *objets[NOMBRE_OBJETS+1];
extern Carte *cartes[NOMBRE_CARTES+1];
extern Monstre *monstres[NOMBRE_MONSTRES+1];
extern GroupeMonstres *groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
extern Heros *heross[NOMBRE_HEROS+1];
extern Tileset *tilesets[NOMBRE_TILESETS+1];
extern Magasin *magasins[NOMBRE_MAGASINS+1];
extern Alteration *alterations[NOMBRE_ALTERATIONS+1];

//Ecran_titre
#define SITUATION_ECRAN_TITRE 0
#define SITUATION_CHARGER 1

//Menu_Sauver
#define NOMBRE_SAUVEGARDES 4

#define SITUATION_CHOIX_SAUVEGARDE 0
#define SITUATION_VALIDATION 1

//Terrain
#define NOMBRE_ORIENTATIONS 4
#define ORIENTATION_DROITE 0
#define ORIENTATION_HAUT 1
#define ORIENTATION_GAUCHE 2
#define ORIENTATION_BAS 3

#define SITUATION_DEPLACEMENT 0 //le personnage et les événements se déplacent librement (script 0)
#define SITUATION_INTERACTION 1 //le personnage a appuyé sur A pour intéragir avec un événement (script 1)
#define SITUATION_CONTACT 2 //le personnage est entré en contact avec un événement (script 2)
#define SITUATION_AUTOMATIQUE 3 //le personnage arrive sur la carte et un événement se déclanche (script 3)
#define SITUATION_INITIALISATION 4 //le personnage arrive sur la carte
#define SITUATION_RECHERCHE 5 //recherche d'événements automatiques

#define SCRIPT_CONTINU 0
#define SCRIPT_INTERACTION 1
#define SCRIPT_CONTACT 2
#define SCRIPT_AUTOMATIQUE 3

//Combat
#define CHOIX_HEROS 0
#define CHOIX_ACTION 1
#define CHOIX_CIBLE 2
#define CHOIX_OBJET 3
#define CHOIX_CAPACITE 4
#define AGIR 5

#define COMBAT_EN_COURS 0
#define COMBAT_DEFAITE 1
#define COMBAT_VICTOIRE 2
#define COMBAT_FUITE 3

#define FACTION_EQUIPE false
#define FACTION_MONSTRES true

std::string Int2String(int i);

class Partie
{
public:
    Partie(int id);
    ~Partie();
    Equipe* GetEquipe() const;
    void SetEquipe(Equipe* val);
    Inventaire* GetInventaire() const;
    void SetInventaire(Inventaire* val);
    GroupeMonstres* GetGroupeCombat() const;
    void SetGroupeCombat(GroupeMonstres* val);
    Carte* GetCarte() const;
    void SetCarte(Carte* val);
    int GetX() const;
    void SetX(int val);
    void ChangerX(int val);
    int GetY() const;
    void SetY(int val);
    void ChangerY(int val);
    int GetOrientation() const;
    void SetOrientation(int val);
    void ChangerOrientation(int val);
    int GetOrientationX() const;
    int GetOrientationY() const;
    int GetOr() const;
    void SetOr(int val);
    void ChangerOr(int val);
    int GetTemps() const; //Donne le temps contenu dans la sauvergarde
    int GetHeures() const; //Du temps de jeu
    int GetMinutes() const;
    int GetSecondes() const;
    void SetTemps(int val);
    int GetTempsJeu() const; //Donne le temps écoulé depuis la création de la partie (temps dans la sauvegarde + temps de la session)
    int GetPas() const;
    void SetPas(int val);
    void AjouterPas(); //Ajouter 1 au nombre de pas

    //Options
    unsigned int GetVitesseCombat() const;
    void SetVitesseCombat(int val);
    void ChangerVitesseCombat(int val);
    unsigned int GetModeCombat() const;
    void SetModeCombat(int val);
    void ChangerModeCombat(int val);
    bool GetMemoriserCurseur() const;
    void SetMemoriserCurseur(bool val);
    void ChangerMemoriserCurseur();

    //Combat
    Input* GetInput() const;
    void SetInput(Input* val);
    int GetMenu() const;
    void SetMenu(int val);

    int GetHeros() const;
    Heros* GetHeros_selection() const;
    void SetHeros(int val);

    int GetAction() const;
    void SetAction(int val);

    int GetObjet() const;
    Objet* GetObjet_selection() const;
    void SetObjet(int val);

    int GetCapacite() const;
    Capacite* GetCapacite_selection() const;
    void SetCapacite(int val);

        //propriétés cible
    int GetCible() const;
    void SetCible(int val);
    bool GetFaction() const; //LANCEUR OU ADVERSE
    void SetFaction(bool val);
    bool GetQuantite() const;
    void SetQuantite(bool val);
    Personnage** GetCible_selection() const;
    int GetCible_nombre() const;

    bool GetChoix_Cible_selection() const;
    bool GetChoix_Faction_selection() const;
    bool GetChoix_Quantite_selection() const;

    int GetDefaut_Cible_selection() const;
    bool GetDefaut_Faction_selection() const;
    bool GetDefaut_Quantite_selection() const;

    ///Affecte la cible
    void SetCible_Defaut(); //Exclusivement pour l'équipe

    Personnage* GetActeur() const;
    void SetActeur(Personnage* val);

        //proprités lanceur
    int GetLanceur() const;
    void SetLanceur(int val);
    bool GetFactionLanceur() const; //EQUIPE OU MONSTRES
    void SetFactionLanceur(bool val);
    Personnage* GetLanceur_selection() const;

    //Terrain
    int GetChoix() const;
    void SetChoix(int val);
    int GetSituation() const;
    void SetSituation(int val);
    bool GetTerrain() const;
    void SetTerrain(bool val);
protected:
private:
    Equipe* m_Equipe;
    Inventaire* m_Inventaire;
    GroupeMonstres* m_GroupeCombat;
    Carte* m_Carte;
    int m_X;
    int m_Y;
    int m_Orientation;
    int m_Or;
    int m_Temps;
    int m_Pas;

    //Options
    unsigned int m_VitesseCombat;
    unsigned int m_ModeCombat;
    bool m_MemoriserCurseur;

    //Combat
    Input* m_Input;
    //Curseur
    int m_Menu; //situation
    int m_Heros; //choix du héros
    int m_Action; //    de l'action
    int m_Objet; //     de l'objet utilisé
    int m_Capacite; //  du sort utilisé
    int m_Cible; //     de la cible
    bool m_Faction; //  de la faction ciblée
    bool m_Quantite; // de la quantité de cibles

    //Action
    Personnage* m_Acteur; //Contient action, cible, capacite, objet

    int m_Lanceur;
    bool m_FactionLanceur;

    //Terrain
    int m_Choix;
    int m_Situation;
    bool m_Terrain;
};

#endif // PARTIE_H
