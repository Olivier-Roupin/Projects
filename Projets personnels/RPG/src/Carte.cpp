#include "Carte.h"

using namespace std;

Rencontreset::Rencontreset(int nombre)
{
    int i;
    SetNombre(nombre);
    if(GetNombre())
    {
        m_Groupes = new GroupeMonstres**[sizeof(GroupeMonstres**)*(GetNombre()+1)];
        m_NombreGroupes = new int[sizeof(int)*(GetNombre()+1)];
        for(i = 0; i < GetNombre()+1; i++)
        {
            m_Groupes[i] = 0;
            SetNombreGroupes(0,i);
        }
    }
    else
    {
        m_NombreGroupes = 0;
        m_Groupes = 0;
    }
}

Rencontreset::~Rencontreset()
{

}

int Rencontreset::GetNombre() const
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void Rencontreset::SetNombre(int val)
{
    if(val < 0)
        val = 0;
    m_Nombre = val;
}

int Rencontreset::GetNombreGroupes(int id) const
{
    if(this == 0)
        return 0;
    return m_NombreGroupes[id];
}

void Rencontreset::SetNombreGroupes(int val, int id)
{
    if(val < 0)
        val = 0;
    if(m_Groupes[id])
        delete m_Groupes[id];
    m_NombreGroupes[id] = val;
    m_Groupes[id] = new GroupeMonstres*[sizeof(GroupeMonstres*)*GetNombreGroupes(id)];
}

GroupeMonstres* Rencontreset::GetGroupes(int i, int j) const
{
    if(this == 0)
        return 0;
    return m_Groupes[i][j];
}

void Rencontreset::SetGroupes(GroupeMonstres* val, int i, int j)
{
    if(val == 0)
        m_Groupes[i][j] = 0;
    m_Groupes[i][j] = val;
}

Carte::Carte(int id, string nom, int largeur, int hauteur, bool repetition, Tileset* tileset, int* bas, int* moyen, int* haut, int Nombre, Evenement** Evenements, Rencontreset* rencontreset)
{
    int i;
    SetId(id);
    SetNom(nom);
    SetLargeur(largeur);
    SetHauteur(hauteur);
    SetRepetition(repetition);
    SetTileset(tileset);
    SetRencontreset(rencontreset);
    m_Bas = new int[sizeof(int)*GetTaille()];
    if(bas)
    {
        *m_Bas = *bas;
    }
    else
    {
        for(i = 0; i < GetTaille(); i++)
            SetBas(0, i);
    }
    m_Moyen = new int[sizeof(int)*GetTaille()];
    if(moyen)
    {
        *m_Moyen = *moyen;
    }
    else
    {
        for(i = 0; i < GetTaille(); i++)
            SetMoyen(0, i);
    }
    m_Haut = new int[sizeof(int)*GetTaille()];
    if(haut)
    {
        *m_Haut = *haut;
    }
    else
    {
        for(i = 0; i < GetTaille(); i++)
            SetHaut(0, i);
    }
    SetNombre(Nombre);
    m_Evenements = new Evenement*[sizeof(Evenement*)*GetNombre()];
    if(Evenements)
    {
        *m_Evenements = *Evenements;
    }
    else
    {
        for(i = 0; i < GetNombre(); i++)
            m_Evenements[i] = 0;
    }
}

Carte::Carte(int Id, string Nom, int Largeur, int Hauteur, bool Repetition, Tileset* tileset, int Nombre, Rencontreset* rencontreset, string fond)
{
    int i;
    SetId(Id);
    SetNom(Nom);
    SetLargeur(Largeur);
    SetHauteur(Hauteur);
    SetRepetition(Repetition);
    SetTileset(tileset);
    SetRencontreset(rencontreset);
    SetFond(fond);
    m_Bas = new int[sizeof(int)*GetTaille()];
    for(i = 0; i < GetTaille(); i++)
        SetBas(0, i);
    m_Moyen = new int[sizeof(int)*GetTaille()];
    for(i = 0; i < GetTaille(); i++)
        SetMoyen(0, i);
    m_Haut = new int[sizeof(int)*GetTaille()];
    for(i = 0; i < GetTaille(); i++)
        SetHaut(0, i);
    if(rencontreset)
    {
        m_Rencontres = new int[sizeof(int)*GetTaille()];
        for(i = 0; i < GetTaille(); i++)
            SetRencontres(0, i);
    }
    else
    {
        m_Rencontres = 0;
    }
    SetNombre(Nombre);
    m_Evenements = new Evenement*[sizeof(Evenement*)*GetNombre()];
    for(i = 0; i < GetNombre(); i++)
        m_Evenements[i] = 0;
}

Carte::~Carte()
{
    //dtor
}

int Carte::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Carte::SetId(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Id = val;
}

string Carte::GetNom() const
{
    if(this == 0)
        return "_";
    return m_Nom;
}

void Carte::SetNom(string val)
{
    if(val == "")
    {
        val = "_";
    }
    m_Nom = val;
}

int Carte::GetLargeur() const
{
    if(this == 0)
        return 0;
    return m_Largeur;
}

void Carte::SetLargeur(int val)
{
    if(val < 1)
    {
        val = 1;
    }
    m_Largeur = val;
}

int Carte::GetHauteur() const
{
    if(this == 0)
        return 0;
    return m_Hauteur;
}

void Carte::SetHauteur(int val)
{
    if(val < 1)
    {
        val = 1;
    }
    m_Hauteur = val;
}

bool Carte::GetRepetition() const
{
    if(this == 0)
        return 0;
    return m_Repetition;
}

void Carte::SetRepetition(bool val)
{
    m_Repetition = val;
}

int Carte::GetBas(int i, int j) const
{
    if(this == 0)
        return 0;
    return m_Bas[i+GetLargeur()*j];
}

void Carte::SetBas(int val, int i, int j)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Bas[i+GetLargeur()*j] = val;
}

int Carte::GetMoyen(int i, int j) const
{
    if(this == 0)
        return 0;
    return m_Moyen[i+GetLargeur()*j];
}

void Carte::SetMoyen(int val, int i, int j)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Moyen[i+GetLargeur()*j] = val;
}

int Carte::GetHaut(int i, int j) const
{
    if(this == 0)
        return 0;
    return m_Haut[i+GetLargeur()*j];
}

void Carte::SetHaut(int val, int i, int j)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Haut[i+GetLargeur()*j] = val;
}

int Carte::GetRencontres(int i, int j) const
{
    if(this == 0 || m_Rencontres == 0)
        return 0;
    return m_Rencontres[i+GetLargeur()*j];
}

void Carte::SetRencontres(int val, int i, int j)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Rencontres[i+GetLargeur()*j] = val;
}

Tileset* Carte::GetTileset() const
{
    if(this == 0)
        return 0;
    return m_Tileset;
}

void Carte::SetTileset(Tileset* val)
{
    m_Tileset = val;
}

int Carte::GetTaille() const
{
    if(this == 0)
        return 0;
    return GetHauteur()*GetLargeur();
}

int Carte::GetNombre() const
{
    if(this == 0)
        return 0;
    return m_Nombre;
}

void Carte::SetNombre(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Nombre = val;
}

Evenement* Carte::GetEvenements(int id) const
{
    if(this == 0)
        return 0;
    if(id < 0)
    {
        return 0;
    }
    return m_Evenements[id];
}

void Carte::SetEvenements(Evenement* val, int id)
{
    m_Evenements[id] = val;
}

Rencontreset* Carte::GetRencontreset() const
{
    if(this == 0)
        return 0;
    return m_Rencontreset;
}

void Carte::SetRencontreset(Rencontreset* val)
{
    m_Rencontreset = val;
}

/*int Carte::GetNombreFonds() const
{
    if(this == 0)
        return 0;
    return m_NombreFonds;
}

void Carte::SetNombreFonds(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_NombreFonds = val;
}

string Carte::GetFonds(int id) const
{
    if(this == 0)
        return 0;
    if(id < 0)
    {
        return 0;
    }
    return m_Fonds[id];
}

void Carte::SetFonds(string val, int id)
{
    m_Fonds[id] = val;
}*/

string Carte::GetFond() const
{
    if(this == 0)
        return "_";
    return m_Fond;
}

void Carte::SetFond(string val)
{
    m_Fond = val;
}
