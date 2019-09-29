#include "Personnage.h"

using namespace std;

Personnage::Personnage(int Id, string Nom, int Vie, int Magie,\
                       int VieMax, int AttaqueP, int DefenseP,\
                       int MagieMax, int AttaqueM, int DefenseM,\
                       int Vitesse, int Precision, int Esquive,\
                       int Statut, int Experience, int Niveau, int Jauge)
{
    SetId(Id);
    SetNom(Nom);
    SetVieMax(VieMax);
    SetAttaqueP(AttaqueP);
    SetDefenseP(DefenseP);
    SetMagieMax(MagieMax);
    SetAttaqueM(AttaqueM);
    SetDefenseM(DefenseM);
    SetVitesse(Vitesse);
    SetPrecision(Precision);
    SetEsquive(Esquive);
    SetExperience(Experience);
    SetNiveau(Niveau);
    SetStatut(Statut);
    SetJauge(Jauge);
    SetVie(Vie);
    SetMagie(Magie);
    SetAction(ACTION_INACTIF);
    SetNombreCibles(0);
    unsigned int i;
    for(i = 0; i < MAX_SORTS; i++)
        m_Sorts[i] = 0;
    for(i = 0; i < MAX_APTITUDES; i++)
        m_Aptitudes[i] = 0;
    for(i = 0; i < MAX_ALTERATIONS; i++)
        m_Alterations[i] = 0;

    m_Objet = 0;
    m_Capacite = 0;
    SetNombreCibles(0);
    m_Cibles = 0;
}

Personnage::Personnage(const Personnage& other)
{
    *this = other;
    m_Objet = 0;
    m_Capacite = 0;
    SetNombreCibles(0);
    m_Cibles = 0;
}

Personnage::~Personnage()
{
    //dtor
    if(m_Cibles)
        delete m_Cibles;
}

int Personnage::GetId() const
{
    if(this == 0)
        return 0;
    return m_Id;
}

void Personnage::SetId(int val)
{
    if(val < 0)
        val = 0;
    m_Id = val;
}

string Personnage::GetNom() const
{
    if(this == 0)
        return "_";
    return m_Nom;
}

void Personnage::SetNom(string val)
{
    m_Nom = val;
}

int Personnage::GetVie() const
{
    if(this == 0)
        return 0;
    return m_Vie;
}

void Personnage::SetVie(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > m_VieMax)
    {
        val = m_VieMax;
    }
    m_Vie = val;
}

void Personnage::ChangerVie(int val)
{
    SetVie(GetVie()+val);
}

int Personnage::GetVieP() const
{
    if(this == 0)
        return 0;
    return 100.*GetVie()/GetVieMax();
}

void Personnage::SetVieP(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > 100)
    {
        val = 100;
    }
    SetVie(val*GetVieMax()/100.);
}

void Personnage::ChangerVieP(int val)
{
    if(val < -100)
    {
        val = -100;
    }
    else if(val > 100)
    {
        val = 100;
    }
    ChangerVie(val*GetVie()/100.);
}

bool Personnage::estEnVie() const
{
    return GetVie() > 0;
}

int Personnage::GetMagie() const
{
    if(this == 0)
        return 0;
    return m_Magie;
}

void Personnage::SetMagie(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > m_MagieMax)
    {
        val = m_MagieMax;
    }
    m_Magie = val;
}

void Personnage::ChangerMagie(int val)
{
    SetMagie(GetMagie()+val);
}

int Personnage::GetMagieP() const
{
    if(this == 0)
        return 0;
    return 100.*GetMagie()/GetMagieMax();
}

void Personnage::SetMagieP(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > 100)
    {
        val = 100;
    }
    SetMagie(val*GetMagieMax()/100.);
}

void Personnage::ChangerMagieP(int val)
{
    if(val < -100)
    {
        val = -100;
    }
    else if(val > 100)
    {
        val = 100;
    }
    ChangerMagie(val*GetMagie()/100.);
}

int Personnage::GetVieMax() const
{
    if(this == 0)
        return 0;
    return m_VieMax;
}

void Personnage::SetVieMax(int val)
{
    if(val < 1)
        val = 1;
    m_VieMax = val;
}

void Personnage::ChangerVieMax(int val)
{
    SetVieMax(GetVieMax()+val);
}

int Personnage::GetAttaqueP() const
{
    if(this == 0)
        return 0;
    return m_AttaqueP;
}

void Personnage::SetAttaqueP(int val)
{
    m_AttaqueP = val;
}

void Personnage::ChangerAttaqueP(int val)
{
    SetAttaqueP(GetAttaqueP()+val);
}

int Personnage::GetDefenseP() const
{
    if(this == 0)
        return 0;
    return m_DefenseP;
}

void Personnage::SetDefenseP(int val)
{
    m_DefenseP = val;
}

void Personnage::ChangerDefenseP(int val)
{
    SetDefenseP(GetDefenseP()+val);
}

int Personnage::GetMagieMax() const
{
    if(this == 0)
        return 0;
    return m_MagieMax;
}

void Personnage::SetMagieMax(int val)
{
    if(val < 0)
        val = 0;
    m_MagieMax = val;
}

void Personnage::ChangerMagieMax(int val)
{
    SetMagieMax(GetMagieMax()+val);
}

int Personnage::GetAttaqueM() const
{
    if(this == 0)
        return 0;
    return m_AttaqueM;
}

void Personnage::SetAttaqueM(int val)
{
    m_AttaqueM = val;
}

void Personnage::ChangerAttaqueM(int val)
{
    SetAttaqueM(GetAttaqueM()+val);
}

int Personnage::GetDefenseM() const
{
    if(this == 0)
        return 0;
    return m_DefenseM;
}

void Personnage::SetDefenseM(int val)
{
    m_DefenseM = val;
}

void Personnage::ChangerDefenseM(int val)
{
    SetDefenseM(GetDefenseM()+val);
}

int Personnage::GetVitesse() const
{
    if(this == 0)
        return 0;
    return m_Vitesse;
}

void Personnage::SetVitesse(int val)
{
    if(val < 0)
        val = 0;
    m_Vitesse = val;
}

void Personnage::ChangerVitesse(int val)
{
    SetVitesse(GetVitesse()+val);
}

int Personnage::GetPrecision() const
{
    if(this == 0)
        return 0;
    return m_Precision;
}

void Personnage::SetPrecision(int val)
{
    if(val < 0)
        val = 0;
    m_Precision = val;
}

void Personnage::ChangerPrecision(int val)
{
    SetPrecision(GetPrecision()+val);
}

int Personnage::GetEsquive() const
{
    if(this == 0)
        return 0;
    return m_Esquive;
}

void Personnage::SetEsquive(int val)
{
    if(val < 0)
        val = 0;
    m_Esquive = val;
}

void Personnage::ChangerEsquive(int val)
{
    SetEsquive(GetEsquive()+val);
}

int Personnage::GetStatut() const
{
    if(this == 0)
        return 0;
    return m_Statut;
}

void Personnage::SetStatut(int val)
{
    m_Statut = val;
}

int Personnage::GetExperience() const
{
    if(this == 0)
        return 0;
    return m_Experience;
}

void Personnage::SetExperience(int val)
{
    if(val < 0)
        val = 0;
    m_Experience = val;
}

void Personnage::ChangerExperience(int val)
{
    SetExperience(GetExperience()+val);
}


int Personnage::GetNiveau()
{
    if(this == 0)
        return 0;
    return m_Niveau;
}

void Personnage::SetNiveau(int val)
{
    if(val < 1)
    {
        val = 1;
    }
    if(val > MAX_NIVEAU)
    {
        val = MAX_NIVEAU;
    }
    m_Niveau = val;
}

int Personnage::GetJauge() const
{
    if(this == 0)
        return 0;
    return m_Jauge;
}

void Personnage::SetJauge(int val)
{
    if(val < 0)
    {
        val = 0;
    }
    else if(val > TAILLE_JAUGE)
    {
        val = TAILLE_JAUGE;
    }
    m_Jauge = val;
}

void Personnage::ActualiserJauge()
{
    SetJauge(GetJauge()+GetVitesse()*VITESSE_COMBAT);
}

void Personnage::ViderJauge()
{
    SetJauge(0);
}

bool Personnage::Jauge_estpleine() const
{
    return (GetJauge() == TAILLE_JAUGE);
}

Capacite* Personnage::GetSorts(int id) const
{
    if(this == 0)
        return 0;
    return m_Sorts[id];
}

int Personnage::SetSorts(Capacite* val, int id)
{
    if(val == 0)
    {
        m_Sorts[id] = 0;
        return 0;
    }
    m_Sorts[id] = val;
    return 0;
}

int Personnage::AjouterSorts(Capacite* val)
{
    if(GetSorts(val->GetId() - 1))
        return -1;
    SetSorts(val, val->GetId() - 1);
    return 0;
}

Capacite* Personnage::GetAptitudes(int id) const
{
    if(this == 0)
        return 0;
    return m_Aptitudes[id];
}

int Personnage::SetAptitudes(Capacite* val, int id)
{
    if(val == 0)
    {
        m_Aptitudes[id] = 0;
        return 0;
    }
    m_Aptitudes[id] = val;
    return 0;
}

int Personnage::AjouterAptitudes(Capacite* val)
{
    if(GetAptitudes(val->GetId() - 1))
        return -1;
    SetAptitudes(val, val->GetId() - 1);
    return 0;
}

Alteration* Personnage::GetAlterations(int id) const
{
    if(this == 0)
        return 0;
    return m_Alterations[id];
}

void Personnage::SetAlterations(Alteration* val, int id)
{
    //On copie l'alteration pour qu'elles ne soient pas toutes liées par le même curseur de script
    delete m_Alterations[id];
    if(val == 0)
        m_Alterations[id] = 0;
    else
        m_Alterations[id] = new Alteration(*val);
}

int Personnage::ChercherAlteration(Alteration *val) const
{
    int i(0);
    while(i < MAX_ALTERATIONS && GetAlterations(i)->GetId() != val->GetId())
    {
        i++;
    }
    if(i >= MAX_ALTERATIONS)
    {
        return -1;
    }
    return i;
}

int Personnage::ChercherLibre(int priorite) const
{
    int i(0);
    //On remplace une alteration qui a la même priorité que la nouvelle
    while(i < MAX_ALTERATIONS && GetAlterations(i)->GetPriorite() > priorite)
    {
        i++;
    }
    if(i >= MAX_ALTERATIONS)
    {
        return -1;
    }
    return i;
}

int Personnage::AjouterAlteration(Alteration* val)
{
    int i(ChercherAlteration(val));
    if(i != -1) //On reset l'altération si elle est déja présente
    {
        SetAlterations(val, i);
    }
    else
    {
        i = ChercherLibre(val->GetPriorite());
        if(i != -1)
        {
            SetAlterations(val, i);
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int Personnage::RetirerAlteration(Alteration* val)
{
    int i(ChercherAlteration(val));
    if(i != -1)
    {
        SetAlterations(0, i);
        return 0;
    }
    return -1;
}

bool Personnage::estOccupe() const
{
    if(this == 0)
        return true;
    return !Jauge_estpleine() || GetAction() != ACTION_INACTIF || !estEnVie();
}

int Personnage::GetAction() const
{
    if(this == 0)
        return -1;
    return m_Action;
}

void Personnage::SetAction(int val)
{
    m_Action = val;
}

Objet* Personnage::GetObjet() const
{
    if(this == 0)
        return 0;
    return m_Objet;
}

void Personnage::SetObjet(Objet* val)
{
    m_Objet = val;
}

Capacite* Personnage::GetCapacite() const
{
    if(this == 0)
        return 0;
    return m_Capacite;
}

void Personnage::SetCapacite(Capacite* val)
{
    m_Capacite = val;
}

int Personnage::GetNombreCibles() const
{
    if(this == 0)
        return 0;
    return m_NombreCibles;
}

void Personnage::SetNombreCibles(int val)
{
    m_NombreCibles = val;
}

Personnage** Personnage::GetCibles() const
{
    if(this == 0)
        return 0;
    return m_Cibles;
}

Personnage* Personnage::GetCible(int id) const
{
    if(this == 0)
        return 0;
    return m_Cibles[id];
}

void Personnage::SetCibles(Personnage** val)
{
    if(m_Cibles)
        delete m_Cibles;
    m_Cibles = val;
}

float Personnage::Probabilite_touche() const
{
    int esquive(GetCible(0)->GetEsquive());
    float pi(exp(-esquive));
    float P(pi);
    int i;
    for(i = 1; i <= GetPrecision(); i++)
    {
        pi*=esquive/(float)i;
        P+=pi;
    }
    return P;
}

void Personnage::Attaquer()
{
    if(rand() < RAND_MAX*Probabilite_touche())
        GetCible(0)->ChangerVie(-GetAttaqueP()/GetCible(0)->GetDefenseP());
}
