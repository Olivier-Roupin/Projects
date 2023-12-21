#include "lib/Inventaire.h"

Inventaire::Inventaire() {
    unsigned char i;
    for (i = 0; i < MAX_OBJETS; ++i)
        m_Objets[i] = 0;
}

Inventaire::~Inventaire() {
    unsigned char i;
    for (i = 0; i < MAX_OBJETS; ++i)
        delete m_Objets[i];
}

GroupeObjets* Inventaire::GetObjets(unsigned char id) const {
    // if (id < 0 || id >= MAX_OBJETS)
    if (id >= MAX_OBJETS)
        return 0;
    return m_Objets[id];
}

void Inventaire::SetObjets(GroupeObjets* val, unsigned char id) {
    delete m_Objets[id];
    if (val)
        m_Objets[id] = new GroupeObjets(*val);
    else
        m_Objets[id] = 0;
}

void Inventaire::SetObjets(Objet* val, unsigned char nombre, unsigned char id) {
    delete m_Objets[id];
    if (val)
        m_Objets[id] = new GroupeObjets(val, nombre);
    else
        m_Objets[id] = 0;
}

unsigned char Inventaire::ChercherObjet(const Objet* val) const {
    unsigned char i = 0;
    while (i < MAX_OBJETS && GetObjet(i) != val)
        ++i;
    // if (i >= MAX_OBJETS)
        // return -1;
        // return MAX_OBJETS;
    return i; // == MAX_OBJETS si non trouvé
}

unsigned char Inventaire::ChercherObjet(GroupeObjets* val) const {
    if (val == 0)
        return ChercherObjet((Objet*)0);
    return ChercherObjet(val->GetObjet());
}

unsigned char Inventaire::ChercherLibre() const {
    return ChercherObjet();
}

bool Inventaire::AjouterObjets(GroupeObjets* val) {
    unsigned char i = ChercherObjet(val);
    // if (i != -1 && m_Objets[i]) //double sécurité
    if (i != MAX_OBJETS && m_Objets[i]) //double sécurité
        m_Objets[i]->ChangerNombre(val->GetNombre());
    else {
        i = ChercherLibre();
        // if (i != -1)
        if (i != MAX_OBJETS)
            SetObjets(val, i);
        else
            return false;
    }
    return true;
}

bool Inventaire::AjouterObjets(Objet* val, unsigned char nombre) {
    if (val) {
        /*GroupeObjets *cible;
        cible = new GroupeObjets(val, nombre);
        return AjouterObjets(cible);*/
        GroupeObjets cible(val, nombre);
        return AjouterObjets(&cible);
    }
    return false;
}

bool Inventaire::RetirerObjets(GroupeObjets* val) {
    unsigned char i = ChercherObjet(val);
    // if (i != -1 && m_Objets[i]) { //double sécurité
    if (i != MAX_OBJETS && m_Objets[i]) { //double sécurité
        m_Objets[i]->ChangerNombre(-val->GetNombre());
        if (GetNombre(i) == 0)
            SetObjets(0, i);
        return true;
    }
    return false;
}

bool Inventaire::RetirerObjets(Objet* val, unsigned char nombre) {
    if (val) {
        /*GroupeObjets *cible;
        cible = new GroupeObjets(val, nombre);
        return RetirerObjets(cible);*/
        GroupeObjets cible(val, nombre);
        return RetirerObjets(&cible);
    }
    return false;
}

void Inventaire::EchangerObjets(unsigned char id1, unsigned char id2) {
    GroupeObjets* copie = m_Objets[id1];
    m_Objets[id1] = m_Objets[id2];
    m_Objets[id2] = copie;
}

unsigned char Inventaire::GetNombre(const Objet* val) const {
    unsigned char i = ChercherObjet(val);
    // if (i != -1)
    if (i != MAX_OBJETS)
        return GetNombre(i);
    return 0;
}

//Pour les menus
unsigned char Inventaire::GetType(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    // return GetObjets(id)->GetType();
    return m_Objets[id]->GetType();
}

//Pour l'affichage
const char* Inventaire::GetNom(unsigned char id) const {
    if (GetObjets(id) == 0)
        return "_";
    return m_Objets[id]->GetNom();
}

unsigned int Inventaire::GetPrix(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    return m_Objets[id]->GetPrix();
}

unsigned char Inventaire::GetNombre(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    return m_Objets[id]->GetNombre();
}

Objet* Inventaire::GetObjet(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    return m_Objets[id]->GetObjet();
}

//Pour la sauvegarde
int Inventaire::GetId(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    return m_Objets[id]->GetId();
}
