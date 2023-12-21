#include <fonctions_graphiques.h>
#include <moteur_graphique.h>

#define afficherCaractere(c,x,y,i,j) AfficherElement(PAGE_POLICE, x, y, i, j, Caractere2Element(c))
#define afficherCaractere_(c,i,j)    AfficherElement(PAGE_POLICE,       i, j, Caractere2Element(c))

#define MAX_LONGUEUR_TEXTE 64

#define afficherTexte(t,x,y,i,j)\
for (unsigned char l=0; l < MAX_LONGUEUR_TEXTE; ++l)\
{ if ((t)[l]=='\0') break; afficherCaractere((t)[l],x,y,i+l,j);}

#define afficherTexte_(t,i,j)\
for (unsigned char l=0; l < MAX_LONGUEUR_TEXTE; ++l)\
{ if ((t)[l]=='\0') break; afficherCaractere_((t)[l],i+l,j);}

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

#define afficherCurseur(x,y,i,j) AfficherElement(PAGE_POLICE, x, y, i, j, P_arrow)
#define afficherCurseur_(i,j)    AfficherElement(PAGE_POLICE,       i, j, P_arrow)

#define afficherDither(d,x,y,i,j) AfficherElement(PAGE_POLICE,x,y,i,j,MIN(MAX(P_dither_0,P_dither_0+d),P_dither_4))
#define afficherDither_(d,i,j)    AfficherElement(PAGE_POLICE,    i,j,MIN(MAX(P_dither_0,P_dither_0+d),P_dither_4))

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

#define afficherSprite(t,x,y,i,j,fw,fh) AfficherTexture(PAGE_SPRITES,x,y,i,j,Caractere2Sprite((t)[0],(t)[1]),2,2,fw,fh)
#define afficherSprite_(t,x,y,i,j)      AfficherTexture(PAGE_SPRITES,x,y,i,j,Caractere2Sprite((t)[0],(t)[1]),2,2)
#define afficherSprite__(t,i,j)         AfficherTexture(PAGE_SPRITES,0,0,i,j,Caractere2Sprite((t)[0],(t)[1]),2,2)

#define afficherTuile(t,x,y,i,j) AfficherTexture(PAGE_TUILES, x, y, i, j, Caractere2Tuile((t)[0]), 2, 2)
#define afficherTuile_(t,i,j)    AfficherTexture(PAGE_TUILES, 0, 0, i, j, Caractere2Tuile((t)[0]), 2, 2)

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