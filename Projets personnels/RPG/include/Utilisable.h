#ifndef UTILISABLE_H
#define UTILISABLE_H

#include <Objet.h>
#include <Effet.h>

class Utilisable : public Objet
{
public:
    Utilisable(int Id = 0, std::string Nom = "_", int Type = UTILISABLE, int Prix = 0, std::string Description = "_",\
               bool Illimite = false, Effet* effet = 0);
    virtual ~Utilisable();
    bool GetIllimite() const;
    void SetIllimite(bool val);
    Effet* GetEffet() const;
    void SetEffet(Effet* val);
protected:
private:
    bool m_Illimite;
    Effet* m_Effet;
};

#endif // UTILISABLE_H
