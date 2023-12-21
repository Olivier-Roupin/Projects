#include "fonctions_graphiques.h"

#include <bdd/POLICE.h>

#define POLICE_BLANC  0
#define POLICE_GRIS  (5*LARGEUR_PAGE)
#define POLICE_VERT  (6*LARGEUR_PAGE)
#define POLICE_ROUGE (7*LARGEUR_PAGE)

/*int premierElementListe(int id, int hauteur, int nombre) {
    if (id < hauteur/2 || nombre < hauteur)
        return 0;
    if (id > nombre - (hauteur+1)/2 - 1)
        return nombre - hauteur-1;
    return id - hauteur/2;
}*/

// '\0' == 0
int Caractere2Element(char val) {
    switch (val) {
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
        // case '…':
        //    return P_ellipsis;
        case ';':
            return P_semicolon;
        case '#':
            return P_hash;
        case '+':
            return P_plus;
        case '(':
            return P_open;
        case ')':
            return P_close;
        case '%':
            return P_percent;
        case '~':
            return P_tilde;
        case '*':
            return P_times;
        case ' ':
        case '_':
            return P__;
        default:
            return P__;
    }
}

int Caractere2Element(char val, char couleur) {
    if (val == '_' || val == ' ')
        return P__;
    switch (couleur) {
        default:
        case COULEUR_BLANC:
            return Caractere2Element(val)+POLICE_BLANC;
        case COULEUR_GRIS:
            return Caractere2Element(val)+POLICE_GRIS;
        case COULEUR_VERT:
            return Caractere2Element(val)+POLICE_VERT;
        case COULEUR_ROUGE:
            return Caractere2Element(val)+POLICE_ROUGE;
    }
}

int Caractere2Tuile(char val) {
    switch (val) {
        case '_': // herbe
            return  2;
        case ',': // gazon
            return  2+ 6*LARGEUR_PAGE;
        case '.': // sol
            return  2+ 8*LARGEUR_PAGE;
        case 'O': // mur
            return 10+ 6*LARGEUR_PAGE;
        case 'A': //porte
            return  4+ 6*LARGEUR_PAGE;
        case 'a': //porte ouverte
            return 22+ 6*LARGEUR_PAGE;
        case 'B': //porte maison
            return  4+ 8*LARGEUR_PAGE;
        case 'b': //porte maison ouverte
            return 22+ 8*LARGEUR_PAGE;
        case 'H': //barrière
            return 20+ 6*LARGEUR_PAGE;
        case 'P': // mur maison
            return  6+ 6*LARGEUR_PAGE;
        case 'p': // mur intérieur
            return  6+ 8*LARGEUR_PAGE;
        case '~': // eau
            return 12;
        case 'M': // montagnes
            return 12+ 4*LARGEUR_PAGE;
        case '*': // foret
            return 12+ 2*LARGEUR_PAGE;
        case '%': // arbres
            return 14+ 6*LARGEUR_PAGE;
        case ' ': // noir
            return 0;
        default:
            return 0;
    }
}

int Caractere2Sprite(char id, char pose) {
    switch (id) {
        case '_':
            return 0;
        case 'A':
            return 2*5;
        case 'H':
            return 2*4;
        case 'v':
            return 2*LARGEUR_PAGE+2*pose;
        case 'b':
            return 4*LARGEUR_PAGE+2*pose;
        case 'e':
            return 6*LARGEUR_PAGE+2*pose;
        case ' ':
            return 0;
        default:
            return 0;
    }
}

int Caractere2Heros(char id, char pose) {
    if (pose < 6)
        return LARGEUR_PAGE+3*LARGEUR_PAGE*(id-1)+2*pose;
    if (pose < 12)
        return 3*LARGEUR_PAGE*(id-1)+2*pose;
    return LARGEUR_PAGE+3*LARGEUR_PAGE*(id-1)+2*pose;
}

int Caractere2Monstre(char id) {
    if (id < 3)
        return 4*(id-1);
    return 4*LARGEUR_PAGE+4*(id-3);
}