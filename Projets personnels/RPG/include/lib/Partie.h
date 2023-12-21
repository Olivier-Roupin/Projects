#ifndef PARTIE_H
#define PARTIE_H

#include <lib/Carte.h> //Orientations
#include <lib/Equipe.h>
#include <lib/Inventaire.h>
    #include <lib/Utilisable.h>
#include <lib/GroupeMonstres.h>
    #include <lib/Magasin.h>

class Input;

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

#define NOMBRE_EFFETS           200 //
#define NOMBRE_CAPACITES        100
#define NOMBRE_OBJETS           100
#define NOMBRE_EVENEMENTS       1000 //
#define NOMBRE_CARTES           100
#define NOMBRE_MONSTRES         100
#define NOMBRE_GROUPES_MONSTRES 100
#define NOMBRE_HEROS            8
#define NOMBRE_TILESETS         100
#define NOMBRE_SCRIPTS          1000 //
#define NOMBRE_MAGASINS         50
#define NOMBRE_ALTERATIONS      20

extern Effet*          effets[NOMBRE_EFFETS+1]; //
extern Capacite*       capacites[NOMBRE_CAPACITES+1];
extern Objet*          objets[NOMBRE_OBJETS+1];
extern Evenement*      evenements[NOMBRE_EVENEMENTS+1]; //
extern Carte*          cartes[NOMBRE_CARTES+1];
extern Monstre*        monstres[NOMBRE_MONSTRES+1];
extern GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
extern Heros*          heross[NOMBRE_HEROS+1];
extern Tileset*        tilesets[NOMBRE_TILESETS+1];
extern Script*         scripts[NOMBRE_SCRIPTS+1]; //
extern Magasin*        magasins[NOMBRE_MAGASINS+1];
extern Alteration*     alterations[NOMBRE_ALTERATIONS+1];

//Ecran_titre
#define SITUATION_ECRAN_TITRE 0
#define SITUATION_CHARGER 1

//Menu_Sauver
#define NOMBRE_SAUVEGARDES 4

#define SITUATION_CHOIX_SAUVEGARDE 0
#define SITUATION_VALIDATION 1

//Terrain
//le personnage et les événements se déplacent librement (script 0)
#define SITUATION_DEPLACEMENT 0
//le personnage a appuyé sur A pour intéragir avec un événement (script 1)
#define SITUATION_INTERACTION 1
//le personnage est entré en contact avec un événement (script 2)
#define SITUATION_CONTACT 2
//le personnage arrive sur la carte et un événement se déclanche (script 3)
#define SITUATION_AUTOMATIQUE 3
//le personnage arrive sur la carte
#define SITUATION_INITIALISATION 4
//recherche d'événements automatiques
#define SITUATION_RECHERCHE 5

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

class Partie {
public:
    // Partie(int id, Input* input = 0);
    Partie(Input* input = 0);
    ~Partie();
    unsigned char GetId() const;
    void SetId(unsigned char val);
    Equipe* GetEquipe() const;
    void SetEquipe(Equipe* val);
    Inventaire* GetInventaire() const;
    void SetInventaire(Inventaire* val);
    GroupeMonstres* GetGroupeCombat() const;
    void SetGroupeCombat(GroupeMonstres* val);
    Monstre* GetMonstre(int id) const; //Monstres du combat
    Carte* GetCarte() const;
    void SetCarte(Carte* val);
    void ExecuterEvenement(unsigned char id, unsigned char id_script);
    int GetX() const;
    void SetX(int val);
    void ChangerX(int val);
    int GetY() const;
    void SetY(int val);
    void ChangerY(int val);
    char GetOrientation() const;
    void SetOrientation(char val);
    void ChangerOrientation(char val);
    char GetOrientationX() const;
    char GetOrientationY() const;
    char GetDeplace() const;
    void SetDeplace(char val);
    void ChangerDeplace(char val);
    char GetMeneur() const;
    void SetMeneur(char val);
    void IncMeneur();
    void ResetMeneur(); //vérifie que le meneur actuel est valide et corrige
    unsigned int GetOr() const;
    void SetOr(unsigned int val);
    void ChangerOr(int val);
    int GetTemps() const; //Donne le temps contenu dans la sauvergarde
    void SetTemps(int val);
    //Donne le temps écoulé depuis la création de la partie
    //(temps dans la sauvegarde + temps de la session)
    unsigned int GetTempsJeu() const;
    unsigned int GetTempsActif() const;
    void SetTempsActif(unsigned int val);
    // unsigned int GetHeures() const; //Du temps de jeu, ASCII
    // unsigned int GetMinutes() const; //Du temps de jeu, ASCII
    // unsigned int GetSecondes() const; //Du temps de jeu, ASCII
    unsigned int GetPas() const;
    void SetPas(unsigned int val);
    void AjouterPas(); //Ajouter 1 au nombre de pas

    //Options
    unsigned char GetVitesseCombat() const;
    void SetVitesseCombat(unsigned char val);
    void ChangerVitesseCombat(char val);
    unsigned char GetModeCombat() const;
    void SetModeCombat(unsigned char val);
    void ChangerModeCombat(char val);
    bool GetMemoriserCurseur() const;
    void SetMemoriserCurseur(bool val);
    void ChangerMemoriserCurseur();

    //Combat
    Input* GetInput() const;
    void SetInput(Input* val);
    char GetMenu() const;
    void SetMenu(char val);

    char GetHeros() const;
    Heros* GetHeros_selection() const;
    void SetHeros(char val);

    char GetAction() const;
    void SetAction(char val);
    void ApplyAction_selection(); //applique l'action au héros

    int GetObjet() const;
    Objet* GetObjet_selection() const;
    void SetObjet(int val);
    void ApplyObjet_selection();

    int GetCapacite() const;
    Capacite* GetCapacite_selection() const;
    void SetCapacite(int val);
    void ApplyCapacite_selection();

        //propriétés cible
    int GetCible() const;
    void SetCible(int val);
    void IncCible(const int taille);
    void DecCible(const int taille);
    bool GetFaction() const; //LANCEUR OU ADVERSE
    void SetFaction(bool val);
    bool GetQuantite() const;
    void SetQuantite(bool val);
    Personnage** GetCible_selection() const;
    int GetCible_nombre() const;
    void ApplyCible_selection(); //applique la cible au héros

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
    char GetChoix() const;
    void SetChoix(char val);
    char GetSituation() const;
    void SetSituation(char val);
    bool GetTerrain() const;
    void SetTerrain(bool val);

    unsigned char GetEvenement() const; //utile pour l'exécution des scripts
    //Evenement* GetEvenements_selection() const;
    void SetEvenement(unsigned char val);

    int Ecrire(char* data) const;
    void Lire(int& i, const char* data);
protected:
private:
    unsigned char m_Id;
    Equipe* m_Equipe;
    Inventaire* m_Inventaire;
    GroupeMonstres* m_GroupeCombat;
    Carte* m_Carte;
    int m_X;
    int m_Y;
    char m_Orientation;
    char m_Deplace;
    char m_Meneur; //indice dans l'équipe du personnage affiché à l'écran
    int m_Or;
    int m_Temps;
    unsigned int m_TempsActif;
    unsigned int m_Pas;

    //Options
    unsigned char m_VitesseCombat;
    unsigned char m_ModeCombat;
    bool m_MemoriserCurseur;

    //Combat
    Input* m_Input;
    //Curseur
    char m_Menu; //situation
    char m_Heros; //choix du héros
    char m_Action; //   de l'action
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
    char m_Choix;
    char m_Situation;
    bool m_Terrain;
    char m_Evenement;
};

#endif // PARTIE_H
