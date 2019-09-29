#ifndef GROUPEMONSTRES_H
#define GROUPEMONSTRES_H

#include <Monstre.h>

#define MAX_MONSTRES 30

class GroupeMonstres
{
    public:
        GroupeMonstres(int Id, int nombre = 0, std::string fond = "_", Monstre** monstres = 0); //utilisé, dernier paramètre utile ?
        GroupeMonstres(int Id, const GroupeMonstres& cible); //NOPE utile pour création groupe combat
        ~GroupeMonstres();
        int GetId() const;
        void SetId(int val = 0);
        int GetNombre() const;
        void SetNombre(int val = 0);
        Monstre** GetMonstres() const;
        Monstre* GetMonstres(int id) const;
        void SetMonstres(Monstre* val, int id);
        int ChercherMonstres(Monstre *val = 0) const; //Chercher un type de monstre dans le groupe
        int ChercherLibre() const; //Chercher une place de libre dans le groupe
        int AjouterMonstres(Monstre *val, int nombre = 1); //Ajouter des monstres dans les places libres
        int AjouterMonstres(Monstre *val, int X, int Y); //Ajouter des monstres dans les places libres

        std::string GetFond() const;
        void SetFond(std::string val);
        int GetX(int id) const;
        void SetX(int val, int id);
        int GetY(int id) const;
        void SetY(int val, int id);

        int GetExperience() const; //Somme de l'expérience des monstres
        int GetOr() const; //Somme de l'or des monstres
        //Script* GetScript() const;
        //void SetScript(Script* val);
    protected:
    private:
        int m_Id;
        int m_Nombre;
        Monstre** m_Monstres;
        //Script* m_Script;
        std::string m_Fond;
        int* m_X;
        int* m_Y;
};

#endif // GROUPEMONSTRES_H
