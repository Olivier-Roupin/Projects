#include "lib/GroupeMonstres.h"

#define MAX_MONSTRES 30
#define MAX_MONSTRES_DISTANCE 255

GroupeMonstres::GroupeMonstres(int id) { //utilisé
    SetId(id);
    m_Nombre = 0;
    m_Monstres = 0;
    SetFond("_");
    m_X = 0;
    m_Y = 0;
}

GroupeMonstres::GroupeMonstres(int id, const GroupeMonstres& cible) {
    //: GroupeMonstres(0, cible.GetNombre())
    unsigned char i;
    SetId(id);
    m_Nombre = cible.GetNombre();
    SetFond(cible.GetFond());

    // m_Monstres = new Monstre*[GetNombre()];
    // m_X = new int[GetNombre()];
    // m_Y = new int[GetNombre()];
    m_Monstres = new Monstre*[m_Nombre];
    m_X = new int[m_Nombre];
    m_Y = new int[m_Nombre];
    Monstre* copie = 0;
    // for (i = 0; i < GetNombre(); ++i) {
    for (i = 0; i < m_Nombre; ++i) {
        if (cible.GetMonstres(i)) {
            copie = new Monstre(*(cible.GetMonstres(i))); //les monstres sont des copies
            SetMonstres(copie,i);
        } else
            m_Monstres[i] = 0;
        SetX(cible.GetX(i),i);
        SetY(cible.GetY(i),i);
    }
}

GroupeMonstres::~GroupeMonstres() {
}

int GroupeMonstres::GetId() const {
    return m_Id;
}

void GroupeMonstres::SetId(int val) {
    if (val < 0)
        val = 0;
    m_Id = val;
}

unsigned char GroupeMonstres::GetNombre() const {
    return m_Nombre;
}

void GroupeMonstres::SetNombre(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    if (val > MAX_MONSTRES)
        val = MAX_MONSTRES;
    // if (val == GetNombre())
    if (val == m_Nombre)
        return;
    Monstre** nouveau = new Monstre*[val];
    int* X = new int[val];
    int* Y = new int[val];
    unsigned char i;
    // if (val > GetNombre()) {
    if (val > m_Nombre) {
        // for (i = 0; i < GetNombre(); ++i) {
        for (i = 0; i < m_Nombre; ++i) {
            nouveau[i] = m_Monstres[i];
            X[i] = m_X[i];
            Y[i] = m_Y[i];
        }
        // for (i = GetNombre(); i < val; ++i) {
        for (i = m_Nombre; i < val; ++i) {
            nouveau[i] = 0;
            X[i] = 0;
            Y[i] = 0;
        }
    } else
        for (i = 0; i < val; ++i) {
            nouveau[i] = m_Monstres[i];
            X[i] = m_X[i];
            Y[i] = m_Y[i];
        }
    delete[] m_Monstres;
    delete[] m_X;
    delete[] m_Y;
    m_Monstres = nouveau;
    m_X = X;
    m_Y = Y;
    m_Nombre = val;
}

// Monstre** GroupeMonstres::GetMonstres() const {
//     return m_Monstres;
// }

Monstre* GroupeMonstres::GetMonstres(unsigned char id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_Monstres[id];
}

void GroupeMonstres::SetMonstres(Monstre* val, unsigned char id) {
    m_Monstres[id] = val;
}

unsigned char GroupeMonstres::ChercherMonstres(Monstre *val) const {
    unsigned char i = 0;
    // int n = GetNombre();
    // while (GetMonstres(i) != val && i < n)
    while (m_Monstres[i] != val && i < m_Nombre)
        ++i;
    // if (i >= n)
    // if (i >= m_Nombre)
        // return -1;
        // return m_Nombre;
    return i; // == m_Nombre si pas trouvé
}

unsigned char GroupeMonstres::ChercherLibre() const {
    return ChercherMonstres();
}

bool GroupeMonstres::AjouterMonstres(Monstre *val, unsigned char nombre) {
    unsigned char k, i;
    for (k = 0; k < nombre; ++k) {
        i = ChercherLibre();
        // if (i != -1)
        if (i != m_Nombre)
            SetMonstres(val,i);
        else
            return false;
    }
    return true;
}

bool GroupeMonstres::AjouterMonstres(Monstre *val, int X, int Y) {
    unsigned char i = ChercherLibre();
    // if (i != -1) {
    if (i != m_Nombre) {
        SetMonstres(val,i);
        SetX(X,i);
        SetY(Y,i);
    }
    else
        return false;
    return true;
}

const char* GroupeMonstres::GetFond() const {
    return m_Fond;
}

void GroupeMonstres::SetFond(const char* val) {
    //m_Fond = val;
    for (unsigned int i = 0; i < TAILLE_FOND_MONSTRES; i++) {
        m_Fond[i] = val[i];
        if (val[i] == '\0') return;
    }
    m_Fond[TAILLE_FOND_MONSTRES] = '\0';
}

// int GroupeMonstres::GetId(int id) const {
//     if (GetMonstres(id) == 0) //GetMonstres vérifie déjà l'id
//         return 0;
//     return GetMonstres(id)->GetId();
// }

int GroupeMonstres::GetX(unsigned char id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_X[id];
}

void GroupeMonstres::SetX(int val, unsigned char id) {
    if (val < 0)
        val = 0;
    m_X[id] = val;
}

int GroupeMonstres::GetY(unsigned char id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_Y[id];
}

void GroupeMonstres::SetY(int val, unsigned char id) {
    if (val < 0)
        val = 0;
    m_Y[id] = val;
}

int GroupeMonstres::GetExperience() const {
    unsigned char i;
    int exp = 0;
    // for (i = 0; i < GetNombre(); ++i)
    for (i = 0; i < m_Nombre; ++i)
        // if (GetMonstres(i))
        if (m_Monstres[i])
            // exp += GetMonstres(i)->GetExperience();
            exp += m_Monstres[i]->GetExperience();
    return exp;
}

int GroupeMonstres::GetOr() const {
    unsigned char i;
    int Or = 0;
    // for (i = 0; i < GetNombre(); ++i)
    for (i = 0; i < m_Nombre; ++i)
        // if (GetMonstres(i))
        if (m_Monstres[i])
            // Or += GetMonstres(i)->GetOr();
            Or += m_Monstres[i]->GetOr();
    return Or;
}
/*
Script* GroupeMonstres::GetScript() const {
    return m_Script;
}

void GroupeMonstres::SetScript(Script* val) {
    if (m_Script)
        delete[] m_Script;
    m_Script = new Script(*val);
}
*/

unsigned char GroupeMonstres::GetNombreEnVie() const { // redondance avec GetNombre() ?
    unsigned char n = 0, i;
    // for (i = 0; i < GetNombre(); ++i)
    for (i = 0; i < m_Nombre; ++i)
        // if (GetMonstres(i) && GetMonstres(i)->estEnVie())
        if (m_Monstres[i] && m_Monstres[i]->estEnVie())
            ++n;
    return n;
}

unsigned char GroupeMonstres::GetHaut(unsigned char id) const {
    // const int x = GetX(id);
    // const int y = GetY(id);
    const int x = m_X[id];
    const int y = m_Y[id];
    // int d = 0, n = id, i;
    int d = 2*MAX_MONSTRES_DISTANCE;
    unsigned char n = id, i;
    // for (i = 0; i < GetNombre(); ++i) {
    for (i = 0; i < m_Nombre; ++i) {
        // if (GetMonstres(i) && GetMonstres(i)->estEnVie() // && d < GetY(i)
        if (m_Monstres[i] && m_Monstres[i]->estEnVie() // && d < GetY(i)
        // && d > y-GetY(i) + (GetX(i) > x ? GetX(i)-x : x-GetX(i))
        && d > y-m_Y[i] + (m_X[i] > x ? m_X[i]-x : x-m_X[i])
        // && d > (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + (GetX(i) > x ? GetX(i)-x : x-GetX(i))
        //&& GetX(i)-x > GetY(i)-y && GetX(i)-x < y-GetY(i)) {
        // && y > GetY(i)) {
        && y > m_Y[i]) {
            n = i;
            // d = GetY(i);
            // d = y-GetY(i) + (GetX(i) > x ? GetX(i)-x : x-GetX(i)); // y > GetY
            d = y-m_Y[i] + (m_X[i] > x ? m_X[i]-x : x-m_X[i]); // y > GetY
            // d = (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + (GetX(i) > x ? GetX(i)-x : x-GetX(i));
        }
    }
    return n;
}

unsigned char GroupeMonstres::GetDroite(unsigned char id) const {
    // const int x = GetX(id);
    // const int y = GetY(id);
    const int x = m_X[id];
    const int y = m_Y[id];
    int d = 2*MAX_MONSTRES_DISTANCE;
    unsigned char n = m_Nombre, i; //TODO: -1 ou m_Nombre ?
    // for (i = 0; i < GetNombre(); ++i) {
    for (i = 0; i < m_Nombre; ++i) {
        // if (GetMonstres(i) && GetMonstres(i)->estEnVie() // && d > GetX(i)
        if (m_Monstres[i] && m_Monstres[i]->estEnVie() // && d > GetX(i)
        // && d > (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + GetX(i)-x
        && d > (m_Y[i] > y ? m_Y[i]-y : y-m_Y[i]) + m_X[i]-x
        //&& GetX(i)-x > GetY(i)-y && GetX(i)-x > y-GetY(i)) {
        // && x < GetX(i)) {
        && x < m_X[i]) {
            n = i;
            // d = GetX(i);
            // d = (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + GetX(i)-x; // x < GetX
            d = (m_Y[i] > y ? m_Y[i]-y : y-m_Y[i]) + m_X[i]-x; // x < GetX
        }
    }
    return n;
}

unsigned char GroupeMonstres::GetBas(unsigned char id) const {
    // const int x = GetX(id);
    // const int y = GetY(id);
    const int x = m_X[id];
    const int y = m_Y[id];
    int d = 2*MAX_MONSTRES_DISTANCE;
    unsigned char n = id, i;
    // for (i = 0; i < GetNombre(); ++i) {
    for (i = 0; i < m_Nombre; ++i) {
        // if (GetMonstres(i) && GetMonstres(i)->estEnVie() // && d > GetY(i)
        if (m_Monstres[i] && m_Monstres[i]->estEnVie() // && d > GetY(i)
        // && d > GetY(i)-y + (GetX(i) > x ? GetX(i)-x : x-GetX(i))
        && d > m_Y[i]-y + (m_X[i] > x ? m_X[i]-x : x-m_X[i])
        // && d > (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + (GetX(i) > x ? GetX(i)-x : x-GetX(i))
        //&& GetX(i)-x < GetY(i)-y && GetX(i)-x > y-GetY(i)) {
        // && y < GetY(i)) {
        && y < m_Y[i]) {
            n = i;
            // d = GetY(i);
            // d = GetY(i)-y + (GetX(i) > x ? GetX(i)-x : x-GetX(i)); // y < GetY
            d = m_Y[i]-y + (m_X[i] > x ? m_X[i]-x : x-m_X[i]); // y < GetY
            // d = (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + (GetX(i) > x ? GetX(i)-x : x-GetX(i));
        }
    }
    return n;
}

unsigned char GroupeMonstres::GetGauche(unsigned char id) const {
    // const int x = GetX(id);
    // const int y = GetY(id);
    const int x = m_X[id];
    const int y = m_Y[id];
    // int d = 0, n = id, i;
    int d = MAX_MONSTRES_DISTANCE;
    unsigned char n = id, i;
    // for (i = 0; i < GetNombre(); ++i) {
    for (i = 0; i < m_Nombre; ++i) {
        // if (GetMonstres(i) && GetMonstres(i)->estEnVie() // && d < GetX(i)
        if (m_Monstres[i] && m_Monstres[i]->estEnVie() // && d < GetX(i)
        // && d > (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + x-GetX(i)
        && d > (m_Y[i] > y ? m_Y[i]-y : y-m_Y[i]) + x-m_X[i]
        //&& GetX(i)-x < GetY(i)-y && GetX(i)-x < y-GetY(i)) {
        // && x > GetX(i)) {
        && x > m_X[i]) {
            n = i;
            // d = GetX(i);
            // d = (GetY(i) > y ? GetY(i)-y : y-GetY(i)) + x-GetX(i); // x > GetX
            d = (m_Y[i] > y ? m_Y[i]-y : y-m_Y[i]) + x-m_X[i]; // x > GetX
        }
    }
    return n;
}

unsigned char GroupeMonstres::GetDroite() const {
    int x = 0;
    unsigned char n = m_Nombre, i; //TODO: 0 pour éviter les erreurs de segmentation ou m_Nombre ?
    // for (i = 0; i < GetNombre(); ++i)
    for (i = 0; i < m_Nombre; ++i)
        // if (GetMonstres(i) && GetMonstres(i)->estEnVie() && x < GetX(i)) {
        if (m_Monstres[i] && m_Monstres[i]->estEnVie() && x < m_X[i]) {
            n = i;
            // x = GetX(i);
            x = m_X[i];
        }
    return n;
}

// const char* GroupeMonstres::GetNom(int id) const {
//     if (GetMonstres(id) == 0)
//         return "_";
//     return GetMonstres(id)->GetNom();
// }

/*string GroupeMonstres::GetNom() const {
    if (GetNombre() == 0)
        return "_";
    string val = GetNom(0);
    int i;
    for (i = 1; i < GetNombre(); i++) {
        val += "/";
        val += GetNom(i);
    }
    return val;
}*/

void GroupeMonstres::Ecrire(char* data) const {
    int i = 0;
    // ECRIRE_2CHIFFRES(i,data,GetNombre());
    ECRIRE_2CHIFFRES(i,data,m_Nombre);
    unsigned char j;
    // for (j = 0; j < GetNombre(); j++) {
    for (j = 0; j < m_Nombre; j++) {
        data[i++] = ' ';
        // if (GetMonstres(j)) {
        if (m_Monstres[j]) {
            // ECRIRE_3CHIFFRES(i,data,GetMonstres(j)->GetId());
            ECRIRE_3CHIFFRES(i,data,m_Monstres[j]->GetId());
        } else
            data[i++] = '0';
        data[i++] = ' ';
        // ECRIRE_2CHIFFRES(i,data,GetX(j));
        ECRIRE_2CHIFFRES(i,data,m_X[j]);
        data[i++] = ' ';
        // ECRIRE_2CHIFFRES(i,data,GetY(j));
        ECRIRE_2CHIFFRES(i,data,m_Y[j]);
    }
    data[i++] = '\0';
}

extern Monstre* monstres[];

void GroupeMonstres::Lire(int& i, const char* data) {
    int entier;
    LIRE_ENTIER(i,data,entier); m_Nombre = entier;
    SetFond("_");

    unsigned char j;
    // m_X = new int[GetNombre()];
    m_X = new int[m_Nombre];
    // for (j = 0; j < GetNombre(); j++)
    for (j = 0; j < m_Nombre; ++j)
        m_X[j] = 0;
    // m_Y = new int[GetNombre()];
    m_Y = new int[m_Nombre];
    // for (j = 0; j < GetNombre(); j++)
    for (j = 0; j < m_Nombre; ++j)
        m_Y[j] = 0;
    // m_Monstres = new Monstre*[GetNombre()];
    m_Monstres = new Monstre*[m_Nombre];
    // for (j = 0; j < GetNombre(); j++)
    for (j = 0; j < m_Nombre; ++j)
        m_Monstres[j] = 0;

    // for (j = 0; j < GetNombre(); j++) {
    for (j = 0; j < m_Nombre; j++) {
        LIRE_ENTIER(i,data,entier); SetMonstres(monstres[entier], j);
        LIRE_ENTIER(i,data,entier); SetX(entier, j);
        LIRE_ENTIER(i,data,entier); SetY(entier, j);
    }
}

unsigned int GroupeMonstres::TailleD() const {
    return 1 +m_Nombre*3;
}

char* GroupeMonstres::EcrireD(char* data) const {
    unsigned int i = 0;
    unsigned char j;
    data[i] = (unsigned char)(255 & m_Nombre);
    for (j = 0; j < m_Nombre; ++j) {
        data[++i] = m_Monstres[j] ? m_Monstres[j]->GetId() : 0;
        data[++i] = m_X[j];
        data[++i] = m_Y[j];
    }
    return &data[i+1];
}

const char* GroupeMonstres::LireD(const char* data) {
    unsigned int i = 0;
    unsigned char j;
    SetFond("_");
    m_Nombre = data[i];
    m_X = m_Nombre ? new int[m_Nombre] : 0;
    m_Y = m_Nombre ? new int[m_Nombre] : 0;
    m_Monstres = m_Nombre ? new Monstre*[m_Nombre] : 0;
    for (j = 0; j < m_Nombre; ++j) {
        m_Monstres[j] = monstres[(unsigned char)data[++i]];
        m_X[j] = data[++i];
        m_Y[j] = data[++i];
    }
    return &data[i+1];
}