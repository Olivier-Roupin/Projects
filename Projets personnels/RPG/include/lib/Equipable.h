#ifndef EQUIPABLE_H
#define EQUIPABLE_H

#include <lib/Objet.h>
#include <lib/Elements.h>

#define EQUIPABLE_ARME 11
#define EQUIPABLE_ARMURE 12
#define EQUIPABLE_BOUCLIER 13
#define EQUIPABLE_CASQUE 14
#define EQUIPABLE_ACCESSOIRE 15

#define NOMBRE_ATTRIBUTS 9
#define ATTRIBUT_VIE 0
#define ATTRIBUT_ATKP 1
#define ATTRIBUT_DEFP 2
#define ATTRIBUT_MAG 3
#define ATTRIBUT_ATKM 4
#define ATTRIBUT_DEFM 5
#define ATTRIBUT_VIT 6
#define ATTRIBUT_PRE 7
#define ATTRIBUT_ESQ 8

#define MAX_RATIO 15

class Equipable : public Objet {
public:
    Equipable(int id, const char* nom = "_", int type = EQUIPABLE, int prix = 0,
              const char* description = "_",\
              int vieMax   = 0, int attaqueP  = 0, int defenseP = 0,\
              int magieMax = 0, int attaqueM  = 0, int defenseM = 0,\
              int vitesse  = 0, int precision = 0, int esquive  = 0,\
              char poids = 0, unsigned char ratio = 8); //utilisé
    virtual ~Equipable();
    bool EstEquipable() const;

    int GetAttribut(unsigned char id) const;
    void SetAttribut(int val, unsigned char id);

    //Evolution
    char GetPoids() const; //TODO: interdire négatif ?
    void SetPoids(char val);
    unsigned char GetRatio() const;
    void SetRatio(unsigned char val);
    //Affichage
    char GetOffensif() const;
    char GetDefensif() const;
    char GetPhysionomique() const;

    char GetElement() const;
    void SetElement(char val);
    // int GetDegats() const;
    // void SetDegats(int val);
    
    int Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    //Permanent
    int m_Attributs[NOMBRE_ATTRIBUTS];
    //Evolution
    char m_Poids;
    unsigned char m_Ratio;
    char m_Element;
    // int m_Degats;
};

#endif // EQUIPABLE_H
