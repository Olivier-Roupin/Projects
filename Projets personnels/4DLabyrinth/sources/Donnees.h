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
#include "Labyrinthe.h"

typedef struct Donnees Donnees;

struct Donnees
{
    gsl_matrix* Points; //tableau des points (nombre*dimension)
    int a; //nombre d'hyper-arêtes
    double** H; //hyper-arêtes
};

int parite(int x);
double degres2rad(int val);

int Donnees_free(Donnees* donnees);

gsl_matrix* Angles2Matrix(double* angles, int d);
int Angles2Matrix(double* angles, gsl_matrix* Mangles);
double* Matrix2Angles(gsl_matrix* Mangles);
int Matrix2Angles(gsl_matrix* Mangles, double* angles);
int Reparer(gsl_matrix* Mangles);
int TrouverAxe(gsl_matrix* Mangles, int axe);

Donnees* init_translation_rotation_homothetie(Donnees* entree);

int rotation(Donnees* entree, gsl_matrix* Mangles, Donnees* sortie);
int translation(Donnees* entree, gsl_vector* Vvecteur, Donnees* sortie);
int homothetie(Donnees* entree, double r, Donnees* sortie);

int Labyrinthe2Donnees(Labyrinthe* labyrinthe, Donnees* bloc, Donnees* donnees);

void print_mat(gsl_matrix* M);

#endif // DONNEES_H_INCLUDED
