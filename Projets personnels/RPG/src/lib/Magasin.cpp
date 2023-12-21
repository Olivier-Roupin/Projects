#include "lib/Magasin.h"

#define MAX_OBJETS_MAGASIN 20

Magasin::Magasin(int id) {
    SetId(id);
    m_Nombre = 0;
    m_Objets = 0;
}

Magasin::Magasin(int id, unsigned char nombre, Objet** objets) {
    SetId(id);
    // SetNombre(nombre);
    m_Nombre = nombre;
    // m_Objets = new Objet*[GetNombre()];
    m_Objets = new Objet*[m_Nombre];
    if (objets)
        *m_Objets = *objets;
    else {
        unsigned char i;
        // for (i = 0; i < GetNombre(); i++)
        for (i = 0; i < m_Nombre; ++i)
            m_Objets[i] = 0;
    }
}

Magasin::~Magasin() {
}

int Magasin::GetId() const {
    return m_Id;
}

void Magasin::SetId(int val) {
    if (val < 0)
        val = 0;
    m_Id = val;
}

unsigned char Magasin::GetNombre() const {
    return m_Nombre;
}

void Magasin::SetNombre(unsigned char val) {
    if (val > MAX_OBJETS_MAGASIN)
        val = MAX_OBJETS_MAGASIN;
    if (val == GetNombre())
        return;
    Objet** nouveau = new Objet*[val];
    unsigned char i;
    if (val > GetNombre()) {
        for (i = 0; i < GetNombre(); i++)
            nouveau[i] = m_Objets[i];
        for (i = GetNombre(); i < val; i++)
            nouveau[i] = 0;
    }
    else
        for (i = 0; i < val; i++)
            nouveau[i] = m_Objets[i];
    delete[] m_Objets;
    m_Objets = nouveau;
    m_Nombre = val;
}

Objet* Magasin::GetObjets(unsigned char id) const {
    // if (id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_Objets[id];
}

void Magasin::SetObjets(Objet* val, unsigned char id) {
    m_Objets[id] = val;
}

// char Magasin::ChercherLibre() const {
//     char i = 0;
//     char n = GetNombre();
//     while (GetObjets(i) && i < n)
//         i++;
//     if (i >= n)
//         return -1;
//     return i;
// }

// int Magasin::AjouterObjet(Objet* val) {
//     char i = ChercherLibre();
//     if (i != -1)
//         SetObjets(val,i);
//     else
//         return -1;
//     return 0;
// }

// int Magasin::GetId(char id) const {
//     if (GetObjets(id) == 0)
//         return 0;
//     return GetObjets(id)->GetId();
// }

const char* Magasin::GetNom(unsigned char id) const {
    if (GetObjets(id) == 0)
        return "_";
    // return GetObjets(id)->GetNom();
    return m_Objets[id]->GetNom();
}

unsigned int Magasin::GetPrix(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    // return GetObjets(id)->GetPrix();
    return m_Objets[id]->GetPrix();
}

/*unsigned char Magasin::GetType(unsigned char id) const {
    if (GetObjets(id) == 0)
        return 0;
    return m_Objets[id]->GetType();
}*/

/*string Magasin::GetNom() const {
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

void Magasin::Ecrire(char* data) const {
    int i = 0;
    ECRIRE_2CHIFFRES(i,data,GetNombre());
    unsigned char j;
    for (j = 0; j < GetNombre(); j++) {
        data[i++] = ' ';
        if (GetObjets(j)) {
            ECRIRE_3CHIFFRES(i,data,GetObjets(j)->GetId());
        } else
            data[i++] = '0';
    }
    data[i++] = '\0';
}

extern Objet* objets[];

void Magasin::Lire(int& i, const char* data) {
    char octet;
    int entier;
    LIRE_ENTIER(i,data,octet); m_Nombre = octet;
    // if (GetNombre())
    //     m_Objets = new Objet*[GetNombre()];
    if (m_Nombre)
        m_Objets = new Objet*[m_Nombre];
    else
        m_Objets = 0;
    unsigned char j;
    // for (j = 0; j < GetNombre(); j++) {
    for (j = 0; j < m_Nombre; ++j) {
        LIRE_ENTIER(i,data,entier); SetObjets(objets[entier],j);
    }
}

unsigned int Magasin::TailleD() const {
    return 1 +m_Nombre*1;
}

char* Magasin::EcrireD(char* data) const {
    unsigned int i = 0, j;
    data[i] = (unsigned char)(255 & m_Nombre);
    for (j = 0; j < m_Nombre; ++j)
        data[++i] = m_Objets[j] ? m_Objets[j]->GetId() : 0;
    return &data[i+1];
}

const char* Magasin::LireD(const char* data) {
    unsigned int i = 0, j;
    m_Nombre = data[i];
    m_Objets = m_Nombre ? new Objet*[m_Nombre] : 0;
    for (j = 0; j < m_Nombre; ++j)
        m_Objets[j] = objets[(unsigned char)data[++i]];
    return &data[i+1];
}