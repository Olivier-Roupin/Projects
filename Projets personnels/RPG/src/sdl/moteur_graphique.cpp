#include "moteur_graphique.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio> //printf
#include <macros.h> //MIN, MAX
#include <ctime>   // clock, CLOCKS_PER_SEC
//#include <SDL2/SDL_mixer.h>

#define TAILLE_BASIQUE 8
#define LARGEUR_ECRAN (LARGEUR_FENETRE*TAILLE_BASIQUE) // 256 // 320//
#define HAUTEUR_ECRAN (HAUTEUR_FENETRE*TAILLE_BASIQUE) // 224 // 256//
#define TEMPS_IMAGE 20 // 16

#include <fonctions_graphiques.h>
// #define LARGEUR_PAGE 32
#define TAILLE_PAGE (32*LARGEUR_PAGE)

SDL_Window *ecran;
SDL_Renderer *renderer;
//Mix_Music *music = 0;
//Mix_Music *intro = 0;

SDL_Rect ecran_rect;
int ecran_fondu = 0;
unsigned int frameLimit = 0;

SDL_Texture* textures[NOMBRE_PAGES];
const char* fichiers_pages[NOMBRE_PAGES] = {
    "graphics/page_police.png", //256.gif
    "graphics/page_tuiles.png",
    "graphics/page_sprites.png",
    "graphics/page_heros.png",
    "graphics/page_monstres.png"
};

void allumerEcran(const char *titre) {
    ecran = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, LARGEUR_ECRAN,
                             HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer,LARGEUR_ECRAN,HAUTEUR_ECRAN);

    atexit(SDL_Quit);

    ecran_rect.x = ecran_rect.y = 0;
    ecran_rect.w = LARGEUR_ECRAN;
    ecran_rect.h = HAUTEUR_ECRAN;

    if (ecran == 0 || renderer == 0) {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n",
               LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_GetError());
        exit(1);
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags )) {
        printf("SDL_image n'a pu être initialisée! SDL_image Error: %s\n",
               IMG_GetError());
        exit(1);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //pour les fondus

    /*
    if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL_TTF: %s\n", TTF_GetError());
        exit(1);
    }
    */

    /*int flags = MIX_INIT_MP3;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        printf("Impossible d'initialiser SDL_Mixer: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_AllocateChannels(32);*/
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

SDL_Texture* ChargerImage(const char* fichier) {
    SDL_Surface* image = 0;
    SDL_Texture* texture = 0;
    image = IMG_Load(fichier);
    if (image) {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
        image = 0;
    }
    return texture;
}

SDL_Texture* ChargerImage(const char* fichier,
    unsigned char r, unsigned char v, unsigned char b) {
    SDL_Surface* image = 0;
    SDL_Texture* texture = 0;
    image = IMG_Load(fichier);
    if (image) {
        // if(image->format->BitsPerPixel != 8) {
        //     fprintf(stderr, "Not an 8-bit surface: %d\n", image->format->BitsPerPixel);
        // } else {  
        //     SDL_Color *color;
        //     Uint8 index;
        //     SDL_LockSurface(image);
        //     index = *(Uint8 *)image->pixels; // Get the topleft pixel
        //     color = &image->format->palette->colors[index];
        //     SDL_UnlockSurface(image);
        //     printf("Pixel Color-> Red: %d, Green: %d, Blue: %d. Index: %d\n",
        //             color->r, color->g, color->b, index);
        // }
        SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, r, v, b));
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
        /*Uint32 format;
        SDL_QueryTexture(texture, &format, 0, 0, 0);
        fprintf(stdout, "texture format: %d\n", format);
        printf("SDL_PIXELTYPE %d\nSDL_PIXELORDER %d\nSDL_PIXELLAYOUT %d\nSDL_BITSPERPIXEL %d\nSDL_BYTESPERPIXEL %d\nSDL_ISPIXELFORMAT_INDEXED %d\nSDL_ISPIXELFORMAT_ALPHA %d\nSDL_ISPIXELFORMAT_FOURCC %d\n",
            SDL_PIXELTYPE(format),
            SDL_PIXELORDER(format),
            SDL_PIXELLAYOUT(format),
            SDL_BITSPERPIXEL(format),
            SDL_BYTESPERPIXEL(format),
            SDL_ISPIXELFORMAT_INDEXED(format),
            SDL_ISPIXELFORMAT_ALPHA(format),
            SDL_ISPIXELFORMAT_FOURCC(format));*/
        image = 0;
    }
    return texture;
}

bool ChargerPage(unsigned char page) {
    return (textures[page] = ChargerImage(fichiers_pages[page],
                                          0x00, 0xFF, 0x00)) != 0;
}

void setCouleurEcran(unsigned char r, unsigned char v, unsigned char b,
                     unsigned char a) {
    SDL_SetRenderDrawColor(renderer, r, v, b, a); //couleur du fond
}

void effacerEcran() {
    SDL_RenderClear(renderer);
}

void afficherEcran() {
    SDL_RenderPresent(renderer);
}

void remplirEcran() {
    SDL_RenderFillRect(renderer, &ecran_rect);
}

bool changePleinEcran(bool vrai_ratio) {
    SDL_DisplayMode actuel;
    if (SDL_GetCurrentDisplayMode(0, &actuel))
        SDL_Log("Impossible de lire les infos de l'écran : %s", SDL_GetError());
    bool actif = SDL_GetWindowFlags(ecran) & SDL_WINDOW_FULLSCREEN;
    if (actif) {
        SDL_SetWindowFullscreen(ecran, 0); //avant redimensionnage
        SDL_SetWindowSize(ecran, LARGEUR_ECRAN, HAUTEUR_ECRAN);
        SDL_ShowCursor(SDL_ENABLE);
    } else {
        SDL_SetWindowSize(ecran, vrai_ratio
            ? LARGEUR_ECRAN*actuel.h/HAUTEUR_ECRAN : actuel.w, actuel.h);
        SDL_SetWindowFullscreen(ecran, SDL_WINDOW_FULLSCREEN);
        SDL_ShowCursor(SDL_DISABLE);
    }
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
    SDL_Texture* texture = textures[page];
    SDL_Rect    position = {x,y,w,h};
    SDL_Rect    source   = {u,v,w,h};
    SDL_RendererFlip flip = fw ?
        fh ? (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL) : SDL_FLIP_HORIZONTAL :
        fh ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &source, &position, 0, 0, flip);
    return 1;
} //p,x,y,u,v,w,h,fw,fh

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h) {
    SDL_Texture* texture = textures[page];
    SDL_Rect    position = {x,y,w,h};
    SDL_Rect    source   = {u,v,w,h};
    SDL_RenderCopy(renderer, texture, &source, &position);
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
        AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 2, 2, fw, fh);
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
    AfficherTexture(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]), 2, 2, fw, fh);
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

/*  Mix_HaltMusic();
    if (intro)
        Mix_FreeMusic(intro);
    if (music)
        Mix_FreeMusic(music);
    intro = Mix_LoadMUS("audio/island_0.ogg");
    music = Mix_LoadMUS("audio/island_1.ogg");
    if (music == 0) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_PlayMusic(intro, 1);*/
