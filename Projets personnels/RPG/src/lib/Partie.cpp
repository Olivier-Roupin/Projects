#include "lib/Partie.h"
#include <conversions.h>

Partie::Partie(Input* input) {
    m_Equipe = new Equipe();
    m_Inventaire = new Inventaire();
    m_GroupeCombat = 0;
    SetId(0);
    SetTempsActif(0);
    SetInput(input);
    SetTerrain(true);
    //combat
    SetObjet(0);
    SetCapacite(0);
    SetDeplace(0);
}

Partie::~Partie() {
    unsigned char i;
    if (m_GroupeCombat)
        for (i = 0; i < m_GroupeCombat->GetNombre(); ++i)
            if (m_GroupeCombat->GetMonstres(i))
                delete m_GroupeCombat->GetMonstres(i);
    if (m_Equipe)
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
            if (m_Equipe->GetHeros(i))
                delete m_Equipe->GetHeros(i);
}

unsigned char Partie::GetId() const {
    return m_Id;
}

void Partie::SetId(unsigned char val) {
    m_Id = val;
}

Equipe* Partie::GetEquipe() const {
    return m_Equipe;
}

void Partie::SetEquipe(Equipe* val) {
    m_Equipe = val;
}

Inventaire* Partie::GetInventaire() const {
    return m_Inventaire;
}

void Partie::SetInventaire(Inventaire* val) {
    m_Inventaire = val;
}

GroupeMonstres* Partie::GetGroupeCombat() const {
    return m_GroupeCombat;
}

void Partie::SetGroupeCombat(GroupeMonstres* val) {
    m_GroupeCombat = new GroupeMonstres(0, *val); //copie
}

Monstre* Partie::GetMonstre(int id) const {
    if (GetGroupeCombat() == 0)
        return 0;
    return GetGroupeCombat()->GetMonstres(id); //vérifie l'indice
}

Carte* Partie::GetCarte() const {
    return m_Carte;
}

void Partie::SetCarte(Carte* val) {
    m_Carte = val;
}

void Partie::ExecuterEvenement(unsigned char id, unsigned char id_script) {
    if (GetCarte() && GetCarte()->GetEvenements(id)
     && GetCarte()->GetEvenements(id)->GetScripts(id_script)) {
        SetEvenement(id);
        GetCarte()->GetEvenements(id)->GetScripts(id_script)->Executer(this);
    }
}

unsigned int Partie::GetOr() const {
    return m_Or;
}

void Partie::SetOr(unsigned int val) {
    // if (val < 0)
    //     val = 0;
    // else if (val > MAX_OR)
    if (val > MAX_OR)
        val = MAX_OR;
    m_Or = val;
}

void Partie::ChangerOr(int val) {
    SetOr(GetOr()+val);
}

int Partie::GetX() const {
    return m_X;
}

void Partie::SetX(int val) {
    // if (val < 0)
    //     val = 0;
    // else if (val > GetCarte()->GetLargeur()-1) //pas de test !
    //     val = GetCarte()->GetLargeur()-1;
    m_X = val;
}

void Partie::ChangerX(int val) {
    if (GetCarte()->GetRepetition()) //pas de test !
        SetX((GetX()+val+GetCarte()->GetLargeur()) % GetCarte()->GetLargeur());
    else
        SetX(GetX()+val);
}

int Partie::GetY() const {
    return m_Y;
}

void Partie::SetY(int val) {
    // if (val < 0)
    //     val = 0;
    // else if (val > GetCarte()->GetHauteur()-1) //pas de test !
    //     val = GetCarte()->GetHauteur()-1;
    m_Y = val;
}

void Partie::ChangerY(int val) {
    if (GetCarte()->GetRepetition()) //pas de test !
        SetY((GetY()+val+GetCarte()->GetHauteur()) % GetCarte()->GetHauteur());
    else
        SetY(GetY()+val);
}

char Partie::GetOrientation() const {
    return m_Orientation;
}

void Partie::SetOrientation(char val) {
    //if (val >= 0 && val <= NOMBRE_ORIENTATIONS-1)
    if (val >= 0)
        m_Orientation = val;
}

void Partie::ChangerOrientation(char val) {
    SetOrientation((GetOrientation()+val+NOMBRE_ORIENTATIONS) % NOMBRE_ORIENTATIONS);
}

char Partie::GetOrientationX() const {
    if (m_Orientation == ORIENTATION_DROITE)
        return 1;
    if (m_Orientation == ORIENTATION_GAUCHE)
        return -1;
    return 0;
}

char Partie::GetOrientationY() const {
    if (m_Orientation == ORIENTATION_BAS)
        return 1;
    if (m_Orientation == ORIENTATION_HAUT)
        return -1;
    return 0;
}

char Partie::GetDeplace() const {
    return m_Deplace;
}

void Partie::SetDeplace(char val) {
    m_Deplace = val;
}

void Partie::ChangerDeplace(char val) {
    SetDeplace(GetDeplace()+val);
}

char Partie::GetMeneur() const {
    return m_Meneur;
}

void Partie::SetMeneur(char val) {
    if (val >= -1 && val <= MAX_HEROS_EQUIPE)
        m_Meneur = val;
}

//TODO: remplacer par boucle for pour éviter boucle infinie ?
void Partie::IncMeneur() {
    if (GetEquipe() == 0)
        return;
    do {
        SetMeneur(APRES(GetMeneur(), MAX_HEROS_EQUIPE));
    } while (!GetEquipe()->GetHeros(GetMeneur())
          || !GetEquipe()->GetHeros(GetMeneur())->estEnVie()); //sécure ?
}

void Partie::ResetMeneur() {
    if (GetEquipe() == 0)
        return;
    while (!GetEquipe()->GetHeros(GetMeneur())
        || !GetEquipe()->GetHeros(GetMeneur())->estEnVie()) //sécure ?
        SetMeneur(APRES(GetMeneur(), MAX_HEROS_EQUIPE));
}

int Partie::GetTemps() const {
    return m_Temps;
}

void Partie::SetTemps(int val) {
    m_Temps = val;
}

unsigned int Partie::GetTempsJeu() const {
    if (m_Temps < 0 && (unsigned int)(-m_Temps) > m_TempsActif)
        return 0;
    return (unsigned int)m_Temps + m_TempsActif;
}

unsigned int Partie::GetTempsActif() const {
    return m_TempsActif;
}

void Partie::SetTempsActif(unsigned int val) {
    m_TempsActif = val;
}

/*unsigned int Partie::GetHeures() const {
    return GetTempsJeu()/3600;
}

unsigned int Partie::GetMinutes() const {
    return (GetTempsJeu()/60)%60;
}

unsigned int Partie::GetSecondes() const {
    return GetTempsJeu()%60;
}*/

unsigned int Partie::GetPas() const {
    return m_Pas;
}

void Partie::SetPas(unsigned int val) {
    m_Pas = val;
}

void Partie::AjouterPas() {
    SetPas(GetPas()+1);
}

unsigned char Partie::GetVitesseCombat() const {
    return m_VitesseCombat;
}

void Partie::SetVitesseCombat(unsigned char val) {
    if (val < MIN_VITESSE_COMBAT)
        val = MIN_VITESSE_COMBAT;
    else if (val > MAX_VITESSE_COMBAT)
        val = MAX_VITESSE_COMBAT;
    m_VitesseCombat = val;
}

void Partie::ChangerVitesseCombat(char val) {
    SetVitesseCombat(GetVitesseCombat()+val); //correct pour les signes ?
}

unsigned char Partie::GetModeCombat() const {
    return m_ModeCombat;
}

void Partie::SetModeCombat(unsigned char val) {
    // if (val < MODE_ACTIF)
    if (val > MODE_PASSIF+1)
        val = MODE_ACTIF;
    else if (val > MODE_PASSIF)
    // if (val > MODE_PASSIF)
        val = MODE_PASSIF;
    m_ModeCombat = val;
}

void Partie::ChangerModeCombat(char val) {
    SetModeCombat(GetModeCombat()+val); //correct pour les signes ?
}

bool Partie::GetMemoriserCurseur() const {
    return m_MemoriserCurseur;
}

void Partie::SetMemoriserCurseur(bool val) {
    m_MemoriserCurseur = val;
}

void Partie::ChangerMemoriserCurseur() {
    SetMemoriserCurseur(!GetMemoriserCurseur());
}

Input* Partie::GetInput() const {
    return m_Input;
}

void Partie::SetInput(Input* val) {
    m_Input = val;
}

char Partie::GetMenu() const {
    return m_Menu;
}

void Partie::SetMenu(char val) {
    m_Menu = val;
}

char Partie::GetHeros() const {
    return m_Heros;
}

Heros* Partie::GetHeros_selection() const {
    if (GetEquipe() == 0)
        return 0;
    return GetEquipe()->GetHeros(GetHeros());
}

void Partie::SetHeros(char val) {
    m_Heros = val;
}

char Partie::GetAction() const {
    return m_Action;
}

void Partie::SetAction(char val) {
    m_Action = val;
}

void Partie::ApplyAction_selection() {
    if (GetHeros_selection())
        GetHeros_selection()->SetAction(GetAction());
}

int Partie::GetObjet() const {
    return m_Objet;
}

Objet* Partie::GetObjet_selection() const {
    if (GetInventaire() == 0)
        return 0;
    return GetInventaire()->GetObjet(GetObjet());
}

void Partie::SetObjet(int val) {
    m_Objet = val;
}

void Partie::ApplyObjet_selection() {
    GetHeros_selection()->SetObjet(GetObjet_selection());
}

int Partie::GetCapacite() const {
    return m_Capacite;
}

Capacite* Partie::GetCapacite_selection() const {
    if (GetHeros_selection() == 0)
        return 0;
    return GetHeros_selection()->GetSorts(GetCapacite());
}

void Partie::SetCapacite(int val) {
    m_Capacite = val;
}

void Partie::ApplyCapacite_selection() {
    GetHeros_selection()->SetCapacite(GetCapacite_selection());
}

int Partie::GetCible() const {
    return m_Cible;
}

void Partie::SetCible(int val) {
    m_Cible = val;
}

void Partie::IncCible(const int taille) {
    SetCible(APRES(GetCible(),taille));
}

void Partie::DecCible(const int taille) {
    SetCible(AVANT(GetCible(),taille));
}

bool Partie::GetFaction() const {
    return m_Faction;
}

void Partie::SetFaction(bool val) {
    m_Faction = val;
}

bool Partie::GetQuantite() const {
    return m_Quantite;
}

void Partie::SetQuantite(bool val) {
    m_Quantite = val;
}

// On part du principe que les sorts de groupe ne sélectionnent pas les
// personnages morts. Peut-être faut-il rajouter un booléen qui décide de ça.
Personnage** Partie::GetCible_selection() const {
    Personnage** Cible;
    if (GetCible_nombre() == 0)
        return 0;
    unsigned char i, j = 0;
    //if (GetCible() == CIBLE_AUCUNE)
    //    return 0;
    Cible = new Personnage*[GetCible_nombre()]; // fait la bonne taille ?
    if (GetCible() == CIBLE_TOUS) {
        if (GetGroupeCombat())
            for (i = 0; i < GetGroupeCombat()->GetNombre(); ++i)
                if (GetMonstre(i) && GetMonstre(i)->estEnVie()) {
                    Cible[j] = (Personnage*)GetMonstre(i);
                    ++j;
                }
        // j == GetGroupeCombat()->GetNombreEnVie() ?
        if (GetEquipe())
            for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
                if (GetEquipe()->GetHeros(i) && GetEquipe()->GetHeros(i)->estEnVie()) {
                    Cible[j] = (Personnage*)GetEquipe()->GetHeros(i);
                    ++j;
                }
        // j == GetCible_nombre() ?
        return Cible;
    }
    if (GetCible() == CIBLE_LANCEUR) {
        Cible[0] = GetLanceur_selection();
        return Cible;
    }
    //if (GetCible() >= 0)
    if (GetQuantite() == QUANTITE_UNE) {
        if ((GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_EQUIPE) ||\
                (GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_MONSTRES)) {
            Cible[0] = GetEquipe()->GetHeros(GetCible());
            return Cible;
        }
        if ((GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_EQUIPE) ||\
                (GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_MONSTRES)) {
            Cible[0] = GetMonstre(GetCible());
            return Cible;
        }
    }
    //if (GetQuantite() == QUANTITE_FACTION)
    if ((GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_EQUIPE) ||\
            (GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_MONSTRES)) {
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
            if (GetEquipe()->GetHeros(i) && GetEquipe()->GetHeros(i)->estEnVie()) {
                Cible[j] = (Personnage*)GetEquipe()->GetHeros(i);
                ++j;
            }
        // j == GetCible_nombre() ?
        return Cible;
    }
    if ((GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_EQUIPE) ||\
            (GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_MONSTRES)) {
        if (GetGroupeCombat())
            for (i = 0; i < GetGroupeCombat()->GetNombre(); ++i)
                if (GetMonstre(i) && GetMonstre(i)->estEnVie()) {
                    Cible[j] = (Personnage*)GetMonstre(i);
                    ++j;
                }
        // j == GetCible_nombre() ?
        return Cible;
    }
    //Sinon supprimer Cible, ne doit pas atteindre ce cas car GetCible_nombre() == 0
    delete[] Cible;
    return 0;
}

int Partie::GetCible_nombre() const {
    if (GetCible() == CIBLE_AUCUNE)
        return 0;
    if (GetCible() == CIBLE_TOUS)
        return GetGroupeCombat()->GetNombreEnVie() + GetEquipe()->GetNombreEnVie();
    if (GetCible() == CIBLE_LANCEUR)
        return 1;
    //if (GetCible() >= 0)
    if (GetQuantite() == QUANTITE_UNE)
        return 1;
    //if (GetQuantite() == QUANTITE_FACTION)
    if ((GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_EQUIPE) ||\
            (GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_MONSTRES))
        return GetEquipe()->GetNombreEnVie(); //MAX_HEROS_EQUIPE
    if ((GetFaction() == FACTION_ADVERSE && GetFactionLanceur() == FACTION_EQUIPE) ||\
            (GetFaction() == FACTION_LANCEUR && GetFactionLanceur() == FACTION_MONSTRES))
        if (GetGroupeCombat())
            return GetGroupeCombat()->GetNombreEnVie(); //GetNombre()
    return 0;
}

void Partie::ApplyCible_selection() {
    GetHeros_selection()->SetCibles(GetCible_selection());
    GetHeros_selection()->SetNombreCibles(GetCible_nombre());
}

bool Partie::GetChoix_Cible_selection() const {
    if (GetHeros_selection() == 0) // situation impossible ?
        return false;
    switch (GetAction()) {
    case ACTION_ATTAQUER:
        return true;
    case ACTION_OBJETS:
        //return ((Utilisable*)GetObjet_selection())->GetEffet()->GetChoix_Cible();
        if (GetHeros_selection()->GetObjet() == 0
        || ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet() == 0)
            return false;
        return ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet()->GetChoix_Cible();
    case ACTION_CAPACITE:
        //return GetCapacite_selection()->GetEffet()->GetChoix_Cible();
        if (GetHeros_selection()->GetCapacite() == 0
        || GetHeros_selection()->GetCapacite()->GetEffet() == 0)
            return false;
        return GetHeros_selection()->GetCapacite()->GetEffet()->GetChoix_Cible();
    default:
        return false;
    }
}

bool Partie::GetChoix_Faction_selection() const {
    if (GetHeros_selection() == 0) // situation impossible ?
        return false;
    switch (GetAction()) {
        case ACTION_ATTAQUER:
            return true;
        case ACTION_OBJETS:
            //return ((Utilisable*)GetObjet_selection())->GetEffet()->GetChoix_Faction();
            if (GetHeros_selection()->GetObjet() == 0
            || ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet() == 0)
                return false;
            return ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet()->GetChoix_Faction();
        case ACTION_CAPACITE:
            //return GetCapacite_selection()->GetEffet()->GetChoix_Faction();
            if (GetHeros_selection()->GetCapacite() == 0
            || GetHeros_selection()->GetCapacite()->GetEffet() == 0)
                return false;
            return GetHeros_selection()->GetCapacite()->GetEffet()->GetChoix_Faction();
        default:
            return false;
    }
}

bool Partie::GetChoix_Quantite_selection() const {
    if (GetHeros_selection() == 0) // situation impossible ?
        return false;
    switch (GetAction()) {
        case ACTION_ATTAQUER:
            return false;
        case ACTION_OBJETS:
            //return ((Utilisable*)GetObjet_selection())->GetEffet()->GetChoix_Quantite();
            if (GetHeros_selection()->GetObjet() == 0
            || ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet() == 0)
                return false;
            return ((Utilisable*)GetHeros_selection()->GetObjet())->GetEffet()->GetChoix_Quantite();
        case ACTION_CAPACITE:
            //return GetCapacite_selection()->GetEffet()->GetChoix_Quantite();
            if (GetHeros_selection()->GetCapacite() == 0
            || GetHeros_selection()->GetCapacite()->GetEffet() == 0)
                return false;
            return GetHeros_selection()->GetCapacite()->GetEffet()->GetChoix_Quantite();
        default:
            return false;
    }
}

int Partie::GetDefaut_Cible_selection() const {
    switch (GetAction()) {
        case ACTION_ATTAQUER:
            return 0;
        case ACTION_OBJETS:
            if (GetObjet_selection() == 0
            || ((Utilisable*)GetObjet_selection())->GetEffet() == 0)
                return false;
            return ((Utilisable*)GetObjet_selection())->GetEffet()->GetDefaut_Cible();
        case ACTION_CAPACITE:
            if (GetCapacite_selection() == 0
            || GetCapacite_selection()->GetEffet() == 0)
                return false;
            return GetCapacite_selection()->GetEffet()->GetDefaut_Cible();
        default:
            return false;
    }
}

bool Partie::GetDefaut_Faction_selection() const {
    switch (GetAction()) {
        case ACTION_ATTAQUER:
            return FACTION_ADVERSE;
        case ACTION_OBJETS:
            if (GetObjet_selection() == 0
            || ((Utilisable*)GetObjet_selection())->GetEffet() == 0)
                return false;
            return ((Utilisable*)GetObjet_selection())->GetEffet()->GetDefaut_Faction();
        case ACTION_CAPACITE:
            if (GetCapacite_selection() == 0
            || GetCapacite_selection()->GetEffet() == 0)
                return false;
            return GetCapacite_selection()->GetEffet()->GetDefaut_Faction();
        default:
            return FACTION_LANCEUR;
    }
}

bool Partie::GetDefaut_Quantite_selection() const {
    switch (GetAction()) {
        case ACTION_ATTAQUER:
            return false;
        case ACTION_OBJETS:
            if (GetObjet_selection() == 0
            || ((Utilisable*)GetObjet_selection())->GetEffet() == 0)
                return false;
            return ((Utilisable*)GetObjet_selection())->GetEffet()->GetDefaut_Quantite();
        case ACTION_CAPACITE:
            if (GetCapacite_selection() == 0
            || GetCapacite_selection()->GetEffet() == 0)
                return false;
            return GetCapacite_selection()->GetEffet()->GetDefaut_Quantite();
        default:
            return false;
    }
}

void Partie::SetCible_Defaut() {//Pour l'équipe : les monstres n'ont pas de curseur
    SetFactionLanceur(FACTION_EQUIPE); //Pour l'équipe : pour ne pas risquer de considérer le joueur comme un monstre
    SetCible(GetDefaut_Cible_selection());
    SetFaction(GetDefaut_Faction_selection());
    SetQuantite(GetDefaut_Quantite_selection());
    if (GetCible() == CIBLE_LANCEUR)
        SetFaction(FACTION_LANCEUR);
    if (GetCible() == CIBLE_LANCEUR)
        SetCible(GetHeros()); //Ne marche que pour l'équipe
    //Possibilité de viser l'équipe du lanceur? => Quantité inchangée
}

Personnage* Partie::GetActeur() const {
    return m_Acteur;
}

void Partie::SetActeur(Personnage* val) {
    m_Acteur = val;
}

int Partie::GetLanceur() const {
    return m_Lanceur;
}

void Partie::SetLanceur(int val) {
    m_Lanceur = val;
}

bool Partie::GetFactionLanceur() const {
    return m_FactionLanceur;
}

void Partie::SetFactionLanceur(bool val) {
    m_FactionLanceur = val;
}

Personnage* Partie::GetLanceur_selection() const {
    if (GetFactionLanceur() == FACTION_EQUIPE)
        return (Personnage*)GetEquipe()->GetHeros(GetLanceur());
    if (GetFactionLanceur() == FACTION_MONSTRES)
        return (Personnage*)GetGroupeCombat()->GetMonstres(GetLanceur());
    return 0;
}

char Partie::GetChoix() const {
    return m_Choix;
}

void Partie::SetChoix(char val) {
    m_Choix = val;
}

char Partie::GetSituation() const {
    return m_Situation;
}

void Partie::SetSituation(char val) {
    m_Situation = val;
}

bool Partie::GetTerrain() const {
    return m_Terrain;
}

void Partie::SetTerrain(bool val){
    m_Terrain = val;
}

unsigned char Partie::GetEvenement() const {
    return m_Evenement;
}

// Evenement* Partie::GetEvenement_selection() const {
//     if (GetCarte() == 0)
//         return 0;
//     return GetCarte()->GetEvenement(GetEvenement());
// }

void Partie::SetEvenement(unsigned char val) {
    m_Evenement = val;
}

int Partie::Ecrire(char* data) const {
    unsigned int i = 0, j, k;
    ECRIRE_3CHIFFRES(i,data,GetId());
    data[i++] = ' ';
    //Stats
    char tbuf[10];
    EntierGauche(GetOr(), tbuf, 10);
    ECRIRE_CHAINE(i,j,data,tbuf,9);
    data[i++] = ' ';
    EntierGauche(GetTempsJeu(), tbuf, 10);
    ECRIRE_CHAINE(i,j,data,tbuf,9);
    data[i++] = ' ';
    EntierGauche(GetPas(), tbuf, 10);
    ECRIRE_CHAINE(i,j,data,tbuf,9);
    data[i++] = ' ';
    data[i++] = ' ';
    //Options
    ECRIRE_CHIFFRE(i,data,GetVitesseCombat());
    data[i++] = ' ';
    ECRIRE_CHIFFRE(i,data,GetModeCombat());
    data[i++] = ' ';
    ECRIRE_BOOLEEN(i,data,GetMemoriserCurseur());
    data[i++] = ' ';
    data[i++] = ' ';

    //Position
    if (GetCarte()) {
        EntierGauche(GetCarte()->GetId(), tbuf, 10);
        ECRIRE_CHAINE(i,j,data,tbuf,9);
    } else
        data[i++] = '0';
    data[i++] = ' ';
    EntierGauche(GetX(), tbuf, 10);
    ECRIRE_CHAINE(i,j,data,tbuf,9);
    data[i++] = ' ';
    EntierGauche(GetY(), tbuf, 10);
    ECRIRE_CHAINE(i,j,data,tbuf,9);
    data[i++] = ' ';
    ECRIRE_CHIFFRE(i,data,GetOrientation());
    data[i++] = ' ';
    ECRIRE_CHIFFRE(i,data,GetMeneur());
    data[i++] = '\n';

    //Inventaire
    Inventaire* inventaire = GetInventaire();
    for (k = 0; k < MAX_OBJETS; ++k) {
        ECRIRE_3CHIFFRES(i,data,inventaire->GetId(k));
        data[i++] = ' ';
        ECRIRE_2CHIFFRES(i,data,inventaire->GetNombre(k));
        data[i++] = '\n';
    }
    //Equipe
    for (k = 0; k < MAX_HEROS_EQUIPE; ++k) {
        Heros* heros = GetEquipe()->GetHeros(k);
        //Stats :
        if (heros) {
            ECRIRE_CHIFFRE(i,data,heros->GetId());
            data[i++] = ' ';
            ECRIRE_CHAINE(i,j,data,heros->GetNom(),TAILLE_NOM_PERSONNAGE);
            data[i++] = ' ';
            ECRIRE_3CHIFFRES(i,data,heros->GetVie());
            data[i++] = ' ';
            ECRIRE_3CHIFFRES(i,data,heros->GetMagie());
            data[i++] = ' ';
            for (j = 0; j < NOMBRE_ATTRIBUTS; ++j) {
                ECRIRE_3CHIFFRES(i,data,heros->GetAttribut(j));
                data[i++] = ' ';
            }
            ECRIRE_CHIFFRE(i,data,heros->GetStatut());
            data[i++] = ' ';
            ECRIRE_3CHIFFRES(i,data,heros->GetExperience());
            data[i++] = ' ';
            ECRIRE_2CHIFFRES(i,data,heros->GetNiveau());
            data[i++] = ' ';
            ECRIRE_2CHIFFRES(i,data,heros->GetForce());
            data[i++] = ' ';
            ECRIRE_2CHIFFRES(i,data,heros->GetIntelligence());
            data[i++] = ' ';
            ECRIRE_2CHIFFRES(i,data,heros->GetAgilite());
            data[i++] = ' ';
            ECRIRE_BOOLEEN(i,data,heros->GetRang());
            //Equipement :
            for (j = 0; j < NOMBRE_EQUIPEMENTS; ++j) {
                data[i++] = ' ';
                if (heros->GetEquipement(j)) {
                    ECRIRE_3CHIFFRES(i,data,heros->GetEquipement(j)->GetId());
                } else
                    data[i++] = '0';
            }
            data[i++] = '\n';
            //Capacités - Magies :
            for (j = 0; j < MAX_SORTS; ++j) {
                if (heros->GetSorts(j)) {
                    ECRIRE_3CHIFFRES(i,data,heros->GetSorts(j)->GetId());
                } else
                    data[i++] = '0';
                data[i++] = ' ';
            }
            data[i++] = '\n';
            //Alterations :
            for (j = 0; j < MAX_ALTERATIONS; ++j) {
                if (heros->GetAlterations(j)) {
                    ECRIRE_2CHIFFRES(i,data,heros->GetAlterations(j)->GetId());
                } else
                    data[i++] = '0';
                data[i++] = ' ';
            }
        } else {
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '_';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            for (j = 0; j < NOMBRE_ATTRIBUTS; ++j) {
                data[i++] = '0';
                data[i++] = ' ';
            }
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            //Equipement :
            for (j = 0; j < NOMBRE_EQUIPEMENTS; ++j) {
                data[i++] = ' ';
                data[i++] = '0';
            }
            data[i++] = '\n';
            //Capacités - Magies :
            for (j = 0; j < MAX_SORTS; ++j) {
                data[i++] = '0';
                data[i++] = ' ';
            }
            data[i++] = '\n';
            //Alterations :
            for (j = 0; j < MAX_ALTERATIONS; ++j) {
                data[i++] = '0';
                data[i++] = ' ';
            }
        }
        data[i++] = '\n';
    }

    return i;
}

void Partie::Lire(int& i, const char* data) {
    unsigned int id = 0;
    unsigned int nombre = 0;
    unsigned int j;
    LIRE_ENTIER(i,data,m_Id);
    //Stats
    LIRE_ENTIER(i,data,m_Or);
    LIRE_ENTIER(i,data,m_Temps);
    LIRE_ENTIER(i,data,m_Pas); LIRE_SUIVANT(i,data);
    //Options
    LIRE_ENTIER(i,data,m_VitesseCombat);
    LIRE_ENTIER(i,data,m_ModeCombat);
    LIRE_ENTIER(i,data,m_MemoriserCurseur); LIRE_SUIVANT(i,data);
    //Position
    LIRE_ENTIER(i,data,id);
    LIRE_ENTIER(i,data,m_X);
    LIRE_ENTIER(i,data,m_Y);
    LIRE_ENTIER(i,data,m_Orientation);
    LIRE_ENTIER(i,data,m_Meneur); LIRE_SUIVANT(i,data);
    // char* fbuf = new char[8192];
    // char fichier[] = "bdd/cartes/0.txt";
    // fichier[11] += id;
    // if (fichier_lire(fichier, fbuf)) {
    //     int j = 0;
    //     m_Carte = new Carte(id);
    //     m_Carte->Lire(j, fbuf);
    // }
    m_Carte = cartes[id];
    //Inventaire
    for (j = 0; j < MAX_OBJETS; ++j) {
        LIRE_ENTIER(i,data,id);
        LIRE_ENTIER(i,data,nombre); LIRE_SUIVANT(i,data);
        m_Inventaire->SetObjets(objets[id],nombre,j);
    }
    //Equipe
    for (j = 0; j < MAX_HEROS_EQUIPE; ++j) {
        LIRE_ENTIER(i,data,id);
        Heros* heros = new Heros(id); //on crée un héros même si id est 0
        //Stats, Equipement :
        heros->Lire(i, data);
        LIRE_SUIVANT(i,data);
        //Capacités - Magies :
        unsigned int k, l;
        for (l = 0; l < MAX_SORTS; ++l) {
            LIRE_ENTIER(i,data,k);
            if (k)
                heros->AjouterSorts(capacites[k]);
        }
        LIRE_SUIVANT(i,data);
        for (l = 0; l < MAX_ALTERATIONS; ++l) {
            LIRE_ENTIER(i,data,k);
            if (k)
                heros->AjouterAlteration(alterations[k]);
        }
        LIRE_SUIVANT(i,data);
        if (id)
            m_Equipe->SetHeros(heros,j);
        else
            delete heros;
    }
}