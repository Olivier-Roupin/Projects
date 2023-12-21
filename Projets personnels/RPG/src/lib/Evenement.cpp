#include "lib/Evenement.h"

Evenement::Evenement(int id) { //utilisé
    SetId(id);
    SetX(0);
    SetY(0);
    SetZ(0);
    SetOrientation(ORIENTATION_BAS);
    SetDeplace(0);
    SetDx(0);
    SetDy(0);
    m_Nombre = 0;
    m_Scripts = 0;
    SetTraversable(true);
    SetImage("_");
}

Evenement::Evenement(int id, unsigned char nombre, const char* image,
                       int x, int y, int z, bool traversable) {
    SetId(id);
    SetX(x);
    SetY(y);
    SetZ(z);
    SetOrientation(ORIENTATION_BAS);
    SetDeplace(0);
    SetDx(0);
    SetDy(0);
    SetNombre(nombre);
    // m_Scripts = new Script*[GetNombre()];
    m_Scripts = new Script*[m_Nombre];
    unsigned char i;
    // for (i = 0; i < GetNombre(); i++)
    for (i = 0; i < m_Nombre; ++i)
        m_Scripts[i] = 0;
    SetTraversable(traversable);
    SetImage(image);
}

Evenement::~Evenement() {
}

int Evenement::GetId() const {
    return m_Id;
}

void Evenement::SetId(int val) {
    m_Id = val;
}

int Evenement::GetX() const {
    return m_X;
}

void Evenement::SetX(int val) {
    m_X = val;
}

void Evenement::ChangerX(int val) {
    SetX(GetX()+val);
}

int Evenement::GetY() const {
    return m_Y;
}

void Evenement::SetY(int val) {
    m_Y = val;
}

void Evenement::ChangerY(int val) {
    SetY(GetY()+val);
}

int Evenement::GetZ() const {
    return m_Z;
}

void Evenement::SetZ(int val) {
    if (val >= Z_BAS && val <= Z_HAUT)
        m_Z = val;
}

char Evenement::GetOrientation() const {
    return m_Orientation;
}

void Evenement::SetOrientation(char val) {
    if (val >= 0)
        m_Orientation = val;
}

char Evenement::GetDeplace() const {
    return m_Deplace;
}

void Evenement::SetDeplace(char val) {
    m_Deplace = val;
}

void Evenement::ChangerDeplace(char val) {
    SetDeplace(GetDeplace()+val);
}

int Evenement::GetDx() const {
    return m_Dx;
}

void Evenement::SetDx(int val) {
    m_Dx = val;
}

int Evenement::GetDy() const {
    return m_Dy;
}

void Evenement::SetDy(int val) {
    m_Dy = val;
}

unsigned char Evenement::GetNombre() const {
    return m_Nombre;
}

void Evenement::SetNombre(unsigned char val) {
    // if (val < 0)
    //     val = 0;
    if (val == m_Nombre)
        return;
    Script** nouveau = new Script*[val];
    unsigned char i;
    if (val > m_Nombre) {
        for (i = 0; i < m_Nombre; ++i)
            nouveau[i] = m_Scripts[i];
        for (i = m_Nombre; i < val; ++i)
            nouveau[i] = 0;
    }
    else
        for (i = 0; i < val; ++i)
            nouveau[i] = m_Scripts[i];
    delete[] m_Scripts;
    m_Scripts = nouveau;
    m_Nombre = val;
}

Script* Evenement::GetScripts(unsigned char id) const {
    // if (id < 0 || id >= GetNombre())
    if (id >= m_Nombre)
        return 0;
    return m_Scripts[id];
}

void Evenement::SetScripts(Script* val, unsigned char id) {
    m_Scripts[id] = val;
}

bool Evenement::GetTraversable() const {
    return m_Traversable;
}

void Evenement::SetTraversable(bool val) {
    m_Traversable = val;
}

const char* Evenement::GetImage() const {
    return m_Image;
}

void Evenement::SetImage(const char* val) {
    //m_Image = val;
    for (int i = 0; i < TAILLE_IMAGE_EVENEMENT; i++) {
        m_Image[i] = val[i];
        if (val[i] == '\0')
            return;
    }
    m_Image[TAILLE_IMAGE_EVENEMENT] = '\0';
}

void Evenement::RenduTerrain(char* image, unsigned char largeur) const {
    if (GetImage() == 0) {
        image[0] = '_';
        image[1] = 0;
        image[2] = 0;
    } else {
        image[0] = GetImage()[0];
        const bool step = GetDeplace()<=-largeur/2;
        switch (GetOrientation()) {
            case ORIENTATION_DROITE:
                image[1] = step ? 5 : 4;
                image[2] = 1;
                break;
            case ORIENTATION_HAUT:
                image[1] = step ? 3 : 2;
                image[2] = 0;
                break;
            case ORIENTATION_GAUCHE:
                image[1] = step ? 5 : 4;
                image[2] = 0;
                break;
            case ORIENTATION_BAS:
            default:
                image[1] = step ? 1 : 0;
                image[2] = 0;
        }
    }
}

void Evenement::Ecrire(char* data) const {
    int i = 0, j;
    ECRIRE_CHAINE(i,j,data,m_Image,TAILLE_IMAGE_EVENEMENT);
    data[i++] = ' ';
    ECRIRE_2CHIFFRES(i,data,GetNombre());
    for (j = 0; j < GetNombre(); j++) {
        data[i++] = ' ';
        if (GetScripts(j)) {
            ECRIRE_3CHIFFRES(i,data,GetScripts(j)->GetId());
        } else
            data[i++] = '0';
    }
    data[i++] = '\0';
}

void Evenement::Lire(int& i, const char* data) {
    int j = 0;
    char img[TAILLE_IMAGE_EVENEMENT+1];
    LIRE_CHAINE(i,j,data,img,TAILLE_IMAGE_EVENEMENT); SetImage(img);
    int entier;
    LIRE_ENTIER(i,data,entier); m_Nombre = entier;
    if (GetNombre())
        m_Scripts = new Script*[GetNombre()];
    else
        m_Scripts = 0;
    for (j = 0; j < GetNombre(); j++) {
        LIRE_ENTIER(i,data,entier); SetScripts(scripts[entier],j);
    }
}

unsigned int Evenement::TailleD() const {
    return TAILLE_IMAGE_EVENEMENT +1 +m_Nombre*1;
}

char* Evenement::EcrireD(char* data) const {
    unsigned int i = 0, j;
    data[  i] = m_Image[0]; //TAILLE_IMAGE_EVENEMENT == 1
    data[++i] = m_Nombre;
    for (j = 0; j < m_Nombre; ++j)
        data[++i] = m_Scripts[j] ? m_Scripts[j]->GetId() : 0;
    return &data[i+1];
}

const char* Evenement::LireD(const char* data) {
    unsigned int i = 0, j;
    m_Image[0] = data[  i]; //TAILLE_IMAGE_EVENEMENT == 1
    m_Image[1] = '\0';
    m_Nombre   = (unsigned char)(data[++i]);
    // if (m_Nombre)
        m_Scripts = m_Nombre ? new Script*[m_Nombre] : 0;
    // else
        // m_Scripts = 0;
    for (j = 0; j < m_Nombre; ++j)
        m_Scripts[j] = scripts[(unsigned char)data[++i]];
    return &data[i+1];
}