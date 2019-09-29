#include "Monstre.h"

using namespace std;

Monstre::Monstre(int Id, string Nom, int Vie, int Magie,\
                 int VieMax, int AttaqueP, int DefenseP,\
                 int MagieMax, int AttaqueM, int DefenseM,\
                 int Vitesse, int Precision, int Esquive,\
                 int Statut, int Experience, int Niveau, int Jauge,\
                 GroupeObjets* Butin, GroupeObjets* Objetporte, int Or):\
    Personnage(Id,Nom,Vie,Magie,VieMax,AttaqueP,DefenseP,MagieMax,AttaqueM,DefenseM,\
               Vitesse,Precision,Esquive,Statut,Experience,Niveau,Jauge)
{
    SetButin(Butin);
    SetObjetPorte(Objetporte);
    SetOr(Or);
    m_Script = 0;
    SetX(0);
    SetY(0);
}

Monstre::Monstre(int Id, string Nom, int Vie, int Magie,\
                 int VieMax, int AttaqueP, int DefenseP,\
                 int MagieMax, int AttaqueM, int DefenseM,\
                 int Vitesse, int Precision, int Esquive,\
                 int Experience, int Niveau,\
                 GroupeObjets* Butin, GroupeObjets* Objetporte, int Or, int Statut, int Jauge):\
    Personnage(Id,Nom,Vie,Magie,VieMax,AttaqueP,DefenseP,MagieMax,AttaqueM,DefenseM,\
               Vitesse,Precision,Esquive,Statut,Experience,Niveau,Jauge)
{
    SetButin(Butin);
    SetObjetPorte(Objetporte);
    SetOr(Or);
    m_Script = 0;
    SetX(0);
    SetY(0);
}

Monstre::Monstre(const Monstre& cible) : Personnage(cible)
{
    SetOr(cible.GetOr());
    m_Butin = 0;
    m_ObjetPorte = 0;
    m_Script = 0;
    if(cible.GetButin())
    {
        m_Butin = new GroupeObjets(*(cible.GetButin()));
    }
    if(cible.GetObjetPorte())
    {
        m_ObjetPorte = new GroupeObjets(*(cible.GetObjetPorte()));
    }
    if(cible.GetScript())
    {
        m_Script = new Script(*(cible.GetScript()));
    }
    SetX(cible.GetX());
    SetY(cible.GetY());
}

Monstre::~Monstre()
{
    //dtor
}

GroupeObjets* Monstre::GetButin() const
{
    if(this == 0)
        return 0;
    return m_Butin;
}

void Monstre::SetButin(GroupeObjets* val)
{
    m_Butin = val;
}

GroupeObjets* Monstre::GetObjetPorte() const
{
    if(this == 0)
        return 0;
    return m_ObjetPorte;
}

void Monstre::SetObjetPorte(GroupeObjets* val)
{
    m_ObjetPorte = val;
}

int Monstre::GetOr() const
{
    if(this == 0)
        return 0;
    return m_Or;
}

void Monstre::SetOr(int val)
{
    if(val < 0)
        m_Or = 0;
    else
        m_Or = val;
}

Script* Monstre::GetScript() const
{
    if(this == 0)
        return 0;
    return m_Script;
}

void Monstre::SetScript(Script* val)
{
    if(m_Script)
        delete m_Script;
    m_Script = new Script(*val);
}

int Monstre::GetX() const
{
    if(this == 0)
        return 0;
    return m_X;
}

void Monstre::SetX(int val)
{
    if(val < 0)
        m_X = 0;
    else
        m_X = val;
}

int Monstre::GetY() const
{
    if(this == 0)
        return 0;
    return m_Y;
}

void Monstre::SetY(int val)
{
    if(val < 0)
        m_Y = 0;
    else
        m_Y = val;
}
