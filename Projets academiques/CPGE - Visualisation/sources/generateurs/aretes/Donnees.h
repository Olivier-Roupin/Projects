#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

typedef struct Donnees Donnees;

struct Donnees
{
    int d; //dimension
    int n; //nombre de points
    double* T; //coordonnées des points
    int a; //nombre d'hyper-arêtes
    double** H; //hyper-arêtes
};

Donnees* aretes(Donnees* entree);


#endif // DONNEES_H_INCLUDED
