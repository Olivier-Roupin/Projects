#include "GroupeCapacites.h"

GroupeCapacites::GroupeCapacites()
{
    for (int i = 0; i < MAX_CAPACITES; ++i)
    {
        m_Capacites[i] = 0;
    }
}

GroupeCapacites::~GroupeCapacites()
{

}

Capacite* GroupeCapacites::GetCapacites(unsigned int id) const
{
    if (this == 0)
    {
        return 0;
    }
    return m_Capacites[id];
}

void GroupeCapacites::SetCapacites(Capacite* val, unsigned int id)
{
    delete m_Capacites[id];
    m_Capacites[id] = val;
}

unsigned int GroupeCapacites::ChercherCapacite(Capacite *val) const
{
    int i(0);
    while (i < MAX_CAPACITES && GetCapacites(i) != val)
    {
        i++;
    }
    if (i >= MAX_CAPACITES)
    {
        return -1;
    }
    return i;
}

unsigned int GroupeCapacites::ChercherLibre() const
{
    return ChercherCapacite();
}

unsigned int GroupeCapacites::AjouterCapacites(Capacite *val)
{
    int i(ChercherCapacite(val));
    if (i == -1)
    {
        i = ChercherLibre();
        if (i != -1)
        {
            SetCapacites(val, i);
            return 0;
        }
    }
    return -1;
}

unsigned int GroupeCapacites::RetirerCapacites(Capacite *val)
{
    int i(ChercherCapacite(val));
    if (i != -1)
    {
        SetCapacites(0, i);
        return 0;
    }
    return -1;
}
