#include "Donnees.h"

using namespace std;

int parite(int x)
{
    if(x%2)
        return -1;
    return 1;
}

double degres2rad(int val)
{
    return M_PI*val/180.;
}

int Donnees_free(Donnees* donnees)
{
    int i;
    for(i = 0; i < donnees->a; i++)
        delete donnees->H[i];
    delete donnees->H;
    gsl_matrix_free(donnees->Points);
    delete donnees;
    return 0;
}

gsl_matrix* Angles2Matrix(double* angles, int d)
{
    gsl_matrix* Mangles;
    Mangles = gsl_matrix_calloc(d,d);
    Angles2Matrix(angles, Mangles);
    return Mangles;
}

int Angles2Matrix(double* angles, gsl_matrix* Mangles)
{
    int k,l,m;
    int d(Mangles->size1);
    gsl_matrix_set_identity(Mangles);
    m = 0;
    for(k = 0; k < d-1; k++)
    {
        for(l = k+1; l < d; l++)
        {
            gsl_matrix_set(Mangles,k,k,cos(angles[m]));
            gsl_matrix_set(Mangles,l,l,cos(angles[m]));
            gsl_matrix_set(Mangles,k,l,-parite(k+l)*sin(angles[m]));
            gsl_matrix_set(Mangles,l,k,parite(k+l)*sin(angles[m]));
            m++;
        }
    }
    return 0;
}

double* Matrix2Angles(gsl_matrix* Mangles)
{
    int d(Mangles->size1);
    double* angles;
    angles = new double[sizeof(double)*(int)gsl_sf_choose(d,2)];
    Matrix2Angles(Mangles, angles);
    return angles;
}

int Matrix2Angles(gsl_matrix* Mangles, double* angles)
{
    int d(Mangles->size1);
    int k,l,m;
    gsl_complex z;

    m = 0;
    for(k = 0; k < d-1; k++)
    {
        for(l = k+1; l < d; l++)
        {
            GSL_SET_COMPLEX(&z, gsl_matrix_get(Mangles,k,k), parite(k+l)*gsl_matrix_get(Mangles,l,k));
            angles[m] = gsl_complex_arg(z);
            m++;
        }
    }
    return 0;
}

int Reparer(gsl_matrix* Mangles)
{
    int d(Mangles->size1);
    int i,j;
    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            if(gsl_matrix_get(Mangles,i,j) >= 0.5)
                gsl_matrix_set(Mangles,i,j,1);
            else if(gsl_matrix_get(Mangles,i,j) <= -0.5)
                gsl_matrix_set(Mangles,i,j,-1);
            else
                gsl_matrix_set(Mangles,i,j,0);
        }
    }
    return 0;
}

int TrouverAxe(gsl_matrix* Mangles, int axe)
{
    int d(Mangles->size1);
    int i;
    for(i = 0; i < d; i++)
    {
        if(gsl_matrix_get(Mangles,d-1,i))
            return i;
    }
    return axe;
}

Donnees* init_translation_rotation_homothetie(Donnees* entree)
{
    Donnees* sortie;
    sortie = new Donnees();
    sortie->Points = gsl_matrix_calloc(entree->Points->size1,entree->Points->size2);
    sortie->a = entree->a;
    sortie->H = entree->H;
    gsl_matrix_memcpy(sortie->Points, entree->Points);
    return sortie;
}

int rotation(Donnees* entree, gsl_matrix* Mangles, Donnees* sortie)
{
    //Rotation
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, entree->Points, Mangles, 0.0, sortie->Points); //Ts = Te*tMangles
    return 0;
}

int translation(Donnees* entree, gsl_vector* Vvecteur, Donnees* sortie)
{
    int i;
    int n(entree->Points->size1);
    int d(entree->Points->size2);
    gsl_matrix* M;
    M = gsl_matrix_alloc(n,d);

    for(i = 0; i < n; i++)
        gsl_matrix_set_row(M, i, Vvecteur);

    //Translation
    gsl_matrix_memcpy(sortie->Points, entree->Points);
    gsl_matrix_add(sortie->Points, M);
    gsl_matrix_free(M);
    return 0;
}

int homothetie(Donnees* entree, double r, Donnees* sortie)
{
    gsl_matrix_memcpy(sortie->Points, entree->Points);
    //Homothétie
    gsl_matrix_scale(sortie->Points, r);
    return 0;
}

int Labyrinthe2Donnees(Labyrinthe* labyrinthe, Donnees* bloc, Donnees* donnees)
{
    int n(bloc->Points->size1);
    int d(bloc->Points->size2);
    int a(bloc->a);
    int b(0);
    gsl_matrix* Points;
    double** H;
    int i,j,k;
    int x,y,z,w;

    Points = gsl_matrix_calloc(n*labyrinthe->GetTaille(),d);

    for(x = 0; x < labyrinthe->GetX(); x++)
    {
        for(y = 0; y < labyrinthe->GetY(); y++)
        {
            for(z = 0; z < labyrinthe->GetZ(); z++)
            {
                for(w = 0; w < labyrinthe->GetW(); w++)
                {
                    i = labyrinthe->Conversion(x,y,z,w);
                    for(j = 0; j < n; j++)
                    {
                        for(k = 0; k < d; k++)
                            gsl_matrix_set(Points,j+i*n,k,gsl_matrix_get(bloc->Points,j,k)+1*((k==0)*x+(k==1)*y+(k==2)*z+(k==3)*w));
                    }
                }
            }
        }
    }
    donnees->Points = Points;
    H = new double*[sizeof(double*)*a*labyrinthe->GetTaille()];
    donnees->a = a*labyrinthe->GetTaille();
    for(k = 0; k < labyrinthe->GetTaille(); k++)
    {
        if(labyrinthe->GetTableau(k))
        {
            for(i = 0; i < a; i++)
            {
                b = bloc->H[i][0];
                H[i+k*a] = new double[sizeof(double)*(b+1)];
                H[i+k*a][0] = b;
                for(j = 1; j < b+1; j++)
                    H[i+k*a][j] = bloc->H[i][j]+k*n;
            }
        }
        else
        {
            for(i = 0; i < a; i++)
            {
                H[i+k*a] = new double[sizeof(double)];
                H[i+k*a][0] = 0;
            }
        }
    }
    donnees->H = H;

    return 0;
}
/*
int Labyrinthe2Donnees(Labyrinthe* labyrinthe, Donnees* bloc, Donnees* donnees)
{
    int d(0);
    int n(0);
    int a(0);
    int b(0);
    gsl_matrix* Points;
    double** H;
    int i,j,k;
    int x,y,z,w;
    gsl_vector* vect;
    gsl_vector* copie;
    gsl_matrix* mat;

    d = bloc->d;
    n = bloc->n*labyrinthe->GetTaille();
    Points = gsl_matrix_calloc(n,d);
    donnees->d = d;
    donnees->n = n;
    vect = gsl_vector_calloc(d);
    copie = gsl_vector_calloc(d);
    mat = gsl_matrix_calloc(n,d);

    for(x = 0; x < labyrinthe->GetX(); x++)
    {
        gsl_vector_set(vect,0,x);
        for(y = 0; y < labyrinthe->GetY(); y++)
        {
            gsl_vector_set(vect,1,y);
            for(z = 0; z < labyrinthe->GetZ(); z++)
            {
                gsl_vector_set(vect,2,z);
                for(w = 0; w < labyrinthe->GetW(); w++)
                {
                    gsl_vector_set(vect,3,w);
                    i = labyrinthe->Conversion(x,y,z,w);
                    for(j = 0; j < bloc->n; j++)
                    {
                        gsl_matrix_set_row(mat,j+i*bloc->n,vect);
                        gsl_matrix_get_row(copie,bloc->Points,j);
                        gsl_matrix_set_row(Points,j+i*bloc->n,copie);
                    }
                }
            }
        }
    }
    gsl_matrix_add(Points,mat);
    donnees->Points = Points;

    a = bloc->a*labyrinthe->GetTaille();
    H = new double*[sizeof(double*)*a];
    donnees->a = a;
    for(k = 0; k < labyrinthe->GetTaille(); k++)
    {
        if(labyrinthe->GetTableau(k))
        {
            for(i = 0; i < bloc->a; i++)
            {
                b = bloc->H[i][0];
                H[i+k*bloc->a] = new double[sizeof(double)*(b+1)];
                H[i+k*bloc->a][0] = b;
                for(j = 1; j < b+1; j++)
                    H[i+k*bloc->a][j] = bloc->H[i][j]+k*bloc->n;
            }
        }
        else
        {
            for(i = 0; i < bloc->a; i++)
            {
                H[i+k*bloc->a] = new double[sizeof(double)];
                H[i+k*bloc->a][0] = 0;
            }
        }
    }
    donnees->H = H;

    gsl_vector_free(vect);
    gsl_vector_free(copie);
    gsl_matrix_free(mat);
    return 0;
}
*/
void print_mat(gsl_matrix* M)
{
    int i,j;
    for(i = 0; i < (int)M->size1; i++)
    {
        for(j = 0; j < (int)M->size2; j++)
            cout << gsl_matrix_get(M,i,j) << "\t";
        cout << endl;
    }
    cout << endl;
}
