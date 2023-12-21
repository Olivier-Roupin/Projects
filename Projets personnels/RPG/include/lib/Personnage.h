#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <lib/Capacite.h>
#include <lib/Equipable.h> //pour les attributs et Objet.h
#include <lib/Alteration.h>

#define VITESSE_COMBAT 1 //BETA
#define TAILLE_JAUGE 1024 //1000
#define MAX_SORTS 10
#define MAX_APTITUDES 30
#define MAX_ALTERATIONS 5

//Combat
#define NOMBRE_ACTIONS 6

#define ACTION_INACTIF -1
#define ACTION_ATTAQUER 0
#define ACTION_DEFENSE 1
#define ACTION_RANG 2
#define ACTION_OBJETS 3
#define ACTION_CAPACITE 4
#define ACTION_FUITE 5

#define TAILLE_NOM_PERSONNAGE 7

class Personnage {
public:
    enum Action {
        action_attaquer,action_defense,action_rang,action_objets,action_fuite
    };
    Personnage(int id, const char* nom = "_", int vie = 0, int magie = 0,
               int vieMax   = 0, int attaqueP  = 0, int defenseP = 0,
               int magieMax = 0, int attaqueM  = 0, int defenseM = 0,
               int vitesse  = 0, int precision = 0, int esquive  = 0,
               unsigned char statut = 0, unsigned int experience = 0,
               unsigned char niveau = 1, unsigned int jauge = 0);
    Personnage(const Personnage& other);
    virtual ~Personnage();
    int GetId() const;
    void SetId(int val);
    const char* GetNom() const;
    void SetNom(const char* val);

    int GetVie() const;
    void SetVie(int val);
    void ChangerVie(int val);
    int GetVieP() const;
    void SetVieP(int val);
    int ChangerVieP(int val); //retourne la valeur calculée
    bool estEnVie() const;

    int GetMagie() const;
    void SetMagie(int val);
    void ChangerMagie(int val);
    int GetMagieP() const;
    void SetMagieP(int val);
    void ChangerMagieP(int val);

    int GetAttribut(unsigned char id) const;
    void SetAttribut(int val, unsigned char id);
    void ChangerAttribut(int val, unsigned char id);

    unsigned char GetStatut() const;
    void SetStatut(unsigned char val);

    unsigned int GetExperience() const;
    void SetExperience(int val); //TODO: changer en unsigned ?
    void ChangerExperience(int val);

    unsigned char GetNiveau() const;
    void SetNiveau(unsigned char val);

    unsigned int GetJauge() const;
    void SetJauge(unsigned int val);
    void ActualiserJauge(); //BETA : ajoute la vitesse du personnage à la jauge pour la faire avancer
    void ViderJauge();
    bool Jauge_estpleine() const; //Dit si la jauge est au maximum

    Capacite* GetSorts(unsigned char id) const;
    int SetSorts(Capacite* val, unsigned char id);
    int AjouterSorts(Capacite* val);

    Capacite* GetAptitudes(unsigned char id) const;
    int SetAptitudes(Capacite* val, unsigned char id);
    int AjouterAptitudes(Capacite* val);

    Alteration* GetAlterations(unsigned char id) const;
    void SetAlterations(Alteration* val, unsigned char id);
    int ChercherAlteration(Alteration* val) const;
    int ChercherLibre(unsigned char priorite = 0) const;
    int AjouterAlteration(Alteration* val);
    int RetirerAlteration(Alteration* val);
    void RetirerAlterations();

    //Combat
    bool estOccupe() const; //le personnage ne peut pas être utilisé : MORT, ACTIF ou JAUGE NON PLEINE
    char GetAction() const;
    void SetAction(char val);
    Objet* GetObjet() const;
    void SetObjet(Objet* val);
    Capacite* GetCapacite() const;
    void SetCapacite(Capacite* val);
    unsigned char GetNombreCibles() const;
    void SetNombreCibles(unsigned char val);
    Personnage** GetCibles() const;
    Personnage* GetCible(unsigned char id) const;
    void SetCibles(Personnage** val);
    //NOMBRE CIBLES

    //Commandes de combat
    unsigned int Probabilite_touche() const; // maths à point fixe
    //void Attaquer();
    //TODO Retirer cette fonction et ajouter un GetAttributBrut à Heros
    virtual int GetAttributTotal(unsigned char id) const; // fait la même chose que GetAttribut
    virtual int GetModificateurElementaire(unsigned char id, char element) const; //Moyenne des modificateurs de dégats pondérée par un attribut
    virtual void Attaquer(unsigned int de, unsigned int max_de); //non const pour le temps d'affichage
    // int Attaquer() const; // retourne le nombre de dégats pour l'affichage

    //Animations combat
    int GetTempsMessage() const;
    void SetTempsMessage(int val);
    virtual void ActualiserMessage(); // décrémente le temps
    int GetMessage() const;
    virtual void SetMessage(int val);

    int GetTempsAnimation() const;
    void SetTempsAnimation(int val);
    virtual void ActualiserAnimation(); // décrémente le temps
    char GetAnimation() const;
    virtual void SetAnimation(char val);

    virtual int Ecrire(char* data) const;
    virtual void Lire(int& i, const char* data);
    virtual unsigned int TailleD() const;
    virtual char* EcrireD(char* data) const;
    virtual const char* LireD(const char* data);
protected:
private:
    int m_Id;
    char m_Nom[TAILLE_NOM_PERSONNAGE+1];
    int m_Vie;
    int m_Magie;

    int m_Attributs[NOMBRE_ATTRIBUTS];

    unsigned char m_Statut; //TODO: inutile
    unsigned int  m_Experience;
    unsigned char m_Niveau;
    unsigned int  m_Jauge;
    //Capacités
    Capacite *m_Sorts[MAX_SORTS];
    Capacite *m_Aptitudes[MAX_APTITUDES];

    Alteration *m_Alterations[MAX_ALTERATIONS];

    //Combat
    char m_Action;           //action à exécuter
    Objet* m_Objet;         //objet choisi
    Capacite* m_Capacite;   //capacité choisie
    unsigned char m_NombreCibles;
    Personnage** m_Cibles;  //cibles selectionnées
    //Animations combat
    int m_TempsMessage;
    int m_Message; //char m_Message[5];
    int m_TempsAnimation;
    char m_Animation;
};

#endif // PERSONNAGE_H
