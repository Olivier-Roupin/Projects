#ifndef CAPACITE_H
#define CAPACITE_H

#include <string>
#include <Effet.h>

#define NOMBRE_IN_CAPACITE 5

class Capacite
{
    public:
        Capacite(int Id = 0, std::string Nom = "_", std::string Description = "_",\
                 int CoutMagie = 0, int CoutMagieP = 0, int CoutVie = 0, int CoutVieP = 0,\
                 Effet* effet = 0); //utilisé
        virtual ~Capacite();
        //Capacite(const Capacite& cible);
        int GetId() const;
        void SetId(int val);
        std::string GetNom() const;
        void SetNom(std::string val);
        std::string GetDescription() const;
        void SetDescription(std::string val);
        int GetCoutVie() const;
        void SetCoutVie(int val);
        int GetCoutVieP() const;
        void SetCoutVieP(int val);
        int GetCoutMagie() const;
        void SetCoutMagie(int val);
        int GetCoutMagieP() const;
        void SetCoutMagieP(int val);
        Effet* GetEffet() const;
        void SetEffet(Effet* val);

    protected:
    private:
        int m_Id;
        std::string m_Nom;
        std::string m_Description;
        int m_CoutVie;
        int m_CoutVieP;
        int m_CoutMagie;
        int m_CoutMagieP;
        Effet* m_Effet;
};

#endif // CAPACITE_H
