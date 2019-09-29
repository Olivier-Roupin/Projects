#ifndef PERSPECTIVE_H_INCLUDED
#define PERSPECTIVE_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <gsl/gsl_blas.h>

#include "Donnees.h"

double* perspectived(Donnees* entree, int k, gsl_matrix* Tb, double r);
double* selected(Donnees* entree, int k, gsl_matrix* Tb);
gsl_matrix* selected(Donnees* entree, int k, gsl_matrix* Tb, Labyrinthe* lab, int axe, int indice, int taille);
int selected(Donnees* entree, int k, gsl_matrix* Tb, Labyrinthe* lab, int axe, int indice, int taille, Donnees* sortie);


#endif // PERSPECTIVE_H_INCLUDED
