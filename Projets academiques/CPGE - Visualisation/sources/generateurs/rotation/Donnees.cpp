#include "Donnees.h"

using namespace std;

void genunit(int d, double* u)
{
    int i;
    double s = 0.0;

    for(i = 0; i < d; i++)
    {
        u[i] = ((double) rand()) / ((double) RAND_MAX) - 0.5;
        s += u[i]*u[i];
    }
    s = 1.0/sqrt(s);

    for(i = 0; i < d; i++)
    {
        u[i] *= s;
    }
}

void proj(int d, double* u, double* v, double* p)
{
    gsl_vector_view U,V,P;
    double produit,norme;
    U = gsl_vector_view_array(u,d);
    V = gsl_vector_view_array(v,d);
    P = gsl_vector_view_array(p,d);

    gsl_vector_memcpy(&P.vector, &U.vector);
    norme = 1.0/gsl_blas_dnrm2(&U.vector);
    gsl_blas_ddot(&U.vector, &V.vector, &produit);
    gsl_vector_scale(&P.vector, produit*norme*norme);
}

void genunit(int d, gsl_vector* u)
{
    int i;
    double s = 0.0;

    for(i = 0; i < d; i++)
    {
        gsl_vector_set(u, i, ((double) rand()) / ((double) RAND_MAX) - 0.5);
    }
    s = 1.0/gsl_blas_dnrm2(u);
    gsl_vector_scale(u, s);
}

void proj(int d, gsl_vector* u, gsl_vector* v, gsl_vector* p)
{
    double produit,norme;
    gsl_vector_memcpy(p, u);
    norme = 1.0/gsl_blas_dnrm2(u);
    gsl_blas_ddot(u, v, &produit);
    gsl_vector_scale (p, produit*norme*norme);
}

Donnees* rotation(Donnees* entree, int k)
{
    int d(entree->d);
    int n(entree->n);

    //déclaration de P(k*k) et de sortie(k*n)
    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = k;
    sortie->n = n;
    sortie->T = new double[sizeof(double)*n*k];
    sortie->a = entree->a;
    sortie->H = entree->H;

    gsl_matrix_view Tee;
    gsl_matrix* Te;
    gsl_matrix_view Ts;

    gsl_matrix* P;

    Tee = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, k);

    P = gsl_matrix_calloc(k,k);
    Te = gsl_matrix_calloc(n,k);

    int i,j,m;
    gsl_vector_view colonne,u;
    gsl_vector *v,*p;
    double norme;
    v = gsl_vector_alloc(k);
    p = gsl_vector_alloc(k);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < d; j++)
        {
            gsl_matrix_set(Te,i,j,gsl_matrix_get(&Tee.matrix,i,j));
        }
    }

    for(j = 0; j < k; j++)
    {
        colonne = gsl_matrix_column(P, j);
        genunit(k, &colonne.vector);
        gsl_vector_memcpy(v, &colonne.vector);
        for(m = 0; m < j; m++)
        {
            u = gsl_matrix_column(P, m);
            proj(k, &u.vector, v, p);
            gsl_vector_sub(&colonne.vector, p);
            norme = 1.0/gsl_blas_dnrm2(&colonne.vector);
            gsl_vector_scale(&colonne.vector, norme);
        }

    }
    cout << endl;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < k; j++)
        {
            cout << gsl_matrix_get(Te,i,j) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for(i = 0; i < k; i++)
    {
        for(j = 0; j < k; j++)
        {
            cout << gsl_matrix_get(P,i,j) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, Te, P, 0.0, &Ts.matrix);// Ts = Te * P

    return sortie;

}
