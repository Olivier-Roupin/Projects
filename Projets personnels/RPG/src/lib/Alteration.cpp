#include "lib/Alteration.h"

Alteration::Alteration(int id, const char* nom, Script* script, bool postCombat,
                       bool postDeces, unsigned char priorite,
                       Script* scriptTerrain) { //utilisé
    SetId(id);
    SetNom(nom);
    SetScript(script);
    SetPostCombat(postCombat);
    SetPostDeces(postDeces);
    SetPriorite(priorite);
    SetScriptTerrain(scriptTerrain);
}

Alteration::Alteration(const Alteration& cible) {
    SetId(cible.GetId());
    SetNom(cible.GetNom());
    SetPostCombat(cible.GetPostCombat());
    SetPostDeces(cible.GetPostDeces());
    SetPriorite(cible.GetPriorite());
    Script* script = new Script(*(cible.GetScript()));
    SetScript(script);
    if (cible.GetScriptTerrain()) {
        Script* scriptTerrain = new Script(*(cible.GetScriptTerrain()));
        SetScriptTerrain(scriptTerrain);
    } else
        m_ScriptTerrain = 0;
}

Alteration::~Alteration() {
}

int Alteration::GetId() const {
    return m_Id;
}

void Alteration::SetId(int val) {
    m_Id = val;
}

const char* Alteration::GetNom() const {
    return m_Nom;
}

/*void Alteration::SetNom(const char* val) {
    for (int i = 0; i < TAILLE_NOM_ALTERATION; i++) {
        m_Nom[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Nom[TAILLE_NOM_ALTERATION] = '\0';
    return;
}*/

int Alteration::SetNom(const char* val) {
    int i;
    for (i = 0; i < TAILLE_NOM_ALTERATION; i++) {
        if (val[i] == '\0' || val[i] == ' ')
            break;
        m_Nom[i] = val[i];
    }
    m_Nom[i] = '\0';
    return i;
}

Script* Alteration::GetScript() const {
    return m_Script;
}

void Alteration::SetScript(Script* val) {
    m_Script = val;
}

Script* Alteration::GetScriptTerrain() const {
    return m_ScriptTerrain;
}

void Alteration::SetScriptTerrain(Script* val) {
    m_ScriptTerrain = val;
}

bool Alteration::GetPostCombat() const {
    return m_PostCombat;
}

void Alteration::SetPostCombat(bool val) {
    m_PostCombat = val;
}

bool Alteration::GetPostDeces() const {
    return m_PostDeces;
}

void Alteration::SetPostDeces(bool val) {
    m_PostDeces = val;
}

unsigned char Alteration::GetPriorite() const {
    return m_Priorite;
}

void Alteration::SetPriorite(unsigned char val) {
    m_Priorite = val;
}

//char str[TAILLE_NOM_ALTERATION+1 +2+1 +1+1 +1+1 +1+1  +1];
void Alteration::Ecrire(char* data) const {
    int i = 0, j;
    ECRIRE_CHAINE(i,j,data,m_Nom,TAILLE_NOM_ALTERATION);
    data[i++] = ' ';

    if (GetScript()) {
        ECRIRE_2CHIFFRES(i,data,GetScript()->GetId());
    } else
        data[i++] = '0';
    data[i++] = ' ';
    ECRIRE_BOOLEEN(i,data,GetPostCombat());
    data[i++] = ' ';
    ECRIRE_BOOLEEN(i,data,GetPostDeces());
    data[i++] = ' ';
    ECRIRE_CHIFFRE(i,data,GetPriorite());
    if (GetScriptTerrain()) { // && GetPostCombat()
        data[i++] = ' ';
        ECRIRE_2CHIFFRES(i,data,GetScriptTerrain()->GetId());
    }
    data[i++] = '\0';
}

extern Script* scripts[];

void Alteration::Lire(int& i, const char* data) {
    int j = 0;
    char nom[TAILLE_NOM_ALTERATION+1];
    LIRE_CHAINE(i,j,data,nom,TAILLE_NOM_ALTERATION); SetNom(nom);
    int entier;
    unsigned char chiffre;
    LIRE_ENTIER(i,data,entier);   SetScript(scripts[entier]);
    bool booleen;
    LIRE_BOOLEEN(i,data,booleen); SetPostCombat(booleen);
    LIRE_BOOLEEN(i,data,booleen); SetPostDeces(booleen);
    LIRE_CHIFFRE(i,data,chiffre);  SetPriorite(chiffre);
    if (GetPostCombat()) {
        LIRE_ENTIER(i,data,entier);   SetScriptTerrain(scripts[entier]);
    }
}

unsigned int Alteration::TailleD() const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_ALTERATION; ++i)
        if (m_Nom[i] == '\0')
            break;
    if (m_PostCombat)
        return i +1 +1+1+1 +1;
    return i +1 +1+1+1;
}

char* Alteration::EcrireD(char* data) const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_ALTERATION; ++i) {
        data[i] = m_Nom[i]; //0 est écrit s'il est présent
        if (m_Nom[i] == '\0')
            break;
    }
    if (i == TAILLE_NOM_ALTERATION) --i;
    // for (i = 0; i < TAILLE_NOM_ALTERATION; ++i) {
    //     if (m_Nom[i] == '\0') // sécurité
    //         break;
    //     data[i] = m_Nom[i];
    // }
    // for (; i < TAILLE_NOM_ALTERATION; ++i)
    //     data[i] = '\0';
    data[++i] = m_Script ? m_Script->GetId() : 0;
    data[++i] = m_PostCombat;
    data[++i] = m_PostDeces;
    data[++i] = m_Priorite;
    if (m_ScriptTerrain)
        data[++i] = m_ScriptTerrain->GetId();
    return &data[i+1];
}

const char* Alteration::LireD(const char* data) {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_ALTERATION; ++i) {
        if (data[i] == '\0')
            break;
        m_Nom[i] = data[i];
    }
    unsigned int j;
    for (j = i; j < TAILLE_NOM_ALTERATION+1; ++j) // sécurité
        m_Nom[j] = '\0';

    if (i == TAILLE_NOM_ALTERATION) --i;
    
    m_Script     = scripts[(unsigned char)data[++i]];
    m_PostCombat = data[++i];
    m_PostDeces  = data[++i];
    m_Priorite   = data[++i];
    if (m_PostCombat)
        m_ScriptTerrain = m_PostCombat ? scripts[(unsigned char)data[++i]] : 0;
    return &data[i+1];
}