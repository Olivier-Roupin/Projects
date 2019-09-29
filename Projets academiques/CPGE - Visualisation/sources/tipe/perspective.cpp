#include "perspective.h"

using namespace std;

//on considère l'oeil à l'origine (0,0,...) la distance à l'oeil est donc la norme du vecteur Origine-Point

Donnees* perspective(Donnees* entree, int k, double* B, int r) //B : base orthonormale de l'espace d'arrivée (tableau d*k)
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

    gsl_vector_view ve,vs;
    gsl_vector* vdif;
    double dist;

    int i,j;

    Te = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, k);
    Tb = gsl_matrix_view_array(B, k, d);

    vdif = gsl_vector_calloc(d);

    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, &Te.matrix, &Tb.matrix, 0.0, &Ts.matrix);// Ts = Te*tTb

    for(i = 0; i < n; i++)
    {
        ve = gsl_matrix_row(&Te.matrix,i);
        vs = gsl_matrix_row(&Ts.matrix,i);

        for(j = 0; j < k; j++)
        {
            gsl_vector_set(vdif,j,gsl_vector_get(&vs.vector,j));
        }
        for(j = k; j < d; j++)
        {
            gsl_vector_set(vdif,j,0);
        }
        gsl_vector_sub(vdif, &ve.vector);
        dist = gsl_blas_dnrm2(vdif);

        gsl_vector_scale(&vs.vector, r/(r+dist));
    }
    return sortie;
}
