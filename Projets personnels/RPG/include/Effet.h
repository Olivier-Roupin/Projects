#ifndef EFFET_H
#define EFFET_H

#include <Script.h>

#define NOMBRE_IN_EFFET 9
#define IN_EFFET_ID_SCRIPT 0
#define IN_EFFET_ELEMENT 1
#define IN_EFFET_DISPONIBILITE 2
#define IN_EFFET_CHOIX_CIBLE 3
#define IN_EFFET_CHOIX_FACTION 4
#define IN_EFFET_CHOIX_QUANTITE 5
#define IN_EFFET_DEFAUT_CIBLE 6
#define IN_EFFET_DEFAUT_FACTION 7
#define IN_EFFET_DEFAUT_QUANTITE 8

//Disponibilité et situation
#define TOUJOURS 0
#define COMBAT 1
#define MENU 2

#define CIBLE_LANCEUR -1
#define CIBLE_TOUS -2
#define CIBLE_AUCUNE -3
//INDICE CIBLE >= 0
#define FACTION_LANCEUR false
#define FACTION_ADVERSE true
#define QUANTITE_UNE false
#define QUANTITE_FACTION true

class Effet
{
public:
    Effet(Script* script, int Element = 0, int Disponibilite = TOUJOURS);
    Effet(Script* script, int Element, int Disponibilite,\
          bool Choix_Cible, bool Choix_Faction, bool Choix_Quantite,\
          int Defaut_Cible, bool Defaut_Faction, bool Defaut_Quantite); //utilisé
    virtual ~Effet();
    Script* GetScript() const;
    void SetScript(Script* val);
    int GetElement() const;
    void SetElement(int val);
    int GetDisponibilite() const;
    void SetDisponibilite(int val);
    bool GetChoix_Cible() const;
    void SetChoix_Cible(bool val);
    bool GetChoix_Faction() const;
    void SetChoix_Faction(bool val);
    bool GetChoix_Quantite() const;
    void SetChoix_Quantite(bool val);
    int GetDefaut_Cible() const;
    void SetDefaut_Cible(int val);
    bool GetDefaut_Faction() const;
    void SetDefaut_Faction(bool val);
    bool GetDefaut_Quantite() const;
    void SetDefaut_Quantite(bool val);

protected:
private:
    Script* m_Script;
    int m_Element;
    int m_Disponibilite;
    bool m_Choix_Cible; //droit de changer de cible
    bool m_Choix_Faction; //droit de changer de faction
    bool m_Choix_Quantite; //droit de changer entre une/faction
    int m_Defaut_Cible; //indice par défaut -1:lanceur -2:tous -3:aucune
    bool m_Defaut_Faction; //faction par défaut 0:allier 1:adverse
    bool m_Defaut_Quantite; //quantité par défaut 0:unique 1:faction
};

#endif // EFFET_H
