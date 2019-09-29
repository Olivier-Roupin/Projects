#include "ElementGraphique.h"

using namespace std;

ElementGraphique::ElementGraphique(SDL_Texture* Texture, int x_source, int y_source)
{
    m_Position = new SDL_Rect();
    m_Source = new SDL_Rect();
    SetTexture(Texture);
    SetPosition(0, 0);
    SetSource(x_source, y_source);
    SetTaille(TAILLE_BASIQUE, TAILLE_BASIQUE);
}

ElementGraphique::ElementGraphique(const ElementGraphique& cible)
{
    m_Position = new SDL_Rect();
    m_Source = new SDL_Rect();
    m_Texture = cible.GetTexture();
    SetPosition(cible.GetPosition()->x, cible.GetPosition()->y);
    SetSource(cible.GetSource()->x, cible.GetSource()->y);
    SetTaille(cible.GetPosition()->w, cible.GetPosition()->h);
}

ElementGraphique::~ElementGraphique()
{
    //dtor
}

SDL_Rect* ElementGraphique::GetPosition() const
{
    return m_Position;
}

void ElementGraphique::SetPosition(SDL_Rect* val)
{
    m_Position = val;
}

void ElementGraphique::SetPosition(int x, int y)
{
    SetPositionx(x);
    SetPositiony(y);
}

void ElementGraphique::SetPositionx(int val)
{
    m_Position->x = val;
}

void ElementGraphique::SetPositiony(int val)
{
    m_Position->y = val;
}

SDL_Rect* ElementGraphique::GetSource() const
{
    return m_Source;
}

void ElementGraphique::SetSource(SDL_Rect* val)
{
    m_Source = val;
}

void ElementGraphique::SetSource(int x, int y)
{
    SetSourcex(x);
    SetSourcey(y);
}

void ElementGraphique::SetSourcex(int val)
{
    m_Source->x = TAILLE_BASIQUE*val;
}

void ElementGraphique::SetSourcey(int val)
{
    m_Source->y = TAILLE_BASIQUE*val;
}

SDL_Texture* ElementGraphique::GetTexture() const
{
    return m_Texture;
}

void ElementGraphique::SetTexture(SDL_Texture* val)
{
    m_Texture = val;
}

void ElementGraphique::SetTaille(int largeur, int hauteur)
{
    Setlargeur(largeur);
    Sethauteur(hauteur);
}

void ElementGraphique::Setlargeur(int val)
{
    m_Position->w = val;
    m_Source->w = val;
}

void ElementGraphique::Sethauteur(int val)
{
    m_Position->h = val;
    m_Source->h = val;
}

void ElementGraphique::Afficher(int x, int y, int j, int i)
{
    SetPosition(x + TAILLE_BASIQUE*j, y + TAILLE_BASIQUE*i);
    SDL_RenderCopy(renderer, GetTexture(), GetSource(), GetPosition());
    SetPosition(0, 0); // pas nécessaire ?
}
