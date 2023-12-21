#include "lib/Tileset.h"
#include <macros.h>

#define MAX_TILES 99
#define TAILLE_IMAGE_TILESET 1

Tileset::Tileset(int id) {
    SetId(id);
    m_Nombre = 0;
}

Tileset::Tileset(int id, unsigned int nombre, char* traversable,
                 const char* image) : m_Id(id), m_Nombre(nombre) {
    unsigned int i;
    // m_Traversable = new char[GetNombre()];
    m_Traversable = new char[m_Nombre];
    if (traversable)
        *m_Traversable = *traversable;
    else
        // for (i = 0; i < GetNombre(); i++)
        for (i = 0; i < m_Nombre; ++i)
            // SetTraversable(0, i);
            m_Traversable[i] = 0;
    // m_Image = new char[(TAILLE_IMAGE_TILESET+1)*GetNombre()];
    m_Image = new char[(TAILLE_IMAGE_TILESET+1)*m_Nombre];
    if (image)
        *m_Image = *image; // fonctionne ?
    else
        // for (i = 0; i < GetNombre(); i++)
        for (i = 0; i < m_Nombre; ++i)
            SetImage("_", i);
}

Tileset::~Tileset() {
}

int Tileset::GetId() {
    return m_Id;
}

void Tileset::SetId(int val) {
    m_Id = val;
}

unsigned int Tileset::GetNombre() const {
    return m_Nombre;
}

void Tileset::SetNombre(unsigned int val) {
    // if (val < 0)
    //     val = 0;
    if (val > MAX_TILES)
        val = MAX_TILES;
    // if (val == GetNombre())
    if (val == m_Nombre)
        return;
    //on suppose que la taille des images est constante dans le temps
    char* nouveau = new char[(TAILLE_IMAGE_TILESET+1)*val];
    char* traversable = new char[val];
    unsigned int i,j;
    // if (val > GetNombre()) {
    if (val > m_Nombre) {
        // for (i = 0; i < (TAILLE_IMAGE_TILESET+1)*GetNombre(); i++)
        for (i = 0; i < (TAILLE_IMAGE_TILESET+1)*m_Nombre; ++i)
            nouveau[i] = m_Image[i];
        // for (i = GetNombre(); i < val; i++) {
        for (i = m_Nombre; i < val; ++i) {
            for (j = 0; j < TAILLE_IMAGE_TILESET; ++j)
                nouveau[(TAILLE_IMAGE_TILESET+1)*i+j] = '_';
            nouveau[(TAILLE_IMAGE_TILESET+1)*i+TAILLE_IMAGE_TILESET] = '\0';
        }
        // for (i = 0; i < GetNombre(); i++)
        for (i = 0; i < m_Nombre; ++i)
            traversable[i] = m_Traversable[i];
        // for (i = GetNombre(); i < val; i++)
        for (i = m_Nombre; i < val; ++i)
            traversable[i] = 0;
    } else {
        for (i = 0; i < (TAILLE_IMAGE_TILESET+1)*val; ++i)
            nouveau[i] = m_Image[i];
        for (i = 0; i < val; i++)
            traversable[i] = m_Traversable[i];
    }
    delete[] m_Image;
    delete[] m_Traversable;
    m_Image = nouveau;
    m_Traversable = traversable;
    m_Nombre = val;
}

char Tileset::GetTraversable(unsigned int id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_Traversable[id];
}

void Tileset::SetTraversable(char val, unsigned int id) {
    m_Traversable[id] = val;
}

const char* Tileset::GetImage(unsigned int id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return "_";//0;
    return &m_Image[(TAILLE_IMAGE_TILESET+1)*id];
}

void Tileset::SetImage(const char* val, unsigned int id) {
    for (unsigned int i = 0; i < TAILLE_IMAGE_TILESET; ++i)
        m_Image[(TAILLE_IMAGE_TILESET+1)*id+i] = val[i];
    m_Image[(TAILLE_IMAGE_TILESET+1)*id+TAILLE_IMAGE_TILESET] = '\0';
}

void Tileset::Ecrire(char* data) const {
    unsigned int i = 0, j;
    // ECRIRE_2CHIFFRES(i,data,GetNombre());
    ECRIRE_2CHIFFRES(i,data,m_Nombre);
    // for (j = 0; j < GetNombre(); j++) {
    for (j = 0; j < m_Nombre; ++j) {
        data[i++] = '\n';
        int k;
        ECRIRE_CHAINE(i,k,data,GetImage(j),TAILLE_IMAGE_TILESET);
        data[i++] = ' ';
        // ECRIRE_CHIFFRE(i,data,GetTraversable(j));
        ECRIRE_CHIFFRE(i,data,m_Traversable[j]);
    }
    data[i++] = '\n';
    data[i++] = '\0';
}

void Tileset::Lire(int& i, const char* data) {
    unsigned int entier;
    LIRE_ENTIER(i,data,entier); m_Nombre = entier;
    // if (GetNombre()) {
    if (m_Nombre) {
        // m_Traversable = new char[GetNombre()];
        m_Traversable = new char[m_Nombre];
        // m_Image = new char[(TAILLE_IMAGE_TILESET+1)*GetNombre()];
        m_Image = new char[(TAILLE_IMAGE_TILESET+1)*m_Nombre];
    } else {
        m_Traversable = 0;
        m_Image = 0;
    }
    char img[TAILLE_IMAGE_TILESET+1];
    char octet;
    unsigned int j;
    // for (j = 0; j < GetNombre(); j++) {
    for (j = 0; j < m_Nombre; ++j) {
        LIRE_SUIVANT(i,data);
        int k = 0;
        LIRE_CHAINE(i,k,data,img,TAILLE_IMAGE_TILESET); SetImage(img, j);
        LIRE_CHIFFRE(i,data,octet); SetTraversable(octet, j);
    }
}

unsigned int Tileset::TailleD() const {
    return 1+m_Nombre*2;
}

char* Tileset::EcrireD(char* data) const {
// char* Tileset::EcrireD(char* data, unsigned int taille) const {
    unsigned int i = 0, j;
    // if (1+m_Nombre*2 > taille) // pas assez de place dans le buffer
    //     return 0;
    data[i] = (unsigned char)(255 & m_Nombre);
    for (j = 0; j < m_Nombre; ++j) {
        data[++i] =       m_Image[j*(TAILLE_IMAGE_TILESET+1)];
        data[++i] = m_Traversable[j];
    }
    return &data[i+1]; //pointeur vers le tileset suivant
}

const char* Tileset::LireD(const char* data) {
    unsigned int i = 0, j;
    m_Nombre = data[i];
    if (m_Nombre) {
        m_Traversable = new char[m_Nombre];
        m_Image       = new char[m_Nombre*(TAILLE_IMAGE_TILESET+1)];
    } else {
        m_Traversable = 0;
        m_Image       = 0;
    }
    for (j = 0; j < m_Nombre; ++j) {
        m_Image[j*(TAILLE_IMAGE_TILESET+1)  ] = data[++i];
        m_Image[j*(TAILLE_IMAGE_TILESET+1)+1] = '\0';
        m_Traversable[j] = data[++i];
    }
    return &data[i+1]; //pointeur vers le tileset suivant
}