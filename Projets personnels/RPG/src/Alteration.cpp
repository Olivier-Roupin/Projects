#include "Alteration.h"

using namespace std;

Alteration::Alteration(int id, string nom, Script* script, bool postCombat, bool postDeces, int priorite)
{
    SetId(id);
    SetNom(nom);
    SetScript(script);
    SetPostCombat(postCombat);
    SetPostDeces(postDeces);
    SetPriorite(priorite);
}

Alteration::Alteration(const Alteration& cible)
{
    SetId(cible.GetId());
    SetNom(cible.GetNom());
    SetPostCombat(cible.GetPostCombat());
    SetPostDeces(cible.GetPostDeces());
    SetPriorite(cible.GetPriorite());
    Script* script = new Script(*(cible.GetScript()));
    SetScript(script);
}

Alteration::~Alteration()
{
    //dtor
}

int Alteration::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Alteration::SetId(int val)
{
    m_Id = val;
}

string Alteration::GetNom() const
{
    if(this == 0)
        return "_";
    return m_Nom;
}

void Alteration::SetNom(string val)
{
    m_Nom = val;
}

Script* Alteration::GetScript() const
{
    if(this == 0)
        return 0;
    return m_Script;
}

void Alteration::SetScript(Script* val)
{
    m_Script = val;
}

bool Alteration::GetPostCombat() const
{
    if(this == 0)
        return false;
    return m_PostCombat;
}

void Alteration::SetPostCombat(bool val)
{
    m_PostCombat = val;
}

bool Alteration::GetPostDeces() const
{
    if(this == 0)
        return false;
    return m_PostDeces;
}

void Alteration::SetPostDeces(bool val)
{
    m_PostDeces = val;
}


int Alteration::GetPriorite() const
{
    if(this == 0)
        return 0;
    return m_Priorite;
}

void Alteration::SetPriorite(int val)
{
    m_Priorite = val;
}
