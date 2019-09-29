#include "Input.h"

Input::Input()
{
    Sethaut(0);
    Setdroite(0);
    Setbas(0);
    Setgauche(0);
    SetA(0);
    SetB(0);
    SetX(0);
    SetY(0);
    SetL(0);
    SetR(0);
    SetStart(0);
    SetSelect(0);
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

bool Input::GetB() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_B;
}

void Input::SetB(bool val)
{
    m_B = val;
}

bool Input::GetX() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_X;
}

void Input::SetX(bool val)
{
    m_X = val;
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

bool Input::GetL() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_L;
}

void Input::SetL(bool val)
{
    m_L = val;
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

bool Input::GetStart() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_Start;
}

void Input::SetStart(bool val)
{
    m_Start = val;
}

bool Input::GetSelect() const
{
    if (this == 0)
    {
        return 0;
    }
    return m_Select;
}

void Input::SetSelect(bool val)
{
    m_Select = val;
}

void Input::Actualiser()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
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
            case SDLK_b:
                SetB(1);
                break;
            case SDLK_x:
                SetX(1);
                break;
            case SDLK_y:
                SetY(1);
                break;
            case SDLK_l:
                SetL(1);
                break;
            case SDLK_r:
                SetR(1);
                break;
            case SDLK_RETURN:
                SetStart(1);
                break;
            case SDLK_DELETE:
                SetSelect(1);
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
            case SDLK_b:
                SetB(0);
                break;
            case SDLK_x:
                SetX(0);
                break;
            case SDLK_y:
                SetY(0);
                break;
            case SDLK_l:
                SetL(0);
                break;
            case SDLK_r:
                SetR(0);
                break;
            case SDLK_RETURN:
                SetStart(0);
                break;
            case SDLK_DELETE:
                SetSelect(0);
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
    SetB(0);
    SetX(0);
    SetY(0);
    SetL(0);
    SetR(0);
    SetStart(0);
    SetSelect(0);
}
