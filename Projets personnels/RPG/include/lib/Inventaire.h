#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <lib/GroupeObjets.h>

#define MAX_OBJETS 100

class Inventaire {
public:
    Inventaire();
    ~Inventaire();
    GroupeObjets* GetObjets(unsigned char id) const;
    void SetObjets(GroupeObjets *val, unsigned char id);
    void SetObjets(Objet *val, unsigned char nombre, unsigned char id);
    unsigned char ChercherObjet(const Objet *val = 0) const; //Chercher un type d'objet dans l'inventaire
    unsigned char ChercherObjet(GroupeObjets *val) const;
    unsigned char ChercherLibre() const; //Chercher une place de libre dans l'inventaire
    bool AjouterObjets(GroupeObjets *val); //Ajouter des objets dans les places libres
    bool AjouterObjets(Objet *val, unsigned char nombre = 1);
    bool RetirerObjets(GroupeObjets *val); //Retirer des objets particuliers de l'inventaire
    bool RetirerObjets(Objet *val, unsigned char nombre = 1);
    void EchangerObjets(unsigned char id1, unsigned char id2);
    unsigned char GetNombre(const Objet *val = 0) const; //Donne la quantité d'objets d'un type dans l'inventaire
    //Pour les menus
    unsigned char GetType(unsigned char id) const;
    //Pour l'affichage
    const char* GetNom(unsigned char id) const;
    unsigned int GetPrix(unsigned char id) const;
    unsigned char GetNombre(unsigned char id) const;
    Objet* GetObjet(unsigned char id) const;
    //Pour la sauvegarde
    int GetId(unsigned char id) const;
protected:
private:
    GroupeObjets *m_Objets[MAX_OBJETS]; //Tableau de GroupeObjets*
};

#endif // INVENTAIRE_H
