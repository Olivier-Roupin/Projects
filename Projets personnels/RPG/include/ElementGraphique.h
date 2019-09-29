#ifndef ELEMENTGRAPHIQUE_H
#define ELEMENTGRAPHIQUE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TAILLE_BASIQUE 8

extern SDL_Renderer* renderer;

class ElementGraphique
{
    public:
        ElementGraphique(SDL_Texture* Texture, int x_source = 0, int y_source = 0);
        ElementGraphique(const ElementGraphique& cible);
        virtual ~ElementGraphique();
        SDL_Rect* GetSource() const;
        void SetSource(SDL_Rect* val);
        void SetSource(int x, int y);
        void SetSourcex(int val);
        void SetSourcey(int val);
        SDL_Texture* GetTexture() const;
        void SetTexture(SDL_Texture* val);
        void Afficher(int x, int y, int j = 0, int i = 0);
    protected:
    private:
        SDL_Rect* GetPosition() const;
        void SetPosition(SDL_Rect* val);
        void SetPosition(int x, int y);
        void SetPositionx(int val);
        void SetPositiony(int val);
        void SetTaille(int largeur, int hauteur);
        void Setlargeur(int val);
        void Sethauteur(int val);

        SDL_Rect* m_Position;
        SDL_Rect* m_Source;
        SDL_Texture* m_Texture;
};

#endif // ELEMENTGRAPHIQUE_H
