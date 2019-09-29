#ifndef BOITETEXTE_H
#define BOITETEXTE_H

#include <string>
#include <ElementGraphique.h>

#include <POLICE.h>

class BoiteTexte
{
    public:
        BoiteTexte(char* texte, int X, int Y, int L, int H);
        virtual ~BoiteTexte();
        char* GetTexte() const;
        void SetTexte(char* val);
        SDL_Texture* GetTexture() const;
        void SetTexture(SDL_Texture* val);
        ElementGraphique* GetLettres(int id) const;
        void SetLettres(ElementGraphique* val, int id);
        ElementGraphique* GetFenetre(int id) const;
        void SetFenetre(ElementGraphique* val, int id);
        int GetL() const;
        void SetL(int val);
        int GetH() const;
        void SetH(int val);
        void Afficher();
    protected:
    private:
        char* m_Texte;
        SDL_Texture* m_Texture;
        ElementGraphique** m_Lettres;
        ElementGraphique** m_Fenetre;
        int m_L;
        int m_H;
};

SDL_Rect* Caractere2Rect(char val);
SDL_Rect* Int2Rect(int val);

#endif // BOITETEXTE_H
