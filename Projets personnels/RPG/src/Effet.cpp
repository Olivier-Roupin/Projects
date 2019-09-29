#include "Effet.h"

Effet::Effet(Script* script, int Element, int Disponibilite)
{
    SetScript(script); //non prise en compte du curseur
    SetElement(Element);
    SetDisponibilite(Disponibilite);
}

Effet::Effet(Script* script, int Element, int Disponibilite,\
             bool Choix_Cible, bool Choix_Faction, bool Choix_Quantite,\
             int Defaut_Cible, bool Defaut_Faction, bool Defaut_Quantite)
{
    SetScript(script); //non prise en compte du curseur
    SetElement(Element);
    SetDisponibilite(Disponibilite);
    SetChoix_Cible(Choix_Cible);
    SetChoix_Faction(Choix_Faction);
    SetChoix_Quantite(Choix_Quantite);
    SetDefaut_Cible(Defaut_Cible);
    SetDefaut_Faction(Defaut_Faction);
    SetDefaut_Quantite(Defaut_Quantite);
}

Effet::~Effet()
{
    //dtor
}

Script* Effet::GetScript() const
{
    if(this == 0)
        return 0;
    return m_Script;
}

void Effet::SetScript(Script* val)
{
    m_Script = val;
}

void Effet::SetElement(int val)
{
    m_Element = val;
}

int Effet::GetElement() const
{
    if(this == 0)
        return 0;
    return m_Element;
}

int Effet::GetDisponibilite() const
{
    if(this == 0)
        return 0;
    return m_Disponibilite;
}

void Effet::SetDisponibilite(int val)
{
    m_Disponibilite = val;
}

bool Effet::GetChoix_Cible() const
{
    if(this == 0)
        return false;
    return m_Choix_Cible;
}

void Effet::SetChoix_Cible(bool val)
{
    m_Choix_Cible = val;
}

bool Effet::GetChoix_Faction() const
{
    if(this == 0)
        return false;
    return m_Choix_Faction;
}

void Effet::SetChoix_Faction(bool val)
{
    m_Choix_Faction = val;
}

bool Effet::GetChoix_Quantite() const
{
    if(this == 0)
        return false;
    return m_Choix_Quantite;
}

void Effet::SetChoix_Quantite(bool val)
{
    m_Choix_Quantite = val;
}

int Effet::GetDefaut_Cible() const
{
    if(this == 0)
        return 0;
    return m_Defaut_Cible;
}

void Effet::SetDefaut_Cible(int val)
{
    m_Defaut_Cible = val;
}

bool Effet::GetDefaut_Faction() const
{
    if(this == 0)
        return false;
    return m_Defaut_Faction;
}

void Effet::SetDefaut_Faction(bool val)
{
    m_Defaut_Faction = val;
}

bool Effet::GetDefaut_Quantite() const
{
    if(this == 0)
        return false;
    return m_Defaut_Quantite;
}

void Effet::SetDefaut_Quantite(bool val)
{
    m_Defaut_Quantite = val;
}
