#ifndef FONCTIONS_GRAPHIQUES_H_INCLUDED
#define FONCTIONS_GRAPHIQUES_H_INCLUDED

#define LARGEUR_PAGE 32

// int premierElementListe(int id, int hauteur, int nombre);
int Caractere2Element(char val);
int Caractere2Element(char val, char couleur);
int Caractere2Tuile(char val);
int Caractere2Sprite(char id, char pose);
int Caractere2Heros(char id, char pose);
int Caractere2Monstre(char id);

#endif // MOTEUR_GRAPHIQUE_H_INCLUDED