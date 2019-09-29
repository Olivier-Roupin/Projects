#include "GroupeMonstres.h"

using namespace std;

GroupeMonstres::GroupeMonstres(int Id, int nombre, string fond, Monstre** monstres)
{
    int i;
    SetId(Id);
    SetNombre(nombre);
    SetFond(fond);
    m_Monstres = new Monstre*[sizeof(Monstre*)*GetNombre()];
    m_X = new int[sizeof(int)*GetNombre()];
    m_Y = new int[sizeof(int)*GetNombre()];
    for(i = 0; i < GetNombre(); i++)
        m_X[i] = 0;
    for(i = 0; i < GetNombre(); i++)
        m_Y[i] = 0;
    if(monstres)
    {
        *m_Monstres = *monstres;
    }
    else
    {
        for(i = 0; i < GetNombre(); i++)
            m_Monstres[i] = 0;
    }
}

GroupeMonstres::GroupeMonstres(int Id, const GroupeMonstres& cible)//: GroupeMonstres(0, cible.GetNombre())
{
    int i;
    SetId(Id);
    SetNombre(cible.GetNombre());
    SetFond(cible.GetFond());
    m_Monstres = new Monstre*[sizeof(Monstre*)*GetNombre()];
    m_X = new int[sizeof(int)*GetNombre()];
    m_Y = new int[sizeof(int)*GetNombre()];
    Monstre* copie(0);
    for(i = 0; i < GetNombre(); i++)
    {
        if(cible.GetMonstres(i))
        {
            copie = new Monstre(*(cible.GetMonstres(i)));
            SetMonstres(copie,i);
            GetMonstres(i)->SetX(cible.GetX(i));
            GetMonstres(i)->SetY(cible.GetY(i));
        }
        else
        {
            m_Monstres[i] = 0;
        }
        SetX(cible.GetX(i),i);
        SetY(cible.GetY(i),i);
    }
}

GroupeMonstres::~GroupeMonstres()
{
    //dtor
}

int GroupeMonstres::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void GroupeMonstres::SetId(int val)
{
    if(val < 0)
        val = 0;
    m_Id = val;
}

int GroupeMonstres::GetNombre() const
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void GroupeMonstres::SetNombre(int val)
{
    if(val < 0)
        val = 0;
    if(val > MAX_MONSTRES)
        val = MAX_MONSTRES;
    m_Nombre = val;
}

Monstre** GroupeMonstres::GetMonstres() const
{
    if(this == 0)
        return 0;
    return m_Monstres;
}

Monstre* GroupeMonstres::GetMonstres(int id) const
{
    if(this == 0)
        return 0;
    return m_Monstres[id];
}

void GroupeMonstres::SetMonstres(Monstre* val, int id)
{
    m_Monstres[id] = val;
}

int GroupeMonstres::ChercherMonstres(Monstre *val) const
{
    int i(0);
    int n(GetNombre());
    while (GetMonstres(i) != val && i < n)
    {
        i++;
    }
    if(i >= n)
        return -1;
    return i;
}

int GroupeMonstres::ChercherLibre() const
{
    return ChercherMonstres();
}

int GroupeMonstres::AjouterMonstres(Monstre *val, int nombre)
{
    int k,i;
    for(k = 0; k < nombre; k++)
    {
        i = ChercherLibre();
        if(i != -1)
            SetMonstres(val,i);
        else
            return -1;
    }
    return 0;
}

int GroupeMonstres::AjouterMonstres(Monstre *val, int X, int Y)
{
    int i;
    i = ChercherLibre();
    if(i != -1)
    {
        SetMonstres(val,i);
        SetX(X,i);
        SetY(Y,i);
    }
    else
        return -1;
    return 0;
}

string GroupeMonstres::GetFond() const
{
    if(this == 0)
        return "_";
    return m_Fond;
}

void GroupeMonstres::SetFond(string val)
{
    m_Fond = val;
}

int GroupeMonstres::GetX(int id) const
{
    if(this == 0)
        return 0;
    return m_X[id];
}

void GroupeMonstres::SetX(int val, int id)
{
    if(val < 0)
        val = 0;
    m_X[id] = val;
}

int GroupeMonstres::GetY(int id) const
{
    if(this == 0)
        return 0;
    return m_Y[id];
}

void GroupeMonstres::SetY(int val, int id)
{
    if(val < 0)
        val = 0;
    m_Y[id] = val;
}


int GroupeMonstres::GetExperience() const
{
    int i;
    int exp(0);
    for(i = 0; i < GetNombre(); i++)
        exp += GetMonstres(i)->GetExperience();
    return exp;
}

int GroupeMonstres::GetOr() const
{
    int i;
    int Or(0);
    for(i = 0; i < GetNombre(); i++)
        Or += GetMonstres(i)->GetOr();
    return Or;
}
/*
Script* GroupeMonstres::GetScript() const
{
    if(this == 0)
    {
        return 0;
    }
    return m_Script;
}

void GroupeMonstres::SetScript(Script* val)
{
    if(m_Script)
    {
        delete m_Script;
    }
    m_Script = new Script(*val);
}
*/
