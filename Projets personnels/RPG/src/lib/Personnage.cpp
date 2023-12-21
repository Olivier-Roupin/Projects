#include "lib/Personnage.h"
// #include <cstdlib> //rand, RAND_MAX

#define MAX_NIVEAU 99

Personnage::Personnage(int id, const char* nom, int vie, int magie,\
                       int vieMax,   int attaqueP,  int defenseP,\
                       int magieMax, int attaqueM,  int defenseM,\
                       int vitesse,  int precision, int esquive,\
                       unsigned char statut, unsigned int experience,\
                       unsigned char niveau, unsigned int jauge) {
    SetId(id);
    SetNom(nom);

    SetAttribut(vieMax,    ATTRIBUT_VIE);
    SetAttribut(attaqueP,  ATTRIBUT_ATKP);
    SetAttribut(defenseP,  ATTRIBUT_DEFP);
    SetAttribut(magieMax,  ATTRIBUT_MAG);
    SetAttribut(attaqueM,  ATTRIBUT_ATKM);
    SetAttribut(defenseM,  ATTRIBUT_DEFM);
    SetAttribut(vitesse,   ATTRIBUT_VIT);
    SetAttribut(precision, ATTRIBUT_PRE);
    SetAttribut(esquive,   ATTRIBUT_ESQ);

    SetStatut(statut);
    SetExperience(experience);
    SetNiveau(niveau);
    SetJauge(jauge);

    SetVie(vie); // doit être après vieMax et magieMax sinon == 0
    SetMagie(magie);

    unsigned int i;
    for (i = 0; i < MAX_SORTS; i++)
        m_Sorts[i] = 0;
    for (i = 0; i < MAX_APTITUDES; i++)
        m_Aptitudes[i] = 0;
    for (i = 0; i < MAX_ALTERATIONS; i++)
        m_Alterations[i] = 0;

    SetAction(ACTION_INACTIF);
    m_Objet = 0;
    m_Capacite = 0;
    SetNombreCibles(0);
    m_Cibles = 0;
    SetTempsMessage(0);
    SetMessage(0);
    SetTempsAnimation(0);
    SetAnimation(0);
}

Personnage::Personnage(const Personnage& other){
    SetId(other.GetId());
    SetNom(other.GetNom());

    unsigned int i;
    for (i = 0; i < NOMBRE_ATTRIBUTS; i++)
        SetAttribut(other.GetAttribut(i), i);

    SetStatut(other.GetStatut());
    SetExperience(other.GetExperience());
    SetNiveau(other.GetNiveau());
    SetJauge(other.GetJauge());

    SetVie(other.GetVie());
    SetMagie(other.GetMagie());

    for (i = 0; i < MAX_SORTS; i++)
        m_Sorts[i] = 0;
    for (i = 0; i < MAX_APTITUDES; i++)
        m_Aptitudes[i] = 0;
    for (i = 0; i < MAX_ALTERATIONS; i++)
        m_Alterations[i] = 0;

    //*this = other;
    SetAction(ACTION_INACTIF);
    m_Objet = 0;
    m_Capacite = 0;
    SetNombreCibles(0);
    m_Cibles = 0;
    SetTempsMessage(0);
    SetMessage(0);
    SetTempsAnimation(0);
    SetAnimation(0);
}

Personnage::~Personnage() {
    if (m_Cibles)
        delete[] m_Cibles;
}

int Personnage::GetId() const {
    return m_Id;
}

void Personnage::SetId(int val) {
    if (val < 0)
        val = 0;
    m_Id = val;
}

const char* Personnage::GetNom() const {
    return m_Nom;
}

void Personnage::SetNom(const char* val) {
    for (int i = 0; i < TAILLE_NOM_PERSONNAGE; i++) {
        m_Nom[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Nom[TAILLE_NOM_PERSONNAGE] = '\0';
}

int Personnage::GetVie() const {
    return m_Vie;
}

void Personnage::SetVie(int val) {
    if (val < 0)
        val = 0;
    else if (val > m_Attributs[ATTRIBUT_VIE])
        val = m_Attributs[ATTRIBUT_VIE];
    m_Vie = val;
}

void Personnage::ChangerVie(int val) {
    SetVie(GetVie()+val);
}

int Personnage::GetVieP() const {
    return 100*GetVie()/GetAttribut(ATTRIBUT_VIE);
}

void Personnage::SetVieP(int val) {
    if (val < 0)
        val = 0;
    else if (val > 100)
        val = 100;
    SetVie(val*GetAttribut(ATTRIBUT_VIE)/100);
}

int Personnage::ChangerVieP(int val) {
    if (val < -100)
        val = -100;
    else if (val > 100)
        val = 100;
    val = val*GetVie()/100;
    ChangerVie(val);
    return val;
}

bool Personnage::estEnVie() const {
    return GetVie() > 0;
}

int Personnage::GetMagie() const {
    return m_Magie;
}

void Personnage::SetMagie(int val) {
    if (val < 0)
        val = 0;
    else if (val > m_Attributs[ATTRIBUT_MAG])
        val = m_Attributs[ATTRIBUT_MAG];
    m_Magie = val;
}

void Personnage::ChangerMagie(int val) {
    SetMagie(GetMagie()+val);
}

int Personnage::GetMagieP() const {
    return 100*GetMagie()/GetAttribut(ATTRIBUT_MAG);
}

void Personnage::SetMagieP(int val) {
    if (val < 0)
        val = 0;
    else if (val > 100)
        val = 100;
    SetMagie(val*GetAttribut(ATTRIBUT_MAG)/100);
}

void Personnage::ChangerMagieP(int val) {
    if (val < -100)
        val = -100;
    else if (val > 100)
        val = 100;
    ChangerMagie(val*GetMagie()/100);
}

int Personnage::GetAttribut(unsigned char id) const {
    // if (id < 0 || id >= NOMBRE_ATTRIBUTS)
    if (id >= NOMBRE_ATTRIBUTS)
        return 0;
    return m_Attributs[id];
}

void Personnage::SetAttribut(int val, unsigned char id) {
    if (val < 0)
        val = 0;
    // if (id >= 0 && id < NOMBRE_ATTRIBUTS)
    if (id < NOMBRE_ATTRIBUTS)
        m_Attributs[id] = val;
}

void Personnage::ChangerAttribut(int val, unsigned char id) {
    SetAttribut(GetAttribut(id)+val, id);
}

unsigned char Personnage::GetStatut() const {
    return m_Statut;
}

void Personnage::SetStatut(unsigned char val) {
    m_Statut = val;
}

unsigned int Personnage::GetExperience() const {
    return m_Experience;
}

void Personnage::SetExperience(int val) {
    if (val < 0)
        val = 0;
    m_Experience = val;
}

void Personnage::ChangerExperience(int val) {
    SetExperience(m_Experience+val);
}

unsigned char Personnage::GetNiveau() const {
    return m_Niveau;
}

void Personnage::SetNiveau(unsigned char val) {
    if (val < 1)
        val = 1;
    else if (val > MAX_NIVEAU)
        val = MAX_NIVEAU;
    m_Niveau = val;
}

unsigned int Personnage::GetJauge() const {
    return m_Jauge;
}

void Personnage::SetJauge(unsigned int val) {
    // if (val < 0)
    //     val = 0;
    // else if (val > TAILLE_JAUGE)
    if (val > TAILLE_JAUGE)
        val = TAILLE_JAUGE;
    m_Jauge = val;
}

void Personnage::ActualiserJauge() {
    // SetJauge(GetJauge()+GetAttribut(ATTRIBUT_VIT)*VITESSE_COMBAT);
    SetJauge(m_Jauge+m_Attributs[ATTRIBUT_VIT]*VITESSE_COMBAT);
}

void Personnage::ViderJauge() {
    SetJauge(0);
}

bool Personnage::Jauge_estpleine() const {
    // return (GetJauge() == TAILLE_JAUGE);
    return (m_Jauge == TAILLE_JAUGE);
}

Capacite* Personnage::GetSorts(unsigned char id) const {
    // if (id < 0 || id >= MAX_SORTS)
    if (id >= MAX_SORTS)
        return 0;
    return m_Sorts[id];
}

int Personnage::SetSorts(Capacite* val, unsigned char id) {
    if (val == 0) {
        m_Sorts[id] = 0;
        return 0;
    }
    m_Sorts[id] = val;
    return 0;
}

int Personnage::AjouterSorts(Capacite* val) {
    if (GetSorts(val->GetId() - 1))
        return -1;
    SetSorts(val, val->GetId() - 1);
    return 0;
}

Capacite* Personnage::GetAptitudes(unsigned char id) const {
    // if (id < 0 || id >= MAX_APTITUDES)
    if (id >= MAX_APTITUDES)
        return 0;
    return m_Aptitudes[id];
}

int Personnage::SetAptitudes(Capacite* val, unsigned char id) {
    if (val == 0) {
        m_Aptitudes[id] = 0;
        return 0;
    }
    m_Aptitudes[id] = val;
    return 0;
}

int Personnage::AjouterAptitudes(Capacite* val) {
    if (GetAptitudes(val->GetId() - 1))
        return -1;
    SetAptitudes(val, val->GetId() - 1);
    return 0;
}

Alteration* Personnage::GetAlterations(unsigned char id) const {
    // if (id < 0 || id >= MAX_ALTERATIONS)
    if (id >= MAX_ALTERATIONS)
        return 0;
    return m_Alterations[id];
}

void Personnage::SetAlterations(Alteration* val, unsigned char id) {
    //On copie l'alteration pour qu'elles ne soient pas toutes liées par le même curseur de script
    delete m_Alterations[id];
    if (val == 0)
        m_Alterations[id] = 0;
    else
        m_Alterations[id] = new Alteration(*val);
}

int Personnage::ChercherAlteration(Alteration *val) const {
    unsigned char i = 0;
    while (i < MAX_ALTERATIONS && GetAlterations(i) && GetAlterations(i)->GetId() != val->GetId()) //à séparer ?
        ++i;
    if (i >= MAX_ALTERATIONS)
        return -1;
    return i;
}

int Personnage::ChercherLibre(unsigned char priorite) const {
    unsigned char i = 0;
    //On remplace une alteration qui a la même priorité que la nouvelle
    while (i < MAX_ALTERATIONS && GetAlterations(i) && GetAlterations(i)->GetPriorite() > priorite) //à séparer ?
        ++i;
    if (i >= MAX_ALTERATIONS)
        return -1;
    return i;
}

int Personnage::AjouterAlteration(Alteration* val) {
    int i = ChercherAlteration(val);
    if (i != -1) //On reset l'altération si elle est déja présente
        SetAlterations(val, i);
    else {
        i = ChercherLibre(val->GetPriorite());
        if (i != -1)
            SetAlterations(val, i);
        else
            return -1;
    }
    return 0;
}

int Personnage::RetirerAlteration(Alteration* val) {
    int i = ChercherAlteration(val);
    if (i != -1) {
        SetAlterations(0, i);
        return 0;
    }
    return -1;
}

void Personnage::RetirerAlterations() {
    unsigned char i;
    for (i = 0; i < MAX_ALTERATIONS; ++i)
        if (GetAlterations(i))
            SetAlterations(0, i);
}

bool Personnage::estOccupe() const {
    return !Jauge_estpleine() || GetAction() != ACTION_INACTIF || !estEnVie();
}

char Personnage::GetAction() const {
    return m_Action;
}

void Personnage::SetAction(char val) {
    m_Action = val;
}

Objet* Personnage::GetObjet() const {
    return m_Objet;
}

void Personnage::SetObjet(Objet* val) {
    m_Objet = val;
}

Capacite* Personnage::GetCapacite() const {
    return m_Capacite;
}

void Personnage::SetCapacite(Capacite* val) {
    m_Capacite = val;
}

unsigned char Personnage::GetNombreCibles() const {
    return m_NombreCibles;
}

void Personnage::SetNombreCibles(unsigned char val) {
    m_NombreCibles = val;
}

Personnage** Personnage::GetCibles() const {
    return m_Cibles;
}

Personnage* Personnage::GetCible(unsigned char id) const {
    // if (id < 0 || id >= GetNombreCibles())
    if (id >= m_NombreCibles)
        return 0;
    return m_Cibles[id];
}

void Personnage::SetCibles(Personnage** val) {
    if (m_Cibles)
        delete[] m_Cibles;
    m_Cibles = val;
}

/*float Personnage::Probabilite_touche() const {
    int esquive = GetCible(0)->GetAttribut(ATTRIBUT_ESQ);
    float pi = exp(-esquive);
    float P = pi;
    int i;
    for (i = 1; i <= GetAttribut(ATTRIBUT_PRE); i++) {
        pi*=esquive/(float)i;
        P+=pi;
    }
    return P;
}*/

const unsigned int valeurs[60] = {
    1,1,2,3,5,8,12,19,27,40,56,79,108,145,192,250,321,405,504,618,747,891,1049,
    1219,1400,1589,1784,1982,2180,2375,2564,2746,2917,3077,3224,3357,3476,3581,
    3672,3751,3818,3875,3921,3959,3990,4015,4035,4050,4062,4071,4078,4083,4087,
    4089,4091,4093,4094,4094,4095,4095};

// #include <cstdio>

unsigned int Personnage::Probabilite_touche() const {
    if (GetCible(0) == 0)
        return 0;
    const int esquive = GetCible(0)->GetAttributTotal(ATTRIBUT_ESQ);
    const int precision = GetAttributTotal(ATTRIBUT_PRE);

    const int pre_inf = (esquive-11)*(64-0)/(100-11)+0;
    if (precision < pre_inf)
        return 0;

    const int pre_sup = (esquive-4)*(100-13)/(68-4)+13;
    if (precision > pre_sup)
        return 4096;

    // printf("precision: %d/%d/%d\n", pre_inf, precision, pre_sup);
    // fflush(stdout);

    return valeurs[(precision-pre_inf)*59/pre_sup];
}

int Personnage::GetAttributTotal(unsigned char id) const {
    return GetAttribut(id);
}

int Personnage::GetModificateurElementaire(unsigned char id, char element) const {
    if (element < ELEMENT_NEUTRE || element >= NOMBRE_ELEMENTS)
        return 0;
    if (id == ATTRIBUT_DEFP || id == ATTRIBUT_DEFM) //ATTRIBUT_ESQ
        return 1;
    return 1;
}

/*void Personnage::Attaquer() const {
    //if (rand() < RAND_MAX*Probabilite_touche())
    if (rand() < RAND_MAX/4096*Probabilite_touche())
        GetCible(0)->ChangerVie(-GetAttributTotal(ATTRIBUT_ATKP)
                            /GetCible(0)->GetAttributTotal(ATTRIBUT_DEFP));
}*/

// void Personnage::Attaquer() {
void Personnage::Attaquer(unsigned int de, unsigned int max_de) {
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
        // const int degats = -GetAttributTotal(ATTRIBUT_ATKP)
        //                     /GetCible(0)->GetAttributTotal(ATTRIBUT_DEFP);
        GetCible(0)->ChangerVie(degats);
        GetCible(0)->SetMessage(degats);
    } else
        GetCible(0)->SetMessage(0); //TODO valeur spéciale pour "raté" ?
    GetCible(0)->SetTempsMessage(30);
}

/*int Personnage::Attaquer() const {
    //if (rand() < RAND_MAX*Probabilite_touche())
    if (rand() < RAND_MAX/4096*Probabilite_touche()) {
        const int degats = -GetAttributTotal(ATTRIBUT_ATKP)
                            /GetCible(0)->GetAttributTotal(ATTRIBUT_DEFP);
        GetCible(0)->ChangerVie(degats);
        return degats;
    }
    return 0; //TODO: valeur spéciale pour "raté" ?
}*/

int Personnage::GetTempsMessage() const {
    return m_TempsMessage;
}

void Personnage::SetTempsMessage(int val) {
    if (val < 0)
        val = 0;
    m_TempsMessage = val;
}

void Personnage::ActualiserMessage() {
    SetTempsMessage(GetTempsMessage()-1);
    // utile ?
    if (GetTempsMessage() == 0)
        Personnage::SetMessage(0); // éviter le reset dans Heros
}

int Personnage::GetMessage() const {
    return m_Message;
}

void Personnage::SetMessage(int val) {
    m_Message = val;
}

int Personnage::GetTempsAnimation() const {
    return m_TempsAnimation;
}

void Personnage::SetTempsAnimation(int val) {
    if (val < 0)
        val = 0;
    m_TempsAnimation = val;
}

void Personnage::ActualiserAnimation() {
    SetTempsAnimation(GetTempsAnimation()-1);
    // utile ?
    if (GetTempsAnimation() == 0)
        SetAnimation(0);
}

char Personnage::GetAnimation() const {
    return m_Animation;
}

void Personnage::SetAnimation(char val) {
    m_Animation = val;
}

int Personnage::Ecrire(char* data) const {
    int i = 0, j;
    ECRIRE_CHAINE(i,j,data,m_Nom,TAILLE_NOM_PERSONNAGE);
    data[i++] = ' ';
    ECRIRE_3CHIFFRES(i,data,GetVie());
    data[i++] = ' ';
    ECRIRE_3CHIFFRES(i,data,GetMagie());
    data[i++] = ' ';
    for (j = 0; j < NOMBRE_ATTRIBUTS; j++) {
        ECRIRE_3CHIFFRES(i,data,m_Attributs[j]);
        data[i++] = ' ';
    }
    ECRIRE_CHIFFRE(i,data,GetStatut());
    data[i++] = ' ';
    ECRIRE_3CHIFFRES(i,data,GetExperience());
    data[i++] = ' ';
    ECRIRE_2CHIFFRES(i,data,GetNiveau());
    data[i++] = '\0';
    return i;
}

void Personnage::Lire(int& i, const char* data) {
    unsigned int j = 0;
    char nom[TAILLE_NOM_PERSONNAGE+1];
    LIRE_CHAINE(i,j,data,nom,TAILLE_NOM_PERSONNAGE); SetNom(nom);
    int entier;
    int vie;
    LIRE_ENTIER(i,data,vie);
    int magie;
    LIRE_ENTIER(i,data,magie);
    for (j = 0; j < NOMBRE_ATTRIBUTS; j++) {
        LIRE_ENTIER(i,data,entier); SetAttribut(entier, j);
    }
    SetVie(vie);
    SetMagie(magie);
    LIRE_ENTIER(i,data,entier); SetStatut((unsigned char)(entier&255));
    LIRE_ENTIER(i,data,entier); SetExperience(entier);
    LIRE_ENTIER(i,data,entier); SetNiveau(entier);
}

unsigned int Personnage::TailleD() const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_PERSONNAGE; ++i)
        if (m_Nom[i] == '\0')
            break;
    return i+2+NOMBRE_ATTRIBUTS+3;
    // return TAILLE_NOM_PERSONNAGE+2+NOMBRE_ATTRIBUTS+3;
}

char* Personnage::EcrireD(char* data) const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_PERSONNAGE; ++i) {
        data[i] = m_Nom[i]; //0 est écrit s'il est présent
        if (m_Nom[i] == '\0')
            break;
    }
    if (i == TAILLE_NOM_PERSONNAGE) --i;
    
    data[++i] = (unsigned char)((m_Vie   >> 8) & 255);
    data[++i] = (unsigned char)( m_Vie   & 255);
    data[++i] = (unsigned char)((m_Magie >> 8) & 255);
    data[++i] = (unsigned char)( m_Magie & 255);
    unsigned int j;
    for (j = 0; j < NOMBRE_ATTRIBUTS; ++j) {
        if (j == ATTRIBUT_VIE || j == ATTRIBUT_MAG) // écrire un second octet
            data[++i] = (unsigned char)((m_Attributs[j] >> 8) & 255);
        data[++i] = (unsigned char)(m_Attributs[j] & 255);
    }
    data[++i] = m_Statut;
    data[++i] = m_Experience;
    data[++i] = m_Niveau;
    return &data[i+1];
}

const char* Personnage::LireD(const char* data) {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_PERSONNAGE; ++i) {
        if (data[i] == '\0')
            break;
        m_Nom[i] = data[i];
    }
    unsigned int j;
    for (j = i; j < TAILLE_NOM_PERSONNAGE+1; ++j) // sécurité
        m_Nom[j] = '\0';

    if (i == TAILLE_NOM_PERSONNAGE) --i;

    m_Vie        = (unsigned char)(data[++i]);
    m_Vie        = (m_Vie   << 8) + (unsigned char)(data[++i]);
    m_Magie      = (unsigned char)(data[++i]);
    m_Magie      = (m_Magie << 8) + (unsigned char)(data[++i]);
    for (j = 0; j < NOMBRE_ATTRIBUTS; ++j) {
        m_Attributs[j] = (unsigned char)(data[++i]);
        if (j == ATTRIBUT_VIE || j == ATTRIBUT_MAG) // lire un second octet
            m_Attributs[j] = (m_Attributs[j] << 8) + (unsigned char)(data[++i]);
    }
    m_Statut     = (unsigned char)(data[++i]);
    m_Experience = (unsigned char)(data[++i]);
    m_Niveau     = (unsigned char)(data[++i]);
    return &data[i+1];
}