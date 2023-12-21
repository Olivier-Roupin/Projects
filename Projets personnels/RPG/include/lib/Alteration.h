#ifndef ALTERATION_H
#define ALTERATION_H

#include <lib/Script.h>
#include <macros.h>

#define TAILLE_NOM_ALTERATION 15

class Alteration {
public:
    Alteration(int id = 0, const char* nom = "_", Script* script = 0,
               bool postCombat = false, bool postDeces = false,
               unsigned char priorite = 0, Script* scriptTerrain = 0); //utilisé
    Alteration(const Alteration& cible);
    virtual ~Alteration();
    int GetId() const;
    void SetId(int val);
    const char* GetNom() const;
    int SetNom(const char* val);
    Script* GetScript() const;
    void SetScript(Script* val);
    Script* GetScriptTerrain() const;
    void SetScriptTerrain(Script* val);
    bool GetPostCombat() const;
    void SetPostCombat(bool val);
    bool GetPostDeces() const;
    void SetPostDeces(bool val);
    unsigned char GetPriorite() const;
    void SetPriorite(unsigned char val);

    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    char m_Nom[TAILLE_NOM_ALTERATION+1];
    Script* m_Script;
    Script* m_ScriptTerrain;
    bool m_PostCombat;
    bool m_PostDeces;
    unsigned char m_Priorite;
};

#endif // ALTERATION_H
