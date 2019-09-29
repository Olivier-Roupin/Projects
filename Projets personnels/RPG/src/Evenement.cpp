#include "Evenement.h"

using namespace std;

Evenement::Evenement(int id, int X, int Y, int Z, int Nombre, Script** Scripts, string Image)
{
    Setid(id);
    SetX(X);
    SetY(Y);
    SetZ(Z);
    SetNombre(Nombre);
    m_Scripts = new Script*[sizeof(Script*)*GetNombre()];
    if(Scripts)
    {
        *m_Scripts = *Scripts;
    }
    else
    {
        int i;
        for (i = 0; i < GetNombre(); i++)
        {
            m_Scripts[i] = 0;
        }
    }
    SetImage(Image);
}

Evenement::Evenement(int id, int Nombre, string Image, int X, int Y, int Z)
{
    Setid(id);
    SetX(X);
    SetY(Y);
    SetZ(Z);
    SetNombre(Nombre);
    m_Scripts = new Script*[sizeof(Script*)*GetNombre()];
    int i;
    for(i = 0; i < GetNombre(); i++)
    {
        m_Scripts[i] = 0;
    }
    SetImage(Image);
}

Evenement::~Evenement()
{
    //dtor
}

int Evenement::Getid() const
{
    if(this == 0)
        return 0;
    return m_id;
}

void Evenement::Setid(int val)
{
    m_id = val;
}

int Evenement::GetX() const
{
    if(this == 0)
        return 0;
    return m_X;
}

void Evenement::SetX(int val)
{
    m_X = val;
}

void Evenement::ChangerX(int val)
{
    SetX(GetX()+val);
}

int Evenement::GetY() const
{
    if(this == 0)
        return 0;
    return m_Y;
}

void Evenement::SetY(int val)
{
    m_Y = val;
}

void Evenement::ChangerY(int val)
{
    SetY(GetY()+val);
}

int Evenement::GetZ() const
{
    if(this == 0)
        return 0;
    return m_Z;
}

void Evenement::SetZ(int val)
{
    if(val >= Z_BAS && val <= Z_HAUT)
    {
        m_Z = val;
    }
}

int Evenement::GetNombre() const
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void Evenement::SetNombre(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Nombre = val;
}

Script* Evenement::GetScripts(int id) const
{
    if(this == 0)
        return 0;
    if(id < 0 || id >= GetNombre())
    {
        return 0;
    }
    return m_Scripts[id];
}

void Evenement::SetScripts(Script* val, int id)
{
    m_Scripts[id] = val;
}

string Evenement::GetImage() const
{
    if(this == 0)
        return "_";
    return m_Image;
}

void Evenement::SetImage(string val)
{
    m_Image = val;
}
