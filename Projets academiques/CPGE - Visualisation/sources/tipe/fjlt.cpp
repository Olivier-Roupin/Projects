#include "fjlt.h"

using namespace std;

Donnees* fjlt(Donnees* entree, int k, double e) //entree : données en entrée; k : dimension de sortie; e : précision
{
    gsl_rng* r = gsl_rng_alloc(gsl_rng_taus); //radom number generator
    int d(entree->d);
    int n(entree->n);

    //déclaration de P(d*k),H(d*d) et D(d*d), et de sortie(n*k)
    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = k;
    sortie->n = n;
    sortie->T = new double[sizeof(double)*n*k];
    sortie->a = entree->a;
    sortie->H = entree->H;

    gsl_matrix_view Te;
    gsl_matrix_view Ts;

    gsl_matrix* P;
    gsl_matrix* HP;
    gsl_matrix* H;
    gsl_matrix* DHP;
    gsl_matrix* D;

    Te = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, k);

    P = gsl_matrix_calloc(d,k);
    HP = gsl_matrix_calloc(d,k);
    H = gsl_matrix_calloc(d,d);
    DHP = gsl_matrix_calloc(d,k);
    D = gsl_matrix_calloc(d,d);//Dij = 0 pour tout i!=j

    int i,j;

    //double q(min(1.0,gsl_sf_pow_int(e,p-2)*gsl_sf_pow_int(gsl_sf_log(n),p)/d));

    gsl_vector_view ligne;
    double norme;

    //calcul des coefficients de P
    for(i = 0; i < d; i++)
    {
        for(j = 0; j < k; j++)
        {
            //if(gsl_ran_bernoulli(r,q))
            //{
            //gsl_matrix_set(P,i,j,gsl_ran_gaussian(r,sqrt(1.0/q)));
            gsl_matrix_set(P,i,j,gsl_ran_ugaussian(r));
            //}
            //cout << gsl_matrix_get(P,i,j) << "\t";
        }
        ligne = gsl_matrix_row(P,i);
        norme = 1.0/gsl_blas_dnrm2(&ligne.vector);
        gsl_vector_scale(&ligne.vector, norme);
        //cout << endl;
    }

    //calcul des coefficients de H
    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            gsl_matrix_set(H,i,j,gsl_sf_pow_int(-1,(i & j)!= 0));//Hij = 1/sqrt(d)*(-1)^<i,j>
            //cout << gsl_matrix_get(H,i,j) << "\t";
        }
        //cout << endl;
    }
    //cout << endl;
    gsl_matrix_scale(H, 1.0/sqrt(d));

    //calcul des coefficients de D
    for(i = 0; i < d; i++)
    {
        gsl_matrix_set(D,i,i,2*(int)gsl_ran_bernoulli(r,0.5)-1);//Dii=2*gsl_ran_bernoulli(r,q)-1;
        //cout << gsl_matrix_get(D,i,i) << " ";
    }
    //cout << endl;

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, H, P, 0.0, HP);//HP =H*P
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, D, HP, 0.0, DHP);// DHP = D*HP
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &Te.matrix, DHP, 0.0, &Ts.matrix);// Ts = Te*DHP

    return sortie;
}

int distortion(Donnees* entree, Donnees* sortie, double e)
{
    int x,y,d,k,n;
    gsl_vector_view vx,vy,ux,uy;
    gsl_vector* vdif;
    gsl_vector* udif;
    double c,distv,distu;
    double* Tv;
    double* Tu;
    n = entree->n;
    d = entree->d;
    k = sortie->d;
    Tv = entree->T;
    Tu = sortie->T;
    c = sqrt(1.0*k/d);
    vdif = gsl_vector_calloc(d);
    udif = gsl_vector_calloc(k);
    for(x = 0; x < n; x++)
    {
        vx = gsl_vector_view_array(Tv + x*d, d);
        ux = gsl_vector_view_array(Tu + x*k, k);
        for(y = x+1; y < n; y++)
        {
            vy = gsl_vector_view_array(Tv + y*d, d);
            uy = gsl_vector_view_array(Tu + y*k, k);

            gsl_vector_memcpy(vdif, &vx.vector);
            gsl_vector_sub(vdif, &vy.vector);
            distv = gsl_blas_dnrm2(vdif);

            gsl_vector_memcpy(udif, &ux.vector);
            gsl_vector_sub(udif, &uy.vector);
            distu = gsl_blas_dnrm2(udif);

            if(distu < distv*c*(1-e) || distu > distv*c*(1+e))
            {
                //cout << x << "\t" << y << "\t" << distu-distv*c << endl;
                return -1;
            }
        }
    }
    return 0;
}
/*
int distortion(Donnees* entree, Donnees* sortie)
{
    int x,y,d,k,n;
    gsl_vector_view vx,vy,ux,uy;
    gsl_vector* vdif;
    gsl_vector* udif;
    double c,distv,distu;
    double* Tv;
    double* Tu;
    n = entree->n;
    d = entree->d;
    k = sortie->d;
    Tv = entree->T;
    Tu = sortie->T;
    c = sqrt(1.0*k/d);
    vdif = gsl_vector_calloc(d);
    udif = gsl_vector_calloc(k);
    for(x = 0; x < n; x++)
    {
        vx = gsl_vector_view_array(Tv + x*d, d);
        ux = gsl_vector_view_array(Tu + x*k, k);
        for(y = x+1; y < n; y++)
        {
            vy = gsl_vector_view_array(Tv + y*d, d);
            uy = gsl_vector_view_array(Tu + y*k, k);

            gsl_vector_memcpy(vdif, &vx.vector);
            gsl_vector_sub(vdif, &vy.vector);
            distv = gsl_blas_dnrm2(vdif);

            gsl_vector_memcpy(udif, &ux.vector);
            gsl_vector_sub(udif, &uy.vector);
            distu = gsl_blas_dnrm2(udif);

            if(distu < distv*c*(1-e) || distu > distv*c*(1+e))
            {
                //cout << x << "\t" << y << "\t" << distu-distv*c << endl;
                return -1;
            }
        }
    }
    return 0;
}
*/
