#include "Capacite.h"

using namespace std;

Capacite::Capacite(int Id, string Nom, string Description,\
                   int CoutMagie, int CoutMagieP, int CoutVie, int CoutVieP,\
                   Effet* effet)
{
    SetId(Id);
    SetNom(Nom);
    SetDescription(Description);
    SetCoutMagie(CoutMagie);
    SetCoutMagieP(CoutMagieP);
    SetCoutVie(CoutVie);
    SetCoutVieP(CoutVieP);
    SetEffet(effet);
}

Capacite::~Capacite()
{
    //dtor
}

/*
Capacite::Capacite(const Capacite& cible)
{
    SetNom(cible.GetNom());
    SetDescription(cible.GetDescription());
    SetCoutMagie(cible.GetCoutMagie());
    SetCoutMagieP(cible.GetCoutMagieP());
    SetCoutVie(cible.GetCoutVie());
    SetCoutVieP(cible.GetCoutVieP());
}
*/

int Capacite::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Capacite::SetId(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Id = val;
}

string Capacite::GetNom() const
{
    if(this == 0)
        return "_";
    return m_Nom;
}

void Capacite::SetNom(string val)
{
    if(val == "")
    {
        val = "_";
    }
    m_Nom = val;
}

string Capacite::GetDescription() const
{
    if(this == 0)
        return "_";
    return m_Description;
}

void Capacite::SetDescription(string val)
{
    if(val == "")
    {
        val = "_";
    }
    m_Description = val;
}

int Capacite::GetCoutVie() const
{
    if(this == 0)
        return 0;
    return m_CoutVie;
}

void Capacite::SetCoutVie(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_CoutVie = val;
}

int Capacite::GetCoutVieP() const
{
    if(this == 0)
        return 0;
    return m_CoutVieP;
}

void Capacite::SetCoutVieP(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > 100)
    {
        val = 100;
    }
    m_CoutVieP = val;
}

int Capacite::GetCoutMagie() const
{
    if(this == 0)
        return 0;
    return m_CoutMagie;
}

void Capacite::SetCoutMagie(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_CoutMagie = val;
}

int Capacite::GetCoutMagieP() const
{
    if(this == 0)
        return 0;
    return m_CoutMagieP;
}

void Capacite::SetCoutMagieP(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > 100)
    {
        val = 100;
    }
    m_CoutMagieP = val;
}

Effet* Capacite::GetEffet() const
{
    if(this == 0)
        return 0;
    return m_Effet;
}

void Capacite::SetEffet(Effet* val)
{
    m_Effet = val;
}
