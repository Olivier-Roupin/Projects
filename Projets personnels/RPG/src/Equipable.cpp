#include "Equipable.h"

using namespace std;

Equipable::Equipable(int Id, string Nom, int Type, int Prix, string Description,\
                     int VieMax, int AttaqueP, int DefenseP,\
                     int MagieMax, int AttaqueM, int DefenseM,\
                     int Vitesse, int Precision, int Esquive,\
                     int Poids, int Offensif, int Defensif) : Objet(Id,Nom,Type,Prix,Description)
{
    SetVieMax(VieMax);
    SetAttaqueP(AttaqueP);
    SetDefenseP(DefenseP);
    SetMagieMax(MagieMax);
    SetAttaqueM(AttaqueM);
    SetDefenseM(DefenseM);
    SetVitesse(Vitesse);
    SetPrecision(Precision);
    SetEsquive(Esquive);
    SetOffensif(Offensif);
    SetDefensif(Defensif);
    SetPoids(Poids);
}

Equipable::~Equipable()
{
    //dtor
}

int Equipable::GetVieMax() const
{
    if(this == 0)
        return 0;
    return m_VieMax;
}

void Equipable::SetVieMax(int val)
{
    m_VieMax = val;
}

int Equipable::GetAttaqueP() const
{
    if(this == 0)
        return 0;
    return m_AttaqueP;
}

void Equipable::SetAttaqueP(int val)
{
    m_AttaqueP = val;
}

int Equipable::GetDefenseP() const
{
    if(this == 0)
        return 0;
    return m_DefenseP;
}

void Equipable::SetDefenseP(int val)
{
    m_DefenseP = val;
}

int Equipable::GetMagieMax() const
{
    if(this == 0)
        return 0;
    return m_MagieMax;
}

void Equipable::SetMagieMax(int val)
{
    m_MagieMax = val;
}

int Equipable::GetAttaqueM() const
{
    if(this == 0)
        return 0;
    return m_AttaqueM;
}

void Equipable::SetAttaqueM(int val)
{
    m_AttaqueM = val;
}

int Equipable::GetDefenseM() const
{
    if(this == 0)
        return 0;
    return m_DefenseM;
}

void Equipable::SetDefenseM(int val)
{
    m_DefenseM = val;
}


int Equipable::GetVitesse() const
{
    if(this == 0)
        return 0;
    return m_Vitesse;
}

void Equipable::SetVitesse(int val)
{
    m_Vitesse = val;
}

int Equipable::GetPrecision() const
{
    if(this == 0)
        return 0;
    return m_Precision;
}

void Equipable::SetPrecision(int val)
{
    m_Precision = val;
}

int Equipable::GetEsquive() const
{
    if(this == 0)
        return 0;
    return m_Esquive;
}

void Equipable::SetEsquive(int val)
{
    m_Esquive = val;
}

int Equipable::GetPoids() const
{
    if(this == 0)
        return 0;
    return m_Poids;
}

void Equipable::SetPoids(int val)
{
    if(val < 0)
        val = 0;
    m_Poids = val;
}

int Equipable::GetOffensif() const
{
    if(this == 0)
        return -1;
    return m_Offensif;
}

void Equipable::SetOffensif(int val)
{
    if(val < 0)
        val = 0;
    else if(val > 100)
        val = 100;
    m_Offensif = val;
}

int Equipable::GetDefensif() const
{
    if(this == 0)
        return -1;
    return m_Defensif;
}

void Equipable::SetDefensif(int val)
{
    if(val < 0)
        val = 0;
    else if(val > 100)
        val = 100;
    m_Defensif = val;
}

int Equipable::GetPhysionomique() const
{
    if(this == 0)
        return -1;
    return 100 - GetOffensif() - GetDefensif();
}

int Equipable::GetDegats() const
{
    if(this == 0)
        return 0;
    return m_Degats;
}

void Equipable::SetDegats(int val)
{
    m_Degats = val;
}
