#ifndef ALTERATION_H
#define ALTERATION_H

#include <Script.h>
#include <string>

class Alteration
{
public:
    Alteration(int id, std::string nom, Script* script, bool postCombat, bool postDeces, int priorite);
    Alteration(const Alteration& cible);
    virtual ~Alteration();
    int GetId() const;
    void SetId(int val);
    std::string GetNom() const;
    void SetNom(std::string val);
    Script* GetScript() const;
    void SetScript(Script* val);
    bool GetPostCombat() const;
    void SetPostCombat(bool val);
    bool GetPostDeces() const;
    void SetPostDeces(bool val);
    int GetPriorite() const;
    void SetPriorite(int val);

protected:
private:
    int m_Id;
    std::string m_Nom;
    Script* m_Script;
    bool m_PostCombat;
    bool m_PostDeces;
    int m_Priorite;
};

#endif // ALTERATION_H
