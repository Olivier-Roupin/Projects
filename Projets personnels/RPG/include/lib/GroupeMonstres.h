#ifndef GROUPEMONSTRES_H
#define GROUPEMONSTRES_H

#include <lib/Monstre.h>

#define TAILLE_FOND_MONSTRES 8

class GroupeMonstres {
public:
    GroupeMonstres(int id); //utilisé
    GroupeMonstres(int id, const GroupeMonstres& cible); //création combat
    ~GroupeMonstres();
    int  GetId() const;
    void SetId(int val = 0);
    unsigned char GetNombre() const;
    void SetNombre(unsigned char val = 0);
    // Monstre** GetMonstres() const;
    Monstre* GetMonstres(unsigned char id) const;
    void SetMonstres(Monstre* val, unsigned char id);
    unsigned char ChercherMonstres(Monstre *val = 0) const; //Chercher un type de monstre dans le groupe
    unsigned char ChercherLibre() const; //Chercher une place de libre dans le groupe
    bool AjouterMonstres(Monstre *val, unsigned char nombre = 1); //Ajouter des monstres dans les places libres
    bool AjouterMonstres(Monstre *val, int X, int Y); //Ajouter des monstres dans les places libres

    const char* GetFond() const;
    void SetFond(const char* val);
    // int GetId(int id) const;
    int  GetX(unsigned char id) const;
    void SetX(int val, unsigned char id);
    int  GetY(unsigned char id) const;
    void SetY(int val, unsigned char id);

    int GetExperience() const; //Somme de l'expérience des monstres
    int GetOr() const; //Somme de l'or des monstres, peut être négatif
    //Script* GetScript() const;
    //void SetScript(Script* val);
    unsigned char GetNombreEnVie() const; //Nombre de monstres en vie (pour calcul des dégats)
    unsigned char GetHaut(unsigned char id) const; //Monstre en haut
    unsigned char GetDroite(unsigned char id) const; //Monstre à droite
    unsigned char GetBas(unsigned char id) const; //Monstre en bas
    unsigned char GetGauche(unsigned char id) const; //Monstre à gauche
    unsigned char GetDroite() const; //Monstre le plus à droite

    // const char* GetNom(int id) const;
    //std::string GetNom() const; //Pour l'éditeur
    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    unsigned char m_Nombre;
    Monstre** m_Monstres;
    //Script* m_Script;
    char m_Fond[TAILLE_FOND_MONSTRES+1];
    int* m_X;
    int* m_Y;
};

#endif // GROUPEMONSTRES_H
