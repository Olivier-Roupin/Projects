#include "Donnees.h"

using namespace std;

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

double* genbase(int d, int k)
{
    double *entree, *sortie;
    entree = new double[sizeof(double)*d*k];
    sortie = new double[sizeof(double)*d*k];

    gsl_matrix_view Tee;
    gsl_matrix* Te;
    gsl_matrix_view Ts;

    gsl_matrix* P;

    Tee = gsl_matrix_view_array(entree, k, d);
    Ts = gsl_matrix_view_array(sortie, k, d);

    P = gsl_matrix_calloc(d,d);
    Te = gsl_matrix_calloc(k,d);

    int i,j,m;
    gsl_vector_view colonne,u;
    gsl_vector *v,*p;
    double norme;
    v = gsl_vector_alloc(d);
    p = gsl_vector_alloc(d);

    for(j = 0; j < k; j++)
    {
        for(i = 0; i < d; i++)
        {
            entree[i*d + j] = 1*(i == j);
        }
    }

    for(i = 0; i < k; i++)
    {
        for(j = 0; j < d; j++)
        {
            gsl_matrix_set(Te,i,j,gsl_matrix_get(&Tee.matrix,i,j));
        }
    }

    for(j = 0; j < d; j++)
    {
        colonne = gsl_matrix_column(P, j);
        genunit(d, &colonne.vector);
        gsl_vector_memcpy(v, &colonne.vector);
        for(m = 0; m < j; m++)
        {
            u = gsl_matrix_column(P, m);
            proj(d, &u.vector, v, p);
            gsl_vector_sub(&colonne.vector, p);
            norme = 1.0/gsl_blas_dnrm2(&colonne.vector);
            gsl_vector_scale(&colonne.vector, norme);
        }
    }

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Te, P, 0.0, &Ts.matrix); //Ts = Te * P

    delete entree;

    return sortie;

}

double degres2rad(int val)
{
    return M_PI*val/180.;
}

double* vecteur_nul(int d)
{
    double* r;
    r = new double[sizeof(double)*d];
    for(int i(0); i < d; i++)
    {
        r[i] = 0;
    }
    return r;
}

gsl_matrix* Angles2Matrix(double* angles, int d)
{
    gsl_matrix* M;
    M = gsl_matrix_calloc(d,d);
    Angles2Matrix(angles, d, M);

    return M;
}

int Angles2Matrix(double* angles, int d, gsl_matrix* Mangles)
{
    gsl_matrix* Mm;
    gsl_matrix* Mcopie;
    int k,l,m;

    Mm = gsl_matrix_calloc(d,d);
    Mcopie = gsl_matrix_calloc(d,d);

    gsl_matrix_set_identity(Mangles);

    m = 0;
    for(k = 0; k < d-1; k++)
    {
        for(l = k+1; l < d; l++)
        {
            gsl_matrix_set_identity(Mm);
            gsl_matrix_set(Mm,k,k,cos(angles[m]));
            gsl_matrix_set(Mm,l,l,cos(angles[m]));
            gsl_matrix_set(Mm,k,l,-pow(-1,k+l)*sin(angles[m]));
            gsl_matrix_set(Mm,l,k,pow(-1,k+l)*sin(angles[m]));
            gsl_matrix_memcpy(Mcopie,Mangles);
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Mcopie, Mm, 0.0, Mangles); //Mangles = Mangles*Mm
            m++;
        }
    }
    gsl_matrix_free(Mcopie);
    gsl_matrix_free(Mm);

    return 0;
}

double* Matrix2Angles(gsl_matrix* M, int d)
{
    double* angles;
    angles = new double[sizeof(double)*(int)gsl_sf_choose(d,2)];
    Matrix2Angles(M, d, angles);

    return angles;
}

int Matrix2Angles(gsl_matrix* M, int d, double* angles)
{
    int k,l,m;
    gsl_complex z;

    m = 0;
    for(k = 0; k < d-1; k++)
    {
        for(l = k+1; l < d; l++)
        {
            GSL_SET_COMPLEX(&z, gsl_matrix_get(M,k,k), gsl_pow_int(-1,k+l)*gsl_matrix_get(M,l,k));
            angles[m] = gsl_complex_arg(z);
            m++;
        }
    }
    return 0;
}

Donnees* rotation(Donnees* entree, double* angles) // (2 parmis d) angles
{
    int d(entree->d);
    int n(entree->n);
    Donnees* sortie;
    gsl_matrix* M;
    sortie = new Donnees();
    sortie->d = d;
    sortie->n = n;
    sortie->T = new double[sizeof(double)*n*d];
    sortie->a = entree->a;
    sortie->H = entree->H;

    gsl_matrix_view Te,Ts;

    Te = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, d);

    M = Angles2Matrix(angles,d);

    //Rotation
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, &Te.matrix, M, 0.0, &Ts.matrix); //Ts = Te*tM

    gsl_matrix_free(M);

    return sortie;
}

Donnees* rotation(Donnees* entree, gsl_matrix* Mangles) // (2 parmis d) angles
{
    int d(entree->d);
    int n(entree->n);
    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = d;
    sortie->n = n;
    sortie->T = new double[sizeof(double)*n*d];
    sortie->a = entree->a;
    sortie->H = entree->H;

    gsl_matrix_view Te,Ts;

    Te = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, d);

    //Rotation
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, &Te.matrix, Mangles, 0.0, &Ts.matrix); //Ts = Te*tMangles

    return sortie;
}

Donnees* homothetie(Donnees* entree, double r)
{
    int d(entree->d);
    int n(entree->n);
    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = d;
    sortie->n = n;
    sortie->T = new double[sizeof(double)*n*d];
    sortie->a = entree->a;
    sortie->H = entree->H;

    gsl_matrix_view Te,Ts;

    Te = gsl_matrix_view_array(entree->T, n, d);
    Ts = gsl_matrix_view_array(sortie->T, n, d);

    gsl_matrix_memcpy(&Ts.matrix, &Te.matrix);
    gsl_matrix_scale(&Ts.matrix, r);

    return sortie;
}

Donnees* translation(Donnees* entree)
{
    return 0;
}

void print_mat(gsl_matrix* M)
{
    int i,j;
    for(i = 0; i < (int)M->size1; i++)
    {
        for(j = 0; j < (int)M->size2; j++)
        {
            cout << gsl_matrix_get(M,i,j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
