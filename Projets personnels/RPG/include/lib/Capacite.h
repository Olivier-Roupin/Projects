#ifndef CAPACITE_H
#define CAPACITE_H

#include <lib/Effet.h>

#define TAILLE_NOM_CAPACITE 7
#define TAILLE_DESCRIPTION_CAPACITE 47

class Capacite {
public:
    Capacite(int Id = 0, const char* Nom = "_", const char* Description = "_",
             int CoutMagie = 0, char CoutMagieP = 0,
             int CoutVie = 0, char CoutVieP = 0, Effet* effet = 0); //utilisé
    virtual ~Capacite();
    //Capacite(const Capacite& cible);
    int GetId() const;
    void SetId(int val);
    const char* GetNom() const;
    void SetNom(const char* val);
    const char* GetDescription() const;
    void SetDescription(const char* val);
    int GetCoutVie() const;
    void SetCoutVie(int val);
    char GetCoutVieP() const;
    void SetCoutVieP(char val);
    int GetCoutMagie() const;
    void SetCoutMagie(int val);
    char GetCoutMagieP() const;
    void SetCoutMagieP(char val);
    Effet* GetEffet() const;
    void SetEffet(Effet* val);

    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    char m_Nom[TAILLE_NOM_CAPACITE+1];
    char m_Description[TAILLE_DESCRIPTION_CAPACITE+1];
    int m_CoutVie;
    char m_CoutVieP;
    int m_CoutMagie;
    char m_CoutMagieP;
    Effet* m_Effet;
};

#endif // CAPACITE_H
