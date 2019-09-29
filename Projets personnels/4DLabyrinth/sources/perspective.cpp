#include "perspective.h"

using namespace std;

double* perspectived(Donnees* entree, int k, gsl_matrix* Tb, double r) //B : base orthonormale de l'espace d'arrivée (tableau d*k)
{
    int n(entree->Points->size1);
    int d(entree->Points->size2);
    double* S = new double[sizeof(double)*n*k];
    gsl_matrix_view Te,Ts;
    gsl_vector_view ve,vs,vd;
    gsl_vector* vdif;
    double dist;

    int i;
    Ts = gsl_matrix_view_array(S, n, k);

    vdif = gsl_vector_calloc(d);
    vd = gsl_vector_subvector(vdif,0,k);

    //Projection
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, &Te.matrix, Tb, 0.0, &Ts.matrix); //Ts = Te*tTb

    //Thalès
    for(i = 0; i < n; i++)
    {
        ve = gsl_matrix_row(&Te.matrix,i);
        vs = gsl_matrix_row(&Ts.matrix,i);

        gsl_vector_set_zero(vdif);
        gsl_vector_memcpy(&vd.vector,&vs.vector);
        gsl_vector_sub(vdif, &ve.vector);
        dist = gsl_blas_dnrm2(vdif);
        gsl_vector_scale(&vs.vector, r/dist);//r/(r+dist));
    }
    gsl_vector_free(vdif);
    return Ts.matrix.data;
}

gsl_matrix* selected(Donnees* entree, int k, gsl_matrix* Tb, Labyrinthe* lab, int axe, int indice, int taille)
{
    int n(entree->Points->size1);
    gsl_matrix* Ts;
    gsl_matrix_view ms;
    int i;
    int x,y,z,w;

    Ts = gsl_matrix_calloc(n,k);

    //Projection
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, entree->Points, Tb, 0.0, Ts); //Ts = Te*tTb

    //Selection
    for(x = 0; x < lab->GetX(); x++)
    {
        if(axe == 0 && x == indice)
            x++;
        if(x == lab->GetX())
            continue;
        for(y = 0; y < lab->GetY(); y++)
        {
            if(axe == 1 && y == indice)
                y++;
            if(y == lab->GetY())
                continue;
            for(z = 0; z < lab->GetZ(); z++)
            {
                if(axe == 2 && z == indice)
                    z++;
                if(z == lab->GetZ())
                    continue;
                for(w = 0; w < lab->GetW(); w++)
                {
                    if(axe == 3 && w == indice)
                        w++;
                    if(w == lab->GetW())
                        continue;
                    i = lab->Conversion(x,y,z,w);
                    ms = gsl_matrix_submatrix(Ts,i*taille,0,taille,k);
                    gsl_matrix_scale(&ms.matrix, 0);
                }
            }
        }
    }
    return Ts;
}

int selected(Donnees* entree, int k, gsl_matrix* Tb, Labyrinthe* lab, int axe, int indice, int taille, Donnees* sortie)
{
    gsl_matrix_view ms;
    int i;
    int x,y,z,w;

    //Projection
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, entree->Points, Tb, 0.0, sortie->Points); //Ts = Te*tTb

    //Selection
    for(x = 0; x < lab->GetX(); x++)
    {
        if(axe == 0 && x == indice)
            x++;
        if(x == lab->GetX())
            continue;
        for(y = 0; y < lab->GetY(); y++)
        {
            if(axe == 1 && y == indice)
                y++;
            if(y == lab->GetY())
                continue;
            for(z = 0; z < lab->GetZ(); z++)
            {
                if(axe == 2 && z == indice)
                    z++;
                if(z == lab->GetZ())
                    continue;
                for(w = 0; w < lab->GetW(); w++)
                {
                    if(axe == 3 && w == indice)
                        w++;
                    if(w == lab->GetW())
                        continue;
                    i = lab->Conversion(x,y,z,w);
                    ms = gsl_matrix_submatrix(sortie->Points,i*taille,0,taille,k);
                    gsl_matrix_scale(&ms.matrix, 0);
                }
            }
        }
    }
    return 0;
}
