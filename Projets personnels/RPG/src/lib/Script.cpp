#include "lib/Script.h"

Script::Script(int id, PtrFonction fonction, int curseur) {
    SetId(id);
    SetCurseur(curseur);
    SetFonction(fonction);
}

Script::Script(const Script& other) {
    SetId(other.GetId());
    SetCurseur(other.GetCurseur());
    SetFonction(other.GetFonction());
}

Script::~Script() {
}

int Script::GetId() const {
    return m_Id;
}

void Script::SetId(int val) {
    m_Id = val;
}

PtrFonction Script::GetFonction() const {
    return m_Fonction;
}

void Script::SetFonction(PtrFonction val) {
    m_Fonction = val;
}

int Script::GetCurseur() const {
    return m_Curseur;
}

void Script::SetCurseur(int val) {
    m_Curseur = val;
}

void Script::Executer(Partie* partie) {
    if (GetFonction())
        SetCurseur(GetFonction()(partie, GetCurseur()));
}
