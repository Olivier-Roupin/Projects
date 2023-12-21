#include "conversions.h"

unsigned int EntierDroite(unsigned int i, char* s, unsigned int taille) {
    unsigned int j = 10;
    unsigned int k = 0, n = 1;
    while (i >= j) {
        j *= 10;
        ++n;
    }
    if (n >= taille) { //unsigned int trop grand pour le char*
        s[0] = '\0';
        return 0;
    }
    for (; k < taille-1-n; ++k)
        s[k] = '_';
    for (; k < taille-1;   ++k) {
        j /= 10;
        s[k] = '0' + i/j;
        i %= j;
    }
    s[taille-1] = '\0';
    return n;
}

unsigned int EntierDroite(int i, char* s, unsigned int taille) {
    int j = 10;
    unsigned int k = 0, n = 1;
    if (i < 0) {
        i = -i;
        s[0] = '-';
        ++k;
        // ++n; //à tester ?
        // EntierDroite((unsigned int)(-i), &(s[1]), taille-1);
    }
    while (i >= j) {
        j *= 10;
        ++n;
    }
    if (n >= taille) { //int trop grand pour le char*
        s[0] = '\0';
        return 0;
    }
    for (; k < taille-1-n; ++k)
        s[k] = '_';
    for (; k < taille-1;   ++k) {
        j /= 10;
        //s[k] = '0' + (i - i%j)/j;
        s[k] = '0' + i/j;
        i %= j;
    }
    s[taille-1] = '\0';
    return n;
}

unsigned int EntierGauche(unsigned int i, char* s, unsigned int taille) {
    unsigned int j = 10;
    unsigned int k = 0, n = 1;
    while (i >= j) {
        j *= 10;
        ++n;
    }
    if (n >= taille) { //unsigned int trop grand pour le char*
        s[0] = '\0';
        return 0;
    }
    for(; k < n; ++k) {
        j /= 10;
        s[k] = '0' + i/j;
        i %= j;
    }
    s[k] = '\0';
    return n;
}

unsigned int EntierGauche(int i, char* s, unsigned int taille) {
    int j = 10;
    unsigned int k = 0, n = 1;
    if (i < 0) {
        i = -i;
        s[0] = '-';
        ++k;
        ++n; //oublié dans l'autre fonction ?
    }
    while (i >= j) {
        j *= 10;
        ++n;
    }
    if (n >= taille) { //int trop grand pour le char*
        s[0] = '\0';
        return 0;
    }
    for(; k < n; ++k) {
        j /= 10;
        s[k] = '0' + i/j;
        i %= j;
    }
    s[k] = '\0';
    return n;
}

void Int2Temps(unsigned int i, char* s) {
    s[0] = '0'+ i/36000;
    s[1] = '0'+(i/3600)%10;
    s[2] = ':';
    s[3] = '0'+(i%3600)/600;
    s[4] = '0'+(i%600)/60; // (i%3600)/60%10;
    s[5] = ':';
    s[6] = '0'+(i%60)/10;
    s[7] = '0'+ i%10;
    s[8] = '\0';
}