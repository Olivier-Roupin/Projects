#include "Objet.h"

using namespace std;

Objet::Objet(int Id, string Nom, int Type, int Prix, string Description)
{
     SetId(Id);
     SetNom(Nom);
     SetType(Type);
     SetPrix(Prix);
     SetDescription(Description);
}

Objet::Objet(const Objet& cible)
{
    SetNom(cible.GetNom());
    SetPrix(cible.GetPrix());
    SetDescription(cible.GetDescription());
}

Objet::~Objet()
{
    //dtor
}

int Objet::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Objet::SetId(int val)
{
    if(val < 0)
        val = 0;
    m_Id = val;
}

int Objet::GetType() const
{
    if(this == 0)
        return 0;
    return m_Type;
}

void Objet::SetType(int val)
{
    if(val < 0)
        val = 0;
    m_Type = val;
}

int Objet::GetPrix() const
{
    if(this == 0)
        return 0;
    return m_Prix;
}

void Objet::SetPrix(int val)
{
    if(val < 0)
        val = 0;
    m_Prix = val;
}

string Objet::GetNom() const
{
    if(this == 0)
        return "_";
    return m_Nom;
}

void Objet::SetNom(string val)
{
    if(val == "")
        val = "_";
    m_Nom = val;
}

string Objet::GetDescription() const
{
    if(this == 0)
        return "_";
    return m_Description;
}

void Objet::SetDescription(string val)
{
    if(val == "")
        val = "_";
    m_Description = val;
}
