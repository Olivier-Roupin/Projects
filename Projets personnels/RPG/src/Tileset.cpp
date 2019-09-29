#include "Tileset.h"

using namespace std;

Tileset::Tileset(int id, int nombre, int* traversable, string* image) : m_Id(id), m_Nombre(nombre)
{
    int i;
    m_Traversable = new int[sizeof(int)*GetNombre()];
    if(traversable)
    {
        *m_Traversable = *traversable;
    }
    else
    {
        for(i = 0; i < GetNombre(); i++)
            SetTraversable(0, i);
    }
    m_Image = new string[sizeof(string)*GetNombre()];
    if(image)
    {
        *m_Image = *image;
    }
    else
    {
        for(i = 0; i < GetNombre(); i++)
            SetImage("_", i);
    }
}

Tileset::~Tileset()
{
    //dtor
}

int Tileset::GetId()
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Tileset::SetId(int val)
{
    m_Id = val;
}

int Tileset::GetNombre()
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void Tileset::SetNombre(int val)
{
    m_Nombre = val;
}

int Tileset::GetTraversable(int id) const
{
    if(this == 0)
        return 0;
    return m_Traversable[id];
}

void Tileset::SetTraversable(int val, int id)
{
    m_Traversable[id] = val;
}

string Tileset::GetImage(int id) const
{
    if(this == 0)
        return 0;
    return m_Image[id];
}

void Tileset::SetImage(string val, int id)
{
    m_Image[id] = val;
}
