#ifndef FJLT_H_INCLUDED
#define FJLT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_sf_pow_int.h>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_blas.h>

#include "Donnees.h"

#define p 2 //Norme 2 (ou 1 si p=1)

Donnees* fjlt(Donnees* entree, int k, double e);

int distortion(Donnees* entree, Donnees* sortie, double e);

#endif // FJLT_H_INCLUDED
