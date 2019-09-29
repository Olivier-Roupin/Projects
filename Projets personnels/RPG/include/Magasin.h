#ifndef MAGASIN_H
#define MAGASIN_H

#include <Objet.h>

#define MAX_OBJETS_MAGASIN 20

class Magasin
{
    public:
        Magasin(int id, int nombre, Objet** objets = 0);
        virtual ~Magasin();
        int GetId() const;
        void SetId(int val);
        int GetNombre() const;
        void SetNombre(int val);
        Objet* GetObjets(int id) const;
        void SetObjets(Objet* val, int id);
        int ChercherLibre() const;
        int AjouterObjet(Objet* val);
        //Pour l'affichage
        std::string GetNom(int id) const;
        int GetPrix(int id) const;
    protected:
    private:
        int m_Id;
        int m_Nombre;
        Objet** m_Objets;
        //multiplicateur de prix
};

#endif // MAGASIN_H
