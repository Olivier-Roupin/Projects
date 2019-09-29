#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_pow_int.h>

typedef struct Donnees Donnees;

struct Donnees
{
    int d; //dimension
    int n; //nombre de points
    double* T; //coordonnées des points
    int a; //nombre d'hyper-arêtes
    double** H; //hyper-arêtes
};

void proj(int d, double* u, double* v, double* p);
void genunit(int d, gsl_vector* u);
void proj(int d, gsl_vector* u, gsl_vector* v, gsl_vector* p);
double* genbase(int d, int k);

double degres2rad(int val);

double* vecteur_nul(int d);

gsl_matrix* Angles2Matrix(double* angles, int d);
int Angles2Matrix(double* angles, int d, gsl_matrix* Mangles);
double* Matrix2Angles(gsl_matrix* M, int d);
int Matrix2Angles(gsl_matrix* M, int d, double* angles);

Donnees* rotation(Donnees* entree, double* angles);
Donnees* rotation(Donnees* entree, gsl_matrix* Mangles);
Donnees* translation(Donnees* entree);
Donnees* homothetie(Donnees* entree, double r);

void print_mat(gsl_matrix* M);

#endif // DONNEES_H_INCLUDED
