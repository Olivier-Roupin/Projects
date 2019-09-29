#include "Script.h"

using namespace std;

Script::Script(PtrFonction fonction, int curseur)
{
    SetCurseur(curseur);
    SetFonction(fonction);
}

Script::Script(const Script& other)
{
    SetCurseur(other.GetCurseur());
    SetFonction(other.GetFonction());
}

Script::~Script()
{
    //dtor
}

PtrFonction Script::GetFonction() const
{
    if(this == 0)
        return 0;
    return m_Fonction;
}

void Script::SetFonction(PtrFonction val)
{
    m_Fonction = val;
}

int Script::GetCurseur() const
{
    if(this == 0)
        return 0;
    return m_Curseur;
}

void Script::SetCurseur(int val)
{
    m_Curseur = val;
}

void Script::Executer(Partie* partie)
{
    if(this)
        SetCurseur(GetFonction()(partie, GetCurseur()));
}
