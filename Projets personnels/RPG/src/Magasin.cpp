#include "Magasin.h"

using namespace std;

Magasin::Magasin(int id, int nombre, Objet** objets)
{
    SetId(id);
    SetNombre(nombre);
    m_Objets = new Objet*[sizeof(Objet*)*GetNombre()];
    if(objets)
    {
        *m_Objets = *objets;
    }
    else
    {
        int i;
        for(i = 0; i < GetNombre(); i++)
        {
            m_Objets[i] = 0;
        }
    }
}

Magasin::~Magasin()
{
    //dtor
}

int Magasin::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Magasin::SetId(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Id = val;
}

int Magasin::GetNombre() const
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void Magasin::SetNombre(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    if(val > MAX_OBJETS_MAGASIN)
    {
        val = MAX_OBJETS_MAGASIN;
    }
    m_Nombre = val;
}

Objet* Magasin::GetObjets(int id) const
{
    if(this == 0)
        return 0;
    return m_Objets[id];
}

void Magasin::SetObjets(Objet* val, int id)
{
    m_Objets[id] = val;
}

int Magasin::ChercherLibre() const
{
    int i(0);
    int n(GetNombre());
    while(GetObjets(i) && i < n)
    {
        i++;
    }
    if(i >= n)
    {
        return -1;
    }
    return i;
}

int Magasin::AjouterObjet(Objet* val)
{
    int i(ChercherLibre());
    if(i != -1)
    {
        SetObjets(val,i);
    }
    else
    {
        return -1;
    }
    return 0;
}

string Magasin::GetNom(int id) const
{
    if(this == 0)
        return "_";
    return GetObjets(id)->GetNom();
}

int Magasin::GetPrix(int id) const
{
    if(this == 0)
        return 0;
    return GetObjets(id)->GetPrix();
}
