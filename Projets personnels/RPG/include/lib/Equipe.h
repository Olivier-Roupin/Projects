#ifndef EQUIPE_H
#define EQUIPE_H

#include <lib/Heros.h>

#define MAX_HEROS_EQUIPE 4

class Equipe {
    public:
        Equipe();
        ~Equipe();
        // Heros** GetHeros() const;
        Heros* GetHeros(unsigned char id) const;
        void SetHeros(Heros* val, unsigned char id);
        unsigned char ChercherHeros(Heros* val = 0) const; //Chercher un héros dans l'équipe
        unsigned char ChercherLibre() const; //Chercher une place de libre dans l'équipe
        bool AjouterHeros(Heros* val); //Ajouter un héros dans une place libre
        bool RetirerHeros(Heros* val); //Retirer un héros particulier de l'équipe
        void EchangerHeros(unsigned char id1, unsigned char id2);
        unsigned char GetNombreEnVie() const; //Nombre de héros en vie (pour calcul des dégats)
        unsigned char GetNombreObjets(const Objet *val) const; //Donne la quantité d'objets d'un type équipé
    protected:
    private:
        Heros* m_Heros[MAX_HEROS_EQUIPE];
};

#endif // EQUIPE_H
