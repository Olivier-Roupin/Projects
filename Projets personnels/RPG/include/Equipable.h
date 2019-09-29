#ifndef EQUIPABLE_H
#define EQUIPABLE_H

#include <Objet.h>

#define NOMBRE_DONNEES_EQUIPABLE 12

#define EQUIPABLE_ARME 11
#define EQUIPABLE_ARMURE 12
#define EQUIPABLE_BOUCLIER 13
#define EQUIPABLE_CASQUE 14
#define EQUIPABLE_ACCESSOIRE 15

class Equipable : public Objet
{
public:
    Equipable(int Id, std::string Nom = "_", int Type = EQUIPABLE, int Prix = 0, std::string Description = "_",\
              int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,\
              int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,\
              int Vitesse = 0, int Precision = 0, int Esquive = 0,\
              int Poids = 0, int Offensif = 0, int Defensif = 0);
    virtual ~Equipable();

    //Force
    int GetVieMax() const;
    void SetVieMax(int val);
    int GetAttaqueP() const;
    void SetAttaqueP(int val);
    int GetDefenseP() const;
    void SetDefenseP(int val);

    //Intelligence
    int GetMagieMax() const;
    void SetMagieMax(int val);
    int GetAttaqueM() const;
    void SetAttaqueM(int val);
    int GetDefenseM() const;
    void SetDefenseM(int val);

    //Agilité
    int GetVitesse() const;
    void SetVitesse(int val);
    int GetPrecision() const;
    void SetPrecision(int val);
    int GetEsquive() const;
    void SetEsquive(int val);

    //Evolution
    int GetPoids() const;
    void SetPoids(int val);
    int GetOffensif() const;
    void SetOffensif(int val);
    int GetDefensif() const;
    void SetDefensif(int val);
    int GetPhysionomique() const; //déduit

    int GetDegats() const;
    void SetDegats(int val);
protected:
private:
    //Permanent
    int m_VieMax;
    int m_AttaqueP;
    int m_DefenseP;
    int m_MagieMax;
    int m_AttaqueM;
    int m_DefenseM;
    int m_Vitesse;
    int m_Precision;
    int m_Esquive;
    //Evolution
    int m_Poids;
    int m_Offensif;
    int m_Defensif;

    int m_Degats;
};

#endif // EQUIPABLE_H
