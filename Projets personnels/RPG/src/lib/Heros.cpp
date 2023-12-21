#include "lib/Heros.h"
// #include <cstdlib> //rand, RAND_MAX

#define MAX_VIE 9999
#define MAX_MAGIE 999

#define COEF_VIE 50
#define COEF_ATKP 3
#define COEF_DEFP 3
#define COEF_MAG 8
#define COEF_ATKM 3
#define COEF_DEFM 3
#define COEF_VIT 3
#define COEF_PRE 3
#define COEF_ESQ 3

Heros::Heros(int id): Personnage(id,"_",0,0,0,0,0,0,0,0,0,0,0,0,0,1,0) {
    SetForce(0);
    SetIntelligence(0);
    SetAgilite(0);
    SetRang(RANG_AVANT);
    SetGarde(false);
    SetEquipement(0,EQUIPEMENT_MAINGAUCHE);
    SetEquipement(0,EQUIPEMENT_MAINDROITE);
    SetEquipement(0,EQUIPEMENT_TETE);
    SetEquipement(0,EQUIPEMENT_CORPS);
    SetEquipement(0,EQUIPEMENT_ACCESSOIRE1);
    SetEquipement(0,EQUIPEMENT_ACCESSOIRE2);
}

/*Heros::Heros(int id, const char* nom, int vie, int magie,\
             int vieMax,   int attaqueP,  int defenseP,\
             int magieMax, int attaqueM,  int defenseM,\
             int vitesse,  int precision, int esquive,\
             unsigned char statut, unsigned int experience, unsigned char niveau,\
             int force, int intelligence, int agilite, bool rang,\
             Objet* maingauche, Objet* maindroite, Objet* tete,\
             Objet* corps, Objet* accessoire1, Objet* accessoire2, unsigned int jauge):\
    Personnage(id,nom,vie,magie,vieMax,attaqueP,defenseP,magieMax,attaqueM,defenseM,\
               vitesse,precision,esquive,statut,experience,niveau,jauge) {
    SetForce(force);
    SetIntelligence(intelligence);
    SetAgilite(agilite);
    SetRang(rang);
    SetGarde(false);
    SetEquipement(maingauche,EQUIPEMENT_MAINGAUCHE);
    SetEquipement(maindroite,EQUIPEMENT_MAINDROITE);
    SetEquipement(tete,EQUIPEMENT_TETE);
    SetEquipement(corps,EQUIPEMENT_CORPS);
    SetEquipement(accessoire1,EQUIPEMENT_ACCESSOIRE1);
    SetEquipement(accessoire2,EQUIPEMENT_ACCESSOIRE2);
}*/

Heros::~Heros() {
}

/*unsigned char Heros::GetOffensif() const {
    unsigned char o = 0;
    if (GetEquipement(EQUIPEMENT_MAINGAUCHE)
    && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_ARME)
        o += ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetRatio();
    if (GetEquipement(EQUIPEMENT_MAINDROITE)
    && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_ARME)
        o += ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetRatio();
    if (GetEquipement(EQUIPEMENT_ACCESSOIRE1)
    && GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetType() == EQUIPABLE_ACCESSOIRE)
        o += ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetRatio();
    else
        o += 8;
    if (GetEquipement(EQUIPEMENT_ACCESSOIRE2)
    && GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetType() == EQUIPABLE_ACCESSOIRE)
        o += ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetRatio();
    else
        o += 8;
    return o;
}*/

unsigned char Heros::GetOffensif() const {
    unsigned char o = 17;
    if (m_Equipement[EQUIPEMENT_MAINGAUCHE]
     && m_Equipement[EQUIPEMENT_MAINGAUCHE]->GetType() == EQUIPABLE_ARME)
        // o += 1+((Equipable*)m_Equipement[EQUIPEMENT_MAINGAUCHE])->GetRatio();
        o += 1+m_Equipement[EQUIPEMENT_MAINGAUCHE]->GetRatio();
    if (m_Equipement[EQUIPEMENT_MAINDROITE]
     && m_Equipement[EQUIPEMENT_MAINDROITE]->GetType() == EQUIPABLE_ARME)
        // o += 1+((Equipable*)m_Equipement[EQUIPEMENT_MAINDROITE])->GetRatio();
        o += 1+m_Equipement[EQUIPEMENT_MAINDROITE]->GetRatio();
    if (m_Equipement[EQUIPEMENT_ACCESSOIRE1]) //EQUIPABLE_ACCESSOIRE ?
        // o += ((Equipable*)m_Equipement[EQUIPEMENT_ACCESSOIRE1])->GetRatio()-7;
        o += m_Equipement[EQUIPEMENT_ACCESSOIRE1]->GetRatio()-7;
    if (m_Equipement[EQUIPEMENT_ACCESSOIRE2]) //EQUIPABLE_ACCESSOIRE ?
        // o += ((Equipable*)m_Equipement[EQUIPEMENT_ACCESSOIRE2])->GetRatio()-7;
        o += m_Equipement[EQUIPEMENT_ACCESSOIRE2]->GetRatio()-7;
    return o;
}

/*unsigned char Heros::GetDefensif() const {
    unsigned char d = 0;
    if (GetEquipement(EQUIPEMENT_MAINGAUCHE)
    && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_BOUCLIER)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetRatio();
    if (GetEquipement(EQUIPEMENT_MAINDROITE)
    && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_BOUCLIER)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetRatio();
    if (GetEquipement(EQUIPEMENT_TETE)
    && GetEquipement(EQUIPEMENT_TETE)->GetType() == EQUIPABLE_CASQUE)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetRatio();
    if (GetEquipement(EQUIPEMENT_CORPS)
    && GetEquipement(EQUIPEMENT_CORPS)->GetType() == EQUIPABLE_ARMURE)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetRatio();
    if (GetEquipement(EQUIPEMENT_ACCESSOIRE1)
    && GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetType() == EQUIPABLE_ACCESSOIRE)
        d += 16-((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetRatio();
    else
        d += 8;
    if (GetEquipement(EQUIPEMENT_ACCESSOIRE2)
    && GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetType() == EQUIPABLE_ACCESSOIRE)
        d += 16-((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetRatio();
    else
        d += 8;
    return d;
}*/

unsigned char Heros::GetDefensif() const {
    unsigned char d = 17;
    if (m_Equipement[EQUIPEMENT_MAINGAUCHE]
     && m_Equipement[EQUIPEMENT_MAINGAUCHE]->GetType() == EQUIPABLE_BOUCLIER)
        // d += 1+((Equipable*)m_Equipement[EQUIPEMENT_MAINGAUCHE])->GetRatio();
        d += 1+m_Equipement[EQUIPEMENT_MAINGAUCHE]->GetRatio();
    if (m_Equipement[EQUIPEMENT_MAINDROITE]
     && m_Equipement[EQUIPEMENT_MAINDROITE]->GetType() == EQUIPABLE_BOUCLIER)
        // d += 1+((Equipable*)m_Equipement[EQUIPEMENT_MAINDROITE])->GetRatio();
        d += 1+m_Equipement[EQUIPEMENT_MAINDROITE]->GetRatio();
    if (m_Equipement[EQUIPEMENT_TETE]) //EQUIPABLE_CASQUE ?
        // d += 1+((Equipable*)m_Equipement[EQUIPEMENT_TETE])->GetRatio();
        d += 1+m_Equipement[EQUIPEMENT_TETE]->GetRatio();
    if (m_Equipement[EQUIPEMENT_CORPS]) //EQUIPABLE_ARMURE ?
        // d += 1+((Equipable*)m_Equipement[EQUIPEMENT_CORPS])->GetRatio();
        d += 1+m_Equipement[EQUIPEMENT_CORPS]->GetRatio();
    if (m_Equipement[EQUIPEMENT_ACCESSOIRE1]) //EQUIPABLE_ACCESSOIRE ?
        // d += 7-((Equipable*)m_Equipement[EQUIPEMENT_ACCESSOIRE1])->GetRatio();
        d += 7-m_Equipement[EQUIPEMENT_ACCESSOIRE1]->GetRatio();
    if (m_Equipement[EQUIPEMENT_ACCESSOIRE2]) //EQUIPABLE_ACCESSOIRE ?
        // d += 7-((Equipable*)m_Equipement[EQUIPEMENT_ACCESSOIRE2])->GetRatio();
        d += 7-m_Equipement[EQUIPEMENT_ACCESSOIRE2]->GetRatio();
    return d;
}

unsigned char Heros::GagnerExperience(int val) {
    unsigned char niveaux = 0;
    ChangerExperience(val);
    while (GetExperience() > 100*GetNiveau()) {
        PasserNiveau();
        ++niveaux;
    }
    return niveaux;
}

// #include <cstdio>

void Heros::PasserNiveau() {
    const int f = CalculerForce(), i = CalculerIntelligence(), a = CalculerAgilite();
    const int o = GetOffensif(), d = GetDefensif(), p = 100-o-d;
    SetNiveau(GetNiveau()+1);

    /*if (GetEquipement(EQUIPEMENT_MAINGAUCHE)
    && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_ARME)
        o += ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetRatio();
    else if (GetEquipement(EQUIPEMENT_MAINGAUCHE)
         && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_BOUCLIER)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetRatio();
    //else {d += 0; o += 0;}
    if (GetEquipement(EQUIPEMENT_MAINDROITE)
    && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_ARME)
        o += ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetRatio();
    else if (GetEquipement(EQUIPEMENT_MAINDROITE)
         && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_BOUCLIER)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetRatio();
    //else {d += 0; o += 0;}
    if (GetEquipement(EQUIPEMENT_TETE)
    && GetEquipement(EQUIPEMENT_TETE)->GetType() == EQUIPABLE_CASQUE)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetRatio();
    //else d += 0;
    if (GetEquipement(EQUIPEMENT_CORPS)
    && GetEquipement(EQUIPEMENT_CORPS)->GetType() == EQUIPABLE_ARMURE)
        d += ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetRatio();
    //else d += 0;
    if (GetEquipement(EQUIPEMENT_ACCESSOIRE1)
    && GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetType() == EQUIPABLE_ACCESSOIRE) {
        o += ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetRatio();
        d += 16-((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetRatio();
    } else {
        o += 8;
        d += 8;
    }
    if (GetEquipement(EQUIPEMENT_ACCESSOIRE2)
    && GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetType() == EQUIPABLE_ACCESSOIRE) {
        o += ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetRatio();
        d += 16-((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetRatio();
    } else {
        o += 8;
        d += 8;
    }
    p = 100-o-d;*/

    // printf("o %d d %d p %d\n", o, d, p);
    // printf("vm %d ap %d dp %d mm %d am %d dm %d vt %d pr %d es %d\n",
    //     GetAttribut(ATTRIBUT_VIE), GetAttribut(ATTRIBUT_ATKP), GetAttribut(ATTRIBUT_DEFP),
    //     GetAttribut(ATTRIBUT_MAG), GetAttribut(ATTRIBUT_ATKM), GetAttribut(ATTRIBUT_DEFM),
    //     GetAttribut(ATTRIBUT_VIT), GetAttribut(ATTRIBUT_PRE ), GetAttribut(ATTRIBUT_ESQ ));
    ChangerAttribut(f*COEF_VIE *p/100, ATTRIBUT_VIE );
    ChangerVie(f*COEF_VIE *p/100);
    ChangerAttribut(f*COEF_ATKP*o/100, ATTRIBUT_ATKP);
    ChangerAttribut(f*COEF_DEFP*d/100, ATTRIBUT_DEFP);
    ChangerAttribut(i*COEF_MAG *p/100, ATTRIBUT_MAG );
    ChangerMagie(i*COEF_MAG *p/100);
    ChangerAttribut(i*COEF_ATKM*o/100, ATTRIBUT_ATKM);
    ChangerAttribut(i*COEF_DEFM*d/100, ATTRIBUT_DEFM);
    ChangerAttribut(a*COEF_VIT *p/100, ATTRIBUT_VIT );
    ChangerAttribut(a*COEF_PRE *o/100, ATTRIBUT_PRE );
    ChangerAttribut(a*COEF_ESQ *d/100, ATTRIBUT_ESQ );
    // printf("vm %d ap %d dp %d mm %d am %d dm %d vt %d pr %d es %d\n",
    //     GetAttribut(ATTRIBUT_VIE), GetAttribut(ATTRIBUT_ATKP), GetAttribut(ATTRIBUT_DEFP),
    //     GetAttribut(ATTRIBUT_MAG), GetAttribut(ATTRIBUT_ATKM), GetAttribut(ATTRIBUT_DEFM),
    //     GetAttribut(ATTRIBUT_VIT), GetAttribut(ATTRIBUT_PRE ), GetAttribut(ATTRIBUT_ESQ ));
}

int Heros::GetForce() const {
    return m_Force;
}

void Heros::SetForce(int val) {
    if (val < 0)
        val = 0;
    m_Force = val;
}

int Heros::GetIntelligence() const {
    return m_Intelligence;
}

void Heros::SetIntelligence(int val) {
    if (val < 0)
        val = 0;
    m_Intelligence = val;
}

int Heros::GetAgilite() const {
    return m_Agilite;
}

void Heros::SetAgilite(int val) {
    if (val < 0)
        val = 0;
    m_Agilite = val;
}

bool Heros::GetRang() const {
    return m_Rang;
}

void Heros::SetRang(bool val) {
    m_Rang = val;
}

void Heros::ChangerRang() {
    m_Rang = !m_Rang;
}

bool Heros::GetGarde() const {
    return m_Garde;
}

void Heros::SetGarde(bool val) {
    m_Garde = val;
}

/*Objet* Heros::GetEquipement(unsigned char id) const {
    // if (id < 0 || id >= NOMBRE_EQUIPEMENTS)
    if (id >= NOMBRE_EQUIPEMENTS)
        return 0;
    return m_Equipement[id];
}*/

Equipable* Heros::GetEquipement(unsigned char id) const {
    if (id >= NOMBRE_EQUIPEMENTS)
        return 0;
    return m_Equipement[id];
}

// int Heros::SetEquipement(Objet *val, int id) {
/*int Heros::SetEquipement(Objet *val, unsigned char id) {
    if (val == 0) {
        m_Equipement[id] = 0;
        return 0;
    }
    switch (id) {
    case EQUIPEMENT_MAINGAUCHE:
    case EQUIPEMENT_MAINDROITE:
        if (val->GetType() == EQUIPABLE_ARME
         || val->GetType() == EQUIPABLE_BOUCLIER) {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    case EQUIPEMENT_TETE:
        if (val->GetType() == EQUIPABLE_CASQUE) {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    case EQUIPEMENT_CORPS:
        if (val->GetType() == EQUIPABLE_ARMURE) {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    case EQUIPEMENT_ACCESSOIRE1:
    case EQUIPEMENT_ACCESSOIRE2:
        if (val->GetType() == EQUIPABLE_ACCESSOIRE) {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    }
    return -1;
}*/

bool Heros::SetEquipement(Equipable *val, unsigned char id) {
    if (val == 0) {
        m_Equipement[id] = 0;
        return true;
    }
    switch (id) {
    case EQUIPEMENT_MAINGAUCHE:
    case EQUIPEMENT_MAINDROITE:
        if (val->GetType() == EQUIPABLE_ARME
         || val->GetType() == EQUIPABLE_BOUCLIER) {
            m_Equipement[id] = val;
            return true;
        }
        break;
    case EQUIPEMENT_TETE:
        if (val->GetType() == EQUIPABLE_CASQUE) {
            m_Equipement[id] = val;
            return true;
        }
        break;
    case EQUIPEMENT_CORPS:
        if (val->GetType() == EQUIPABLE_ARMURE) {
            m_Equipement[id] = val;
            return true;
        }
        break;
    case EQUIPEMENT_ACCESSOIRE1:
    case EQUIPEMENT_ACCESSOIRE2:
        if (val->GetType() == EQUIPABLE_ACCESSOIRE) {
            m_Equipement[id] = val;
            return true;
        }
        break;
    }
    return false;
}

void Heros::SetVieMax(int val) {
    if (val < 1)
        val = 1;
    else if (val > MAX_VIE)
        val = MAX_VIE;
    Personnage::SetAttribut(val, ATTRIBUT_VIE);
}

void Heros::SetMagieMax(int val) {
    if (val < 0)
        val = 0;
    else if (val > MAX_MAGIE)
        val = MAX_MAGIE;
    Personnage::SetAttribut(val, ATTRIBUT_MAG);
}

int Heros::CalculerForce() const {
    return 2;
}

int Heros::CalculerIntelligence() const {
    return 2;
}

int Heros::CalculerAgilite() const {
    return 2;
}

int Heros::GetAttributTotal(unsigned char id) const {
    int val = GetAttribut(id);
    unsigned char i;
    for (i = 0; i < NOMBRE_EQUIPEMENTS; ++i)
        // if (GetEquipement(i))
        //     val += ((Equipable*)GetEquipement(i))->GetAttribut(id);
        if (m_Equipement[i])
            // val += ((Equipable*)m_Equipement[i])->GetAttribut(id);
            val += m_Equipement[i]->GetAttribut(id);
    if ((id==ATTRIBUT_PRE || id==ATTRIBUT_ESQ) && GetRang()==RANG_ARRIERE)
        val /= 2; //prise en compte du rang
    else if (id==ATTRIBUT_DEFP && GetGarde()) // avant ou après équipement ?
        val *= 2;
    return val;
}

int Heros::GetModificateurElementaire(unsigned char id, char element) const {
    int val = GetAttribut(id); //non-élémentaire
    unsigned char i;
    for (i = 0; i < NOMBRE_EQUIPEMENTS; ++i)
        // if (GetEquipement(i))
        //     val += ModificateurElement(((Equipable*)GetEquipement(i))->GetAttribut(id),
        //         element, ((Equipable*)GetEquipement(i))->GetElement());
        if (m_Equipement[i])
            // val += ModificateurElement(((Equipable*)m_Equipement[i])->GetAttribut(id),
            //     element, ((Equipable*)m_Equipement[i])->GetElement());
            val += ModificateurElement(m_Equipement[i]->GetAttribut(id),
                element, m_Equipement[i]->GetElement());
    return val/GetAttributTotal(id);
}

// #include <cstdio>

// void Heros::Attaquer() {
void Heros::Attaquer(unsigned int de, unsigned int max_de) {
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
        const int modif_droite = GetEquipement(EQUIPEMENT_MAINDROITE) ?
            GetCible(0)->GetModificateurElementaire(ATTRIBUT_DEFP,
            // ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetElement()):1;
            GetEquipement(EQUIPEMENT_MAINDROITE)->GetElement()):1;
        const int modif_gauche = GetEquipement(EQUIPEMENT_MAINGAUCHE) ?
            GetCible(0)->GetModificateurElementaire(ATTRIBUT_DEFP,
            // ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetElement()):1;
            GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetElement()):1;

        // printf("Heros::Attaquer modifg %d modifd %d\n", modif_gauche, modif_droite);

        if (GetEquipement(EQUIPEMENT_MAINDROITE)
         && GetEquipement(EQUIPEMENT_MAINGAUCHE)) {
            GetCible(0)->ChangerVie((modif_droite+modif_gauche)*degats/4);
            GetCible(0)->SetMessage((modif_droite+modif_gauche)*degats/4);
        } else if (GetEquipement(EQUIPEMENT_MAINDROITE)) {
            GetCible(0)->ChangerVie(modif_droite*degats/2);
            GetCible(0)->SetMessage(modif_droite*degats/2);
        } else if (GetEquipement(EQUIPEMENT_MAINGAUCHE)) {
            GetCible(0)->ChangerVie(modif_gauche*degats/2);
            GetCible(0)->SetMessage(modif_gauche*degats/2);
        } else {
            GetCible(0)->ChangerVie(degats);
            GetCible(0)->SetMessage(degats);
        }
        // const int degats = -GetAttributTotal(ATTRIBUT_ATKP)
        //                     /GetCible(0)->GetAttributTotal(ATTRIBUT_DEFP);
    } else
        GetCible(0)->SetMessage(0); //TODO valeur spéciale pour "raté" ?
    GetCible(0)->SetTempsMessage(30);
}

/*void Heros::RenduTerrain(char* image, bool marche, char orientation) const {
    image[0] = (char)(GetId() & 255);
    char image[2];
    image[0] = (char)(id & 255);
    switch (orientation) {
        case ORIENTATION_DROITE:
        case ORIENTATION_GAUCHE:
            image[1] = marche ? 5 : 4;
            break;
        case ORIENTATION_HAUT:
            image[1] = marche ? 3 : 2;
            break;
        case ORIENTATION_BAS:
        default:
            image[1] = marche ? 1 : 0;
    }
}*/

void Heros::ActualiserAnimation() {
    SetTempsAnimation(GetTempsAnimation()-1);
    if (GetTempsAnimation() == 0)
        SetAnimation(ACTION_INACTIF);
}

void Heros::RenduCombat(char* image) const {
    image[0] = (char)(GetId() & 255);
    // image[1] = GetMessage() ? 11 : (estEnVie() ? (GetTempsMessage() ? 8 : 6) : 7);
    if (GetMessage()) //Prend un coup
        image[1] = 11;
    else if (estEnVie()) {
        if (GetTempsAnimation()) {
            switch (GetAnimation()) {
            case ACTION_ATTAQUER:
                image[1] = 9;
                break;
            case ACTION_OBJETS:
            case ACTION_CAPACITE:
                image[1] = 10;
                break;
            case ACTION_DEFENSE:
            case ACTION_RANG:
            case ACTION_FUITE:
                image[1] = 8;
                break;
            case ACTION_INACTIF:
            default:
                image[1] = 6;
            }
        // } else if (GetAnimation()) {
        //     SetAnimation(ACTION_INACTIF);
        } else {
            image[1] = GetGarde() ? 8 : (GetVieP() < 33 ? 7 : 6);
        }
    } else
        image[1] = 12;
}

int Heros::Ecrire(char* data) const {
    int i = Personnage::Ecrire(data);
    data[i-1] = ' ';
    ECRIRE_2CHIFFRES(i,data,GetForce());
    data[i++] = ' ';
    ECRIRE_2CHIFFRES(i,data,GetIntelligence());
    data[i++] = ' ';
    ECRIRE_2CHIFFRES(i,data,GetAgilite());
    data[i++] = ' ';
    ECRIRE_BOOLEEN(i,data,GetRang());
    unsigned char j;
    for (j = 0; j < NOMBRE_EQUIPEMENTS; ++j) {
        data[i++] = ' ';
        // if (GetEquipement(j)) {
        if (m_Equipement[j]) {
            // ECRIRE_3CHIFFRES(i,data,GetEquipement(j)->GetId());
            ECRIRE_3CHIFFRES(i,data,m_Equipement[j]->GetId());
        } else
            data[i++] = '0';
    }
    data[i++] = '\0';
    return i;
}

extern Objet* objets[];

void Heros::Lire(int& i, const char* data) {
    Personnage::Lire(i, data);
    int entier;
    LIRE_ENTIER(i,data,entier); SetForce(entier);
    LIRE_ENTIER(i,data,entier); SetIntelligence(entier);
    LIRE_ENTIER(i,data,entier); SetAgilite(entier);
    int booleen;
    LIRE_BOOLEEN(i,data,booleen); SetRang(booleen);
    unsigned char j;
    for (j = 0; j < NOMBRE_EQUIPEMENTS; ++j) {
        // LIRE_ENTIER(i,data,entier); SetEquipement(objets[entier],j);
        LIRE_ENTIER(i,data,entier); SetEquipement((Equipable*)(objets[entier]),j);
    }
}

unsigned int Heros::TailleD() const {
    return Personnage::TailleD()+4+NOMBRE_EQUIPEMENTS;
}

char* Heros::EcrireD(char* data) const {
    data = Personnage::EcrireD(data);
    unsigned int i = 0;
    data[  i] = m_Force;
    data[++i] = m_Intelligence;
    data[++i] = m_Agilite;
    data[++i] = m_Rang;
    unsigned int j;
    for (j = 0; j < NOMBRE_EQUIPEMENTS; ++j)
        data[++i] = m_Equipement[j] ? m_Equipement[j]->GetId() : 0;
    return &data[i+1];
}

const char* Heros::LireD(const char* data) {
    data = Personnage::LireD(data);
    unsigned int i = 0;
    m_Force        = data[  i];
    m_Intelligence = data[++i];
    m_Agilite      = data[++i];
    m_Rang         = data[++i];
    unsigned int j;
    for (j = 0; j < NOMBRE_EQUIPEMENTS; ++j)
        // m_Equipement[j] = objets[(unsigned char)(data[++i])];
        m_Equipement[j] = (Equipable*)(objets[(unsigned char)(data[++i])]);
    return &data[i+1];
}