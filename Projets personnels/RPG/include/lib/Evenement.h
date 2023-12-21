#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <lib/Script.h>
#include <macros.h>

#define NOMBRE_ORIENTATIONS 4 //pour tourner en rond: ChangerOrientation
#define ORIENTATION_DROITE 0
#define ORIENTATION_HAUT   1
#define ORIENTATION_GAUCHE 2
#define ORIENTATION_BAS    3
#define ORIENTATION_NEUTRE 4

#define NOMBRE_Z 3
#define Z_BAS    0
#define Z_MILIEU 1
#define Z_HAUT   2

#define TAILLE_IMAGE_EVENEMENT 1

extern Script* scripts[];

class Evenement {
public:
    Evenement(int id); //utilisé
    Evenement(int id, unsigned char nombre, const char* image = "_",
              int x = 0, int y = 0, int z = 0, bool traversable = true);
    virtual ~Evenement();
    int GetId() const;
    void SetId(int val);
    int GetX() const;
    void SetX(int val);
    void ChangerX(int val);
    int GetY() const;
    void SetY(int val);
    void ChangerY(int val);
    int GetZ() const;
    void SetZ(int val);
    char GetOrientation() const;
    void SetOrientation(char val);
    char GetDeplace() const;
    void SetDeplace(char val);
    void ChangerDeplace(char val);
    int GetDx() const;
    void SetDx(int val);
    int GetDy() const;
    void SetDy(int val);
    unsigned char GetNombre() const;
    void SetNombre(unsigned char val);
    Script* GetScripts(unsigned char id) const;
    void SetScripts(Script* val, unsigned char id);
    bool GetTraversable() const;
    void SetTraversable(bool val);
    const char* GetImage() const;
    void SetImage(const char* val);
    // char GetImage() const;
    // void SetImage(char val);

    void RenduTerrain(char* image, unsigned char largeur) const;

    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    int m_X;
    int m_Y;
    int m_Z;
    char m_Orientation;
    char m_Deplace; //mouvement fluide
    int m_Dx;
    int m_Dy;
    unsigned char m_Nombre;
    Script** m_Scripts;
    bool m_Traversable;
    char m_Image[TAILLE_IMAGE_EVENEMENT+1];
    // char m_Image;
};

#endif // EVENEMENT_H
