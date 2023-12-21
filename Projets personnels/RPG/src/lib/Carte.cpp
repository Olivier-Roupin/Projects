#include "lib/Carte.h"

#define MAX_EVENEMENTS_CARTE 99
#define MAX_GROUPES_RENCONTRESET 5
#define MAX_RENCONTRESET_CARTE 10

#define MAX_LARGEUR_CARTE 256
#define MAX_HAUTEUR_CARTE 256

Rencontreset::Rencontreset(unsigned char nombre) {
    unsigned char i;
    m_Nombre = nombre;
    //SetNombre(nombre);
    if (m_Nombre) {
        m_Groupes = new GroupeMonstres**[m_Nombre+1];
        m_NombreGroupes = new unsigned char[m_Nombre+1];
        for (i = 0; i < m_Nombre+1; ++i) {
            m_Groupes[i] = 0;
            m_NombreGroupes[i] = 0;
        }
    } else {
        m_NombreGroupes = 0;
        m_Groupes = 0;
    }
}

Rencontreset::~Rencontreset() {
}

unsigned char Rencontreset::GetNombre() const {
    return m_Nombre;
}

void Rencontreset::SetNombre(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    if (val > MAX_RENCONTRESET_CARTE)
        val = MAX_RENCONTRESET_CARTE;
    if (val == m_Nombre)
        return;
    GroupeMonstres*** nouveau = new GroupeMonstres**[val];
    unsigned char* nombreGroupes = new unsigned char[val];
    unsigned char i;
    if (val > m_Nombre) {
        for (i = 0; i < m_Nombre; ++i) {
            nouveau[i] = m_Groupes[i];
            nombreGroupes[i] = m_NombreGroupes[i];
        }
        for (i = m_Nombre; i < val; ++i) {
            nouveau[i] = 0;
            nombreGroupes[i] = 0;
        }
    } else {
        for (i = 0; i < val; ++i) {
            nouveau[i] = m_Groupes[i];
            nombreGroupes[i] = m_NombreGroupes[i];
        }
        for (i = val; i < m_Nombre; ++i)
            delete m_Groupes[i];
    }
    delete[] m_Groupes;
    delete[] m_NombreGroupes;
    m_Groupes = nouveau;
    m_NombreGroupes = nombreGroupes;
    m_Nombre = val;
}

unsigned char Rencontreset::GetNombreGroupes(unsigned char id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_NombreGroupes[id];
}

void Rencontreset::SetNombreGroupes(unsigned char val, unsigned char id) {
    // if (val < 0)
    //     val = 0;
    if (val > MAX_GROUPES_RENCONTRESET)
        val = MAX_GROUPES_RENCONTRESET;
    // if (val == GetNombreGroupes(id))
    if (val == m_NombreGroupes[id])
        return;
    GroupeMonstres** nouveau = new GroupeMonstres*[val];
    unsigned char i;
    // if (val > GetNombreGroupes(id)) {
    if (val > m_NombreGroupes[id]) {
        // for (i = 0; i < GetNombreGroupes(id); i++)
        for (i = 0; i < m_NombreGroupes[id]; ++i)
            nouveau[i] = m_Groupes[id][i];
        // for (i = GetNombreGroupes(id); i < val; i++)
        for (i = m_NombreGroupes[id]; i < val; ++i)
            nouveau[i] = 0;
    } else
        for (i = 0; i < val; i++)
            nouveau[i] = m_Groupes[id][i];
    delete m_Groupes[id];
    m_Groupes[id] = nouveau;
    m_NombreGroupes[id] = val;
}

GroupeMonstres* Rencontreset::GetGroupes(unsigned char i, unsigned char j) const {
    // if (i < 0 || i >= GetNombre() || j < 0 || j >= GetNombreGroupes(i))
    if (i >= m_Nombre || j >= m_NombreGroupes[i])
        return 0;
    return m_Groupes[i][j];
}

void Rencontreset::SetGroupes(GroupeMonstres* val, unsigned char i, unsigned char j) {
    if (val == 0)
        m_Groupes[i][j] = 0;
    m_Groupes[i][j] = val;
}

void Rencontreset::Ecrire(int& i, char* data) const {
    unsigned int j, k;
    // for (j = 0; j < GetNombre(); ++j) {
    for (j = 0; j < m_Nombre; ++j) {
        // ECRIRE_2CHIFFRES(i,data,GetNombreGroupes(j));
        ECRIRE_2CHIFFRES(i,data,m_NombreGroupes[j]);
        // for (k = 0; k < GetNombreGroupes(j); k++) {
        for (k = 0; k < m_NombreGroupes[j]; ++k) {
            data[i++] = ' ';
            // if (GetGroupes(j,k)) {
            if (m_Groupes[j][k]) {
                // ECRIRE_2CHIFFRES(i,data,GetGroupes(j,k)->GetId());
                ECRIRE_2CHIFFRES(i,data,m_Groupes[j][k]->GetId());
            } else
                data[i++] = '0';
        }
        data[i++] = '\n';
    }
    //data[i++] = '\0';
}

extern GroupeMonstres* groupes_monstres[];

void Rencontreset::Lire(int& i, const char* data) {
    unsigned int j, k, entier;
    // for (j = 0; j < GetNombre(); j++) {
    for (j = 0; j < m_Nombre; ++j) {
        LIRE_ENTIER(i,data,entier); SetNombreGroupes(entier,j);
        // LIRE_ENTIER(i,data,entier); m_NombreGroupes[j] = entier;
        // for (k = 0; k < GetNombreGroupes(j); k++) {
        for (k = 0; k < m_NombreGroupes[j]; ++k) {
            // LIRE_ENTIER(i,data,entier);SetGroupes(groupes_monstres[entier],j,k);
            LIRE_ENTIER(i,data,entier); m_Groupes[j][k] = groupes_monstres[entier];
        }
        LIRE_SUIVANT(i,data);
    }
}

unsigned int Rencontreset::TailleD() const {
    unsigned char i;
    unsigned int taille = 0;
    for (i = 0; i < m_Nombre; ++i)
        taille += m_NombreGroupes[i];
    // return 1+m_Nombre+taille;
    return m_Nombre+taille;
}

char* Rencontreset::EcrireD(char* data) const {
    unsigned int i = 0, j, k;
    --i;
    for (j = 0; j < m_Nombre; ++j) {
        data[++i] = m_NombreGroupes[j];
        for (k = 0; k < m_NombreGroupes[j]; ++k)
            data[++i] = m_Groupes[j][k] ? m_Groupes[j][k]->GetId() : 0;
    }
    return &data[i+1];
}

const char* Rencontreset::LireD(const char* data) {
    unsigned int i = 0, j, k;
    --i;
    for (j = 0; j < m_Nombre; ++j) {
        m_NombreGroupes[j] = data[++i];
        m_Groupes[j] = m_NombreGroupes[j] ? new GroupeMonstres*[m_NombreGroupes[j]] : 0;
        for (k = 0; k < m_NombreGroupes[j]; ++k)
            m_Groupes[j][k] = groupes_monstres[(unsigned char)data[++i]];
    }
    return &data[i+1];
}

Carte::Carte(int id, const char* nom) {
    SetId(id);
    SetNom(nom);
    m_Largeur = 0;
    m_Hauteur = 0;
    m_Repetition = false;
    // m_Bas = 0;
    // m_Moyen = 0;
    // m_Haut = 0;
    m_Tuiles = 0;
    m_Rencontres = 0;
    m_Tileset = 0;
    m_Nombre = 0;
    m_Evenements = 0;
    m_Rencontreset = 0;
    SetFond("_");
}

Carte::~Carte() {
    if (m_Tuiles)
        delete[] m_Tuiles;
    // if (m_Rencontres)
    //     delete[] m_Rencontres;
    // if (m_Rencontreset)
    //     delete[] m_Rencontreset;
    // if (m_Evenements)
    //     delete[] m_Evenements;
}

int Carte::GetId() const {
    return m_Id;
}

void Carte::SetId(int val) {
    if (val < 0)
        val = 0;
    m_Id = val;
}

const char* Carte::GetNom() const {
    return m_Nom;
}

void Carte::SetNom(const char* val) {
    for (int i = 0; i < TAILLE_NOM_CARTE; i++) {
        m_Nom[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Nom[TAILLE_NOM_CARTE] = '\0';
}

unsigned int Carte::GetLargeur() const {
    return m_Largeur;
}

void Carte::SetLargeur(unsigned int val) {
    if (val < 1)
        val = 1;
    if (val > MAX_LARGEUR_CARTE)
        val = MAX_LARGEUR_CARTE;
    // if (val == GetLargeur())
    if (val == m_Largeur)
        return;

    // unsigned char* nouveau_Tuiles = new unsigned char[val*GetHauteur()*NOMBRE_Z];
    unsigned char* nouveau_Tuiles = new unsigned char[val*m_Hauteur*NOMBRE_Z];
    unsigned char* nouveau_Rencontres = 0;
    if (m_Rencontres)
        // nouveau_Rencontres = new unsigned char[val*GetHauteur()];
        nouveau_Rencontres = new unsigned char[val*m_Hauteur];
    unsigned int i,j,k;

    // if (val > GetLargeur()) {
    if (val > m_Largeur) {
        for (k = 0; k < NOMBRE_Z; ++k)
            // for (j = 0; j < GetHauteur(); ++j) {
            for (j = 0; j < m_Hauteur; ++j) {
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    // nouveau_Tuiles[i+val*(j+GetHauteur()*k)] = m_Tuiles[i+GetLargeur()*(j+GetHauteur()*k)];
                    nouveau_Tuiles[i+val*(j+m_Hauteur*k)] = m_Tuiles[i+m_Largeur*(j+m_Hauteur*k)];
                for (; i < val; ++i)
                    nouveau_Tuiles[i+val*(j+GetHauteur()*k)] = 0;
            }
        if (m_Rencontres)
            // for (j = 0; j < GetHauteur(); j++) {
            for (j = 0; j < m_Hauteur; j++) {
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    nouveau_Rencontres[i+val*j] = m_Rencontres[i+m_Largeur*j];
                for (; i < val; ++i)
                    nouveau_Rencontres[i+val*j] = 0;
            }
    } else {
        for (k = 0; k < NOMBRE_Z; ++k)
            // for (j = 0; j < GetHauteur(); ++j)
            for (j = 0; j < m_Hauteur; ++j)
                for (i = 0; i < val; ++i)
                    // nouveau_Tuiles[i+val*(j+GetHauteur()*k)] = m_Tuiles[i+GetLargeur()*(j+GetHauteur()*k)];
                    nouveau_Tuiles[i+val*(j+m_Hauteur*k)] = m_Tuiles[i+m_Largeur*(j+m_Hauteur*k)];
        if (m_Rencontres)
            // for (j = 0; j < GetHauteur(); ++j)
            for (j = 0; j < m_Hauteur; ++j)
                for (i = 0; i < val; ++i)
                    // nouveau_Rencontres[i+val*j] = m_Rencontres[i+GetLargeur()*j];
                    nouveau_Rencontres[i+val*j] = m_Rencontres[i+m_Largeur*j];
    }

    delete[] m_Tuiles;
    m_Tuiles = nouveau_Tuiles;
    if (m_Rencontres) {
        delete[] m_Rencontres;
        m_Rencontres = nouveau_Rencontres;
    }
    m_Largeur = val;
}

unsigned int Carte::GetHauteur() const {
    return m_Hauteur;
}

void Carte::SetHauteur(unsigned int val) {
    if (val < 1)
        val = 1;
    if (val > MAX_HAUTEUR_CARTE)
        val = MAX_HAUTEUR_CARTE;
    // if (val == GetHauteur())
    if (val == m_Hauteur)
        return;

    // unsigned char* nouveau_Tuiles = new unsigned char[val*GetLargeur()*NOMBRE_Z];
    unsigned char* nouveau_Tuiles = new unsigned char[val*m_Largeur*NOMBRE_Z];
    unsigned char* nouveau_Rencontres = 0;
    if (m_Rencontres)
        // nouveau_Rencontres = new unsigned char[val*GetLargeur()];
        nouveau_Rencontres = new unsigned char[val*m_Largeur];
    unsigned int i,j,k;

    // if (val > GetHauteur()) {
    if (val > m_Hauteur) {
        for (k = 0; k < NOMBRE_Z; ++k)
            // for (j = 0; j < GetHauteur(); ++j)
            for (j = 0; j < m_Hauteur; ++j)
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    // nouveau_Tuiles[i+GetLargeur()*(j+val*k)] = m_Tuiles[i+GetLargeur()*(j+GetHauteur()*k)];
                    nouveau_Tuiles[i+m_Largeur*(j+val*k)] = m_Tuiles[i+m_Largeur*(j+m_Hauteur*k)];
        if (m_Rencontres) {
            // for (j = 0; j < GetHauteur(); ++j)
            for (j = 0; j < m_Hauteur; ++j)
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    // nouveau_Rencontres[i+GetLargeur()*j] = m_Rencontres[i+GetLargeur()*j];
                    nouveau_Rencontres[i+m_Largeur*j] = m_Rencontres[i+m_Largeur*j];
            for (; j < val; ++j)
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    // nouveau_Rencontres[i+GetLargeur()*j] = 0;
                    nouveau_Rencontres[i+m_Largeur*j] = 0;
        }
    } else {
        for (k = 0; k < NOMBRE_Z; ++k)
            for (j = 0; j < val; ++j)
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    // nouveau_Tuiles[i+GetLargeur()*(j+val*k)] = m_Tuiles[i+GetLargeur()*(j+GetHauteur()*k)];
                    nouveau_Tuiles[i+m_Largeur*(j+val*k)] = m_Tuiles[i+m_Largeur*(j+m_Hauteur*k)];
        if (m_Rencontres)
            for (j = 0; j < val; ++j)
                // for (i = 0; i < GetLargeur(); ++i)
                for (i = 0; i < m_Largeur; ++i)
                    // nouveau_Rencontres[i+GetLargeur()*j] = m_Rencontres[i+GetLargeur()*j];
                    nouveau_Rencontres[i+m_Largeur*j] = m_Rencontres[i+m_Largeur*j];
    }
    delete[] m_Tuiles;
    m_Tuiles = nouveau_Tuiles;
    if (m_Rencontres) {
        delete[] m_Rencontres;
        m_Rencontres = nouveau_Rencontres;
    }
    m_Hauteur = val;
}

bool Carte::GetRepetition() const {
    return m_Repetition;
}

void Carte::SetRepetition(bool val) {
    m_Repetition = val;
}

bool Carte::GetRepetition(int &i, int &j) const {
    if (m_Repetition) {
        i = (i+m_Largeur) % m_Largeur;
        j = (j+m_Hauteur) % m_Hauteur;
    }
    return m_Repetition;
}

unsigned char Carte::GetTuile(int i) const {
    if (i < 0 || (unsigned int)i >= NOMBRE_Z*GetTaille())
        return 0;
    return m_Tuiles[i];
}

unsigned char Carte::GetTuile(int i, int j, unsigned char k) const {
    // if (i < 0 || i >= GetLargeur()
    //  || j < 0 || j >= GetHauteur() || k >= NOMBRE_Z)
    //     return 0;
    // return m_Tuiles[i+GetLargeur()*(j+GetHauteur()*k)];
    return m_Tuiles[i+m_Largeur*(j+m_Hauteur*k)];
}

void Carte::SetTuile(unsigned char val, int i, int j, unsigned char k) {
    // if (val >= GetTileset()->GetNombre())
    //     val = 0;
    // m_Tuiles[i+GetLargeur()*(j+GetHauteur()*k)] = val;
    m_Tuiles[i+m_Largeur*(j+m_Hauteur*k)] = val;
}

const char* Carte::GetImageTuile(int i, int j, unsigned char k) const {
    // if (GetTileset() == 0)
    if (m_Tileset == 0)
        return "_";
    // if (i < 0 || i >= GetLargeur()
    //  || j < 0 || j >= GetHauteur() || k >= NOMBRE_Z)
    //     return "_";
    // return GetTileset()->GetImage(GetTuile(i,j,k));
    return m_Tileset->GetImage(GetTuile(i,j,k));
}

unsigned char Carte::GetRencontres(int i, int j) const {
    if (m_Rencontres == 0
    //  || i+GetLargeur()*j < 0 || i+GetLargeur()*j >= GetTaille())
     || i+m_Largeur*j >= GetTaille())
        return 0;
    return m_Rencontres[i+m_Largeur*j];
}

void Carte::SetRencontres(unsigned char val, int i, int j) {
    // if (val < 0)
    //     val = 0;
    // m_Rencontres[i+GetLargeur()*j] = val;
    m_Rencontres[i+m_Largeur*j] = val;
}

Tileset* Carte::GetTileset() const {
    return m_Tileset;
}

void Carte::SetTileset(Tileset* val) {
    m_Tileset = val;
}

unsigned int Carte::GetTaille() const {
    // return GetHauteur()*GetLargeur();
    return m_Hauteur*m_Largeur;
}

unsigned char Carte::GetNombre() const {
    return m_Nombre;
}

void Carte::SetNombre(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    if (val > MAX_EVENEMENTS_CARTE)
        val = MAX_EVENEMENTS_CARTE;
    // if (val == GetNombre())
    if (val == m_Nombre)
        return;
    Evenement** nouveau = new Evenement*[val];
    unsigned char i;
    // if (val > GetNombre()) {
    if (val > m_Nombre) {
        // for (i = 0; i < GetNombre(); i++)
        for (i = 0; i < m_Nombre; ++i)
            nouveau[i] = m_Evenements[i];
        // for (i = GetNombre(); i < val; i++)
        for (i = m_Nombre; i < val; ++i)
            nouveau[i] = 0;
    }
    else
        for (i = 0; i < val; ++i)
            nouveau[i] = m_Evenements[i];
    delete[] m_Evenements;
    m_Evenements = nouveau;
    m_Nombre = val;
}

Evenement* Carte::GetEvenements(unsigned char id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_Evenements[id];
}

void Carte::SetEvenements(Evenement* val, unsigned char id) {
    m_Evenements[id] = val;
}

Rencontreset* Carte::GetRencontreset() const {
    return m_Rencontreset;
}

void Carte::SetRencontreset(Rencontreset* val) {
    m_Rencontreset = val;
}

/*int Carte::GetNombreFonds() const {
    return m_NombreFonds;
}

void Carte::SetNombreFonds(int val) {
    if (val < 0)
        val = 0;
    m_NombreFonds = val;
}

const char* Carte::GetFonds(int id) const {
}

void Carte::SetFonds(const char* val, int id) {
}*/

const char* Carte::GetFond() const {
    return m_Fond;
}

void Carte::SetFond(const char* val) {
    for (unsigned int i = 0; i < TAILLE_FOND_CARTE; i++) {
        m_Fond[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Fond[TAILLE_FOND_CARTE] = '\0';
}

bool Carte::GetTraversable(int i, int j) const {
    if (GetTileset() == 0)
        return false;
    return (GetTileset()->GetTraversable(GetTuile(i,j,Z_BAS   )) != 0) &&\
           (GetTileset()->GetTraversable(GetTuile(i,j,Z_MILIEU)) != 0) &&\
           (GetTileset()->GetTraversable(GetTuile(i,j,Z_HAUT  )) != 0);
}

void Carte::Ecrire(char* data) const {
    int i = 0;
    unsigned int j;
    ECRIRE_CHAINE(i,j,data,m_Nom,TAILLE_NOM_CARTE);
    data[i++] = ' ';
    ECRIRE_CHAINE(i,j,data,m_Fond,TAILLE_FOND_CARTE);
    data[i++] = ' ';
    // ECRIRE_3CHIFFRES(i,data,GetLargeur());
    ECRIRE_3CHIFFRES(i,data,m_Largeur);
    data[i++] = ' ';
    // ECRIRE_3CHIFFRES(i,data,GetHauteur());
    ECRIRE_3CHIFFRES(i,data,m_Hauteur);
    data[i++] = ' ';
    // ECRIRE_BOOLEEN(i,data,GetRepetition());
    ECRIRE_BOOLEEN(i,data,m_Repetition);
    data[i++] = ' ';
    if (GetTileset()) {
        ECRIRE_2CHIFFRES(i,data,GetTileset()->GetId());
    } else
        data[i++] = '0';
    data[i++] = '\n';
    ECRIRE_2CHIFFRES(i,data,GetNombre());
    data[i++] = ' ';
    if (GetRencontreset()) {
        ECRIRE_2CHIFFRES(i,data,GetRencontreset()->GetNombre());
    } else
        data[i++] = '0';
    data[i++] = '\n';

    for (j = 0; j < GetNombre(); j++) {
        if (GetEvenements(j)) {
            ECRIRE_2CHIFFRES(i,data,GetEvenements(j)->GetId());
            data[i++] = ' ';
            ECRIRE_3CHIFFRES(i,data,GetEvenements(j)->GetX());
            data[i++] = ' ';
            ECRIRE_3CHIFFRES(i,data,GetEvenements(j)->GetY());
            data[i++] = ' ';
            ECRIRE_CHIFFRE(i,data,GetEvenements(j)->GetZ());
            data[i++] = ' ';
            ECRIRE_BOOLEEN(i,data,GetEvenements(j)->GetTraversable());
            data[i++] = '\n';
        } else {
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = ' ';
            data[i++] = '0';
            data[i++] = '\n';
        }
    }
    if (GetRencontreset() && GetRencontreset()->GetNombre())
        GetRencontreset()->Ecrire(i, data);

    for (j = 0; j < NOMBRE_Z*GetTaille(); j++)
        // if (j % GetLargeur()) {
        if (j % m_Largeur) {
            data[i++] = ' ';
            ECRIRE_CHIFFRE(i,data,GetTuile(j));
        } else {
            if (j % GetTaille() == 0)
                data[i++] = '\n';
            data[i++] = '\n';
            ECRIRE_CHIFFRE(i,data,GetTuile(j));
        }
    data[i++] = '\n';
    if (GetRencontreset() && GetRencontreset()->GetNombre()) {
        for (j = 0; j < GetTaille(); j++)
            // if (j % GetLargeur()) {
            if (j % m_Largeur) {
                data[i++] = ' ';
                ECRIRE_CHIFFRE(i,data,GetRencontres(j));
            } else {
                data[i++] = '\n';
                ECRIRE_CHIFFRE(i,data,GetRencontres(j));
            }
    }
    data[i++] = '\n';
    data[i++] = '\0';
}

extern Evenement* evenements[];
extern Tileset* tilesets[];

void Carte::Lire(int& i, const char* data) {
    unsigned int j = 0;
    char nom[TAILLE_NOM_CARTE+1];
    LIRE_CHAINE(i,j,data,nom,TAILLE_NOM_CARTE); SetNom(nom);
    j = 0;
    char fond[TAILLE_FOND_CARTE+1];
    LIRE_CHAINE(i,j,data,fond,TAILLE_FOND_CARTE); SetFond(fond);

    int entier;
    LIRE_ENTIER(i,data,entier); m_Largeur = entier;
    LIRE_ENTIER(i,data,entier); m_Hauteur = entier;
    bool booleen;
    LIRE_BOOLEEN(i,data,booleen); SetRepetition(booleen);
    LIRE_ENTIER(i,data,entier);   SetTileset(tilesets[entier]);
    LIRE_SUIVANT(i,data);

    LIRE_ENTIER(i,data,entier);   m_Nombre = entier;
    int nombre_rencontres;
    LIRE_ENTIER(i,data,nombre_rencontres);
    LIRE_SUIVANT(i,data);

    m_Evenements = new Evenement*[GetNombre()];
    for (j = 0; j < GetNombre(); j++) {
        int evenement;
        LIRE_ENTIER(i,data,evenement);
        LIRE_ENTIER(i,data,entier); evenements[evenement]->SetX(entier);
        LIRE_ENTIER(i,data,entier); evenements[evenement]->SetY(entier);
        LIRE_ENTIER(i,data,entier); evenements[evenement]->SetZ(entier);
        evenements[evenement]->SetDeplace(0);
        evenements[evenement]->SetDx(0);
        evenements[evenement]->SetDy(0);
        LIRE_BOOLEEN(i,data,booleen); evenements[evenement
                                                 ]->SetTraversable(booleen);
        SetEvenements(evenements[evenement],j);
        LIRE_SUIVANT(i,data);
    }

    if (nombre_rencontres) {
        m_Rencontreset = new Rencontreset(0);
        m_Rencontreset->SetNombre(nombre_rencontres);
        m_Rencontreset->Lire(i, data);
        LIRE_SUIVANT(i,data);
    }

    m_Tuiles = new unsigned char[GetTaille()*NOMBRE_Z];
    for (j = 0; j < GetTaille()*NOMBRE_Z; ++j) {
        if (j % GetLargeur() == 0)         LIRE_SUIVANT(i,data);
        if (j % GetTaille()*NOMBRE_Z == 0) LIRE_SUIVANT(i,data);
        LIRE_ENTIER(i,data,entier); m_Tuiles[j] = entier;
    }

    if (GetRencontreset() && GetRencontreset()->GetNombre()) {
        m_Rencontres = new unsigned char[GetTaille()];
        for (j = 0; j < GetTaille(); j++) {
            if (j % GetLargeur() == 0) LIRE_SUIVANT(i,data);
            LIRE_ENTIER(i,data,entier); m_Rencontres[j] = entier;
        }
    }
}

unsigned int Carte::TailleD() const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_CARTE; ++i)
        if (m_Nom[i] == '\0')
            break;
    if (m_Rencontreset && m_Rencontreset->GetNombre())
        return i+TAILLE_FOND_CARTE+2 +2 +2 +m_Nombre*5 +m_Rencontreset->TailleD() +\
               m_Largeur*m_Hauteur*NOMBRE_Z +m_Largeur*m_Hauteur;
    return i+TAILLE_FOND_CARTE+2 +2 +2 +m_Nombre*5 +\
           m_Largeur*m_Hauteur*NOMBRE_Z;
}

char* Carte::EcrireD(char* data) const {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_CARTE; ++i) {
        data[i] = m_Nom[i]; //0 est écrit s'il est présent
        if (m_Nom[i] == '\0')
            break;
    }
    if (i == TAILLE_NOM_CARTE) --i;
    // unsigned int j;
    // for (j = 0; j < TAILLE_FOND_CARTE; ++j)
    //     data[++i] = m_Fond[j];

    unsigned int j;
    for (j = 0; j < TAILLE_FOND_CARTE; ++j) {
        data[++i] = m_Fond[j]; //0 est écrit s'il est présent
        if (m_Fond[j] == '\0')
            break;
    }

    data[++i] = m_Largeur;
    data[++i] = m_Hauteur;
    data[++i] = m_Repetition;
    data[++i] = m_Tileset ? m_Tileset->GetId() : 0;
    data[++i] = m_Nombre;
    data[++i] = m_Rencontreset ? m_Rencontreset->GetNombre() : 0;
    for (j = 0; j < m_Nombre; ++j) {
        if (m_Evenements[j]) {
            data[++i] = m_Evenements[j]->GetId();
            data[++i] = m_Evenements[j]->GetX();
            data[++i] = m_Evenements[j]->GetY();
            data[++i] = m_Evenements[j]->GetZ();
            data[++i] = m_Evenements[j]->GetTraversable();
        } else { // changer m_Nombre et ignorer ?
            data[++i] = 0;
            data[++i] = 0;
            data[++i] = 0;
            data[++i] = 0;
            data[++i] = 0;
        }
    }

    char* p_data = &data[i+1];
    if (m_Rencontreset && m_Rencontreset->GetNombre()) {
        p_data = m_Rencontreset->EcrireD(p_data);
        i = p_data - &data[0];
    }
    --i;
    for (j = 0; j < NOMBRE_Z*m_Largeur*m_Hauteur; ++j)
        data[++i] = m_Tuiles[j];
    if (m_Rencontreset && m_Rencontreset->GetNombre())
        for (j = 0; j < m_Largeur*m_Hauteur; ++j)
            data[++i] = m_Rencontres[j];

    return &data[i+1];
}

const char* Carte::LireD(const char* data) {
    unsigned int i;
    for (i = 0; i < TAILLE_NOM_CARTE; ++i) {
        if (data[i] == '\0')
            break;
        m_Nom[i] = data[i];
    }
    unsigned int j;
    for (j = i; j < TAILLE_NOM_CARTE+1; ++j) // sécurité
        m_Nom[j] = '\0';

    if (i == TAILLE_NOM_CARTE) --i;
    
    // for (j = 0; j < TAILLE_FOND_CARTE; ++j)
    //     m_Fond[j] = data[++i];
    // m_Fond[TAILLE_FOND_CARTE] = '\0';

    for (j = 0; j < TAILLE_FOND_CARTE; ++j) {
        if (data[++i] == '\0')
            break;
        m_Fond[j] = data[i];
    }
    // if (j == TAILLE_FOND_CARTE) --i;

    for (j = i; j < TAILLE_FOND_CARTE+1; ++j) // sécurité
        m_Fond[j] = '\0';

    m_Largeur    = data[++i];
    m_Hauteur    = data[++i];
    m_Repetition = data[++i];
    m_Tileset    = tilesets[(unsigned char)data[++i]];
    m_Nombre     = data[++i];
    unsigned int nombre_rencontres = data[++i];
    m_Evenements = new Evenement*[m_Nombre];
    for (j = 0; j < m_Nombre; ++j) {
        m_Evenements[j] = evenements[(unsigned char)data[++i]];
        if (m_Evenements[j]) {
            m_Evenements[j]->SetX(data[++i]);
            m_Evenements[j]->SetY(data[++i]);
            m_Evenements[j]->SetZ(data[++i]);
            m_Evenements[j]->SetDeplace(0);
            m_Evenements[j]->SetDx(0);
            m_Evenements[j]->SetDy(0);
            m_Evenements[j]->SetTraversable(data[++i]);
        } else
            i += 4; // ne pas écrire dans un pointeur nul
    }

    const char* p_data = &data[i+1];
    if (nombre_rencontres) {
        m_Rencontreset = new Rencontreset(0);
        m_Rencontreset->SetNombre(nombre_rencontres);
        p_data = m_Rencontreset->LireD(p_data);
        i = p_data - &data[0];
    }
    --i;

    m_Tuiles = new unsigned char[m_Largeur*m_Hauteur*NOMBRE_Z];
    for (j = 0; j < NOMBRE_Z*m_Largeur*m_Hauteur; ++j)
        m_Tuiles[j] = (unsigned char)(data[++i]);
    if (m_Rencontreset && m_Rencontreset->GetNombre()) {
        m_Rencontres = new unsigned char[m_Largeur*m_Hauteur];
        for (j = 0; j < m_Largeur*m_Hauteur; ++j)
            m_Rencontres[j] = (unsigned char)(data[++i]);
    }

    return &data[i+1];
}