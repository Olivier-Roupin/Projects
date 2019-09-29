#ifndef OBJET_H
#define OBJET_H

#include <string>

#define OBJET 1 //objet de quête ?
#define EQUIPABLE 10 //utile ?
#define UTILISABLE 20

class Objet
{
    public:
        enum Type
        {
            type_quete, type_equipable, type_utilisable
        };
        Objet(int Id, std::string Nom = "_", int Type = OBJET, int Prix = 0, std::string Description = "_");
        Objet(const Objet& cible); //utile ?
        ~Objet();
        int GetId() const;
        void SetId(int val);
        int GetType() const;
        void SetType(int val);
        int GetPrix() const;
        void SetPrix(int val);
        std::string GetNom() const;
        void SetNom(std::string val);
        std::string GetDescription() const;
        void SetDescription(std::string val);

    protected:
    private:
        int m_Id;
        int m_Type;
        int m_Prix;
        std::string m_Nom;
        std::string m_Description;
};

#endif // OBJET_H
