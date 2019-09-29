#ifndef GROUPEOBJETS_H
#define GROUPEOBJETS_H

#include <Objet.h>

#define MAX_OBJETS_GROUPE 99

class GroupeObjets
{
    public:
        GroupeObjets(Objet *objet, int Nombre = 1);
        GroupeObjets(GroupeObjets const& copie);
        ~GroupeObjets();
        Objet* GetObjet() const;
        void SetObjet(Objet *val);
        int GetNombre() const;
        void SetNombre(int val);
        void ChangerNombre(int val);
        int GetPrix() const;
        //Propriétés de l'objet
        std::string GetNom() const;
    protected:
    private:
        Objet* m_Objet;
        int m_Nombre;
};

#endif // GROUPEOBJETS_H
