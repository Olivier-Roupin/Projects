#include "lib/Effet.h"

Effet::Effet(int id, Script* script, char Element, char Disponibilite) { //utilisé
    SetId(id);
    SetScript(script); //non prise en compte du curseur
    SetElement(Element);
    SetDisponibilite(Disponibilite);
    SetChoix_Cible(false);
    SetChoix_Faction(false);
    SetChoix_Quantite(false);
    SetDefaut_Cible(0);
    SetDefaut_Faction(false);
    SetDefaut_Quantite(false);
}

Effet::Effet(int id, Script* script, char Element, char Disponibilite,\
             bool Choix_Cible, bool Choix_Faction, bool Choix_Quantite,\
             int Defaut_Cible, bool Defaut_Faction, bool Defaut_Quantite) {
    SetId(id);
    SetScript(script); //non prise en compte du curseur
    SetElement(Element);
    SetDisponibilite(Disponibilite);
    SetChoix_Cible(Choix_Cible);
    SetChoix_Faction(Choix_Faction);
    SetChoix_Quantite(Choix_Quantite);
    SetDefaut_Cible(Defaut_Cible);
    SetDefaut_Faction(Defaut_Faction);
    SetDefaut_Quantite(Defaut_Quantite);
}

Effet::~Effet() {
}

int Effet::GetId() const {
    return m_Id;
}

void Effet::SetId(int val) {
    m_Id = val;
}

Script* Effet::GetScript() const {
    return m_Script;
}

void Effet::SetScript(Script* val) {
    m_Script = val;
}

void Effet::SetElement(char val) {
    m_Element = val;
}

char Effet::GetElement() const {
    return m_Element;
}

char Effet::GetDisponibilite() const {
    return m_Disponibilite;
}

void Effet::SetDisponibilite(char val) {
    m_Disponibilite = val;
}

bool Effet::GetChoix_Cible() const {
    return m_Choix_Cible;
}

void Effet::SetChoix_Cible(bool val) {
    m_Choix_Cible = val;
}

bool Effet::GetChoix_Faction() const {
    return m_Choix_Faction;
}

void Effet::SetChoix_Faction(bool val) {
    m_Choix_Faction = val;
}

bool Effet::GetChoix_Quantite() const {
    return m_Choix_Quantite;
}

void Effet::SetChoix_Quantite(bool val) {
    m_Choix_Quantite = val;
}

int Effet::GetDefaut_Cible() const {
    return m_Defaut_Cible;
}

void Effet::SetDefaut_Cible(int val) {
    m_Defaut_Cible = val;
}

bool Effet::GetDefaut_Faction() const {
    return m_Defaut_Faction;
}

void Effet::SetDefaut_Faction(bool val) {
    m_Defaut_Faction = val;
}

bool Effet::GetDefaut_Quantite() const {
    return m_Defaut_Quantite;
}

void Effet::SetDefaut_Quantite(bool val) {
    m_Defaut_Quantite = val;
}

void Effet::Ecrire(char* data) const {
    //char str[2+1 +1+1 +1+1  +1+1 +1+1 +1+1  +1+1 +1+1 +1+1  +1];
    int i = 0;
    if (GetScript()) {
        if (GetScript()->GetId() > 9)
            data[i++] = '0'+(GetScript()->GetId()-GetScript()->GetId()%10)/10;
        data[i++] = '0'+(GetScript()->GetId()%10);
    } else
        data[i++] = '0';
    data[i++] = ' ';

    data[i++] = '0'+GetElement();
    data[i++] = ' ';
    data[i++] = '0'+GetDisponibilite();
    data[i++] = ' ';
    data[i++] = '0'+(char)GetChoix_Cible();
    data[i++] = ' ';
    data[i++] = '0'+(char)GetChoix_Faction();
    data[i++] = ' ';
    data[i++] = '0'+(char)GetChoix_Quantite();
    data[i++] = ' ';
    data[i++] = '0'-GetDefaut_Cible();
    data[i++] = ' ';
    data[i++] = '0'+(char)GetDefaut_Faction();
    data[i++] = ' ';
    data[i++] = '0'+(char)GetDefaut_Quantite();
    data[i++] = '\0';
}

extern Script* scripts[];

void Effet::Lire(int& i, const char* data) {
    int entier;
    char octet;
    LIRE_ENTIER(i,data,entier); SetScript(scripts[entier]);
    LIRE_CHIFFRE(i,data,octet); SetElement(octet);
    LIRE_CHIFFRE(i,data,octet); SetDisponibilite(octet);
    bool booleen;
    LIRE_BOOLEEN(i,data,booleen); SetChoix_Cible(booleen);
    LIRE_BOOLEEN(i,data,booleen); SetChoix_Faction(booleen);
    LIRE_BOOLEEN(i,data,booleen); SetChoix_Quantite(booleen);
    LIRE_CHIFFRE(i,data,entier);   SetDefaut_Cible(-entier);
    LIRE_BOOLEEN(i,data,booleen); SetDefaut_Faction(booleen);
    LIRE_BOOLEEN(i,data,booleen); SetDefaut_Quantite(booleen);
}

unsigned int Effet::TailleD() const {
    return 9;
}

char* Effet::EcrireD(char* data) const {
    unsigned int i = 0;
    data[  i] = m_Script ? m_Script->GetId() : 0;
    data[++i] = m_Element;
    data[++i] = m_Disponibilite;
    data[++i] = m_Choix_Cible;
    data[++i] = m_Choix_Faction;
    data[++i] = m_Choix_Quantite;
    data[++i] = m_Defaut_Cible;
    data[++i] = m_Defaut_Faction;
    data[++i] = m_Defaut_Quantite;
    return &data[i+1];
}

const char* Effet::LireD(const char* data) {
    unsigned int i = 0;
    m_Script = scripts[(unsigned char)data[i]];
    m_Element         = data[++i];
    m_Disponibilite   = data[++i];
    m_Choix_Cible     = data[++i];
    m_Choix_Faction   = data[++i];
    m_Choix_Quantite  = data[++i];
    m_Defaut_Cible    = data[++i];
    m_Defaut_Faction  = data[++i];
    m_Defaut_Quantite = data[++i];
    return &data[i+1];
}