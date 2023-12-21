#ifndef EFFET_H
#define EFFET_H

#include <lib/Script.h>
#include <lib/Elements.h>
#include <macros.h>

//Disponibilité et situation
#define TOUJOURS 0
#define COMBAT   1
#define MENU     2
// #define TOUJOURS 3 // utiliser cette définition ?

#define CIBLE_LANCEUR -1
#define CIBLE_TOUS    -2
#define CIBLE_AUCUNE  -3
//INDICE CIBLE >= 0
#define FACTION_LANCEUR false
#define FACTION_ADVERSE true
#define QUANTITE_UNE false
#define QUANTITE_FACTION true

class Effet {
public:
    Effet(int id = 0, Script* script = 0, char Element = ELEMENT_NEUTRE, char Disponibilite = TOUJOURS); //utilisé
    Effet(int id, Script* script, char Element, char Disponibilite,\
          bool Choix_Cible, bool Choix_Faction, bool Choix_Quantite,\
          int Defaut_Cible, bool Defaut_Faction, bool Defaut_Quantite);
    virtual ~Effet();
    int GetId() const;
    void SetId(int val);
    Script* GetScript() const;
    void SetScript(Script* val);
    char GetElement() const;
    void SetElement(char val);
    char GetDisponibilite() const;
    void SetDisponibilite(char val);
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

    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    Script* m_Script;
    char m_Element;
    char m_Disponibilite;
    bool m_Choix_Cible; //droit de changer de cible
    bool m_Choix_Faction; //droit de changer de faction
    bool m_Choix_Quantite; //droit de changer entre une/faction
    int m_Defaut_Cible; //indice par défaut -1:lanceur -2:tous -3:aucune
    bool m_Defaut_Faction; //faction par défaut 0:allier 1:adverse
    bool m_Defaut_Quantite; //quantité par défaut 0:unique 1:faction
};

#endif // EFFET_H
