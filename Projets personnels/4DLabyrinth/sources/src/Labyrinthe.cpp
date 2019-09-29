#include "Labyrinthe.h"

using namespace std;

Labyrinthe::Labyrinthe(int X, int Y, int Z, int W)
{
    int i;
    SetX(X);
    SetY(Y);
    SetZ(Z);
    SetW(W);
    m_Tableau = new bool[GetTaille()];
    for(i = 0; i < GetTaille(); i++)
    {
        SetTableau(i, TROU);
    }
}

Labyrinthe::~Labyrinthe()
{
    //dtor
}

int Labyrinthe::GetX() const
{
    if(this)
        return m_X;
    return 0;
}

void Labyrinthe::SetX(int val)
{
    if(this)
        m_X = val;
}

int Labyrinthe::GetY() const
{
    if(this)
        return m_Y;
    return 0;
}

void Labyrinthe::SetY(int val)
{
    if(this)
        m_Y = val;
}

int Labyrinthe::GetZ() const
{
    if(this)
        return m_Z;
    return 0;
}

void Labyrinthe::SetZ(int val)
{
    if(this)
        m_Z = val;
}

int Labyrinthe::GetW() const
{
    if(this)
        return m_W;
    return 0;
}

void Labyrinthe::SetW(int val)
{
    if(this)
        m_W = val;
}

int Labyrinthe::GetTaille() const
{
    if(this)
        return GetX()*GetY()*GetZ()*GetW();
    return 0;
}

bool Labyrinthe::GetTableau(int i) const
{
    if(this && m_Tableau && i >= 0 && i < GetTaille())
        return m_Tableau[i];
    return TROU;
}

bool Labyrinthe::GetTableau(int x, int y, int z, int w) const
{
    if(this && m_Tableau && x >= 0 && y >= 0 && z >= 0 && w >= 0\
            && x < GetX() && y < GetY() && z < GetZ() && w < GetW())
        return m_Tableau[Conversion(x,y,z,w)];
    return MUR;
}

bool Labyrinthe::GetTableau(float x, float y, float z, float w) const
{
    return GetTableau((int)x, (int)y, (int)z, (int)w);
}

bool Labyrinthe::GetTableau(gsl_vector* camera, gsl_vector* deplacement) const
{
    return GetTableau((int)(100*gsl_vector_get(deplacement,0)-gsl_vector_get(camera,0)-0.5+0.1),\
                      (int)(100*gsl_vector_get(deplacement,1)-gsl_vector_get(camera,1)-0.5+0.1),\
                      (int)(100*gsl_vector_get(deplacement,2)-gsl_vector_get(camera,2)-0.5+0.1),\
                      (int)(100*gsl_vector_get(deplacement,3)-gsl_vector_get(camera,3)-0.5+0.1));
}

void Labyrinthe::SetTableau(int i, bool val)
{
    if(this && m_Tableau && i >= 0 && i < GetTaille())
        m_Tableau[i] = val;
}

void Labyrinthe::SetTableau(int x, int y, int z, int w, bool val)
{
    if(this && m_Tableau && x >= 0 && y >= 0 && z >= 0 && w >= 0\
            && x < GetX() && y < GetY() && z < GetZ() && w < GetW())
        m_Tableau[Conversion(x,y,z,w)] = val;
}

int Labyrinthe::GetNombreMurs() const
{
    int i,nombre(0);
    for(i = 0; i < GetTaille(); i++)
    {
        nombre += (int)GetTableau(i);
    }
    return nombre;
}

int Labyrinthe::Conversion(int x, int y, int z, int w) const
{
    return x+(y+(z+w*GetZ())*GetY())*GetX();
}

int Labyrinthe::Conversion2(int i, int &x, int &y, int &z, int &w) const
{
    x = i % GetX();
    i = (i-x) / GetX();
    y = i % GetY();
    i = (i-y) / GetY();
    z = i % GetZ();
    i = (i-z) / GetZ();
    w = i % GetW();
    return 0;
}
