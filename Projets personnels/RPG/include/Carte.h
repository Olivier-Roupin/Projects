#ifndef CARTE_H
#define CARTE_H

#define NOMBRE_IN_CARTE 5
#define IN_CARTE_LARGEUR 0
#define IN_CARTE_HAUTEUR 1
#define IN_CARTE_REPETITION 2
#define IN_CARTE_ID_TILESET 3
#define IN_CARTE_NOMBRE 4

#include <Tileset.h>
#include <Evenement.h>
#include <GroupeMonstres.h>

class Rencontreset
{
    public:
        Rencontreset(int nombre = 0); //utilisé
        virtual ~Rencontreset();
        int GetNombre() const;
        void SetNombre(int val);
        int GetNombreGroupes(int id) const;
        void SetNombreGroupes(int val, int id);
        GroupeMonstres* GetGroupes(int i, int j) const;
        void SetGroupes(GroupeMonstres* val, int i, int j);
    protected:
    private:
        int m_Nombre;
        int* m_NombreGroupes;
        GroupeMonstres*** m_Groupes;
};

class Carte
{
    public:
        Carte(int id, std::string nom = "_", int largeur = 1, int hauteur = 1, bool repetition = 0,\
              Tileset* tileset = 0, int* bas = 0, int* moyen = 0, int* haut = 0, int Nombre = 0,\
              Evenement** Evenements = 0, Rencontreset* rencontreset = 0);
        Carte(int Id, std::string Nom = "_", int Largeur = 1, int Hauteur = 1, bool Repetition = 0,\
              Tileset* tileset = 0, int Nombre = 0, Rencontreset* rencontreset = 0, std::string fond = "_"); //utilisé
        virtual ~Carte();
        int GetId() const;
        void SetId(int val);
        std::string GetNom() const;
        void SetNom(std::string val);
        int GetLargeur() const;
        void SetLargeur(int val);
        int GetHauteur() const;
        void SetHauteur(int val);
        bool GetRepetition() const;
        void SetRepetition(bool val);
        int GetBas(int i, int j = 0) const;
        void SetBas(int val, int i, int j = 0);
        int GetMoyen(int i, int j = 0) const;
        void SetMoyen(int val, int i, int j = 0);
        int GetHaut(int i, int j = 0) const;
        void SetHaut(int val, int i, int j = 0);
        int GetRencontres(int i, int j = 0) const;
        void SetRencontres(int val, int i, int j = 0);
        Tileset* GetTileset() const;
        void SetTileset(Tileset* val);
        int GetNombre() const;
        void SetNombre(int val);
        Evenement* GetEvenements(int id) const;
        void SetEvenements(Evenement* val, int id);
        Rencontreset* GetRencontreset() const;
        void SetRencontreset(Rencontreset* val);
        //int GetNombreFonds() const;
        //void SetNombreFonds(int val);
        //std::string GetFonds(int id) const;
        //void SetFonds(std::string val, int id);
        std::string GetFond() const;
        void SetFond(std::string val);

        int GetTaille() const; //donne la taille du tableau hauteur*largeur
    protected:
    private:
        int m_Id;
        std::string m_Nom;
        int m_Largeur;
        int m_Hauteur;
        bool m_Repetition;
        int* m_Bas;
        int* m_Moyen;
        int* m_Haut;
        int* m_Rencontres;
        Tileset* m_Tileset;
        int m_Nombre;
        Evenement** m_Evenements; //tableau 1D
        Rencontreset* m_Rencontreset; //tableau 2D
        //int m_NombreFonds;
        //std::string* m_Fonds; //tableau 1D
        std::string m_Fond;
};

#endif // CARTE_H
