#include "lib/Objet.h"

Objet::Objet(int Id, const char* Nom, unsigned char Type, unsigned int Prix,
             const char* Description) {
     SetId(Id);
     SetNom(Nom);
     SetType(Type);
     SetPrix(Prix);
     SetDescription(Description);
}

Objet::Objet(const Objet& cible) {
    SetNom(cible.GetNom());
    SetPrix(cible.GetPrix());
    SetDescription(cible.GetDescription());
}

Objet::~Objet() {
}

int Objet::GetId() const {
    return m_Id;
}

void Objet::SetId(int val) {
    if (val < 0)
        val = 0;
    m_Id = val;
}

unsigned char Objet::GetType() const {
    return m_Type;
}

void Objet::SetType(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    m_Type = val;
}

bool Objet::EstEquipable() const {
    return false;
}

unsigned int Objet::GetPrix() const {
    return m_Prix;
}

void Objet::SetPrix(unsigned int val) {
    // if (val < 0)
    //     val = 0;
    m_Prix = val;
}

const char* Objet::GetNom() const {
    return m_Nom;
}

void Objet::SetNom(const char* val) {
    for (int i = 0; i < TAILLE_NOM_OBJET; i++) {
        m_Nom[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Nom[TAILLE_NOM_OBJET] = '\0';
}

const char* Objet::GetDescription() const {
    return m_Description;
}

void Objet::SetDescription(const char* val) {
    for (int i = 0; i < TAILLE_DESCRIPTION_OBJET; i++) {
        m_Description[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Description[TAILLE_DESCRIPTION_OBJET] = '\0';
}

int Objet::Ecrire(char* data) const {
    int i = 0, j;
    // ECRIRE_2CHIFFRES(i,data,GetType());
    ECRIRE_2CHIFFRES(i,data,m_Type);
    data[i++] = ' ';
    ECRIRE_CHAINE(i,j,data,m_Nom,TAILLE_NOM_OBJET);
    data[i++] = ' ';

    // ECRIRE_3CHIFFRES(i,data,GetPrix());
    ECRIRE_3CHIFFRES(i,data,m_Prix);
    data[i++] = ' ';

    ECRIRE_CHAINE(i,j,data,m_Description,TAILLE_DESCRIPTION_OBJET);
    data[i++] = '\0';
    return i;
}

void Objet::Lire(int& i, const char* data) {
    int j = 0;
    char nom[TAILLE_NOM_OBJET+1];
    LIRE_CHAINE(i,j,data,nom,TAILLE_NOM_OBJET); SetNom(nom);
    j = 0;
    int entier;
    LIRE_ENTIER(i,data,entier); SetPrix(entier);
    char des[TAILLE_DESCRIPTION_OBJET+1];
    LIRE_CHAINE(i,j,data,des,TAILLE_DESCRIPTION_OBJET); SetDescription(des);
}

unsigned int Objet::TailleD() const {
    unsigned int i, taille = 0;
    for (i = 0; i < TAILLE_NOM_OBJET; ++i)
        if (m_Nom[i] == '\0')
            break;
    taille += i;
    for (i = 0; i < TAILLE_DESCRIPTION_OBJET; ++i)
        if (m_Description[i] == '\0')
            break;
    taille += i;
    return taille+1;
}

char* Objet::EcrireD(char* data) const {
    unsigned int i = 0;
    data[i] = m_Type;
    unsigned int j;
    for (j = 0; j < TAILLE_NOM_OBJET; ++j) {
        data[++i] = m_Nom[j]; //0 est écrit s'il est présent
        if (m_Nom[j] == '\0')
            break;
    }
    // if (i == TAILLE_NOM_OBJET) --i;
    data[++i] = m_Prix;
    for (j = 0; j < TAILLE_DESCRIPTION_OBJET; ++j) {
        data[++i] = m_Description[j]; //0 est écrit s'il est présent
        if (m_Description[j] == '\0')
            break;
    }
    return &data[i+1];
}

const char* Objet::LireD(const char* data) {
    unsigned int i;
    // m_Type = data[i];
    for (i = 0; i < TAILLE_NOM_OBJET; ++i) {
        if (data[i] == '\0')
            break;
        m_Nom[i] = data[i];
    }
    unsigned int j;
    for (j = i; j < TAILLE_NOM_OBJET+1; ++j) // sécurité
        m_Nom[j] = '\0';

    if (i == TAILLE_NOM_OBJET) --i;
    m_Prix = (unsigned char)(data[++i]);

    for (j = 0; j < TAILLE_DESCRIPTION_OBJET; ++j) {
        if (data[++i] == '\0')
            break;
        m_Description[j] = data[i];
    }
    for (; j < TAILLE_DESCRIPTION_OBJET+1; ++j) // sécurité
        m_Description[j] = '\0';
        
    return &data[i+1];
}