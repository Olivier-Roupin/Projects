#include "Heros.h"

using namespace std;

Heros::Heros(int Id, string Nom, int Vie, int Magie,\
             int VieMax, int AttaqueP, int DefenseP,\
             int MagieMax, int AttaqueM, int DefenseM,\
             int Vitesse, int Precision, int Esquive,\
             int Statut, int Experience, int Niveau, int Jauge,\
             int Force, int Intelligence, int Agilite, bool Rang) :\
    Personnage(Id,Nom,Vie,Magie,VieMax,AttaqueP,DefenseP,MagieMax,AttaqueM,DefenseM,\
               Vitesse,Precision,Esquive,Statut,Experience,Niveau,Jauge)
{
    SetForce(Force);
    SetIntelligence(Intelligence);
    SetAgilite(Agilite);
    SetRang(Rang);
    for(int i = 0; i < NOMBRE_EQUIPEMENTS; ++i)
    {
        m_Equipement[i] = 0;
    }
}

Heros::Heros(int Id, string Nom, int Vie, int Magie,\
             int VieMax, int AttaqueP, int DefenseP,\
             int MagieMax, int AttaqueM, int DefenseM,\
             int Vitesse, int Precision, int Esquive,\
             int Statut, int Experience, int Niveau,\
             int Force, int Intelligence, int Agilite, bool Rang,\
             Objet* Maingauche, Objet* Maindroite, Objet* Tete,\
             Objet* Corps, Objet* Accessoire1, Objet* Accessoire2, int Jauge) :\
    Personnage(Id,Nom,Vie,Magie,VieMax,AttaqueP,DefenseP,MagieMax,AttaqueM,DefenseM,\
               Vitesse,Precision,Esquive,Statut,Experience,Niveau,Jauge)
{
    SetForce(Force);
    SetIntelligence(Intelligence);
    SetAgilite(Agilite);
    SetRang(Rang);
    SetEquipement(Maingauche,EQUIPEMENT_MAINGAUCHE);
    SetEquipement(Maindroite,EQUIPEMENT_MAINDROITE);
    SetEquipement(Tete,EQUIPEMENT_TETE);
    SetEquipement(Corps,EQUIPEMENT_CORPS);
    SetEquipement(Accessoire1,EQUIPEMENT_ACCESSOIRE1);
    SetEquipement(Accessoire2,EQUIPEMENT_ACCESSOIRE2);
}

Heros::~Heros()
{
    //dtor
}

/*
void Heros::PasserNiveau()
{
    int f(0), i(0), a(0);
    int fo(1), io(1), ao(1);
    int fd(1), id(1), ad(1);
    SetNiveau(GetNiveau()+1);
    f = CalculerOffensif();
    i = CalculerIntelligence();
    a = CalculerAgilite();
    if(GetEquipement(EQUIPEMENT_MAINGAUCHE) && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_ARME)
    {
        fo *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetOffensif();
        io *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetIntelligence();
        ao *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_ARME)
    {
        fo *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetOffensif();
        io *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetIntelligence();
        ao *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_BOUCLIER)
    {
        fd *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetOffensif();
        id *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetIntelligence();
        ad *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_TETE) && GetEquipement(EQUIPEMENT_TETE)->GetType() == EQUIPABLE_CASQUE)
    {
        fd *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetOffensif();
        id *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetIntelligence();
        ad *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_CORPS) && GetEquipement(EQUIPEMENT_CORPS)->GetType() == EQUIPABLE_ARMURE)
    {
        fd *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetOffensif();
        id *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetIntelligence();
        ad *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetAgilite();
    }
    ChangerVieMax(f*COEF_VIE*(1-fo/(fo+io+ao)-fd/(fd+id+ad)));
    ChangerAttaqueP(f*COEF_ATKP*(fo/(fo+io+ao)));
    ChangerDefenseP(f*COEF_DEFP*(fd/(fd+id+ad)));
    ChangerMagieMax(i*COEF_MAG*(1-io/(fo+io+ao)-id/(fd+id+ad)));
    ChangerAttaqueM(i*COEF_ATKM*(io/(fo+io+ao)));
    ChangerDefenseM(i*COEF_DEFM*(id/(fd+id+ad)));
    ChangerVitesse(a*COEF_VIT*(1-(1-fo/(fo+io+ao)-io/(fo+io+ao))-(1-fd/(fd+id+ad)-id/(fd+id+ad))));
    ChangerPrecision(a*COEF_PRE*(1-fo/(fo+io+ao)-io/(fo+io+ao)));
    ChangerEsquive(a*COEF_ESQ*(1-fd/(fd+id+ad)-id/(fd+id+ad)));
}
*/
int Heros::GetForce()
{
    if(this == 0)
        return 0;
    return m_Force;
}

void Heros::SetForce(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Force = val;
}

int Heros::GetIntelligence()
{
    if(this == 0)
        return 0;
    return m_Intelligence;
}

void Heros::SetIntelligence(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Intelligence = val;
}

int Heros::GetAgilite()
{
    if(this == 0)
        return 0;
    return m_Agilite;
}

void Heros::SetAgilite(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    m_Agilite = val;
}

bool Heros::GetRang() const
{
    if(this == 0)
        return false;
    return m_Rang;
}

void Heros::SetRang(bool val)
{
    m_Rang = val;
}

void Heros::ChangerRang()
{
    m_Rang = not(m_Rang);
}

bool Heros::GetGarde() const
{
    if(this == 0)
        return 0;
    return m_Garde;
}
void Heros::SetGarde(bool val)
{
    m_Garde = val;
}

Objet* Heros::GetEquipement(int id) const
{
    if(this == 0)
        return 0;
    return m_Equipement[id];
}

int Heros::SetEquipement(Objet *val, int id)
{
    if(val == 0)
    {
        m_Equipement[id] = 0;
        return 0;
    }
    switch(id)
    {
    case EQUIPEMENT_MAINGAUCHE:
    case EQUIPEMENT_MAINDROITE:
    {
        if(val->GetType() == EQUIPABLE_ARME || val->GetType() == EQUIPABLE_BOUCLIER)
        {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    }
    case EQUIPEMENT_TETE:
    {
        if(val->GetType() == EQUIPABLE_CASQUE)
        {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    }
    case EQUIPEMENT_CORPS:
    {
        if(val->GetType() == EQUIPABLE_ARMURE)
        {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    }
    case EQUIPEMENT_ACCESSOIRE1:
    case EQUIPEMENT_ACCESSOIRE2:
    {
        if(val->GetType() == EQUIPABLE_ACCESSOIRE)
        {
            m_Equipement[id] = val;
            return 0;
        }
        break;
    }
    }
    return -1;
}

void Heros::SetVieMax(int val)
{
    if(val < 1)
    {
        val = 1;
    }
    else if(val > MAX_VIE)
    {
        val = MAX_VIE;
    }
    Personnage::SetVieMax(val);
}

void Heros::SetMagieMax(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > MAX_MAGIE)
    {
        val = MAX_MAGIE;
    }
    Personnage::SetMagieMax(val);
}

/*
int Heros::CalculerOffensif() const
{
    return 1;
}

int Heros::CalculerIntelligence() const
{
    return 1;
}

int Heros::CalculerAgilite() const
{
    return 1;
}

int Heros::CalculerNormeOffensif() const
{
    int f(1), i(1), a(1);
    if(GetEquipement(EQUIPEMENT_MAINGAUCHE) && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_ARME)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetOffensif();
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetIntelligence();
        a *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_ARME)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetOffensif();
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetIntelligence();
        a *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetAgilite();
    }
    return f + i + a;
}

int Heros::CalculerNormeDefensif() const
{
    int f(1), i(1), a(1);
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_BOUCLIER)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetOffensif();
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetIntelligence();
        a *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_TETE) && GetEquipement(EQUIPEMENT_TETE)->GetType() == EQUIPABLE_CASQUE)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetOffensif();
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetIntelligence();
        a *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetAgilite();
    }
    if(GetEquipement(EQUIPEMENT_CORPS) && GetEquipement(EQUIPEMENT_CORPS)->GetType() == EQUIPABLE_ARMURE)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetOffensif();
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetIntelligence();
        a *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetAgilite();
    }
    return f + i + a;
}

int Heros::CalculerVieMaxP() const
{
    return 100 - CalculerAttaquePP() - CalculerDefensePP();
}

int Heros::CalculerAttaquePP() const
{
    int f(1);
    if(GetEquipement(EQUIPEMENT_MAINGAUCHE) && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_ARME)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetOffensif();
    }
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_ARME)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetOffensif();
    }
    return 100*f/CalculerNormeOffensif();
}

int Heros::CalculerDefensePP() const
{
    int f(1);
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_BOUCLIER)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetOffensif();
    }
    if(GetEquipement(EQUIPEMENT_TETE) && GetEquipement(EQUIPEMENT_TETE)->GetType() == EQUIPABLE_CASQUE)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetOffensif();
    }
    if(GetEquipement(EQUIPEMENT_CORPS) && GetEquipement(EQUIPEMENT_CORPS)->GetType() == EQUIPABLE_ARMURE)
    {
        f *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetOffensif();
    }
    return 100*f/CalculerNormeDefensif();
}

int Heros::CalculerMagieMaxP() const
{
    return 100 - CalculerAttaqueMP() - CalculerDefenseMP();
}

int Heros::CalculerAttaqueMP() const
{
    int i(1);
    if(GetEquipement(EQUIPEMENT_MAINGAUCHE) && GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetType() == EQUIPABLE_ARME)
    {
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetIntelligence();
    }
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_ARME)
    {
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetIntelligence();
    }
    return 100*i/CalculerNormeOffensif();
}

int Heros::CalculerDefenseMP() const
{
    int i(1);
    if(GetEquipement(EQUIPEMENT_MAINDROITE) && GetEquipement(EQUIPEMENT_MAINDROITE)->GetType() == EQUIPABLE_BOUCLIER)
    {
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetIntelligence();
    }
    if(GetEquipement(EQUIPEMENT_TETE) && GetEquipement(EQUIPEMENT_TETE)->GetType() == EQUIPABLE_CASQUE)
    {
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetIntelligence();
    }
    if(GetEquipement(EQUIPEMENT_CORPS) && GetEquipement(EQUIPEMENT_CORPS)->GetType() == EQUIPABLE_ARMURE)
    {
        i *= ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetIntelligence();
    }
    return 100*i/CalculerNormeDefensif();
}

int Heros::CalculerVitesseP() const
{
    return 100 - CalculerPrecisionP() - CalculerEsquiveP();
}

int Heros::CalculerPrecisionP() const
{
    return 100 - CalculerAttaquePP() - CalculerAttaqueMP();
}

int Heros::CalculerEsquiveP() const
{
    return 100 - CalculerDefensePP() - CalculerDefenseMP();
}

int Heros::CalculerVieMax(int force) const
{
    return force*CalculerVieMaxP();
}

int Heros::CalculerAttaqueP(int force) const
{
    return force/100*CalculerAttaquePP();
}

int Heros::CalculerDefenseP(int force) const
{
    return force/100*CalculerDefensePP();
}

int Heros::CalculerMagieMax(int intelligence) const
{
    return intelligence/10*CalculerMagieMaxP();
}

int Heros::CalculerAttaqueM(int intelligence) const
{
    return intelligence/100*CalculerAttaqueMP();
}

int Heros::CalculerDefenseM(int intelligence) const
{
    return intelligence/100*CalculerDefenseMP();
}

int Heros::CalculerVitesse(int agilite) const
{
    return agilite/100*CalculerVitesseP();
}

int Heros::CalculerPrecision(int agilite) const
{
    return agilite/100*CalculerPrecisionP();
}

int Heros::CalculerEsquive(int agilite) const
{
    return agilite/100*CalculerEsquiveP();
}
*/
int Heros::GetVieMaxTotal() const
{
    if(this == 0)
        return 0;
    return GetVieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetVieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetVieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetVieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetVieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetVieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetVieMax();
}

int Heros::GetAttaquePTotal() const
{
    if(this == 0)
        return 0;
    return GetAttaqueP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetAttaqueP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetAttaqueP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetAttaqueP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetAttaqueP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetAttaqueP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetAttaqueP();
}

int Heros::GetDefensePTotal() const
{
    if(this == 0)
        return 0;
    return GetDefenseP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetDefenseP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetDefenseP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetDefenseP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetDefenseP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetDefenseP()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetDefenseP(); //prendre en compte position défensive
}

int Heros::GetMagieMaxTotal() const
{
    if(this == 0)
        return 0;
    return GetMagieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetMagieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetMagieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetMagieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetMagieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetMagieMax()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetMagieMax();
}

int Heros::GetAttaqueMTotal() const
{
    if(this == 0)
        return 0;
    return GetAttaqueM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetAttaqueM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetAttaqueM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetAttaqueM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetAttaqueM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetAttaqueM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetAttaqueM();
}

int Heros::GetDefenseMTotal() const
{
    if(this == 0)
        return 0;
    return GetDefenseM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetDefenseM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetDefenseM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetDefenseM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetDefenseM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetDefenseM()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetDefenseM();
}

int Heros::GetVitesseTotal() const
{
    if(this == 0)
        return 0;
    return GetVitesse()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetVitesse()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetVitesse()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetVitesse()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetVitesse()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetVitesse()+\
           ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetVitesse();
}

int Heros::GetPrecisionTotal() const
{
    if(this == 0)
        return 0;
    return (GetPrecision()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetPrecision()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetPrecision()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetPrecision()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetPrecision()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetPrecision()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetPrecision())/(1 + GetRang()==RANG_ARRIERE); //prise en compte du rang
}

int Heros::GetEsquiveTotal() const
{
    if(this == 0)
        return 0;
    return (GetEsquive()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_MAINGAUCHE))->GetEsquive()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_MAINDROITE))->GetEsquive()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_TETE))->GetEsquive()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_CORPS))->GetEsquive()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE1))->GetEsquive()+\
            ((Equipable*)GetEquipement(EQUIPEMENT_ACCESSOIRE2))->GetEsquive())*(1 + GetRang()==RANG_ARRIERE); //prise en compte du rang;
}
