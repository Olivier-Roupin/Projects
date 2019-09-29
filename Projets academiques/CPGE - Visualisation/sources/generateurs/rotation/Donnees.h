#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <gsl/gsl_blas.h>

typedef struct Donnees Donnees;

struct Donnees
{
    int d; //dimension
    int n; //nombre de points
    double* T; //coordonnées des points
    int a; //nombre d'hyper-arêtes
    double** H; //hyper-arêtes
};

void genunit(int d, double* u);
void proj(int d, double* u, double* v, double* p);
void genunit(int d, gsl_vector* u);
void proj(int d, gsl_vector* u, gsl_vector* v, gsl_vector* p);
Donnees* rotation(Donnees* entree, int k);


#endif // DONNEES_H_INCLUDED
