#ifndef INPUT_H
#define INPUT_H

#include <cstdio>
#include <cstdlib>
#include <SDL/SDL.h>

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
    bool GetZ() const;
    void SetZ(bool val);
    bool GetE() const;
    void SetE(bool val);
    bool GetR() const;
    void SetR(bool val);
    bool GetT() const;
    void SetT(bool val);
    bool GetY() const;
    void SetY(bool val);
    bool GetQ() const;
    void SetQ(bool val);
    bool GetS() const;
    void SetS(bool val);
    bool GetD() const;
    void SetD(bool val);
    bool GetF() const;
    void SetF(bool val);
    bool GetG() const;
    void SetG(bool val);
    bool GetH() const;
    void SetH(bool val);
    bool GetBouton() const;
    void Actualiser();
    void Vider();
protected:
private:
    bool m_haut;
    bool m_droite;
    bool m_bas;
    bool m_gauche;
    bool m_A;
    bool m_Z;
    bool m_E;
    bool m_R;
    bool m_T;
    bool m_Y;
    bool m_Q;
    bool m_S;
    bool m_D;
    bool m_F;
    bool m_G;
    bool m_H;
};

#endif // INPUT_H
