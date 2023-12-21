#include "moteur_graphique.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstdio> //printf
#include <macros.h> //MIN, MAX
#include <ctime>   // clock, CLOCKS_PER_SEC

#define TAILLE_BASIQUE 8
#define LARGEUR_ECRAN (LARGEUR_FENETRE*TAILLE_BASIQUE) // 256 // 320//
#define HAUTEUR_ECRAN (HAUTEUR_FENETRE*TAILLE_BASIQUE) // 224 // 256//
#define TEMPS_IMAGE 16 // 20

#include <fonctions_graphiques.h>
// #define LARGEUR_PAGE 32
#define TAILLE_PAGE (32*LARGEUR_PAGE)

SDL_Surface *ecran;

SDL_Rect ecran_rect;
int ecran_fondu = 0;
unsigned int frameLimit = 0;

SDL_Surface* textures[NOMBRE_PAGES];
const char* fichiers_pages[NOMBRE_PAGES] = {
    "graphics/page_police.png", //256.gif
    "graphics/page_tuiles.png",
    "graphics/page_sprites.png",
    "graphics/page_heros.png",
    "graphics/page_monstres.png"
};

#define SDL_SURFACE_MODE SDL_SWSURFACE // SDL_HWSURFACE // CPU vs GPU

void allumerEcran(const char *titre) {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Can't init SDL:  %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    ecran_rect.x = ecran_rect.y = 0;
    ecran_rect.w = LARGEUR_ECRAN;
    ecran_rect.h = HAUTEUR_ECRAN;

    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_SURFACE_MODE | SDL_DOUBLEBUF);
    if (ecran == 0) {
        printf("Can't set video mode: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_WM_SetCaption(titre, 0); //nom, icone
    // SDL_EnableUNICODE(1); //azerty?
}

void syncEcran(unsigned int &frameLimit) {
    const unsigned int ticks = SDL_GetTicks();
    if (frameLimit < ticks) {
        frameLimit = SDL_GetTicks() + TEMPS_IMAGE; //déplacé dans la fonction
        return;
    }
    if (frameLimit > ticks + TEMPS_IMAGE)
        SDL_Delay(TEMPS_IMAGE);
    else
        SDL_Delay(frameLimit - ticks);
    frameLimit = SDL_GetTicks() + TEMPS_IMAGE; //déplacé dans la fonction
}

SDL_Surface* ChargerImage(const char* fichier) {
	SDL_Surface* loadedImage = 0;
	SDL_Surface* optimizedImage = 0;
	loadedImage = IMG_Load(fichier);
	if (loadedImage) { 
		optimizedImage = SDL_DisplayFormat(loadedImage); 
		SDL_FreeSurface(loadedImage); 
	}
	return optimizedImage; 
}

SDL_Surface* ChargerImage(const char* fichier,
    unsigned char r, unsigned char v, unsigned char b) {
	SDL_Surface* loadedImage = 0;
	SDL_Surface* optimizedImage = 0;
	loadedImage = IMG_Load(fichier);
	if (loadedImage) { 
		optimizedImage = SDL_DisplayFormat(loadedImage); 
        SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY,
            SDL_MapRGB(optimizedImage->format, r, v, b));
		SDL_FreeSurface(loadedImage); 
	}
	return optimizedImage; 
}

bool ChargerPage(unsigned char page) {
    return (textures[page] = ChargerImage(fichiers_pages[page],
                                          0x00, 0xFF, 0x00)) != 0;
}

unsigned int couleur_ecran = 0;
unsigned int couleur_fondu = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN //inversé
    #define SDL_RMASK 0xff000000
    #define SDL_GMASK 0x00ff0000
    #define SDL_BMASK 0x0000ff00
    #define SDL_AMASK 0x000000ff
#else
    #define SDL_RMASK 0x000000ff
    #define SDL_GMASK 0x0000ff00
    #define SDL_BMASK 0x00ff0000
    #define SDL_AMASK 0xff000000
#endif

SDL_Surface* fondu = SDL_CreateRGBSurface(SDL_SURFACE_MODE,
    LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_RMASK, SDL_GMASK, SDL_BMASK, SDL_AMASK);

void setCouleurEcran(unsigned char r, unsigned char v, unsigned char b,
                     unsigned char a) {
    couleur_ecran = SDL_MapRGBA(ecran->format, r, v, b, a);
    couleur_fondu = SDL_MapRGBA(fondu->format, r, v, b, a);
}

void effacerEcran() {
    SDL_FillRect(ecran, &ecran_rect, couleur_ecran);
}

void afficherEcran() {
    SDL_Flip(ecran);
	// if (SDL_Flip(ecran) == -1)
	// 	exit(1);
}

void remplirEcran() {
    SDL_FillRect(fondu, &ecran_rect, couleur_fondu);
	SDL_BlitSurface(fondu, &ecran_rect, ecran, &ecran_rect);
}

bool changePleinEcran(bool vrai_ratio) {
    // SDL_WM_ToggleFullScreen(ecran);
    // return ecran->flags & SDL_FULLSCREEN;
    SDL_Surface* actuel = ecran;
    SDL_Rect** modes = SDL_ListModes(0, SDL_FULLSCREEN|SDL_HWSURFACE);
    if (modes == (SDL_Rect**)0) {
        printf("No modes available!\n");
        exit(-1);
    }
    bool actif = actuel->flags & SDL_FULLSCREEN;
    if (actif) {
        ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_SURFACE_MODE | SDL_DOUBLEBUF);
        SDL_ShowCursor(SDL_ENABLE);
    } else {
        ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_SURFACE_MODE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
        SDL_ShowCursor(SDL_DISABLE);
    }
    SDL_FreeSurface(actuel);
    effacerEcran();
    return !actif;
}

int premierElementListe(int id, int hauteur, int nombre) {
    if (id < hauteur/2 || nombre < hauteur)
        return 0;
    if (id > nombre - (hauteur+1)/2 - 1)
        return nombre - hauteur-1;
    return id - hauteur/2;
}

unsigned int horloge() {
    return clock()/CLOCKS_PER_SEC;
}

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h,
                                        bool fw, bool fh) {
    SDL_Surface* texture = textures[page];
    SDL_Rect    position = {(short int)x,(short int)y,w,h};
    SDL_Rect    source   = {u,v,w,h};
	SDL_BlitSurface(texture, &source, ecran, &position);
    return 1;
} //p,x,y,u,v,w,h,fw,fh

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h) {
    SDL_Surface* texture = textures[page];
    SDL_Rect    position = {(short int)x,(short int)y,w,h};
    SDL_Rect    source   = {u,v,w,h};
	SDL_BlitSurface(texture, &source, ecran, &position);
    return 1;
} //p,x,y,u,v,w,h

int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v) {
    return AfficherTexture(page, x, y, u, v, TAILLE_BASIQUE, TAILLE_BASIQUE);
} //p,x,y,u,v

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                         unsigned char u, unsigned char v) {
    return AfficherTexture(page, x, y, u, v, 2*TAILLE_BASIQUE, 2*TAILLE_BASIQUE);
} //p,x,y,u,v

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n) {
    return AfficherTexture(page,
            TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
            // (e%TAILLE_PAGE) % LARGEUR_PAGE, (e%TAILLE_PAGE) / LARGEUR_PAGE,
            TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE),
            TAILLE_BASIQUE*m,                TAILLE_BASIQUE*n);
} //p,x,y,i,j,e,m,n

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n,
                                        bool fw, bool fh) {
    return AfficherTexture(page,
            TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
            // (e%TAILLE_PAGE) % LARGEUR_PAGE, (e%TAILLE_PAGE) / LARGEUR_PAGE,
            TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE),
            TAILLE_BASIQUE*m,                TAILLE_BASIQUE*n, fw, fh);
} //p,x,y,i,j,e,m,n,fw,fh

int AfficherTexture(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n) {
    return AfficherTexture(page, 0, 0, i, j, e, m, n);
} //p,i,j,e,m,n

int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    return AfficherTexture(page, x, y, i, j, e, 1, 1);
} //p,x,y,i,j,e

int AfficherElement(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    return AfficherElement(page, 0, 0, i, j, e);
    // return AfficherTexture(page, 0, 0, i, j, e, 1, 1);
} //p,i,j,e

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    return AfficherTexture(page, x, y, i, j, e, 2, 2);
} //p,x,y,i,j,e

int AfficherElementL(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    return AfficherElementL(page, 0, 0, i, j, e);
    // return AfficherTexture(page, 0, 0, i, j, e, 2, 2);
} //p,i,j,e

int AfficherCaractere(         char c,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, Caractere2Element(c));
}
                                                   
int AfficherCaractere(         char c,
                      unsigned int  i, unsigned int  j) {
    // return AfficherCaractere(c, 0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j, Caractere2Element(c));
}

int AfficherCaractere(         char c, char couleur,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, Caractere2Element(c, couleur));
}
                                                   
int AfficherCaractere(         char c, char couleur,
                      unsigned int  i, unsigned int  j) {
    // return AfficherCaractere(c, 0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j, Caractere2Element(c, couleur));
}

#define MAX_LONGUEUR_TEXTE 64

int AfficherTexte(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    unsigned int l = 0;
    while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
        AfficherCaractere(t[l], x, y, i+l, j);
        ++l;
    }
    return l;
}

int AfficherTexte(  const char* t,
                  unsigned int  i, unsigned int  j) {
    return AfficherTexte(t, 0, 0, i, j);
    // unsigned int l = 0;
    // while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
    //     AfficherCaractere(t[l], i+l, j);
    //     ++l;
    // }
    // return l;
}

int AfficherTexte(  const char* t, char couleur,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    unsigned int l = 0;
    while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
        AfficherCaractere(t[l], couleur, x, y, i+l, j);
        ++l;
    }
    return l;
}

int AfficherTexte(  const char* t, char couleur,
                  unsigned int  i, unsigned int  j) {
    return AfficherTexte(t, couleur, 0, 0, i, j);
}

void AfficherCadre(int x, int y, int* w, int* h) {
    int i, j;
    if (*w < 0)
        *w = LARGEUR_ECRAN/TAILLE_BASIQUE-x+*w;
    if (*h < 0)
        *h = HAUTEUR_ECRAN/TAILLE_BASIQUE-y+*h;
    for (i = 0; i < *h; ++i)
        for (j = 0; j < *w; ++j)
            AfficherElement(PAGE_POLICE, x+j, y+i, P_blank);
    for (i = 0; i < *h; ++i) {
        AfficherElement(PAGE_POLICE, x- 1, y+i, P_left);
        AfficherElement(PAGE_POLICE, x+*w, y+i, P_right);
    }
    for (j = 0; j < *w; ++j) {
        AfficherElement(PAGE_POLICE, x+j, y- 1, P_top);
        AfficherElement(PAGE_POLICE, x+j, y+*h, P_bottom);
    }
    AfficherElement(PAGE_POLICE, x- 1, y- 1, P_top_left);
    AfficherElement(PAGE_POLICE, x+*w, y- 1, P_top_right);
    AfficherElement(PAGE_POLICE, x- 1, y+*h, P_bottom_left);
    AfficherElement(PAGE_POLICE, x+*w, y+*h, P_bottom_right);
}

void AfficherCadre(int x, int y, int w, int h) {
    AfficherCadre(x, y, &w, &h);
}

void AfficherCadre(int x, int y, int* w, int h) {
    AfficherCadre(x, y, w, &h);
}

void AfficherCadre(int x, int y, int w, int* h) {
    AfficherCadre(x, y, &w, h);
}

int AfficherHeros(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j,
                  bool fw, bool fh) {
    if (t[1] < 6) {
        if (fw)
            AfficherElementL(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1])+12*LARGEUR_PAGE);
        else
            AfficherElementL(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]));
        return 2;
    }
    if (t[1] < 12) {
        AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 2, 3, fw, fh);
        return 3;
    }
    AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 3, 2, fw, fh);
    return 3;
}

int AfficherHeros(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    if (t[1] < 6) {
        AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 2, 2);
        return 2;
    }
    if (t[1] < 12) {
        AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 2, 3);
        return 3;
    }
    AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 3, 2);
    return 3;
}

int AfficherHeros(  const char* t,
                  unsigned int  i, unsigned int  j) {
    return AfficherHeros(t, 0, 0, i, j);
}

int AfficherCurseur(         int  x,          int  y,
                    unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, P_arrow);
}

int AfficherCurseur(unsigned int  i, unsigned int  j) {
    // return AfficherCurseur(0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j, P_arrow);
}

int AfficherDither(         char d,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j,
        MIN(MAX(P_dither_0,P_dither_0+d),P_dither_4));
}

int AfficherDither(         char d,
                   unsigned int  i, unsigned int  j) {
    // return AfficherDither(0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j,
        MIN(MAX(P_dither_0,P_dither_0+d),P_dither_4));
}

int AfficherDithers(         char d,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j,  //*TAILLE_BASIQUE
                    unsigned char m, unsigned char n) {
    for (unsigned char k = 0; k < m; ++k)
        for (unsigned char l = 0; l < n; ++l)
            if (k+(n-1-l)+d >= 0)
                AfficherDither(k+(n-1-l)+d, x, y, i+k, j+l);
    
    return m;
}

int AfficherDithers(         char d,
                    unsigned int  i, unsigned int  j,  //*TAILLE_BASIQUE
                    unsigned char m, unsigned char n) {
    for (unsigned char k = 0; k < m; ++k)
        for (unsigned char l = 0; l < n; ++l)
            if (k+(n-1-l)+d >= 0)
                AfficherDither(k+(n-1-l)+d, i+k, j+l);
    return m;
}

int AfficherSprite(  const char* t,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j,
                   bool fw, bool fh) {
    // AfficherTexture(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]), 2, 2, fw, fh);
    if (fw)
        AfficherElementL(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1])+12*LARGEUR_PAGE);
    else
        AfficherElementL(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]));
    return 2;
}

int AfficherSprite(  const char* t,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j) {
    AfficherTexture(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]), 2, 2);
    return 2;
}

int AfficherSprite(  const char* t,
                   unsigned int  i, unsigned int  j) {
    return AfficherSprite(t, 0, 0, i, j);
}

int AfficherTuile(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    AfficherTexture(PAGE_TUILES, x, y, i, j, Caractere2Tuile(t[0]), 2, 2);
    return 2;
}

int AfficherTuile(  const char* t,
                  unsigned int  i, unsigned int  j) {
    return AfficherTuile(t, 0, 0, i, j);
}

int AfficherMonstre(  const char* t,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j,
                    bool fw, bool fh) {
    if (t[0] < 3) {
        AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 4, fw, fh);
        return 4;
    }
    AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 6, fw, fh);
    return 6;
}

int AfficherMonstre(  const char* t,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j) {
    if (t[0] < 3) {
        AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 4);
        return 4;
    }
    AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 6);
    return 6;
}

int AfficherMonstre(  const char* t,
                    unsigned int  i, unsigned int  j) {
    return AfficherMonstre(t, 0, 0, i, j);
}
