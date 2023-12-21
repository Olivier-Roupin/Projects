#ifndef GROUPEOBJETS_H
#define GROUPEOBJETS_H

#include <lib/Objet.h>

class GroupeObjets {
    public:
        GroupeObjets(Objet *objet, unsigned char nombre = 1);
        GroupeObjets(GroupeObjets const& copie);
        ~GroupeObjets();
        Objet* GetObjet() const;
        void SetObjet(Objet *val);
        unsigned char GetNombre() const;
        void SetNombre(unsigned char val);
        void ChangerNombre(char val);
        unsigned int GetPrix() const;
        //Propriétés de l'objet
        const char* GetNom() const;
        int GetId() const;
        unsigned char GetType() const;
    protected:
    private:
        Objet* m_Objet;
        unsigned char m_Nombre;
};

#endif // GROUPEOBJETS_H
