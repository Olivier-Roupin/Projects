#ifndef CARTE_H
#define CARTE_H

#include <lib/GroupeMonstres.h>

class Rencontreset {
public:
    Rencontreset(unsigned char nombre = 0); //utilisé
    virtual ~Rencontreset();
    unsigned char GetNombre() const; // nombre de sets (plusieurs groupes)
    void SetNombre(unsigned char val);
    unsigned char GetNombreGroupes(unsigned char id) const; // nombre de groupes dans un set
    void SetNombreGroupes(unsigned char val, unsigned char id);
    GroupeMonstres* GetGroupes(unsigned char i, unsigned char j) const;
    void SetGroupes(GroupeMonstres* val, unsigned char i, unsigned char j);
    void Ecrire(int& i, char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    unsigned char  m_Nombre;
    unsigned char* m_NombreGroupes;
    GroupeMonstres*** m_Groupes;
};

#define TAILLE_NOM_CARTE 7
#define TAILLE_FOND_CARTE 8

#include <lib/Tileset.h>
#include <lib/Evenement.h> //Z_BAS, Z_MILIEU, Z_HAUT, NOMBRE_Z

class Carte {
public:
    Carte(int id, const char* nom = "_");
    /*Carte(int id, const char* nom, unsigned int largeur, unsigned int hauteur = 1,
          bool repetition = 0, Tileset* tileset = 0,
          int* bas = 0, int* moyen = 0, int* haut = 0, int Nombre = 0,
          Evenement** Evenements = 0, Rencontreset* rencontreset = 0);
    Carte(int Id, const char* Nom, int Largeur, int Hauteur = 1,
          bool Repetition = 0, Tileset* tileset = 0, int Nombre = 0,
          Rencontreset* rencontreset = 0, const char* fond = "_"); //utilisé*/
    virtual ~Carte();
    int GetId() const;
    void SetId(int val);
    const char* GetNom() const;
    void SetNom(const char* val);
    unsigned int GetLargeur() const;
    void SetLargeur(unsigned int val);
    unsigned int GetHauteur() const;
    void SetHauteur(unsigned int val);
    bool GetRepetition() const;
    void SetRepetition(bool val);
    //si la carte se répète, applique le modulo
    bool GetRepetition(int &i, int &j) const;
    unsigned char GetTuile(int i) const;
    unsigned char GetTuile(int i, int j, unsigned char k = Z_BAS) const;
    void SetTuile(unsigned char val, int i, int j = 0, unsigned char k = Z_BAS);
    const char* GetImageTuile(int i, int j = 0, unsigned char k = Z_BAS) const; //accès rapide
    unsigned char GetRencontres(int i, int j = 0) const;
    void SetRencontres(unsigned char val, int i, int j = 0);
    Tileset* GetTileset() const;
    void SetTileset(Tileset* val);
    unsigned char GetNombre() const;
    void SetNombre(unsigned char val);
    Evenement* GetEvenements(unsigned char id) const;
    void SetEvenements(Evenement* val, unsigned char id);
    Rencontreset* GetRencontreset() const;
    void SetRencontreset(Rencontreset* val);
    //int GetNombreFonds() const;
    //void SetNombreFonds(int val);
    //const char* GetFonds(int id) const;
    //void SetFonds(const char* val, int id);
    const char* GetFond() const;
    void SetFond(const char* val);

    unsigned int GetTaille() const; //donne la taille du tableau hauteur*largeur
    //teste si les 3 couches sont traversables
    bool GetTraversable(int i, int j) const;

    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    char m_Nom[TAILLE_NOM_CARTE+1];
    unsigned int m_Largeur;
    unsigned int m_Hauteur;
    bool m_Repetition;
    unsigned char* m_Tuiles;
    unsigned char* m_Rencontres;
    Tileset* m_Tileset;
    unsigned char m_Nombre;
    Evenement** m_Evenements; //tableau 1D
    Rencontreset* m_Rencontreset; //tableau 2D
    //int m_NombreFonds;
    //char* m_Fonds; //tableau 1D
    char m_Fond[TAILLE_FOND_CARTE+1];
};

#endif // CARTE_H
