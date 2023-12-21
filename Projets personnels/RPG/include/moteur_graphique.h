#ifndef MOTEUR_GRAPHIQUE_H_INCLUDED
#define MOTEUR_GRAPHIQUE_H_INCLUDED

#include <bdd/POLICE.h>

#define NOMBRE_PAGES 5
#define PAGE_POLICE   0
#define PAGE_TUILES   1
#define PAGE_SPRITES  2
#define PAGE_HEROS    3
#define PAGE_MONSTRES 4

#define LARGEUR_TUILE 16
// #define LARGEUR_FENETRE 32
// #define HAUTEUR_FENETRE 28
#define LARGEUR_FENETRE 40
#define HAUTEUR_FENETRE 30
// #define HAUTEUR_FENETRE 32

extern int ecran_fondu;
extern unsigned int frameLimit;

void allumerEcran(const char *titre);
void syncEcran(unsigned int &frameLimit);
bool ChargerPage(unsigned char page);

void  setCouleurEcran(unsigned char r, unsigned char v, unsigned char b,
                      unsigned char a = 0xFF);
void     effacerEcran();
void    afficherEcran();
void     remplirEcran();
bool changePleinEcran(bool vrai_ratio);

int premierElementListe(int id, int hauteur, int nombre);

unsigned int horloge();

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h,
                                        bool fw, bool fh);

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h);

int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v);
                                        // TAILLE_BASIQUE, TAILLE_BASIQUE

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                         unsigned char u, unsigned char v);
                                        //2*TAILLE_BASIQUE,2*TAILLE_BASIQUE

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                        unsigned int  e, //0-1023
                                        unsigned char m, unsigned char n); //*TAILLE_BASIQUE

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                        unsigned int  e, //0-1023
                                        unsigned char m, unsigned char n, //*TAILLE_BASIQUE
                                        bool fw, bool fh);

int AfficherTexture(unsigned char page, unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                        unsigned int  e, //0-1023
                                        unsigned char m, unsigned char n); //*TAILLE_BASIQUE

int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                        unsigned int  e); //0-1023
                                        //1*TAILLE_BASIQUE, 1*TAILLE_BASIQUE

int AfficherElement(unsigned char page, unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                        unsigned int  e); //0-1023
                                        //1*TAILLE_BASIQUE, 1*TAILLE_BASIQUE

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                         unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                         unsigned int  e); //0-1023
                                         //2*TAILLE_BASIQUE, 2*TAILLE_BASIQUE

int AfficherElementL(unsigned char page, unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                                         unsigned int  e); //0-1023
                                         //2*TAILLE_BASIQUE, 2*TAILLE_BASIQUE

// Texte
int AfficherCaractere(         char c,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherCaractere(         char c,
                      unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherCaractere(         char c, char couleur,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherCaractere(         char c, char couleur,
                      unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherTexte(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherTexte(  const char* t,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherTexte(  const char* t, char couleur,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherTexte(  const char* t, char couleur,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

#define afficherTexte(t,i,j) AfficherTexte(t,0,0,i,j)

void AfficherCadre(int x, int y, int* w, int* h);
void AfficherCadre(int x, int y, int  w, int  h);
void AfficherCadre(int x, int y, int* w, int  h);
void AfficherCadre(int x, int y, int  w, int* h);

// Heros
int AfficherHeros(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                  bool fw, bool fh);

int AfficherHeros(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherHeros(  const char* t,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

#define afficherHeros(t,i,j) AfficherHeros(t,0,0,i,j)

// Curseur
int AfficherCurseur(         int  x,          int  y,
                    unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherCurseur(unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

// Dither
int AfficherDither(         char d,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherDither(         char d,
                   unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherDithers(         char d,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j,  //*TAILLE_BASIQUE
                    unsigned char m, unsigned char n); //*TAILLE_BASIQUE

int AfficherDithers(         char d,
                    unsigned int  i, unsigned int  j,  //*TAILLE_BASIQUE
                    unsigned char m, unsigned char n); //*TAILLE_BASIQUE

// Sprite
int AfficherSprite(  const char* t,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                   bool fw, bool fh);

int AfficherSprite(  const char* t,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherSprite(  const char* t,
                   unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

#define afficherSprite(t,i,j) AfficherSprite(t,0,0,i,j) 

// Tuile
int AfficherTuile(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

int AfficherTuile(  const char* t,
                  unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

#define afficherTuile(t,i,j) AfficherTuile(t,0,0,i,j)

// Monstre
int AfficherMonstre(  const char* t,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j, //*TAILLE_BASIQUE
                    bool fw, bool fh);

int AfficherMonstre(  const char* t,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

#define afficherMonstre(t,i,j) AfficherMonstre(t,0,0,i,j)

int AfficherMonstre(  const char* t,
                    unsigned int  i, unsigned int  j); //*TAILLE_BASIQUE

#endif // MOTEUR_GRAPHIQUE_H_INCLUDED
