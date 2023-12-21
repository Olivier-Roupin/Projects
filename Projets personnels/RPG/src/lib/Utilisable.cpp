#include "lib/Utilisable.h"

Utilisable::Utilisable(int Id, const char* Nom, int Type, int Prix,
                       const char* Description,
                       bool Illimite, Effet* effet) : Objet(Id, Nom, Type,
                                                            Prix, Description) {
    SetIllimite(Illimite);
    SetEffet(effet);
}

Utilisable::~Utilisable() {
}

bool Utilisable::EstEquipable() const {
    return false;
}

bool Utilisable::GetIllimite() const {
    return m_Illimite;
}

void Utilisable::SetIllimite(bool val) {
    m_Illimite = val;
}

Effet* Utilisable::GetEffet() const {
    return m_Effet;
}

void Utilisable::SetEffet(Effet* val) {
    m_Effet = val;
}

int Utilisable::Ecrire(char* data) const {
    int i(Objet::Ecrire(data));
    data[i-1] = ' '; //effacer le \0
    data[i++] = '0'+(char)GetIllimite();
    data[i++] = ' ';
    if (GetEffet()) {
        if (GetEffet()->GetId() > 9)
            data[i++] = '0'+(GetEffet()->GetId()-GetEffet()->GetId()%10)/10;
        data[i++] = '0'+(GetEffet()->GetId()%10);
    } else
        data[i++] = '0';
    data[i++] = '\0';
    return i;
}

extern Effet* effets[];

void Utilisable::Lire(int& i, const char* data) {
    Objet::Lire(i, data);
    bool booleen;
    LIRE_BOOLEEN(i,data,booleen); SetIllimite(booleen);
    int entier;
    LIRE_ENTIER(i,data,entier);    SetEffet(effets[entier]);
}

unsigned int Utilisable::TailleD() const {
    return Objet::TailleD()+2;
}

char* Utilisable::EcrireD(char* data) const {
    data = Objet::EcrireD(data);
    unsigned int i = 0;
    data[  i] = m_Illimite;
    data[++i] = m_Effet ? m_Effet->GetId() : 0;
    return &data[i+1];
}

const char* Utilisable::LireD(const char* data) {
    data = Objet::LireD(data);
    unsigned int i = 0;
    m_Illimite = data[i];
    m_Effet = effets[(unsigned char)(data[++i])];
    return &data[i+1];
}