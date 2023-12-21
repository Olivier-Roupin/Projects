#ifndef OBJET_H
#define OBJET_H

#include <macros.h>

#define OBJET       1 //objet de quête ?
#define EQUIPABLE  10 //utile ?
#define UTILISABLE 20
//TODO à refaire avec une logique binaire

#define TAILLE_NOM_OBJET 7
#define TAILLE_DESCRIPTION_OBJET 47

class Objet {
public:
    enum Type {
        type_quete, type_equipable, type_utilisable
    };
    Objet(int Id, const char* Nom = "_", unsigned char Type = OBJET,
          unsigned int Prix = 0, const char* Description = "_");
    Objet(const Objet& cible); //utile ?
    virtual ~Objet();
    int GetId() const;
    void SetId(int val);
    unsigned char GetType() const;
    void SetType(unsigned char val);
    virtual bool EstEquipable() const;
    unsigned int GetPrix() const;
    void SetPrix(unsigned int val);
    const char* GetNom() const;
    void SetNom(const char* val);
    const char* GetDescription() const;
    void SetDescription(const char* val);

    virtual int Ecrire(char* data) const;
    virtual void Lire(int& i, const char* data);
    virtual unsigned int TailleD() const;
    virtual char* EcrireD(char* data) const;
    virtual const char* LireD(const char* data);
protected:
private:
    int m_Id;
    unsigned char m_Type;
    unsigned int m_Prix;
    char m_Nom[TAILLE_NOM_OBJET+1];
    char m_Description[TAILLE_DESCRIPTION_OBJET+1];
};

#endif // OBJET_H
