#ifndef INPUT_H
#define INPUT_H

#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>

class Input
{
    public:
        Input();
        virtual ~Input();
        bool Gethaut() const;
        void Sethaut(bool val);
        bool Getdroite() const;
        void Setdroite(bool val);
        bool Getbas() const;
        void Setbas(bool val);
        bool Getgauche() const;
        void Setgauche(bool val);
        bool GetA() const;
        void SetA(bool val);
        bool GetB() const;
        void SetB(bool val);
        bool GetX() const;
        void SetX(bool val);
        bool GetY() const;
        void SetY(bool val);
        bool GetL() const;
        void SetL(bool val);
        bool GetR() const;
        void SetR(bool val);
        bool GetStart() const;
        void SetStart(bool val);
        bool GetSelect() const;
        void SetSelect(bool val);
        void Actualiser();
        void Vider();
    protected:
    private:
        bool m_haut;
        bool m_droite;
        bool m_bas;
        bool m_gauche;
        bool m_A;
        bool m_B;
        bool m_X;
        bool m_Y;
        bool m_L;
        bool m_R;
        bool m_Start;
        bool m_Select;
};

#endif // INPUT_H
