#ifndef HEROS_H
#define HEROS_H

#include <Personnage.h>
#include <Equipable.h>

#define NOMBRE_IN_HEROS 24
#define IN_HEROS_VIE 0
#define IN_HEROS_MAGIE 1
#define IN_HEROS_VIEMAX 2
#define IN_HEROS_ATTAQUEP 3
#define IN_HEROS_DEFENSEP 4
#define IN_HEROS_MAGIEMAX 5
#define IN_HEROS_ATTAQUEM 6
#define IN_HEROS_DEFENSEM 7
#define IN_HEROS_VITESSE 8
#define IN_HEROS_PRECISION 9
#define IN_HEROS_ESQUIVE 10
#define IN_HEROS_STATUT 11
#define IN_HEROS_EXPERIENCE 12
#define IN_HEROS_NIVEAU 13
#define IN_HEROS_FORCE 14
#define IN_HEROS_INTELLIGENCE 15
#define IN_HEROS_AGILITE 16
#define IN_HEROS_RANG 17
#define IN_HEROS_ID_MAINGAUCHE 18
#define IN_HEROS_ID_MAINDROITE 19
#define IN_HEROS_ID_TETE 20
#define IN_HEROS_ID_CORPS 21
#define IN_HEROS_ID_ACCESSOIRE1 22
#define IN_HEROS_ID_ACCESSOIRE2 23

#define MAX_VIE 9999
#define MAX_MAGIE 999

#define NOMBRE_EQUIPEMENTS 6
#define EQUIPEMENT_MAINGAUCHE 0
#define EQUIPEMENT_MAINDROITE 1
#define EQUIPEMENT_TETE 2
#define EQUIPEMENT_CORPS 3
#define EQUIPEMENT_ACCESSOIRE1 4
#define EQUIPEMENT_ACCESSOIRE2 5

#define RANG_AVANT false
#define RANG_ARRIERE true

#define COEF_VIE 100
#define COEF_ATKP 1
#define COEF_DEFP 1
#define COEF_MAG 10
#define COEF_ATKM 1
#define COEF_DEFM 1
#define COEF_VIT 1
#define COEF_PRE 1
#define COEF_ESQ 1

class Heros : public Personnage
{
public:
    Heros(int Id, std::string Nom = "_", int Vie = 0, int Magie = 0,\
          int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,\
          int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,\
          int Vitesse = 0, int Precision = 0, int Esquive = 0,\
          int Statut = 0, int Experience = 0, int Niveau = 1, int Jauge = 0,\
          int Force = 0, int Intelligence = 0, int Agilite = 0, bool Rang = RANG_AVANT);
    Heros(int Id, std::string Nom = "_", int Vie = 0, int Magie = 0,\
          int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,\
          int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,\
          int Vitesse = 0, int Precision = 0, int Esquive = 0,\
          int Statut = 0, int Experience = 0, int Niveau = 1,\
          int Force = 0, int Intelligence = 0, int Agilite = 0, bool Rang = RANG_AVANT,\
          Objet* Maingauche = 0, Objet* Maindroite = 0, Objet* Tete = 0,\
          Objet* Corps = 0, Objet* Accessoire1 = 0, Objet* Accessoire2 = 0, int Jauge = 0); //utilisé
    ~Heros();
    //void PasserNiveau();
    int GetForce();
    void SetForce(int val);
    int GetIntelligence();
    void SetIntelligence(int val);
    int GetAgilite();
    void SetAgilite(int val);
    bool GetRang() const;
    void SetRang(bool val);
    void ChangerRang();
    bool GetGarde() const;
    void SetGarde(bool val);
    Objet* GetEquipement(int id) const;
    int SetEquipement(Objet *val, int id);

    //Avec limites
    void SetVieMax(int val);
    void SetMagieMax(int val);

    /*int CalculerForce() const;
    int CalculerIntelligence() const;
    int CalculerAgilite() const;
    int CalculerNormeOffensif() const;
    int CalculerNormeDefensif() const;
    int CalculerVieMaxP() const;
    int CalculerAttaquePP() const;
    int CalculerDefensePP() const;
    int CalculerMagieMaxP() const;
    int CalculerAttaqueMP() const;
    int CalculerDefenseMP() const;
    int CalculerVitesseP() const;
    int CalculerPrecisionP() const;
    int CalculerEsquiveP() const;

    int CalculerVieMax(int force) const;
    int CalculerAttaqueP(int force) const;
    int CalculerDefenseP(int force) const;
    int CalculerMagieMax(int intelligence) const;
    int CalculerAttaqueM(int intelligence) const;
    int CalculerDefenseM(int intelligence) const;
    int CalculerVitesse(int agilite) const;
    int CalculerPrecision(int agilite) const;
    int CalculerEsquive(int agilite) const;*/

    //Prise en compte des équipements/altérations/rang
    //Force
    int GetVieMaxTotal() const;
    int GetAttaquePTotal() const;
    int GetDefensePTotal() const;
    //Intelligence
    int GetMagieMaxTotal() const;
    int GetAttaqueMTotal() const;
    int GetDefenseMTotal() const;
    //Agilité
    int GetVitesseTotal() const;
    int GetPrecisionTotal() const;
    int GetEsquiveTotal() const;

protected:
private:
    int m_Niveau;
    int m_Force;
    int m_Intelligence;
    int m_Agilite;
    bool m_Rang;
    bool m_Garde;
    Objet* m_Equipement[NOMBRE_EQUIPEMENTS];
};

#endif // HEROS_H
