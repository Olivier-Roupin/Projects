#include "Equipe.h"

Equipe::Equipe()
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        m_Heros[i] = 0;
    }
}

Equipe::~Equipe()
{
    /*
    for(int i = 0; i < MAX_HEROS_EQUIPE; ++i)
    {
        delete m_Heros[i];
    }
    */
}

Heros** Equipe::GetHeros() const
{
    if(this == 0)
    {
        return 0;
    }
    return (Heros**)m_Heros;
}

Heros* Equipe::GetHeros(unsigned int id) const
{
    if(this == 0)
    {
        return 0;
    }
    return m_Heros[id];
}

void Equipe::SetHeros(Heros* val, unsigned int id)
{
    m_Heros[id] = val;
}

unsigned int Equipe::ChercherHeros(Heros *val) const
{
    int i(0);
    while(i < MAX_HEROS_EQUIPE && GetHeros(i) != val)
    {
        i++;
    }
    if(i >= MAX_HEROS_EQUIPE)
    {
        return -1;
    }
    return i;
}

unsigned int Equipe::ChercherLibre() const
{
    return ChercherHeros();
}

unsigned int Equipe::AjouterHeros(Heros *val)
{
    int i(ChercherLibre());
    if(i != -1)
    {
        SetHeros(val, i);
        return 0;
    }
    return -1;
}

unsigned int Equipe::RetirerHeros(Heros *val)
{
    int i(ChercherHeros(val));
    if(i != -1)
    {
        SetHeros(0, i);
        return 0;
    }
    return -1;
}
