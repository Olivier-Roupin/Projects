#include "Inventaire.h"

using namespace std;

Inventaire::Inventaire()
{
    int i;
    for(i = 0; i < MAX_OBJETS; ++i)
    {
        m_Objets[i] = 0;
    }
}

Inventaire::~Inventaire()
{
    int i;
    for(i = 0; i < MAX_OBJETS; ++i)
    {
        delete m_Objets[i];
    }
}

GroupeObjets* Inventaire::GetObjets(int id) const
{
    if(this == 0)
        return 0;
    return m_Objets[id];
}

void Inventaire::SetObjets(GroupeObjets* val, int id)
{
    delete m_Objets[id];
    if(val)
        m_Objets[id] = new GroupeObjets(*val);
    else
        m_Objets[id] = 0;
}

void Inventaire::SetObjets(Objet* val, int nombre, int id)
{
    delete m_Objets[id];
    if(val)
        m_Objets[id] = new GroupeObjets(val, nombre);
    else
        m_Objets[id] = 0;
}

int Inventaire::ChercherObjet(Objet* val) const
{
    int i(0);
    while(i < MAX_OBJETS && GetObjets(i)->GetObjet() != val)
    {
        i++;
    }
    if(i >= MAX_OBJETS)
    {
        return -1;
    }
    return i;
}

int Inventaire::ChercherObjet(GroupeObjets* val) const
{
    return ChercherObjet(val->GetObjet());
}

int Inventaire::ChercherLibre() const
{
    return ChercherObjet();
}

int Inventaire::AjouterObjets(GroupeObjets* val)
{
    int i(ChercherObjet(val));
    if(i != -1)
    {
        m_Objets[i]->ChangerNombre(val->GetNombre());
    }
    else
    {
        i = ChercherLibre();
        if(i != -1)
        {
            SetObjets(val, i);
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int Inventaire::AjouterObjets(Objet* val, int nombre)
{
    if(val)
    {
        /*GroupeObjets *cible;
        cible = new GroupeObjets(val, nombre);
        return AjouterObjets(cible);*/
        GroupeObjets cible(val, nombre);
        return AjouterObjets(&cible);
    }
    return -1;
}

int Inventaire::RetirerObjets(GroupeObjets* val)
{
    int i(ChercherObjet(val));
    if(i != -1)
    {
        m_Objets[i]->ChangerNombre(-val->GetNombre());
        if(GetObjets(i)->GetNombre() == 0)
        {
            SetObjets(0, i);
        }
        return 0;
    }
    return -1;
}

int Inventaire::RetirerObjets(Objet* val, int nombre)
{
    if(val)
    {
        /*GroupeObjets *cible;
        cible = new GroupeObjets(val, nombre);
        return RetirerObjets(cible);*/
        GroupeObjets cible(val, nombre);
        return RetirerObjets(&cible);
    }
    return -1;
}

int Inventaire::EchangerObjets(int id1, int id2)
{
    GroupeObjets* copie(m_Objets[id1]);

    m_Objets[id1] = m_Objets[id2];
    m_Objets[id2] = copie;

    return 0;
}

int Inventaire::GetNombreObjets(Objet* val) const
{
    int i(ChercherObjet(val));
    if(i != -1)
    {
        return m_Objets[i]->GetNombre();
    }
    return 0;
}

string Inventaire::GetNom(int id) const
{
    if(this == 0)
        return "_";
    return GetObjets(id)->GetNom();
}

int Inventaire::GetPrix(int id) const
{
    if(this == 0)
        return 0;
    return GetObjets(id)->GetPrix();
}

int Inventaire::GetNombre(int id) const
{
    if(this == 0)
        return 0;
    return GetObjets(id)->GetNombre();
}
