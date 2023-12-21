#include "lib/Equipe.h"

Equipe::Equipe() {
    unsigned char i;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        m_Heros[i] = 0;
}

Equipe::~Equipe() {
    /*
    for (int i = 0; i < MAX_HEROS_EQUIPE; ++i)
        delete m_Heros[i];
    */
}

/*Heros** Equipe::GetHeros() const {
    return (Heros**)m_Heros;
}*/

Heros* Equipe::GetHeros(unsigned char id) const {
    if (id >= MAX_HEROS_EQUIPE)
        return 0;
    return m_Heros[id];
}

void Equipe::SetHeros(Heros* val, unsigned char id) {
    m_Heros[id] = val;
}

unsigned char Equipe::ChercherHeros(Heros *val) const {
    unsigned char i = 0;
    // while (i < MAX_HEROS_EQUIPE && GetHeros(i) != val)
    while (i < MAX_HEROS_EQUIPE && m_Heros[i] != val)
        ++i;
    // if (i >= MAX_HEROS_EQUIPE)
    //     // return -1;
    //     return MAX_HEROS_EQUIPE;
    return i;
}

unsigned char Equipe::ChercherLibre() const {
    return ChercherHeros();
}

bool Equipe::AjouterHeros(Heros *val) {
    unsigned char i = ChercherLibre();
    // if (i != -1) {
    if (i != MAX_HEROS_EQUIPE) {
        SetHeros(val, i);
        return true;
    }
    return false;
}

bool Equipe::RetirerHeros(Heros *val) {
    unsigned char i = ChercherHeros(val);
    // if (i != -1) {
    if (i != MAX_HEROS_EQUIPE) {
        SetHeros(0, i);
        return true;
    }
    return false;
}

void Equipe::EchangerHeros(unsigned char id1, unsigned char id2) {
    Heros* copie = m_Heros[id1];
    m_Heros[id1] = m_Heros[id2];
    m_Heros[id2] = copie;
}

unsigned char Equipe::GetNombreEnVie() const {
    unsigned char n = 0, i;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        // if (GetHeros(i) && GetHeros(i)->estEnVie())
        if (m_Heros[i] && m_Heros[i]->estEnVie())
            ++n;
    return n;
}

unsigned char Equipe::GetNombreObjets(const Objet* val) const {
    unsigned char n = 0, i;
    switch (val->GetType()) {
    case EQUIPABLE_ACCESSOIRE:
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i) {
            // if (GetHeros(i)) {
            if (m_Heros[i]) {
                // if (GetHeros(i)->GetEquipement(EQUIPEMENT_ACCESSOIRE1) == val)
                if (m_Heros[i]->GetEquipement(EQUIPEMENT_ACCESSOIRE1) == val)
                    ++n;
                // if (GetHeros(i)->GetEquipement(EQUIPEMENT_ACCESSOIRE2) == val)
                if (m_Heros[i]->GetEquipement(EQUIPEMENT_ACCESSOIRE2) == val)
                    ++n;
            }
        }
        return n;
    case EQUIPABLE_ARME:
    case EQUIPABLE_BOUCLIER:
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i) {
            // if (GetHeros(i)) {
            if (m_Heros[i]) {
                // if (GetHeros(i)->GetEquipement(EQUIPEMENT_MAINGAUCHE) == val)
                if (m_Heros[i]->GetEquipement(EQUIPEMENT_MAINGAUCHE) == val)
                    ++n;
                // if (GetHeros(i)->GetEquipement(EQUIPEMENT_MAINDROITE) == val)
                if (m_Heros[i]->GetEquipement(EQUIPEMENT_MAINDROITE) == val)
                    ++n;
            }
        }
        return n;
    case EQUIPABLE_ARMURE:
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
            // if (GetHeros(i)
            //  && GetHeros(i)->GetEquipement(EQUIPEMENT_CORPS) == val)
            if (m_Heros[i] && m_Heros[i]->GetEquipement(EQUIPEMENT_CORPS)==val)
                ++n;
        return n;
    case EQUIPABLE_CASQUE:
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
            // if (GetHeros(i)
            //  && GetHeros(i)->GetEquipement(EQUIPEMENT_TETE) == val)
            if (m_Heros[i] && m_Heros[i]->GetEquipement(EQUIPEMENT_TETE)==val)
                ++n;
        return n;
    case OBJET:
    case UTILISABLE:
    case EQUIPABLE:
    default:
        return 0;
    }
}