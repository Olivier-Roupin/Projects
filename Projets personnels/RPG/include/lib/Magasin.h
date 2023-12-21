#ifndef MAGASIN_H
#define MAGASIN_H

#include <lib/Objet.h>

class Magasin {
public:
    Magasin(int id);
    Magasin(int id, unsigned char nombre, Objet** objets = 0);
    virtual ~Magasin();
    int GetId() const;
    void SetId(int val);
    unsigned char GetNombre() const;
    void SetNombre(unsigned char val);
    Objet* GetObjets(unsigned char id) const;
    void SetObjets(Objet* val, unsigned char id);
    // int ChercherLibre() const;
    // int AjouterObjet(Objet* val);
    //Pour l'affichage
    const char* GetNom(unsigned char id) const;
    // int GetId(char id) const;
    unsigned int GetPrix(unsigned char id) const;
    // unsigned char GetType(unsigned char id) const;

    //std::string GetNom() const; //Pour l'éditeur
    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    unsigned char m_Nombre;
    Objet** m_Objets;
    //multiplicateur de prix, tableau de prix, nom
};

#endif // MAGASIN_H
