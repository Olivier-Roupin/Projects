#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <GroupeObjets.h>

#define MAX_OBJETS 100

class Inventaire
{
public:
    Inventaire();
    ~Inventaire();
    GroupeObjets* GetObjets(int id) const;
    void SetObjets(GroupeObjets *val, int id);
    void SetObjets(Objet *val, int nombre, int id);
    int ChercherObjet(Objet *val = 0) const; //Chercher un type d'objet dans l'inventaire
    int ChercherObjet(GroupeObjets *val) const;
    int ChercherLibre() const; //Chercher une place de libre dans l'inventaire
    int AjouterObjets(GroupeObjets *val); //Ajouter des objets dans les places libres
    int AjouterObjets(Objet *val, int nombre = 1);
    int RetirerObjets(GroupeObjets *val); //Retirer des objets particuliers de l'inventaire
    int RetirerObjets(Objet *val, int nombre = 1);
    int EchangerObjets(int id1, int id2);
    int GetNombreObjets(Objet *val = 0) const; //Donne la quantité d'objets d'un type dans l'inventaire
    //Pour l'affichage
    std::string GetNom(int id) const;
    int GetPrix(int id) const;
    int GetNombre(int id) const;
protected:
private:
    GroupeObjets *m_Objets[MAX_OBJETS]; //Tableau de GroupeObjets*
};

#endif // INVENTAIRE_H
