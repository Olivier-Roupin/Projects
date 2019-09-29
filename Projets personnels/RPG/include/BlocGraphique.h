#ifndef BLOCGRAPHIQUE_H
#define BLOCGRAPHIQUE_H

#include <ElementGraphique.h>
#include <string>

#include <POLICE.h>

#define NOMBRE_TEXTURES 4
#define LARGEUR_TEXTURE 16
#define TAILLE_TEXTURE (32*LARGEUR_TEXTURE)

extern ElementGraphique* elements_graphiques[NOMBRE_TEXTURES*TAILLE_TEXTURE];

class BlocGraphique
{
public:
    BlocGraphique(int Nombre_Elements, int* Elements, int Largeur, int Hauteur, int* Mappage);
    BlocGraphique(std::string text);
    BlocGraphique(std::string tile, int taille);
    virtual ~BlocGraphique();
    ElementGraphique* GetElements(int id) const;
    void SetElements(ElementGraphique* val, int id);
    int GetLargeur() const;
    void SetLargeur(int val);
    int GetHauteur() const;
    void SetHauteur(int val);
    int GetTaille() const;
    int GetMappage(int id) const;
    void SetMappage(int* val);
    void SetMappage(int val, int id);
    void Afficher(int x, int y, int j = 0, int i = 0);
protected:
private:
    ElementGraphique** m_Elements;
    int m_Largeur;
    int m_Hauteur;
    int* m_Mappage;
};

int Caractere2Element(char val);
int Caractere2Tile(char val);

#endif // BLOCGRAPHIQUE_H
