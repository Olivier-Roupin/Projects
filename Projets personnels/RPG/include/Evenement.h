#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <Script.h>
#include <string>

#define Z_BAS 0
#define Z_MILIEU 1
#define Z_HAUT 2

class Evenement
{
    public:
        Evenement(int id, int X, int Y, int Z, int Nombre, Script** Scripts, std::string Image = "_");
        Evenement(int id, int Nombre, std::string Image = "_", int X = 0, int Y = 0, int Z = 0); //utilisé
        virtual ~Evenement();
        int Getid() const;
        void Setid(int val);
        int GetX() const;
        void SetX(int val);
        void ChangerX(int val);
        int GetY() const;
        void SetY(int val);
        void ChangerY(int val);
        int GetZ() const;
        void SetZ(int val);
        int GetNombre() const;
        void SetNombre(int val);
        Script* GetScripts(int id) const;
        void SetScripts(Script* val, int id);
        std::string GetImage() const;
        void SetImage(std::string val);
    protected:
    private:
        int m_id;
        int m_X;
        int m_Y;
        int m_Z;
        int m_Nombre;
        Script** m_Scripts;
        std::string m_Image;
};

#endif // EVENEMENT_H
