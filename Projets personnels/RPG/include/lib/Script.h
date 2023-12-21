#ifndef SCRIPT_H
#define SCRIPT_H

class Partie;

typedef int(*PtrFonction)(Partie*, int);

class Script {
    public:
        Script(int id, PtrFonction fonction, int curseur=0);
        Script(const Script& other);
        virtual ~Script();
        int GetId() const;
        void SetId(int val);
        PtrFonction GetFonction() const;
        void SetFonction(PtrFonction val);
        int GetCurseur() const;
        void SetCurseur(int val);
        void Executer(Partie* partie);
    protected:
    private:
        int m_Id;
        PtrFonction m_Fonction;
        int m_Curseur;
};

#endif // SCRIPT_H
