#include "BoiteTexte.h"

#include <iostream>

using namespace std;

BoiteTexte::BoiteTexte(char* texte, int X, int Y, int L, int H)
{
    /*SetL(L);
    SetH(H);
    SetTexte(texte);
    m_Lettres = new ElementGraphique*[sizeof(ElementGraphique*)*GetL()*GetH()];
    m_Fenetre = new ElementGraphique*[sizeof(ElementGraphique*)*(GetL()+2)*(GetH()+2)];
    ElementGraphique* cible = new ElementGraphique(0, 0, TAILLE_BASIQUE, TAILLE_BASIQUE, "graphics/police.png");
    for(int i(0); i < GetL()*GetH(); i++)
    {
        m_Lettres[i] = 0;
        SetLettres(cible, i);
        GetLettres(i)->SetPositionT(X + i%L + 1, Y + i/L +1);
        GetLettres(i)->SetSource(Caractere2Rect(texte[i]));

        m_Fenetre[i] = 0;
        SetFenetre(cible, i);
        GetFenetre(i)->SetPositionT(X + i%L + 1, Y + i/L + 1);
        GetFenetre(i)->SetSource(Int2Rect(136));
    }
    for(int i(GetL()*GetH()); i < GetL()*GetH()+2*(GetL()+GetH())+4; i++)
    {
        m_Lettres[i] = 0;
        SetLettres(cible, i);
    }
    GetLettres(GetL()*GetH())->SetPositionT(X, Y);
    GetLettres(GetL()*GetH())->SetSource(Int2Rect(128));

    GetLettres(GetL()*GetH()+1)->SetPositionT(X + GetL() + 1, Y);
    GetLettres(GetL()*GetH()+1)->SetSource(Int2Rect(130));

    GetLettres(GetL()*GetH()+2)->SetPositionT(X, Y + GetH() + 1);
    GetLettres(GetL()*GetH()+2)->SetSource(Int2Rect(133));

    GetLettres(GetL()*GetH()+3)->SetPositionT(X + GetL() + 1, Y + GetH() + 1);
    GetLettres(GetL()*GetH()+3)->SetSource(Int2Rect(135));
    for(int i(GetL()*GetH()+4); i < GetL()*GetH()+4+GetL(); i++)
    {
        GetLettres(i)->SetPositionT(X + i - GetL()*GetH() - 3 , Y);
        GetLettres(i)->SetSource(Int2Rect(129));

        GetLettres(i+GetL())->SetPositionT(X + i - GetL()*GetH() - 3, Y + GetH() + 1);
        GetLettres(i+GetL())->SetSource(Int2Rect(134));
    }
    for(int i(GetL()*GetH()+4+2*GetL()); i < GetL()*GetH()+4+2*GetL()+GetH(); i++)
    {
        GetLettres(i)->SetPositionT(X, Y + i - GetL()*GetH() - 3 - 2*GetL());
        GetLettres(i)->SetSource(Int2Rect(131));

        GetLettres(i+GetH())->SetPositionT(X + GetL() + 1, Y + i - GetL()*GetH() - 3 - 2*GetL());
        GetLettres(i+GetH())->SetSource(Int2Rect(132));
    }*/
}

BoiteTexte::~BoiteTexte()
{
    //dtor
}

char* BoiteTexte::GetTexte() const
{
    return m_Texte;
}

void BoiteTexte::SetTexte(char* val)
{
    m_Texte = val;
}

SDL_Texture* BoiteTexte::GetTexture() const
{
    return m_Texture;
}

void BoiteTexte::SetTexture(SDL_Texture* val)
{
    m_Texture = val;
}

ElementGraphique* BoiteTexte::GetLettres(int id) const
{
    return m_Lettres[id];
}

void BoiteTexte::SetLettres(ElementGraphique* val, int id)
{
    delete m_Lettres[id];
    m_Lettres[id] = new ElementGraphique(*val);
}

ElementGraphique* BoiteTexte::GetFenetre(int id) const
{
    return m_Fenetre[id];
}

void BoiteTexte::SetFenetre(ElementGraphique* val, int id)
{
    delete m_Fenetre[id];
    m_Fenetre[id] = new ElementGraphique(*val);
}

int BoiteTexte::GetL() const
{
    return m_L;
}

void BoiteTexte::SetL(int val)
{
    m_L = val;
}

int BoiteTexte::GetH() const
{
    return m_H;
}

void BoiteTexte::SetH(int val)
{
    m_H = val;
}

void BoiteTexte::Afficher()
{
    for(int i(0); i < GetL()*GetH(); i++)
    {
        //GetFenetre(i)->Afficher();
    }
    for(int i(0); i < (GetL()+2)*(GetH()+2); i++)
    {
        //GetLettres(i)->Afficher();
    }
}

SDL_Rect* Caractere2Rect(char val)
{
    int P(0);
    switch (val)
    {
    case 'A':
        P = P_A;
        break;
    case 'B':
        P = P_B;
        break;
    case 'C':
        P = P_C;
        break;
    case 'D':
        P = P_D;
        break;
    case 'E':
        P = P_E;
        break;
    case 'F':
        P = P_F;
        break;
    case 'G':
        P = P_G;
        break;
    case 'H':
        P = P_H;
        break;
    case 'I':
        P = P_I;
        break;
    case 'J':
        P = P_J;
        break;
    case 'K':
        P = P_K;
        break;
    case 'L':
        P = P_L;
        break;
    case 'M':
        P = P_M;
        break;
    case 'N':
        P = P_N;
        break;
    case 'O':
        P = P_O;
        break;
    case 'P':
        P = P_P;
        break;
    case 'Q':
        P = P_Q;
        break;
    case 'R':
        P = P_R;
        break;
    case 'S':
        P = P_S;
        break;
    case 'T':
        P = P_T;
        break;
    case 'U':
        P = P_U;
        break;
    case 'V':
        P = P_V;
        break;
    case 'W':
        P = P_W;
        break;
    case 'X':
        P = P_X;
        break;
    case 'Y':
        P = P_Y;
        break;
    case 'Z':
        P = P_Z;
        break;
    case 'a':
        P = P_a;
        break;
    case 'b':
        P = P_b;
        break;
    case 'c':
        P = P_c;
        break;
    case 'd':
        P = P_d;
        break;
    case 'e':
        P = P_e;
        break;
    case 'f':
        P = P_f;
        break;
    case 'g':
        P = P_g;
        break;
    case 'h':
        P = P_h;
        break;
    case 'i':
        P = P_i;
        break;
    case 'j':
        P = P_j;
        break;
    case 'k':
        P = P_k;
        break;
    case 'l':
        P = P_l;
        break;
    case 'm':
        P = P_m;
        break;
    case 'n':
        P = P_n;
        break;
    case 'o':
        P = P_o;
        break;
    case 'p':
        P = P_p;
        break;
    case 'q':
        P = P_q;
        break;
    case 'r':
        P = P_r;
        break;
    case 's':
        P = P_s;
        break;
    case 't':
        P = P_t;
        break;
    case 'u':
        P = P_u;
        break;
    case 'v':
        P = P_v;
        break;
    case 'w':
        P = P_w;
        break;
    case 'x':
        P = P_x;
        break;
    case 'y':
        P = P_y;
        break;
    case 'z':
        P = P_z;
        break;
    case ' ':
        P = P__;
        break;
    default:
        P = P__;
        break;
    }
    return Int2Rect(P);
}

SDL_Rect* Int2Rect(int val)
{
    SDL_Rect* source(0);
//    int P(0);
    source = new SDL_Rect();
    source->w = TAILLE_BASIQUE;
    source->h = TAILLE_BASIQUE;
    source->x = (val % L_POLICE)*TAILLE_BASIQUE;
    source->y = (val / L_POLICE)*TAILLE_BASIQUE;
    return source;
}
