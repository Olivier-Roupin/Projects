#include "BlocGraphique.h"

using namespace std;

BlocGraphique::BlocGraphique(int Nombre_Elements, int* Elements, int Largeur, int Hauteur, int* Mappage)
{
    SetLargeur(Largeur);
    SetHauteur(Hauteur);
    m_Elements = new ElementGraphique*[sizeof(ElementGraphique*)*Nombre_Elements];
    for(int i(0); i < Nombre_Elements; i++)
    {
        SetElements(elements_graphiques[Elements[i]], i);
    }
    SetMappage(Mappage);
}

BlocGraphique::BlocGraphique(string text)
{
    SetLargeur(text.length());
    SetHauteur(1);
    m_Elements = new ElementGraphique*[sizeof(ElementGraphique*)*text.length()];
    m_Mappage = new int[sizeof(int)*text.length()];
    int i;
    for(i = 0; i < text.length(); i++)
    {
        SetElements(elements_graphiques[Caractere2Element(text[i])], i);
        SetMappage(i,i);
    }
}

BlocGraphique::BlocGraphique(string tile, int taille)
{
    SetLargeur(taille*taille);
    SetHauteur(1);//taille);
    m_Elements = new ElementGraphique*[sizeof(ElementGraphique*)*taille*taille];
    m_Mappage = new int[sizeof(int)*taille*taille];
    int i;
    for(i = 0; i < taille*taille; i++)
    {
        //SetElements(elements_graphiques[0+2*Caractere2Tile(tile[0])+i%taille+1*(i/taille)], i);
        //SetMappage(i%taille,i/taille);
        SetElements(elements_graphiques[32*16+Caractere2Tile(tile[0])], i);
        SetMappage(i,i);
    }
}

BlocGraphique::~BlocGraphique()
{
    //dtor
    delete m_Elements;
    delete m_Mappage;
    m_Elements = 0;
    m_Mappage = 0;
}

ElementGraphique* BlocGraphique::GetElements(int id) const
{
    return m_Elements[id];
}

void BlocGraphique::SetElements(ElementGraphique* val, int id)
{
    m_Elements[id] = val;
}

int BlocGraphique::GetLargeur() const
{
    return m_Largeur;
}

void BlocGraphique::SetLargeur(int val)
{
    m_Largeur = val;
}

int BlocGraphique::GetHauteur() const
{
    return m_Hauteur;
}

void BlocGraphique::SetHauteur(int val)
{
    m_Hauteur = val;
}

int BlocGraphique::GetTaille() const
{
    return GetLargeur()*GetHauteur();
}

int BlocGraphique::GetMappage(int id) const
{
    return m_Mappage[id];
}

void BlocGraphique::SetMappage(int* val)
{
    m_Mappage = val;
}

void BlocGraphique::SetMappage(int val, int id)
{
    m_Mappage[id] = val;
}

void BlocGraphique::Afficher(int x, int y, int j, int i)
{
    int k;
    for(k = 0; k < GetTaille(); k++)
    {
        GetElements(GetMappage(k))->Afficher(x + (k % GetLargeur())*TAILLE_BASIQUE, y + (k / GetLargeur())*TAILLE_BASIQUE, j, i);
    }
}
/*
void BlocGraphique::Afficher(int x, int y)
{
    int i;
    for(i = 0; i < GetTaille(); i++)
    {
        GetElements(GetMappage(i))->Afficher((x + i % GetLargeur())*TAILLE_BASIQUE, (y + i / GetLargeur())*TAILLE_BASIQUE);
    }
}
*/
int Caractere2Element(char val)
{
    switch(val)
    {
    case 'A':
        return P_A;
    case 'B':
        return P_B;
    case 'C':
        return P_C;
    case 'D':
        return P_D;
    case 'E':
        return P_E;
    case 'F':
        return P_F;
    case 'G':
        return P_G;
    case 'H':
        return P_H;
    case 'I':
        return P_I;
    case 'J':
        return P_J;
    case 'K':
        return P_K;
    case 'L':
        return P_L;
    case 'M':
        return P_M;
    case 'N':
        return P_N;
    case 'O':
        return P_O;
    case 'P':
        return P_P;
    case 'Q':
        return P_Q;
    case 'R':
        return P_R;
    case 'S':
        return P_S;
    case 'T':
        return P_T;
    case 'U':
        return P_U;
    case 'V':
        return P_V;
    case 'W':
        return P_W;
    case 'X':
        return P_X;
    case 'Y':
        return P_Y;
    case 'Z':
        return P_Z;
    case 'a':
        return P_a;
    case 'b':
        return P_b;
    case 'c':
        return P_c;
    case 'd':
        return P_d;
    case 'e':
        return P_e;
    case 'f':
        return P_f;
    case 'g':
        return P_g;
    case 'h':
        return P_h;
    case 'i':
        return P_i;
    case 'j':
        return P_j;
    case 'k':
        return P_k;
    case 'l':
        return P_l;
    case 'm':
        return P_m;
    case 'n':
        return P_n;
    case 'o':
        return P_o;
    case 'p':
        return P_p;
    case 'q':
        return P_q;
    case 'r':
        return P_r;
    case 's':
        return P_s;
    case 't':
        return P_t;
    case 'u':
        return P_u;
    case 'v':
        return P_v;
    case 'w':
        return P_w;
    case 'x':
        return P_x;
    case 'y':
        return P_y;
    case 'z':
        return P_z;
    case '0':
        return P_0;
    case '1':
        return P_1;
    case '2':
        return P_2;
    case '3':
        return P_3;
    case '4':
        return P_4;
    case '5':
        return P_5;
    case '6':
        return P_6;
    case '7':
        return P_7;
    case '8':
        return P_8;
    case '9':
        return P_9;
    case '!':
        return P_exclamation;
    case '?':
        return P_question;
    case '/':
        return P_slash;
    case ':':
        return P_colon;
    case '\"':
        return P_quotes;
    case '\'':
        return P_apostrophe;
    case '-':
        return P_dash;
    case '.':
        return P_period;
    case ',':
        return P_coma;
    case '…':
        return P_ellipsis;
    case ';':
        return P_semicolon;
    case ' ':
        return P__;
    default:
        return P__;
    }
}

int Caractere2Tile(char val)
{
    switch(val)
    {
    case '_':
        return 1;
    case '~':
        return 4;
    case 'M':
        return 109;
    case '*':
        return 14+16*8;
    case ' ':
        return 0;
    default:
        return 0;
    }
}
