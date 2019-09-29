#include "GroupeObjets.h"

using namespace std;

GroupeObjets::GroupeObjets(Objet *objet, int Nombre)
{
    SetObjet(objet);
    SetNombre(Nombre);
}

GroupeObjets::GroupeObjets(GroupeObjets const& copie)
{
    SetObjet(copie.GetObjet());
    SetNombre(copie.GetNombre());
}

GroupeObjets::~GroupeObjets()
{
    //delete m_Objet;
}

Objet* GroupeObjets::GetObjet() const
{
    if(this == 0)
        return 0;
    return m_Objet;
}

void GroupeObjets::SetObjet(Objet *val)
{
    m_Objet = val;
}

int GroupeObjets::GetNombre() const
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void GroupeObjets::SetNombre(int val)
{
    if(val < 0)
        val = 0;
    else if(val > MAX_OBJETS_GROUPE)
        val = MAX_OBJETS_GROUPE;
    m_Nombre = val;
}

void GroupeObjets::ChangerNombre(int val)
{
    SetNombre(GetNombre() + val);
}

int GroupeObjets::GetPrix() const
{
    if(this == 0)
        return 0;
    return GetObjet()->GetPrix();
}

string GroupeObjets::GetNom() const
{
    if(this == 0)
        return "_";
    return GetObjet()->GetNom();
}
