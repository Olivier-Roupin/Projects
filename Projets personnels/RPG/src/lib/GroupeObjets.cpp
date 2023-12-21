#include "lib/GroupeObjets.h"

#define MAX_OBJETS_GROUPE 99

GroupeObjets::GroupeObjets(Objet *objet, unsigned char nombre) {
    SetObjet(objet);
    SetNombre(nombre);
}

GroupeObjets::GroupeObjets(GroupeObjets const& copie) {
    SetObjet(copie.GetObjet());
    SetNombre(copie.GetNombre());
}

GroupeObjets::~GroupeObjets() {
}

Objet* GroupeObjets::GetObjet() const {
    return m_Objet;
}

void GroupeObjets::SetObjet(Objet *val) {
    m_Objet = val;
}

unsigned char GroupeObjets::GetNombre() const {
    return m_Nombre;
}

void GroupeObjets::SetNombre(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    // else if (val > MAX_OBJETS_GROUPE)
    if (val > MAX_OBJETS_GROUPE)
        val = MAX_OBJETS_GROUPE;
    m_Nombre = val;
}

void GroupeObjets::ChangerNombre(char val) {
    SetNombre(GetNombre() + val);
}

unsigned int GroupeObjets::GetPrix() const {
    // if (GetObjet() == 0)
    if (m_Objet == 0)
        return 0;
    // return GetObjet()->GetPrix();
    return m_Objet->GetPrix();
}

const char* GroupeObjets::GetNom() const {
    // if (GetObjet() == 0)
    if (m_Objet == 0)
        return "_";
    // return GetObjet()->GetNom();
    return m_Objet->GetNom();
}

int GroupeObjets::GetId() const {
    // if (GetObjet() == 0)
    if (m_Objet == 0)
        return 0;
    // return GetObjet()->GetId();
    return m_Objet->GetId();
}

unsigned char GroupeObjets::GetType() const {
    // if (GetObjet() == 0)
    if (m_Objet == 0)
        return 0;
    // return GetObjet()->GetType();
    return m_Objet->GetType();
}
