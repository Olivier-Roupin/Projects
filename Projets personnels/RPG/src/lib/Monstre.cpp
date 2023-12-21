#include "lib/Monstre.h"
// #include <cstdlib> //rand, RAND_MAX

Monstre::Monstre(int Id, const char* Nom, int Vie, int Magie,\
                 int VieMax, int AttaqueP, int DefenseP,\
                 int MagieMax, int AttaqueM, int DefenseM,\
                 int Vitesse, int Precision, int Esquive,\
                 int Experience, int Niveau,\
                //  GroupeObjets* Butin, GroupeObjets* Objetporte, int Or,
                 Objet* Butin, GroupeObjets* Objetporte, int Or,
                 int Statut, int Jauge):\
    Personnage(Id,Nom,Vie,Magie,VieMax,AttaqueP,DefenseP,
               MagieMax,AttaqueM,DefenseM,
               Vitesse,Precision,Esquive,Statut,Experience,Niveau,Jauge) {
    if (Butin)
        SetButin(Butin);
    else
        m_Butin = 0;
    if (Objetporte)
        SetObjetPorte(Objetporte);
    else
        m_ObjetPorte = 0;
    SetOr(Or);
    m_Script = 0;
    SetElementAttaque(ELEMENT_NEUTRE);
    SetElementDefense(ELEMENT_NEUTRE);
}

Monstre::Monstre(const Monstre& cible) : Personnage(cible) {
    SetOr(cible.GetOr());
    m_Butin = 0;
    m_ObjetPorte = 0;
    m_Script = 0;
    if (cible.GetButin())
        m_Butin = cible.GetButin();
        // m_Butin = new GroupeObjets(*(cible.GetButin()));
    if (cible.GetObjetPorte())
        m_ObjetPorte = new GroupeObjets(*(cible.GetObjetPorte()));
    if (cible.GetScript())
        m_Script = new Script(*(cible.GetScript()));
    SetElementAttaque(cible.GetElementAttaque());
    SetElementDefense(cible.GetElementDefense());
}

Monstre::~Monstre() {
}

// GroupeObjets* Monstre::GetButin() const {
//     return m_Butin;
// }

// void Monstre::SetButin(GroupeObjets* val) {
//     m_Butin = val;
// }

Objet* Monstre::GetButin() const {
    return m_Butin;
}

void Monstre::SetButin(Objet* val) {
    m_Butin = val;
}

GroupeObjets* Monstre::GetObjetPorte() const {
    return m_ObjetPorte;
}

void Monstre::SetObjetPorte(GroupeObjets* val) {
    m_ObjetPorte = val;
}

int Monstre::GetOr() const {
    return m_Or;
}

void Monstre::SetOr(int val) {
    if (val < 0)
        m_Or = 0;
    else
        m_Or = val;
}

Script* Monstre::GetScript() const {
    return m_Script;
}

void Monstre::SetScript(Script* val) {
    if (m_Script)
        delete m_Script;
    m_Script = new Script(*val);
}

void Monstre::ActualiserAnimation() {
    SetTempsAnimation(GetTempsAnimation()-1);
    if (GetTempsAnimation() == 0)
        SetAnimation(estEnVie() ? ANIMATION_MONSTRE_VISIBLE : ANIMATION_MONSTRE_CACHE);
        // SetAnimation(ANIMATION_MONSTRE_VISIBLE);
}

char Monstre::GetElementAttaque() const {
    return m_ElementAttaque;
}

void Monstre::SetElementAttaque(char val) {
    if (val < 0 || val >= NOMBRE_ELEMENTS)
        val = ELEMENT_NEUTRE;
    m_ElementAttaque = val;
}

char Monstre::GetElementDefense() const {
    return m_ElementDefense;
}

void Monstre::SetElementDefense(char val) {
    if (val < 0 || val >= NOMBRE_ELEMENTS)
        val = ELEMENT_NEUTRE;
    m_ElementDefense = val;
}

int Monstre::GetModificateurElementaire(unsigned char id, char element) const {
    if (id == ATTRIBUT_DEFP || id == ATTRIBUT_DEFM) //ATTRIBUT_ESQ
        return ModificateurElement(1, element, GetElementDefense());
    else if (id == ATTRIBUT_ATKP || id == ATTRIBUT_ATKM) //utile ? //ATTRIBUT_PRE
        return ModificateurElement(1, element, GetElementAttaque());
    return 1;
}

// #include <cstdio>

// void Monstre::Attaquer() {
void Monstre::Attaquer(unsigned int de, unsigned int max_de) {
    if (GetCible(0) == 0)
        return;
    // if (rand() < RAND_MAX/4096*Probabilite_touche()) {
    if (de < max_de/4096*Probabilite_touche()) {
        const int atkp = GetAttributTotal(ATTRIBUT_ATKP);
        const int defp = GetCible(0)->GetAttributTotal(ATTRIBUT_DEFP);
        const int plage = 2*atkp*atkp/(atkp+defp);
        const int degats = -2*atkp*atkp*atkp/(atkp+defp)
                        //  + (plage ? (rand()%(2*plage)-plage) : 0);
                         + (plage ? (de%(2*plage)-plage) : 0);
        const int modif = GetCible(0)->GetModificateurElementaire(ATTRIBUT_DEFP,
            GetElementAttaque());

        // printf("Monstre::Attaquer modif %d\n", modif);

        GetCible(0)->ChangerVie(modif*degats/2);
        GetCible(0)->SetMessage(modif*degats/2);
        // const int degats = -GetAttributTotal(ATTRIBUT_ATKP)
        //                     /GetCible(0)->GetAttributTotal(ATTRIBUT_DEFP);
    } else
        GetCible(0)->SetMessage(0); //TODO valeur spéciale pour "raté" ?
    GetCible(0)->SetTempsMessage(30);
}

int Monstre::Ecrire(char* data) const {
    int i = Personnage::Ecrire(data);
    data[i-1] = ' ';
    if (GetButin()) {
        ECRIRE_3CHIFFRES(i,data,GetButin()->GetId());
    } else
        data[i++] = '0';
    data[i++] = ' ';
    if (GetObjetPorte()) {
        ECRIRE_3CHIFFRES(i,data,GetObjetPorte()->GetId());
    } else
        data[i++] = '0';
    data[i++] = ' ';
    ECRIRE_3CHIFFRES(i,data,GetOr());
    data[i++] = ' ';
    if (GetScript()) {
        ECRIRE_3CHIFFRES(i,data,GetScript()->GetId());
    } else
        data[i++] = '0';
    data[i++] = ' ';
    ECRIRE_CHIFFRE(i,data,GetElementAttaque());
    data[i++] = ' ';
    ECRIRE_CHIFFRE(i,data,GetElementDefense());
    data[i++] = '\0';
    return i;
}

extern Objet* objets[];
extern Script* scripts[];

void Monstre::Lire(int& i, const char* data) {
    Personnage::Lire(i, data);
    int entier;
    char octet;
    LIRE_ENTIER(i,data,entier);
    if (entier)
        m_Butin = objets[entier];
        // m_Butin = new GroupeObjets(objets[entier]);
    else
        m_Butin = 0;
    LIRE_ENTIER(i,data,entier);
    if (entier)
        m_ObjetPorte = new GroupeObjets(objets[entier]);
    else
        m_ObjetPorte = 0;
    LIRE_ENTIER(i,data,entier); SetOr(entier);
    LIRE_ENTIER(i,data,entier); SetScript(scripts[entier]);
    LIRE_ENTIER(i,data,octet); SetElementAttaque(octet);
    LIRE_ENTIER(i,data,octet); SetElementDefense(octet);
}

unsigned int Monstre::TailleD() const {
    return Personnage::TailleD()+6;
}

char* Monstre::EcrireD(char* data) const {
    data = Personnage::EcrireD(data);
    unsigned int i = 0;
    data[  i] = m_Butin      ? m_Butin->GetId() : 0;
    data[++i] = m_ObjetPorte ? m_ObjetPorte->GetId() : 0;
    data[++i] = (unsigned char)((m_Or >> 8) & 255);
    data[++i] = (unsigned char)( m_Or & 255);
    data[++i] = m_Script     ? m_Script->GetId() : 0;
    data[++i] = m_ElementAttaque;
    data[++i] = m_ElementDefense;
    return &data[i+1];
}

const char* Monstre::LireD(const char* data) {
    data = Personnage::LireD(data);
    unsigned int i = 0;
    m_Butin      = data[  i] ? objets[(unsigned char)data[i]] : 0;
    m_ObjetPorte = data[++i] ? new GroupeObjets(objets[(unsigned char)data[i]]) : 0;
    m_Or     = (unsigned char)(data[++i]);
    m_Or     = (m_Or << 8) + (unsigned char)(data[++i]);
    m_Script = scripts[(unsigned char)(data[++i])];
    m_ElementAttaque = data[++i];
    m_ElementDefense = data[++i];
    return &data[i+1];
}