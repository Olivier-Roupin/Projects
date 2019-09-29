#include "Input.h"

Input::Input()
{
    Sethaut(0);
    Setdroite(0);
    Setbas(0);
    Setgauche(0);
    SetA(0);
    SetZ(0);
    SetE(0);
    SetR(0);
    SetT(0);
    SetY(0);
    SetQ(0);
    SetS(0);
    SetD(0);
    SetF(0);
    SetG(0);
    SetH(0);
}

Input::~Input()
{
    //dtor
}

bool Input::Gethaut() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_haut;
}

void Input::Sethaut(bool val)
{
    m_haut = val;
}

bool Input::Getdroite() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_droite;
}

void Input::Setdroite(bool val)
{
    m_droite = val;
}

bool Input::Getbas() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_bas;
}

void Input::Setbas(bool val)
{
    m_bas = val;
}

bool Input::Getgauche() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_gauche;
}

void Input::Setgauche(bool val)
{
    m_gauche = val;
}

bool Input::GetA() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_A;
}

void Input::SetA(bool val)
{
    m_A = val;
}

bool Input::GetZ() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_Z;
}

void Input::SetZ(bool val)
{
    m_Z = val;
}

bool Input::GetE() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_E;
}

void Input::SetE(bool val)
{
    m_E = val;
}

bool Input::GetR() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_R;
}

void Input::SetR(bool val)
{
    m_R = val;
}

bool Input::GetT() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_T;
}

void Input::SetT(bool val)
{
    m_T = val;
}

bool Input::GetY() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_Y;
}

void Input::SetY(bool val)
{
    m_Y = val;
}

bool Input::GetQ() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_Q;
}

void Input::SetQ(bool val)
{
    m_Q = val;
}

bool Input::GetS() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_S;
}

void Input::SetS(bool val)
{
    m_S = val;
}

bool Input::GetD() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_D;
}

void Input::SetD(bool val)
{
    m_D = val;
}

bool Input::GetF() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_F;
}

void Input::SetF(bool val)
{
    m_F = val;
}

bool Input::GetG() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_G;
}

void Input::SetG(bool val)
{
    m_G = val;
}

bool Input::GetH() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_H;
}

void Input::SetH(bool val)
{
    m_H = val;
}

bool Input::GetBouton() const
{
    if (this == 0)
    {
        return 0;
    }
    return GetA()||Getbas()||GetD()||Getdroite()||GetE()||GetF()||GetG()||\
    Getgauche()||GetH()||Gethaut()||GetQ()||GetR()||GetS()||GetT()||GetY()||GetZ();
}

void Input::Actualiser()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                exit(0);
                break;
            case SDLK_UP:
                Sethaut(1);
                break;
            case SDLK_RIGHT:
                Setdroite(1);
                break;
            case SDLK_DOWN:
                Setbas(1);
                break;
            case SDLK_LEFT:
                Setgauche(1);
                break;
            case SDLK_a:
                SetA(1);
                break;
            case SDLK_z:
                SetZ(1);
                break;
            case SDLK_e:
                SetE(1);
                break;
            case SDLK_r:
                SetR(1);
                break;
            case SDLK_t:
                SetT(1);
                break;
            case SDLK_y:
                SetY(1);
                break;
            case SDLK_q:
                SetQ(1);
                break;
            case SDLK_s:
                SetS(1);
                break;
            case SDLK_d:
                SetD(1);
                break;
            case SDLK_f:
                SetF(1);
                break;
            case SDLK_g:
                SetG(1);
                break;
            case SDLK_h:
                SetH(1);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                Sethaut(0);
                break;
            case SDLK_RIGHT:
                Setdroite(0);
                break;
            case SDLK_DOWN:
                Setbas(0);
                break;
            case SDLK_LEFT:
                Setgauche(0);
                break;
            case SDLK_a:
                SetA(0);
                break;
            case SDLK_z:
                SetZ(0);
                break;
            case SDLK_e:
                SetE(0);
                break;
            case SDLK_r:
                SetR(0);
                break;
            case SDLK_t:
                SetT(0);
                break;
            case SDLK_y:
                SetY(0);
                break;
            case SDLK_q:
                SetQ(0);
                break;
            case SDLK_s:
                SetS(0);
                break;
            case SDLK_d:
                SetD(0);
                break;
            case SDLK_f:
                SetF(0);
                break;
            case SDLK_g:
                SetG(0);
                break;
            case SDLK_h:
                SetH(0);
                break;
            default:
                break;
            }
            break;
        }
    }
}

void Input::Vider()
{
    Sethaut(0);
    Setdroite(0);
    Setbas(0);
    Setgauche(0);
    SetA(0);
    SetZ(0);
    SetE(0);
    SetR(0);
    SetT(0);
    SetY(0);
    SetQ(0);
    SetS(0);
    SetD(0);
    SetF(0);
    SetG(0);
    SetH(0);
}
