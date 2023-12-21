#include "lib/Capacite.h"

Capacite::Capacite(int Id, const char* Nom, const char* Description,\
                   int CoutMagie, char CoutMagieP, int CoutVie, char CoutVieP,\
                   Effet* effet) { //utilisé
    SetId(Id);
    SetNom(Nom);
    SetDescription(Description);
    SetCoutMagie(CoutMagie);
    SetCoutMagieP(CoutMagieP);
    SetCoutVie(CoutVie);
    SetCoutVieP(CoutVieP);
    SetEffet(effet);
}

Capacite::~Capacite() {
}

/*
Capacite::Capacite(const Capacite& cible) {
    SetNom(cible.GetNom());
    SetDescription(cible.GetDescription());
    SetCoutMagie(cible.GetCoutMagie());
    SetCoutMagieP(cible.GetCoutMagieP());
    SetCoutVie(cible.GetCoutVie());
    SetCoutVieP(cible.GetCoutVieP());
}
*/

int Capacite::GetId() const {
    return m_Id;
}

void Capacite::SetId(int val) {
    if (val < 0)
        val = 0;
    m_Id = val;
}

const char* Capacite::GetNom() const {
    return m_Nom;
}

void Capacite::SetNom(const char* val) {
    for (int i = 0; i < TAILLE_NOM_CAPACITE; i++) {
        m_Nom[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Nom[TAILLE_NOM_CAPACITE] = '\0';
}

const char* Capacite::GetDescription() const {
    return m_Description;
}

void Capacite::SetDescription(const char* val) {
    for (int i = 0; i < TAILLE_DESCRIPTION_CAPACITE; i++) {
        m_Description[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Description[TAILLE_DESCRIPTION_CAPACITE] = '\0';
}

int Capacite::GetCoutVie() const {
    return m_CoutVie;
}

void Capacite::SetCoutVie(int val) {
    if (val < 0)
        val = 0;
    m_CoutVie = val;
}

char Capacite::GetCoutVieP() const {
    return m_CoutVieP;
}

void Capacite::SetCoutVieP(char val) {
    if (val < 0)
        val = 0;
    else if (val > 100)
        val = 100;
    m_CoutVieP = val;
}

int Capacite::GetCoutMagie() const {
    return m_CoutMagie;
}

void Capacite::SetCoutMagie(int val) {
    if (val < 0)
        val = 0;
    m_CoutMagie = val;
}

char Capacite::GetCoutMagieP() const {
    return m_CoutMagieP;
}

void Capacite::SetCoutMagieP(char val) {
    if (val < 0)
        val = 0;
    else if (val > 100)
        val = 100;
    m_CoutMagieP = val;
}

Effet* Capacite::GetEffet() const {
    return m_Effet;
}

void Capacite::SetEffet(Effet* val) {
    m_Effet = val;
}

void Capacite::Ecrire(char* data) const {
    int i = 0, j = 0;
    for (j = 0; j < TAILLE_NOM_CAPACITE; i++, j++) {
        if (m_Nom[j] == '\0') break;
        data[i] = m_Nom[j];
    }
    data[i++] = ' ';
    for (j = 0; j < TAILLE_DESCRIPTION_CAPACITE; i++, j++) {
        if (m_Description[j] == '\0') break;
        data[i] = m_Description[j];
    }
    data[i++] = ' ';

    if (GetCoutMagie() > 99)
        data[i++] = '0'+(GetCoutMagie()-GetCoutMagie()%100)/100;
    if (GetCoutMagie() > 9)
        data[i++] = '0'+(GetCoutMagie()%100-GetCoutMagie()%10)/10;
    data[i++] = '0'+(GetCoutMagie()%10);
    data[i++] = ' ';

    if (GetCoutMagieP() > 99)
        data[i++] = '0'+(GetCoutMagieP()-GetCoutMagieP()%100)/100;
    if (GetCoutMagieP() > 9)
        data[i++] = '0'+(GetCoutMagieP()%100-GetCoutMagieP()%10)/10;
    data[i++] = '0'+(GetCoutMagieP()%10);
    data[i++] = ' ';

    if (GetCoutVie() > 99)
        data[i++] = '0'+(GetCoutVie()-GetCoutVie()%100)/100;
    if (GetCoutVie() > 9)
        data[i++] = '0'+(GetCoutVie()%100-GetCoutVie()%10)/10;
    data[i++] = '0'+(GetCoutVie()%10);
    data[i++] = ' ';

    if (GetCoutVieP() > 99)
        data[i++] = '0'+(GetCoutVieP()-GetCoutVieP()%100)/100;
    if (GetCoutVieP() > 9)
        data[i++] = '0'+(GetCoutVieP()%100-GetCoutVieP()%10)/10;
    data[i++] = '0'+(GetCoutVieP()%10);
    data[i++] = ' ';

    if (GetEffet()) {
        if (GetEffet()->GetId() > 9)
            data[i++] = '0'+(GetEffet()->GetId()-GetEffet()->GetId()%10)/10;
        data[i++] = '0'+(GetEffet()->GetId()%10);
    } else
        data[i++] = '0';
    data[i++] = '\0';
}

extern Effet* effets[];

void Capacite::Lire(int& i, const char* data) {
    int j = 0;
    char nom[TAILLE_NOM_CAPACITE+1];
    LIRE_CHAINE(i,j,data,nom,TAILLE_NOM_CAPACITE); SetNom(nom);
    j=0;
    char des[TAILLE_DESCRIPTION_CAPACITE+1];
    LIRE_CHAINE(i,j,data,des,TAILLE_DESCRIPTION_CAPACITE); SetDescription(des);
    int entier;
    char octet;
    LIRE_ENTIER(i,data,entier); SetCoutMagie(entier);
    LIRE_ENTIER(i,data,octet); SetCoutMagieP(octet);
    LIRE_ENTIER(i,data,entier); SetCoutVie(entier);
    LIRE_ENTIER(i,data,octet); SetCoutVieP(octet);
    LIRE_ENTIER(i,data,entier); SetEffet(effets[entier]);
}

unsigned int Capacite::TailleD() const {
    unsigned int i, taille = 0;
    for (i = 0; i < TAILLE_NOM_CAPACITE; ++i)
        if (m_Nom[i] == '\0')
            break;
    taille += i;
    for (i = 0; i < TAILLE_DESCRIPTION_CAPACITE; ++i)
        if (m_Description[i] == '\0')
            break;
    taille += i;
    return taille+5*1;
    // return TAILLE_NOM_CAPACITE +TAILLE_DESCRIPTION_CAPACITE +1+1+1+1+1;
}

char* Capacite::EcrireD(char* data) const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_CAPACITE; ++i) {
        data[i] = m_Nom[i]; //0 est écrit s'il est présent
        if (m_Nom[i] == '\0')
            break;
    }
    if (i == TAILLE_NOM_CAPACITE) --i;
    // for (; i < TAILLE_NOM_CAPACITE; ++i)
    //     data[i] = '\0';
    unsigned int j;
    for (j = 0; j < TAILLE_DESCRIPTION_CAPACITE; ++j) {
        data[++i] = m_Description[j]; //0 est écrit s'il est présent
        if (m_Description[j] == '\0')
            break;
    }
    // if (j == TAILLE_DESCRIPTION_CAPACITE) --i;

    // i += j; //optimisation ?
    // for (; i < TAILLE_NOM_CAPACITE+TAILLE_DESCRIPTION_CAPACITE; ++i)
    //     data[i] = '\0';
    data[++i] = m_CoutMagie;
    data[++i] = m_CoutMagieP;
    data[++i] = m_CoutVie;
    data[++i] = m_CoutVieP;
    data[++i] = m_Effet ? m_Effet->GetId() : 0;
    return &data[i+1];
}

const char* Capacite::LireD(const char* data) {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_CAPACITE; ++i) {
        if (data[i] == '\0')
            break;
        m_Nom[i] = data[i];
    }
    unsigned int j;
    for (j = i; j < TAILLE_NOM_CAPACITE+1; ++j) // sécurité
        m_Nom[j] = '\0';

    if (i == TAILLE_NOM_CAPACITE) --i;

    for (j = 0; j < TAILLE_DESCRIPTION_CAPACITE; ++j) {
        if (data[++i] == '\0')
            break;
        m_Description[j] = data[i];
    }
    // if (j == TAILLE_DESCRIPTION_CAPACITE) --i;

    for (; j < TAILLE_DESCRIPTION_CAPACITE+1; ++j) // sécurité
        m_Description[j] = '\0';

    m_CoutMagie  = data[++i];
    m_CoutMagieP = data[++i];
    m_CoutVie    = data[++i];
    m_CoutVieP   = data[++i];
    m_Effet      = effets[(unsigned char)data[++i]];
    return &data[i+1];
}