#ifndef MAXCUT_H_INCLUDED
#define MAXCUT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <gsl/gsl_blas.h>

#include "Donnees.h"

#define POIDSBASE 0.0
#define POIDSDISTANCE 10.0
#define POIDSSURFACE 10.0
#define POIDSVOLUME 10.0

#define DTHETA 0.01

Donnees* maxcut(Donnees* entree, int k);

double f(int d, int n, double* T, double* W);

double* poids(int n, int a, double** H);

void angles(int d, int k, int n, double* Tv, double* Tu);

#endif // MAXCUT_H_INCLUDED
