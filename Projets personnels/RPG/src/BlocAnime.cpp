#include "BlocAnime.h"

BlocAnime::BlocAnime(int Nombre_Blocs, int* Blocs, int Vitesse, int Nombre, int* Sequence)
{
    SetVitesse(Vitesse);
    SetNombre(Nombre);
    m_Blocs = new BlocGraphique*[sizeof(BlocGraphique*)*Nombre_Blocs];
    for(int i(0); i < Nombre_Blocs; i++)
    {
        SetBlocs(blocs_graphiques[Blocs[i]], i);
    }
    SetSequence(Sequence);
}

BlocAnime::~BlocAnime()
{
    //dtor
}

BlocGraphique* BlocAnime::GetBlocs(int id) const
{
    return m_Blocs[id];
}

void BlocAnime::SetBlocs(BlocGraphique* val, int id)
{
    m_Blocs[id] = val;
}

int BlocAnime::GetVitesse() const
{
    return m_Vitesse;
}

void BlocAnime::SetVitesse(int val)
{
    m_Vitesse = val;
}

int BlocAnime::GetNombre() const
{
    return m_Nombre;
}

void BlocAnime::SetNombre(int val)
{
    m_Nombre = val;
}

int* BlocAnime::GetSequence() const
{
    return m_Sequence;
}

void BlocAnime::SetSequence(int* val)
{
    m_Sequence = val;
}
