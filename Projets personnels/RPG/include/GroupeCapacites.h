#ifndef GROUPECAPACITES_H
#define GROUPECAPACITES_H

#include <Capacite.h>

#define MAX_CAPACITES 100

class GroupeCapacites
{
    public:
        GroupeCapacites();
        ~GroupeCapacites();
        Capacite* GetCapacites(unsigned int id) const;
        void SetCapacites(Capacite *val, unsigned int id);
        unsigned int ChercherCapacite(Capacite *val = 0) const; //Chercher un type d'objet dans l'inventaire
        unsigned int ChercherLibre() const; //Chercher une place de libre dans l'inventaire
        unsigned int AjouterCapacites(Capacite *val); //Ajouter des objets dans les places libres
        unsigned int RetirerCapacites(Capacite *val); //Retirer des objets particuliers de l'inventaire
    protected:
    private:
        Capacite *m_Capacites[MAX_CAPACITES];
};

#endif // GROUPECAPACITES_H
