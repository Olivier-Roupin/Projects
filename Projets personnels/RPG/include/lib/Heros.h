#ifndef HEROS_H
#define HEROS_H

#include <lib/Personnage.h>
#include <lib/Equipable.h>

#define NOMBRE_EQUIPEMENTS 6
#define EQUIPEMENT_MAINGAUCHE  0
#define EQUIPEMENT_MAINDROITE  1
#define EQUIPEMENT_TETE        2
#define EQUIPEMENT_CORPS       3
#define EQUIPEMENT_ACCESSOIRE1 4
#define EQUIPEMENT_ACCESSOIRE2 5

#define RANG_AVANT   false
#define RANG_ARRIERE true

class Heros : public Personnage {
public:
    Heros(int id); //utilisé
    /*Heros(int id, const char* nom = "_", int vie = 0, int magie = 0,
          int vieMax   = 0, int attaqueP  = 0, int defenseP = 0,
          int magieMax = 0, int attaqueM  = 0, int defenseM = 0,
          int vitesse  = 0, int precision = 0, int esquive  = 0,
          unsigned char statut = 0, unsigned int experience = 0, unsigned char niveau = 1,
          int force = 0, int intelligence = 0, int agilite = 0,
          bool rang = RANG_AVANT,
          Objet* maingauche = 0, Objet* maindroite = 0,
          Objet* tete = 0,
          Objet* corps = 0, Objet* accessoire1 = 0,
          Objet* accessoire2 = 0, unsigned int jauge = 0);*/
    ~Heros();
    unsigned char GetOffensif() const;
    unsigned char GetDefensif() const;
    unsigned char GagnerExperience(int val);
    void PasserNiveau();
    int GetForce() const;
    void SetForce(int val);
    int GetIntelligence() const;
    void SetIntelligence(int val);
    int GetAgilite() const;
    void SetAgilite(int val);
    bool GetRang() const;
    void SetRang(bool val);
    void ChangerRang();
    bool GetGarde() const;
    void SetGarde(bool val);
    // Objet* GetEquipement(unsigned char id) const;
    // int SetEquipement(Objet *val, unsigned char id);
    Equipable* GetEquipement(unsigned char id) const;
    bool SetEquipement(Equipable *val, unsigned char id);

    //Avec limites
    void SetVieMax(int val);
    void SetMagieMax(int val);

    int CalculerForce() const;
    int CalculerIntelligence() const;
    int CalculerAgilite() const;

    //Prise en compte des équipements/altérations/rang
    int GetAttributTotal(unsigned char id) const;
    int GetModificateurElementaire(unsigned char id, char element) const;
    void Attaquer(unsigned int de, unsigned int max_de); //pour prendre en compte les éléments

    // char GetAnimation() const;
    // void SetAnimation(char val);
    // void ActualiserMessage(); // décrémente le temps, met l'action à inactif
    // void SetMessage(int val); // met l'action à inactif
    void ActualiserAnimation();
    void RenduCombat(char* image) const;

    int Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Niveau;
    int m_Force;
    int m_Intelligence;
    int m_Agilite;
    bool m_Rang;
    bool m_Garde;
    // char m_Animation;
    // Objet* m_Equipement[NOMBRE_EQUIPEMENTS];
    Equipable* m_Equipement[NOMBRE_EQUIPEMENTS];
};

#endif // HEROS_H
