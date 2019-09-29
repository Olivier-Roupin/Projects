#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <Capacite.h>
#include <Objet.h>
#include <Alteration.h>

#include <cmath> //pour l'exponentielle
#include <ctime> //pour l'aléatoire
#include <cstdlib> //pour rand()

#define VITESSE_COMBAT 1 //BETA
#define MAX_NIVEAU 99
#define TAILLE_JAUGE 1000
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

class Personnage
{
public:
    enum Action
    {
        action_attaquer, action_defense, action_rang, action_objets, action_fuite
    };
    Personnage(int Id, std::string Nom = "_", int Vie = 0, int Magie = 0,\
               int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,\
               int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,\
               int Vitesse = 0, int Precision = 0, int Esquive = 0,\
               int Statut = 0, int Experience = 0, int Niveau = 1, int Jauge = 0);
    Personnage(const Personnage& other);
    virtual ~Personnage();
    int GetId() const;
    void SetId(int val);
    std::string GetNom() const;
    void SetNom(std::string val);

    int GetVie() const;
    void SetVie(int val);
    void ChangerVie(int val);
    int GetVieP() const;
    void SetVieP(int val);
    void ChangerVieP(int val);
    bool estEnVie() const;

    int GetMagie() const;
    void SetMagie(int val);
    void ChangerMagie(int val);
    int GetMagieP() const;
    void SetMagieP(int val);
    void ChangerMagieP(int val);

    //Force
    int GetVieMax() const;
    void SetVieMax(int val);
    void ChangerVieMax(int val);
    int GetAttaqueP() const;
    void SetAttaqueP(int val);
    void ChangerAttaqueP(int val);
    int GetDefenseP() const;
    void SetDefenseP(int val);
    void ChangerDefenseP(int val);

    //Intelligence
    int GetMagieMax() const;
    void SetMagieMax(int val);
    void ChangerMagieMax(int val);
    int GetAttaqueM() const;
    void SetAttaqueM(int val);
    void ChangerAttaqueM(int val);
    int GetDefenseM() const;
    void SetDefenseM(int val);
    void ChangerDefenseM(int val);

    //Agilité
    int GetVitesse() const;
    void SetVitesse(int val);
    void ChangerVitesse(int val);
    int GetPrecision() const;
    void SetPrecision(int val);
    void ChangerPrecision(int val);
    int GetEsquive() const;
    void SetEsquive(int val);
    void ChangerEsquive(int val);

    int GetStatut() const;
    void SetStatut(int val);

    int GetExperience() const;
    void SetExperience(int val);
    void ChangerExperience(int val);

    int GetNiveau();
    void SetNiveau(int val);

    int GetJauge() const;
    void SetJauge(int val);
    void ActualiserJauge(); //BETA : ajoute la vitesse du personnage à la jauge pour la faire avancer
    void ViderJauge();
    bool Jauge_estpleine() const; //Dit si la jauge est au maximum

    Capacite* GetSorts(int id) const;
    int SetSorts(Capacite* val, int id);
    int AjouterSorts(Capacite* val);

    Capacite* GetAptitudes(int id) const;
    int SetAptitudes(Capacite* val, int id);
    int AjouterAptitudes(Capacite* val);

    Alteration* GetAlterations(int id) const;
    void SetAlterations(Alteration* val, int id);
    int ChercherAlteration(Alteration* val) const;
    int ChercherLibre(int priorite = 0) const;
    int AjouterAlteration(Alteration* val);
    int RetirerAlteration(Alteration* val);

    //Combat
    bool estOccupe() const; //le personnage ne peut pas être utilisé : MORT, ACTIF ou JAUGE NON PLEINE
    int GetAction() const;
    void SetAction(int val);
    Objet* GetObjet() const;
    void SetObjet(Objet* val);
    Capacite* GetCapacite() const;
    void SetCapacite(Capacite* val);
    int GetNombreCibles() const;
    void SetNombreCibles(int val);
    Personnage** GetCibles() const;
    Personnage* GetCible(int id) const;
    void SetCibles(Personnage** val);
    //NOMBRE CIBLES

    //Commandes de combat
    float Probabilite_touche() const;
    void Attaquer();
protected:
private:
    int m_Id;
    std::string m_Nom;
    int m_Vie;
    int m_Magie;
    //Force
    int m_VieMax;
    int m_AttaqueP;
    int m_DefenseP;
    //Intelligence
    int m_MagieMax;
    int m_AttaqueM;
    int m_DefenseM;
    //Agilité
    int m_Vitesse;
    int m_Precision;
    int m_Esquive;

    int m_Statut;
    int m_Experience;
    int m_Niveau;
    int m_Jauge;
    //Capacités
    Capacite *m_Sorts[MAX_SORTS];
    Capacite *m_Aptitudes[MAX_APTITUDES];

    Alteration *m_Alterations[MAX_ALTERATIONS];

    //Combat
    int m_Action;           //action à exécuter
    Objet* m_Objet;         //objet choisi
    Capacite* m_Capacite;   //capacité choisie
    int m_NombreCibles;
    Personnage** m_Cibles;  //cibles selectionnées
};

#endif // PERSONNAGE_H
