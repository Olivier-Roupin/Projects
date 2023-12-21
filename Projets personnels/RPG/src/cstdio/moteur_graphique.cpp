#include "moteur_graphique.h"
#include <cstdio> //printf
#include <conio.h> //system("cls")
#include <Windows.h> //Sleep
#include <macros.h> //MIN, MAX
#include <ctime> //clock, CLOCKS_PER_SEC
#include <fichierES.h> //fichier_lire

#define TAILLE_BASIQUE 8
#define LARGEUR_ECRAN LARGEUR_FENETRE // 32
#define HAUTEUR_ECRAN HAUTEUR_FENETRE // 28
#define TEMPS_IMAGE 20 // 16

#include <fonctions_graphiques.h>
#define HAUTEUR_PAGE 32
#define TAILLE_PAGE (HAUTEUR_PAGE*LARGEUR_PAGE)

char ecran_rect[(LARGEUR_ECRAN+1)*HAUTEUR_ECRAN+1];
int ecran_fondu = 0;
unsigned int frameLimit = 0;

char* textures[NOMBRE_PAGES];
const char* fichiers_pages[NOMBRE_PAGES] = {
    "graphics/page_police.txt",
    "graphics/page_tuiles.txt",
    "graphics/page_sprites.txt",
    "graphics/page_heros.txt",
    "graphics/page_monstres.txt"
};

void allumerEcran(const char *titre) {
    remplirEcran();
    printf("\n");
    for (unsigned char i = 0; i < HAUTEUR_ECRAN; ++i)
        ecran_rect[(LARGEUR_ECRAN+1)*i+LARGEUR_ECRAN] = '\n';
    ecran_rect[(LARGEUR_ECRAN+1)*HAUTEUR_ECRAN] = '\0';
}

void syncEcran(unsigned int &frameLimit) {
    const unsigned int ticks = clock() * 1000 / CLOCKS_PER_SEC;
    if (frameLimit < ticks) {
        frameLimit = clock() * 1000 / CLOCKS_PER_SEC + TEMPS_IMAGE;
        return;
    }
    if (frameLimit > ticks + TEMPS_IMAGE)
        Sleep(TEMPS_IMAGE);
    else
        Sleep(frameLimit - ticks);
    frameLimit = clock() * 1000 / CLOCKS_PER_SEC + TEMPS_IMAGE;
    //Sleep(TEMPS_IMAGE);
}

char* ChargerImage(const char* fichier) {
    char buf[TAILLE_PAGE*2]; // prévoir large (commentaires, sauts de ligne)
    if (fichier_lire(fichier, buf) == 0)
        return 0;
    char* texture = new char[TAILLE_PAGE+1];
    unsigned int i, j = 0;
    for (i = 0; i < TAILLE_PAGE*2; ++i) {
        if (buf[i] == '\n' || buf[i] == '\r')
            continue;
        if (buf[i] == '\0' || j == TAILLE_PAGE)
            break;
        if (buf[i] >= ' ' && buf[i] <= '~')
            texture[j] = buf[i];
        else
            texture[j] = '?';
        ++j;
    }
    texture[j+1] = '\0'; //utile pour débuggage
    return texture;
}

bool ChargerPage(unsigned char page) {
    return (textures[page] = ChargerImage(fichiers_pages[page])) != 0;
}

bool actif_fondu = false;

void setCouleurEcran(unsigned char r, unsigned char v, unsigned char b,
                     unsigned char a) {
    actif_fondu = a != 0xFF;
    return;
}

void effacerEcran() {
    remplirEcran();
}

const char* char_fondu = ".oO0";

void remplirEcran(char c) {
    for (unsigned char i = 0; i < HAUTEUR_ECRAN; ++i) {
        for (unsigned char j = 0; j < LARGEUR_ECRAN; ++j)
            ecran_rect[(LARGEUR_ECRAN+1)*i+j] = c;
        // ecran_rect[(LARGEUR_ECRAN+1)*i+LARGEUR_ECRAN] = '\n';
    }
    // ecran_rect[(LARGEUR_ECRAN+1)*HAUTEUR_ECRAN] = '\0';
}

/*#define RATIO_TEMPOREL 8
unsigned char delai = 0;

void afficherEcran() {
    if (delai) {
        --delai;
        return;
    }
    system("cls"); //efface l'écran
    if (actif_fondu)
        remplirEcran(char_fondu[ecran_fondu/64]);
    printf(ecran_rect);
    delai += RATIO_TEMPOREL;
}*/

char ecran_buffer[(LARGEUR_ECRAN+1)*HAUTEUR_ECRAN+1];

void afficherEcran() {
    if (actif_fondu)
        remplirEcran(char_fondu[ecran_fondu/64]);
    for (unsigned int i = 0; i < (LARGEUR_ECRAN+1)*HAUTEUR_ECRAN+1; ++i) {
        if (ecran_buffer[i] != ecran_rect[i]) {
            system("cls");
            printf(ecran_rect);
            for (unsigned int j = i; j < (LARGEUR_ECRAN+1)*HAUTEUR_ECRAN+1; ++j)
                ecran_buffer[j] = ecran_rect[j];
            return;
        }
    }
}

void remplirEcran() {
    for (unsigned char i = 0; i < HAUTEUR_ECRAN; ++i) {
        for (unsigned char j = 0; j < LARGEUR_ECRAN; ++j)
            ecran_rect[(LARGEUR_ECRAN+1)*i+j] = '_';
        // ecran_rect[(LARGEUR_ECRAN+1)*i+LARGEUR_ECRAN] = '\n';
    }
    // ecran_rect[(LARGEUR_ECRAN+1)*HAUTEUR_ECRAN] = '\0';
}

bool changePleinEcran(bool vrai_ratio) {
    return false;
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
    return AfficherTexture(page, x, y, u, v, w, h);
} //p,x,y,u,v,w,h,fw,fh

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h) {
    // SDL_Texture* texture = textures[page];
    // SDL_Rect    position = {x,y,w,h};
    // SDL_Rect    source   = {u,v,w,h};
    // SDL_RenderCopy(renderer, texture, &source, &position);
    // return 1;
    return AfficherTexture(page, x, y, 0, 0, u/TAILLE_BASIQUE+(v/TAILLE_BASIQUE)*LARGEUR_PAGE, w/TAILLE_BASIQUE, h/TAILLE_BASIQUE);
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
    // return AfficherTexture(page,
    //         TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
    //         // (e%TAILLE_PAGE) % LARGEUR_PAGE, (e%TAILLE_PAGE) / LARGEUR_PAGE,
    //         TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE),
    //         TAILLE_BASIQUE*m,                TAILLE_BASIQUE*n);
    return AfficherTexture(page, i+x/TAILLE_BASIQUE, j+y/TAILLE_BASIQUE, e, m, n);
} //p,x,y,i,j,e,m,n

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n,
                                        bool fw, bool fh) {
    // return AfficherTexture(page,
    //         TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
    //         // (e%TAILLE_PAGE) % LARGEUR_PAGE, (e%TAILLE_PAGE) / LARGEUR_PAGE,
    //         TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE),
    //         TAILLE_BASIQUE*m,                TAILLE_BASIQUE*n, fw, fh);
    return AfficherTexture(page, i+x/TAILLE_BASIQUE, j+y/TAILLE_BASIQUE, e, m, n);
} //p,x,y,i,j,e,m,n,fw,fh

int AfficherTexture(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n) {
    // return AfficherTexture(page, 0, 0, i, j, e, m, n);
    for (unsigned int k = 0; k < m; ++k)
        for (unsigned int l = 0; l < n; ++l)
            AfficherElement(page, i+k, j+l , e+k+l*LARGEUR_PAGE);
    return 1;
} //p,i,j,e,m,n

int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    // return AfficherTexture(page, x, y, i, j, e, 1, 1);
    return AfficherElement(page, i+x/TAILLE_BASIQUE, j+y/TAILLE_BASIQUE, e);
} //p,x,y,i,j,e

int AfficherElement(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    // Transparence ?
    if (i < LARGEUR_ECRAN && j < HAUTEUR_ECRAN)
        if ((page != PAGE_TUILES && page != PAGE_SPRITES) || textures[page][e] != ' ')
            ecran_rect[(LARGEUR_ECRAN+1)*j+i] = textures[page][e];
    return 1;
    // return AfficherTexture(page, 0, 0, i, j, e, 1, 1);
} //p,i,j,e

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                         unsigned int  i, unsigned int  j,
                                         unsigned int  e) {
    // return AfficherTexture(page, x, y, i, j, e, 1, 1);
    return AfficherElementL(page, i+x/TAILLE_BASIQUE, j+y/TAILLE_BASIQUE, e);
} //p,x,y,i,j,e

int AfficherElementL(unsigned char page, unsigned int  i, unsigned int  j,
                                         unsigned int  e) {
    // Transparence ?
    if (i < LARGEUR_ECRAN && j < HAUTEUR_ECRAN) {
        if ((page != PAGE_TUILES && page != PAGE_SPRITES) || textures[page][e] != ' ')
            ecran_rect[(LARGEUR_ECRAN+1)*j+i] = textures[page][e];
        if ((page != PAGE_TUILES && page != PAGE_SPRITES) || textures[page][e+1] != ' ')
            ecran_rect[(LARGEUR_ECRAN+1)*j+i+1] = textures[page][e+1];
        if ((page != PAGE_TUILES && page != PAGE_SPRITES) || textures[page][e+LARGEUR_PAGE] != ' ')
            ecran_rect[(LARGEUR_ECRAN+1)*(j+1)+i] = textures[page][e+LARGEUR_PAGE];
        if ((page != PAGE_TUILES && page != PAGE_SPRITES) || textures[page][e+1+LARGEUR_PAGE] != ' ')
            ecran_rect[(LARGEUR_ECRAN+1)*(j+1)+i+1] = textures[page][e+1+LARGEUR_PAGE];
    }
    return 1;
    // return AfficherTexture(page, 0, 0, i, j, e, 1, 1);
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

int AfficherCaractere(         char c,  char couleur,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, Caractere2Element(c, couleur));
}
                                                   
int AfficherCaractere(         char c,  char couleur,
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

int AfficherTexte(  const char* t,  char couleur,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    unsigned int l = 0;
    while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
        AfficherCaractere(t[l], couleur, x, y, i+l, j);
        ++l;
    }
    return l;
}

int AfficherTexte(  const char* t,  char couleur,
                  unsigned int  i, unsigned int  j) {
    return AfficherTexte(t, couleur, 0, 0, i, j);
}

void AfficherCadre(int x, int y, int* w, int* h) {
    int i, j;
    if (*w < 0)
        *w = LARGEUR_ECRAN-x+*w;
    if (*h < 0)
        *h = HAUTEUR_ECRAN-y+*h;
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