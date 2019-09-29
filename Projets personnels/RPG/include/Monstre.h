#ifndef MONSTRE_H
#define MONSTRE_H

#include <Personnage.h>
#include <GroupeObjets.h>

#define NOMBRE_IN_MONSTRE 15
#define IN_MONSTRE_VIE 0
#define IN_MONSTRE_MAGIE 1
#define IN_MONSTRE_ATTAQUEP 2
#define IN_MONSTRE_DEFENSEP 3
#define IN_MONSTRE_ATTAQUEM 4
#define IN_MONSTRE_DEFENSEM 5
#define IN_MONSTRE_VITESSE 6
#define IN_MONSTRE_PRECISION 7
#define IN_MONSTRE_ESQUIVE 8
#define IN_MONSTRE_EXPERIENCE 9
#define IN_MONSTRE_NIVEAU 10
#define IN_MONSTRE_ID_BUTIN 11
#define IN_MONSTRE_ID_OBJETPORTE 12
#define IN_MONSTRE_OR 13
#define IN_MONSTRE_ID_SCRIPT 14

class Monstre : public Personnage
{
public:
    Monstre(int Id, std::string Nom = "_", int Vie = 0, int Magie = 0,\
            int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,\
            int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,\
            int Vitesse = 0, int Precision = 0, int Esquive = 0,\
            int Statut = 0, int Experience = 0, int Niveau = 1, int Jauge = 0,\
            GroupeObjets* Butin = 0, GroupeObjets* Objetporte = 0, int Or = 0);
    Monstre(int Id, std::string Nom = "_", int Vie = 0, int Magie = 0,\
            int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,\
            int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,\
            int Vitesse = 0, int Precision = 0, int Esquive = 0,\
            int Experience = 0, int Niveau = 1,\
            GroupeObjets* Butin = 0, GroupeObjets* Objetporte = 0, int Or = 0, int Statut = 0, int Jauge = 0); //utilisé
    Monstre(const Monstre& other); //utile pour la création d'un groupe de combat
    ~Monstre();
    GroupeObjets* GetButin() const;
    void SetButin(GroupeObjets* val);
    GroupeObjets* GetObjetPorte() const;
    void SetObjetPorte(GroupeObjets* val);
    int GetOr() const;
    void SetOr(int val);
    Script* GetScript() const;
    void SetScript(Script* val);
    int GetX() const;
    void SetX(int val);
    int GetY() const;
    void SetY(int val);
protected:
private:
    GroupeObjets* m_Butin;
    GroupeObjets* m_ObjetPorte;
    int m_Or;
    Script* m_Script;
    int m_X;
    int m_Y;
};

#endif // MONSTRE_H
