#ifndef EQUIPE_H
#define EQUIPE_H

#include <Heros.h>

#define MAX_HEROS_EQUIPE 4

class Equipe
{
    public:
        Equipe();
        ~Equipe();
        Heros** GetHeros() const;
        Heros* GetHeros(unsigned int id) const;
        void SetHeros(Heros* val, unsigned int id);
        unsigned int ChercherHeros(Heros* val = 0) const; //Chercher un héros dans l'équipe
        unsigned int ChercherLibre() const; //Chercher une place de libre dans l'équipe
        unsigned int AjouterHeros(Heros* val); //Ajouter un héros dans une place libre
        unsigned int RetirerHeros(Heros* val); //Retirer un héros particulier de l'équipe
    protected:
    private:
        Heros* m_Heros[MAX_HEROS_EQUIPE];
};

#endif // EQUIPE_H
