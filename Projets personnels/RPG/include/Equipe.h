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
        unsigned int ChercherHeros(Heros* val = 0) const; //Chercher un h�ros dans l'�quipe
        unsigned int ChercherLibre() const; //Chercher une place de libre dans l'�quipe
        unsigned int AjouterHeros(Heros* val); //Ajouter un h�ros dans une place libre
        unsigned int RetirerHeros(Heros* val); //Retirer un h�ros particulier de l'�quipe
    protected:
    private:
        Heros* m_Heros[MAX_HEROS_EQUIPE];
};

#endif // EQUIPE_H
