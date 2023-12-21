#include "lib/Equipable.h"

Equipable::Equipable(int id, const char* nom, int type, int prix,\
                     const char* description,\
                     int vieMax,   int attaqueP,  int defenseP,\
                     int magieMax, int attaqueM,  int defenseM,\
                     int vitesse,  int precision, int esquive,\
                     char poids, unsigned char ratio) : Objet(id,nom,type,prix,description) { //utilisé
    SetAttribut(vieMax, ATTRIBUT_VIE);
    SetAttribut(attaqueP, ATTRIBUT_ATKP);
    SetAttribut(defenseP, ATTRIBUT_DEFP);
    SetAttribut(magieMax, ATTRIBUT_MAG);
    SetAttribut(attaqueM, ATTRIBUT_ATKM);
    SetAttribut(defenseM, ATTRIBUT_DEFM);
    SetAttribut(vitesse, ATTRIBUT_VIT);
    SetAttribut(precision, ATTRIBUT_PRE);
    SetAttribut(esquive, ATTRIBUT_ESQ);

    SetRatio(ratio);
    SetPoids(poids);
    SetElement(ELEMENT_NEUTRE);
    // SetDegats(0);
}

Equipable::~Equipable() {
}

bool Equipable::EstEquipable() const {
    return true;
}

int Equipable::GetAttribut(unsigned char id) const {
    // if (id < 0 || id >= NOMBRE_ATTRIBUTS)
    if (id >= NOMBRE_ATTRIBUTS)
        return 0;
    return m_Attributs[id];
}

void Equipable::SetAttribut(int val, unsigned char id) {
    if (val < 0)
        val = 0;
    // if (id >= 0 && id < NOMBRE_ATTRIBUTS)
    if (id < NOMBRE_ATTRIBUTS)
        m_Attributs[id] = val;
}

char Equipable::GetPoids() const {
    return m_Poids;
}

void Equipable::SetPoids(char val) {
    if (val < 0)
        val = 0;
    m_Poids = val;
}

unsigned char Equipable::GetRatio() const {
    return m_Ratio;
}

void Equipable::SetRatio(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    // else if (val > 16)
    if (val > MAX_RATIO)
        val = MAX_RATIO;
    m_Ratio = val;
}

/*int Equipable::GetOffensif() const {
    if (GetType() == EQUIPABLE_ARME || GetType() == EQUIPABLE_ACCESSOIRE)
        return m_Ratio;
    //if (GetType() == EQUIPABLE_ARMURE || GetType() == EQUIPABLE_BOUCLIER
    //|| GetType() == EQUIPABLE_CASQUE)
    //    return -1;
    // return -1;
    return 0;
}*/

char Equipable::GetOffensif() const {
    if (GetType() == EQUIPABLE_ARME)
        return 1+m_Ratio;
    else if (GetType() == EQUIPABLE_ACCESSOIRE)
        return m_Ratio-7;
    return 0; //aucun, anormal
}

/*int Equipable::GetDefensif() const {
    //if (GetType() == EQUIPABLE_ARME)
    //    return -1;
    if (GetType() == EQUIPABLE_ACCESSOIRE)
        return 16-m_Ratio;
    if (GetType() == EQUIPABLE_ARMURE || GetType() == EQUIPABLE_BOUCLIER
    || GetType() == EQUIPABLE_CASQUE)
        return m_Ratio;
    // return -1;
    return 0;
}*/

char Equipable::GetDefensif() const {
    if (GetType() == EQUIPABLE_ARMURE || GetType() == EQUIPABLE_BOUCLIER
     || GetType() == EQUIPABLE_CASQUE)
        return 1+m_Ratio;
    else if (GetType() == EQUIPABLE_ACCESSOIRE)
        return 7-m_Ratio;
    return 0; //aucun, anormal
}

/*int Equipable::GetPhysionomique() const {
    if (GetType() == EQUIPABLE_ARME || GetType() == EQUIPABLE_ARMURE
    || GetType() == EQUIPABLE_BOUCLIER || GetType() == EQUIPABLE_CASQUE)
        return 16-m_Ratio;
    //if (GetType() == EQUIPABLE_ACCESSOIRE)
    //    return -1;
    // return -1;
    return 16;
}*/

char Equipable::GetPhysionomique() const {
    if (GetType() == EQUIPABLE_ARME     || GetType() == EQUIPABLE_ARMURE
     || GetType() == EQUIPABLE_BOUCLIER || GetType() == EQUIPABLE_CASQUE)
        return MAX_RATIO-m_Ratio;
    else if (GetType() == EQUIPABLE_ACCESSOIRE)
        return MAX_RATIO+1; //pour l'affichage
    return MAX_RATIO+1; //aucun, anormal
}

char Equipable::GetElement() const {
    return m_Element;
}

void Equipable::SetElement(char val) {
    if (val < 0 || val >= NOMBRE_ELEMENTS)
        val = ELEMENT_NEUTRE;
    m_Element = val;
}

/*int Equipable::GetDegats() const {
    return m_Degats;
}

void Equipable::SetDegats(int val) {
    m_Degats = val;
}*/

int Equipable::Ecrire(char* data) const {
    int i = Objet::Ecrire(data);
    data[i-1] = ' ';

    unsigned int j;
    for (j = 0; j < NOMBRE_ATTRIBUTS; j++) {
        // if (GetAttribut(j) > 9)
        if (m_Attributs[j] > 9)
            // data[i++] = '0'+(GetAttribut(j)-GetAttribut(j)%10)/10;
            data[i++] = '0'+(m_Attributs[j]-m_Attributs[j]%10)/10;
        data[i++] = '0'+ m_Attributs[j]%10;
        data[i++] = ' ';
    }
    if (GetPoids() > 9)
            data[i++] = '0'+(GetPoids()-GetPoids()%10)/10;
    data[i++] = '0'+ GetPoids()%10;
    data[i++] = ' ';

    if (GetRatio() > 9)
            data[i++] = '0'+(GetRatio()-GetRatio()%10)/10;
    data[i++] = '0'+ GetRatio()%10;
    data[i++] = ' ';

    data[i++] = '0'+ GetElement();
    data[i++] = '\0';
    return i;
}

void Equipable::Lire(int& i, const char* data) {
    Objet::Lire(i, data);
    int entier;
    char octet;
    unsigned int j;
    for (j = 0; j < NOMBRE_ATTRIBUTS; j++) {
        LIRE_ENTIER(i,data,entier);
        SetAttribut(entier,j);
    }
    LIRE_ENTIER(i,data,entier); SetPoids(entier);
    LIRE_ENTIER(i,data,entier); SetRatio(entier);
    LIRE_ENTIER(i,data,octet); SetElement(octet);
}

unsigned int Equipable::TailleD() const {
    return Objet::TailleD()+NOMBRE_ATTRIBUTS+3;
}

char* Equipable::EcrireD(char* data) const {
    data = Objet::EcrireD(data);
    unsigned int i;
    for (i = 0; i < NOMBRE_ATTRIBUTS; ++i)
        data[i] = m_Attributs[i];
    data[  i] = m_Poids;
    data[++i] = m_Ratio;
    data[++i] = m_Element;
    return &data[i+1];
}

const char* Equipable::LireD(const char* data) {
    data = Objet::LireD(data);
    unsigned int i;
    for (i = 0; i < NOMBRE_ATTRIBUTS; ++i)
        m_Attributs[i] = data[i];
    m_Poids   = data[  i];
    m_Ratio   = (unsigned char)(data[++i]);
    m_Element = data[++i];
    return &data[i+1];
}