#include "simple.h"

using namespace std;

Donnees* simple(Donnees* entree, int k, double* B) //B : base orthonormale de l'espace d'arrivée (tableau d*k)
{
    int d(entree->d);
    int n(entree->n);
    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = k;
    sortie->n = n;
    sortie->T = new double[sizeof(double)*n*k];
    sortie->a = entree->a;
    sortie->H = entree->H;

    gsl_matrix_view Te,Ts,Tb;

    Te = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, k);
    Tb = gsl_matrix_view_array(B, k, d);

    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, &Te.matrix, &Tb.matrix, 0.0, &Ts.matrix);// Ts = Te*tTb

    return sortie;
}
