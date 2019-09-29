#ifndef PERSPECTIVE_H_INCLUDED
#define PERSPECTIVE_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <gsl/gsl_blas.h>

#include "Donnees.h"

Donnees* perspective(Donnees* entree, int k, double* B, int r);

#endif // PERSPECTIVE_H_INCLUDED
