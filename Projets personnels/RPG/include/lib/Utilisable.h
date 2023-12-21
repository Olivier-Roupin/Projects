#ifndef UTILISABLE_H
#define UTILISABLE_H

#include <lib/Objet.h>
#include <lib/Effet.h>

class Utilisable : public Objet {
public:
    Utilisable(int Id = 0, const char* Nom = "_", int Type = UTILISABLE,
               int Prix = 0, const char* Description = "_",\
               bool Illimite = false, Effet* effet = 0);
    virtual ~Utilisable();
    bool EstEquipable() const;
    bool GetIllimite() const;
    void SetIllimite(bool val);
    Effet* GetEffet() const;
    void SetEffet(Effet* val);
    
    int Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    bool m_Illimite;
    Effet* m_Effet;
};

#endif // UTILISABLE_H
