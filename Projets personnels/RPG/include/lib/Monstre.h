#ifndef MONSTRE_H
#define MONSTRE_H

#include <lib/Personnage.h>
#include <lib/GroupeObjets.h>

#define ANIMATION_MONSTRE_VISIBLE 0
#define ANIMATION_MONSTRE_CACHE   1
#define ANIMATION_MONSTRE_MORT    2

class Monstre : public Personnage {
public:
    Monstre(int Id, const char* Nom = "_", int Vie = 0, int Magie = 0,
            int VieMax = 0, int AttaqueP = 0, int DefenseP = 0,
            int MagieMax = 0, int AttaqueM = 0, int DefenseM = 0,
            int Vitesse = 0, int Precision = 0, int Esquive = 0,
            int Experience = 0, int Niveau = 1,
            // GroupeObjets* Butin = 0, GroupeObjets* Objetporte = 0, int Or = 0,
            Objet* Butin = 0, GroupeObjets* Objetporte = 0, int Or = 0,
            int Statut = 0, int Jauge = 0); //utilisé
    Monstre(const Monstre& other); //utile pour la création d'un groupe de combat
    ~Monstre();
    // GroupeObjets* GetButin() const;
    // void SetButin(GroupeObjets* val);
    Objet* GetButin() const;
    void SetButin(Objet* val);
    GroupeObjets* GetObjetPorte() const;
    void SetObjetPorte(GroupeObjets* val);
    int GetOr() const; //peut être négatif
    void SetOr(int val);
    Script* GetScript() const;
    void SetScript(Script* val);
    void ActualiserAnimation(); // décrémente le temps
    char GetElementAttaque() const;
    void SetElementAttaque(char val);
    char GetElementDefense() const;
    void SetElementDefense(char val);
    int GetModificateurElementaire(unsigned char id, char element) const;
    void Attaquer(unsigned int de, unsigned int max_de); //pour prendre en compte les éléments

    int Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    // GroupeObjets* m_Butin;
    Objet* m_Butin;
    GroupeObjets* m_ObjetPorte;
    int m_Or;
    Script* m_Script;
    char m_ElementAttaque;
    char m_ElementDefense;
    //char m_ElementPhysionomique; ?
};

#endif // MONSTRE_H
