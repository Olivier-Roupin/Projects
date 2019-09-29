#include "Utilisable.h"

using namespace std;

Utilisable::Utilisable(int Id, string Nom, int Type, int Prix, string Description,\
                       bool Illimite, Effet* effet) : Objet(Id, Nom, Type, Prix, Description)
{
    SetIllimite(Illimite);
    SetEffet(effet);
}

Utilisable::~Utilisable()
{
    //dtor
}

bool Utilisable::GetIllimite() const
{
    if(this == 0)
        return false;
    return m_Illimite;
}

void Utilisable::SetIllimite(bool val)
{
    m_Illimite = val;
}

Effet* Utilisable::GetEffet() const
{
    if(this == 0)
        return 0;
    return m_Effet;
}

void Utilisable::SetEffet(Effet* val)
{
    m_Effet = val;
}
