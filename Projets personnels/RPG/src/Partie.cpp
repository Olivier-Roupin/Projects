#include "Partie.h"

using namespace std;

string Int2String(int i)
{
    stringstream ss;
    string s;
    ss << i;
    ss >> s;
    return s;
}

Partie::Partie(int id)
{
    int i,n;
    m_Equipe = new Equipe();
    m_Inventaire = new Inventaire();
    m_GroupeCombat = 0;
    m_Input = new Input();
    SetTerrain(1);
    srand(time(0));
    //combat
    SetObjet(0);
    SetCapacite(0);
    if(id != NOUVELLE_PARTIE)
    {
        string fichier;
        fichier = "sauvegarde";
        fichier += Int2String(id);
        fichier += ".txt";
        ifstream flux(fichier.c_str(), ios::in);
        if(flux)
        {
            int id(0);
            int nombre(0);
            string nom("");
            int in[NOMBRE_IN_HEROS];
            int in_magies[MAX_SORTS];
            int id_Carte(0);
            //Stats
            flux >> m_Or;
            flux >> m_Temps;
            flux >> m_Pas;
            //Options
            flux >> m_VitesseCombat;
            flux >> m_ModeCombat;
            flux >> m_MemoriserCurseur;
            //Position
            flux >> id_Carte;
            flux >> m_X;
            flux >> m_Y;
            flux >> m_Orientation;
            m_Carte = cartes[id_Carte];
            for(i = 0; i < MAX_OBJETS; i++) //remplissage de l'inventaire
            {
                flux >> id;
                flux >> nombre;
                m_Inventaire->SetObjets(objets[id],nombre,i);
            }
            for(i = 0; i < MAX_HEROS_EQUIPE; i++) //remplissage de l'équipe
            {
                flux >> id;
                flux >> nom;
                for(n = 0; n < NOMBRE_IN_HEROS; n++)
                {
                    flux >> in[n];
                }
                for(n = 0; n < MAX_SORTS; n++)
                {
                    flux >> in_magies[n];
                }
                if(id)
                {
                    Heros *heros;
                    //Stats, Equipement :
                    heros = new Heros(id,nom,in[0],in[1],\
                                      in[2],in[3],in[4],\
                                      in[5],in[6],in[7],\
                                      in[8],in[9],in[10],\
                                      in[11],in[12],in[13],\
                                      in[14],in[15],in[16],in[17],\
                                      objets[in[18]],objets[in[19]],objets[in[20]],\
                                      objets[in[21]],objets[in[22]],objets[in[23]]);
                    //Capacités - Magies :
                    for(n = 0; n < MAX_SORTS; n++)
                    {
                        if(in_magies[n])
                        {
                            heros->AjouterSorts(capacites[in_magies[n]]);
                        }
                    }
                    m_Equipe->SetHeros(heros,i);
                }
            }
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }
    }
    else
    {
        ifstream flux("nouvelle.txt");
        if(flux)
        {
            int id(0);
            int nombre(0);
            string nom("");
            int in[NOMBRE_IN_HEROS];
            int in_magies[MAX_SORTS];
            int id_Carte(0);
            //Stats
            flux >> m_Or;
            flux >> m_Temps;
            flux >> m_Pas;
            //Options
            flux >> m_VitesseCombat;
            flux >> m_ModeCombat;
            flux >> m_MemoriserCurseur;
            //Position
            flux >> id_Carte;
            flux >> m_X;
            flux >> m_Y;
            flux >> m_Orientation;
            m_Carte = cartes[id_Carte];
            for(i = 0; i < MAX_OBJETS; i++) //remplissage de l'inventaire
            {
                flux >> id;
                flux >> nombre;
                m_Inventaire->SetObjets(objets[id],nombre,i);
            }
            for(i = 0; i < MAX_HEROS_EQUIPE; i++) //remplissage de l'équipe
            {
                flux >> id;
                flux >> nom;
                for(n = 0; n < NOMBRE_IN_HEROS; n++)
                {
                    flux >> in[n];
                }
                for(n = 0; n < MAX_SORTS; n++)
                {
                    flux >> in_magies[n];
                }
                if(id)
                {
                    Heros *heros;
                    //Stats, Equipement :
                    heros = new Heros(id,nom,in[0],in[1],\
                                      in[2],in[3],in[4],\
                                      in[5],in[6],in[7],\
                                      in[8],in[9],in[10],\
                                      in[11],in[12],in[13],\
                                      in[14],in[15],in[16],in[17],\
                                      objets[in[18]],objets[in[19]],objets[in[20]],\
                                      objets[in[21]],objets[in[22]],objets[in[23]]);
                    //Capacités - Magies :
                    for(n = 0; n < MAX_SORTS; n++)
                    {
                        if(in_magies[n])
                        {
                            heros->AjouterSorts(capacites[in_magies[n]]);
                        }
                    }
                    m_Equipe->SetHeros(heros,i);
                }
            }
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }
    }
}

Partie::~Partie()
{
    int i;
    for(i = 0; i < GetGroupeCombat()->GetNombre(); i++)
    {
        delete GetGroupeCombat()->GetMonstres(i);
    }
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        delete m_Equipe->GetHeros(i);
    }
}

Equipe* Partie::GetEquipe() const
{
    if(this == 0)
        return 0;
    return m_Equipe;
}

void Partie::SetEquipe(Equipe* val)
{
    m_Equipe = val;
}

Inventaire* Partie::GetInventaire() const
{
    if(this == 0)
        return 0;
    return m_Inventaire;
}

void Partie::SetInventaire(Inventaire* val)
{
    m_Inventaire = val;
}

GroupeMonstres* Partie::GetGroupeCombat() const
{
    if(this == 0)
        return 0;
    return m_GroupeCombat;
}

void Partie::SetGroupeCombat(GroupeMonstres* val)
{
    m_GroupeCombat = new GroupeMonstres(0, *val);
    /*int i;
    m_GroupeCombat = new GroupeMonstres(0,val->GetNombre());
    Monstre* copie(0);
    for(i = 0; i < val->GetNombre(); i++)
    {
        copie = new Monstre(*(val->GetMonstres(i)));
        m_GroupeCombat->SetMonstres(copie,i);
        m_GroupeCombat->SetX(val->GetX(i),i);
        m_GroupeCombat->SetY(val->GetY(i),i);
        m_GroupeCombat->GetMonstres(i)->SetX(m_GroupeCombat->GetX(i));
        m_GroupeCombat->GetMonstres(i)->SetY(m_GroupeCombat->GetY(i));
    }*/
}

Carte* Partie::GetCarte() const
{
    if(this == 0)
        return 0;
    return m_Carte;
}

void Partie::SetCarte(Carte* val)
{
    m_Carte = val;
}

int Partie::GetOr() const
{
    if(this == 0)
        return 0;
    return m_Or;
}

void Partie::SetOr(int val)
{
    if(val < 0)
        val = 0;
    else if(val > MAX_OR)
        val = MAX_OR;
    m_Or = val;
}

void Partie::ChangerOr(int val)
{
    SetOr(GetOr()+val);
}

int Partie::GetX() const
{
    if(this == 0)
        return 0;
    return m_X;
}

void Partie::SetX(int val)
{
    if(val < 0)
        val = 0;
    else if(val > GetCarte()->GetLargeur()-1)
        val = GetCarte()->GetLargeur()-1;
    m_X = val;
}

void Partie::ChangerX(int val)
{
    if(GetCarte()->GetRepetition())
        SetX((GetX()+val+GetCarte()->GetLargeur()) % GetCarte()->GetLargeur());
    else
        SetX(GetX()+val);
}

int Partie::GetY() const
{
    if(this == 0)
        return 0;
    return m_Y;
}

void Partie::SetY(int val)
{
    if(val < 0)
        val = 0;
    else if(val > GetCarte()->GetHauteur()-1)
        val = GetCarte()->GetHauteur()-1;
    m_Y = val;
}

void Partie::ChangerY(int val)
{
    if(GetCarte()->GetRepetition())
        SetY((GetY()+val+GetCarte()->GetHauteur()) % GetCarte()->GetHauteur());
    else
        SetY(GetY()+val);
}

int Partie::GetOrientation() const
{
    if(this == 0)
        return 0;
    return m_Orientation;
}

void Partie::SetOrientation(int val)
{
    if(val >= 0 && val <= NOMBRE_ORIENTATIONS-1)
        m_Orientation = val;
}

void Partie::ChangerOrientation(int val)
{
    SetOrientation((GetOrientation()+val+NOMBRE_ORIENTATIONS) % NOMBRE_ORIENTATIONS);
}

int Partie::GetOrientationX() const
{
    if(this == 0)
        return 0;
    if(m_Orientation == ORIENTATION_DROITE)
        return 1;
    if(m_Orientation == ORIENTATION_GAUCHE)
        return -1;
    return 0;
}

int Partie::GetOrientationY() const
{
    if(this == 0)
        return 0;
    if(m_Orientation == ORIENTATION_BAS)
        return 1;
    if(m_Orientation == ORIENTATION_HAUT)
        return -1;
    return 0;
}

int Partie::GetTemps() const
{
    if(this == 0)
        return 0;
    return m_Temps;
}

int Partie::GetHeures() const
{
    return int(GetTempsJeu()/3600);
}

int Partie::GetMinutes() const
{
    return int(GetTempsJeu()/60)%60;
}

int Partie::GetSecondes() const
{
    return GetTempsJeu()%60;
}

void Partie::SetTemps(int val)
{
    m_Temps = val;
}

int Partie::GetTempsJeu() const
{
    if(this == 0)
        return 0;
    return m_Temps + (double)clock()/CLOCKS_PER_SEC;
}

int Partie::GetPas() const
{
    if(this == 0)
        return 0;
    return m_Pas;
}

void Partie::SetPas(int val)
{
    m_Pas = val;
}

void Partie::AjouterPas()
{
    SetPas(GetPas()+1);
}

unsigned int Partie::GetVitesseCombat() const
{
    if(this == 0)
        return MIN_VITESSE_COMBAT;
    return m_VitesseCombat;
}

void Partie::SetVitesseCombat(int val)
{
    if(val < MIN_VITESSE_COMBAT)
        val = MIN_VITESSE_COMBAT;
    else if(val > MAX_VITESSE_COMBAT)
        val = MAX_VITESSE_COMBAT;
    m_VitesseCombat = val;
}

void Partie::ChangerVitesseCombat(int val)
{
    SetVitesseCombat(GetVitesseCombat()+val);
}

unsigned int Partie::GetModeCombat() const
{
    if(this == 0)
        return MODE_SEMI_ACTIF;
    return m_ModeCombat;
}

void Partie::SetModeCombat(int val)
{
    if(val < MODE_ACTIF)
        val = MODE_ACTIF;
    else if(val > MODE_PASSIF)
        val = MODE_PASSIF;
    m_ModeCombat = val;
}

void Partie::ChangerModeCombat(int val)
{
    SetModeCombat(GetModeCombat()+val);
}

bool Partie::GetMemoriserCurseur() const
{
    if(this == 0)
        return false;
    return m_MemoriserCurseur;
}

void Partie::SetMemoriserCurseur(bool val)
{
    m_MemoriserCurseur = val;
}

void Partie::ChangerMemoriserCurseur()
{
    SetMemoriserCurseur(!GetMemoriserCurseur());
}

Input* Partie::GetInput() const
{
    if(this == 0)
        return 0;
    return m_Input;
}

void Partie::SetInput(Input* val)
{
    m_Input = val;
}

int Partie::GetMenu() const
{
    if(this == 0)
        return -1;
    return m_Menu;
}

void Partie::SetMenu(int val)
{
    m_Menu = val;
}

int Partie::GetHeros() const
{
    if(this == 0)
        return -1;
    return m_Heros;
}

Heros* Partie::GetHeros_selection() const
{
    if(this == 0)
        return 0;
    return GetEquipe()->GetHeros(GetHeros());
}

void Partie::SetHeros(int val)
{
    m_Heros = val;
}

int Partie::GetAction() const
{
    if(this == 0)
        return -1;
    return m_Action;
}

void Partie::SetAction(int val)
{
    m_Action = val;
}

int Partie::GetObjet() const
{
    if(this == 0)
        return -1;
    return m_Objet;
}

Objet* Partie::GetObjet_selection() const
{
    if(this == 0)
        return 0;
    return GetInventaire()->GetObjets(GetObjet())->GetObjet();
}

void Partie::SetObjet(int val)
{
    m_Objet = val;
}

int Partie::GetCapacite() const
{
    if(this == 0)
        return -1;
    return m_Capacite;
}

Capacite* Partie::GetCapacite_selection() const
{
    if(this == 0)
        return 0;
    return GetHeros_selection()->GetSorts(GetCapacite());
}

void Partie::SetCapacite(int val)
{
    m_Capacite = val;
}

int Partie::GetCible() const
{
    if(this == 0)
        return -1;
    return m_Cible;
}

void Partie::SetCible(int val)
{
    m_Cible = val;
}

bool Partie::GetFaction() const
{
    if(this == 0)
        return FACTION_LANCEUR;
    return m_Faction;
}

void Partie::SetFaction(bool val)
{
    m_Faction = val;
}

bool Partie::GetQuantite() const
{
    if(this == 0)
        return QUANTITE_UNE;
    return m_Quantite;
}

void Partie::SetQuantite(bool val)
{
    m_Quantite = val;
}

Personnage** Partie::GetCible_selection() const
{
    Personnage** Cible;
    if(GetCible_nombre() == 0)
        return 0;
    int i;
    //if(GetCible() == CIBLE_AUCUNE)
    //    return 0;
    Cible = new Personnage*[sizeof(Personnage*)*GetCible_nombre()];
    if(GetCible() == CIBLE_TOUS)
    {
        for(i = 0; i < GetGroupeCombat()->GetNombre(); i++)
            Cible[i] = (Personnage*)GetGroupeCombat()->GetMonstres(i);
        for(int i = 0; i < MAX_HEROS_EQUIPE; i++)
            Cible[i+GetGroupeCombat()->GetNombre()] = (Personnage*)GetEquipe()->GetHeros(i);
        return Cible;
    }
    if(GetCible() == CIBLE_LANCEUR)
    {
        Cible[0] = GetLanceur_selection();
        return Cible;
    }
    //if(GetCible() >= 0)
    if(GetQuantite() == QUANTITE_UNE)
    {
        if(GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_EQUIPE ||\
                GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_MONSTRES)
        {
            Cible[0] = GetEquipe()->GetHeros(GetCible());
            return Cible;
        }
        if(GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_EQUIPE ||\
                GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_MONSTRES)
        {
            Cible[0] = GetGroupeCombat()->GetMonstres(GetCible());
            return Cible;
        }
    }
    //if(GetQuantite() == QUANTITE_FACTION)
    if(GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_EQUIPE ||\
            GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_MONSTRES)
    {
        for(int i = 0; i < MAX_HEROS_EQUIPE; i++)
            Cible[i] = (Personnage*)GetEquipe()->GetHeros(i);
        return Cible;
    }
    if(GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_EQUIPE ||\
            GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_MONSTRES)
    {
        for(i = 0; i < GetGroupeCombat()->GetNombre(); i++)
            Cible[i] = (Personnage*)GetGroupeCombat()->GetMonstres(i);
        return Cible;
    }
    //Sinon supprimer Cible, ne doit pas atteindre ce cas car GetCible_nombre() == 0
    delete Cible;
    return 0;
}

int Partie::GetCible_nombre() const
{
    if(GetCible() == CIBLE_AUCUNE)
        return 0;
    if(GetCible() == CIBLE_TOUS)
        return GetGroupeCombat()->GetNombre() + MAX_HEROS_EQUIPE;
    if(GetCible() == CIBLE_LANCEUR)
        return 1;
    //if(GetCible() >= 0)
    if(GetQuantite() == QUANTITE_UNE)
        return 1;
    //if(GetQuantite() == QUANTITE_FACTION)
    if(GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_EQUIPE ||\
            GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_MONSTRES)
        return MAX_HEROS_EQUIPE;
    if(GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_EQUIPE ||\
            GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_MONSTRES)
        return GetGroupeCombat()->GetNombre();
    return 0;
}

bool Partie::GetChoix_Cible_selection() const
{
    switch(GetAction())
    {
    case ACTION_ATTAQUER:
        return true;
    case ACTION_OBJETS:
        //return ((Utilisable*)GetObjet_selection())->GetEffet()->GetChoix_Cible();
        return ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet()->GetChoix_Cible();
    case ACTION_CAPACITE:
        //return GetCapacite_selection()->GetEffet()->GetChoix_Cible();
        return GetHeros_selection()->GetCapacite()->GetEffet()->GetChoix_Cible();
    default:
        return false;
    }
}

bool Partie::GetChoix_Faction_selection() const
{
    switch(GetAction())
    {
    case ACTION_ATTAQUER:
        return true;
    case ACTION_OBJETS:
        //return ((Utilisable*)GetObjet_selection())->GetEffet()->GetChoix_Faction();
        return ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet()->GetChoix_Faction();
    case ACTION_CAPACITE:
        //return GetCapacite_selection()->GetEffet()->GetChoix_Faction();
        return GetHeros_selection()->GetCapacite()->GetEffet()->GetChoix_Faction();
    default:
        return false;
    }
}

bool Partie::GetChoix_Quantite_selection() const
{
    switch(GetAction())
    {
    case ACTION_ATTAQUER:
        return false;
    case ACTION_OBJETS:
        //return ((Utilisable*)GetObjet_selection())->GetEffet()->GetChoix_Quantite();
        return ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet()->GetChoix_Quantite();
    case ACTION_CAPACITE:
        //return GetCapacite_selection()->GetEffet()->GetChoix_Quantite();
        return GetHeros_selection()->GetCapacite()->GetEffet()->GetChoix_Quantite();
    default:
        return false;
    }
}

int Partie::GetDefaut_Cible_selection() const
{
    switch(GetAction())
    {
    case ACTION_ATTAQUER:
        return 0;
    case ACTION_OBJETS:
        return ((Utilisable*)GetObjet_selection())->GetEffet()->GetDefaut_Cible();
    case ACTION_CAPACITE:
        return GetCapacite_selection()->GetEffet()->GetDefaut_Cible();
    default:
        return false;
    }
}

bool Partie::GetDefaut_Faction_selection() const
{
    switch(GetAction())
    {
    case ACTION_ATTAQUER:
        return FACTION_ADVERSE;
    case ACTION_OBJETS:
        return ((Utilisable*)GetObjet_selection())->GetEffet()->GetDefaut_Faction();
    case ACTION_CAPACITE:
        return GetCapacite_selection()->GetEffet()->GetDefaut_Faction();
    default:
        return FACTION_LANCEUR;
    }
}

bool Partie::GetDefaut_Quantite_selection() const
{
    switch(GetAction())
    {
    case ACTION_ATTAQUER:
        return false;
    case ACTION_OBJETS:
        return ((Utilisable*)GetObjet_selection())->GetEffet()->GetDefaut_Quantite();
    case ACTION_CAPACITE:
        return GetCapacite_selection()->GetEffet()->GetDefaut_Quantite();
    default:
        return false;
    }
}

void Partie::SetCible_Defaut() //Pour l'équipe : les monstres n'ont pas de curseur
{
    SetFactionLanceur(FACTION_EQUIPE); //Pour l'équipe : pour ne pas risquer de considérer le joueur comme un monstre
    SetCible(GetDefaut_Cible_selection());
    SetFaction(GetDefaut_Faction_selection());
    SetQuantite(GetDefaut_Quantite_selection());
    if(GetCible() == CIBLE_LANCEUR)
        SetFaction(FACTION_LANCEUR);
    if(GetCible() == CIBLE_LANCEUR)
        SetCible(GetHeros()); //Ne marche que pour l'équipe
    //Possibilité de viser l'équipe du lanceur? => Quantité inchangée
}

Personnage* Partie::GetActeur() const
{
     if(this == 0)
        return 0;
    return m_Acteur;
}

void Partie::SetActeur(Personnage* val)
{
    m_Acteur = val;
}

int Partie::GetLanceur() const
{
    if(this == 0)
        return -1;
    return m_Lanceur;
}

void Partie::SetLanceur(int val)
{
    m_Lanceur = val;
}

bool Partie::GetFactionLanceur() const
{
    if(this == 0)
        return FACTION_EQUIPE;
    return m_FactionLanceur;
}

void Partie::SetFactionLanceur(bool val)
{
    m_FactionLanceur = val;
}

Personnage* Partie::GetLanceur_selection() const
{
    if(this == 0)
        return 0;
    if(GetFactionLanceur() == FACTION_EQUIPE)
        return (Personnage*)GetEquipe()->GetHeros(GetLanceur());
    if(GetFactionLanceur() == FACTION_MONSTRES)
        return (Personnage*)GetGroupeCombat()->GetMonstres(GetLanceur());
    return 0;
}

int Partie::GetChoix() const
{
    if(this == 0)
        return -1;
    return m_Choix;
}

void Partie::SetChoix(int val)
{
    m_Choix = val;
}

int Partie::GetSituation() const
{
    if(this == 0)
        return -1;
    return m_Situation;
}

void Partie::SetSituation(int val)
{
    m_Situation = val;
}

bool Partie::GetTerrain() const
{
    if(this == 0)
        return -1;
    return m_Terrain;
}

void Partie::SetTerrain(bool val)
{
    m_Terrain = val;
}
