#include "fichiers.h"

using namespace std;

int sauvercell(string nom)
{
    ofstream flux(nom.c_str(), ios::out | ios::trunc);
    int i,j,k,m,n,p,d;
    double g(0.5*(1.0+sqrt(5.0)));
    double ig(2.0/(1.0+sqrt(5.0)));
    double permutations[12][4] =
    {
        {g,1,ig,0},
        {ig,g,1,0},
        {1,ig,g,0},
        {1,g,0,ig},
        {g,0,1,ig},
        {0,1,g,ig},
        {g,ig,0,1},
        {0,g,ig,1},
        {ig,0,g,1},
        {ig,1,0,g},
        {1,0,ig,g},
        {0,ig,1,g}
    };
    double* T;
    d = 4;
    n = 120; //16+8+96
    T = new double[sizeof(double)*n*d];

    gsl_vector_view vi,vj,vk,vm;
    gsl_vector *vij,*vik,*vim,*vjk,*vjm,*vkm;
    vij = gsl_vector_calloc(d);
    vik = gsl_vector_calloc(d);
    vim = gsl_vector_calloc(d);
    vjk = gsl_vector_calloc(d);
    vjm = gsl_vector_calloc(d);
    vkm = gsl_vector_calloc(d);

    p = 0;

    int c(0),f(0),e(0);

    if (flux)
    {
        flux << d << "\t" << n << endl;
        for(i = 0; i < 16; i++)
        {
            for(j = 0; j < d; j++)
            {
                flux << ((i & (int)pow(2,j)) != 0)-0.5;//+-0.5
                T[p*d + j] = ((i & (int)pow(2,j)) != 0)-0.5;
                if(j<d-1)
                    flux << "\t";
            }
            p++;
            flux << endl;
        }
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < d; j++)
            {
                if(j == i/2)
                {
                    flux << 1-2*(i%2);
                    T[p*d + j] = 1-2*(i%2);
                }
                else
                {
                    flux << 0;
                    T[p*d + j] = 0;
                }
                if(j<d-1)
                    flux << "\t";
            }
            p++;
            flux << endl;
        }
        for(k = 0; k < 12; k++)
        {
            for(i = 0; i < 8; i++)
            {
                m = 0;
                for(j = 0; j < d; j++)
                {
                    if(permutations[k][j])
                    {
                        flux << (((i & (int)pow(2,m)) != 0)-0.5)*permutations[k][j];
                        T[p*d + j] = (((i & (int)pow(2,m)) != 0)-0.5)*permutations[k][j];
                        m++;
                    }
                    else
                    {
                        flux << 0;
                        T[p*d + j] = 0;
                    }
                    if(j<d-1)
                        flux << "\t";
                }
                p++;
                flux << endl;
            }
        }

        cout << p << endl;

        flux << 2520 << endl;//720 edges 1200 faces 600 cells

        for(i = 0; i < n; i++)
        {
            vi = gsl_vector_view_array(T + i*d, d);
            for(j = i+1; j < n; j++)
            {
                vj = gsl_vector_view_array(T + j*d, d);
                gsl_vector_memcpy(vij, &vi.vector);
                gsl_vector_sub(vij, &vj.vector);

                cout << fabs(gsl_blas_dnrm2(vij)-ig) << endl;

                if(fabs(gsl_blas_dnrm2(vij)-ig) <= PRE)
                {
                    e++;
                    flux << 2 << "\t" << i << "\t" << j << endl;
                    for(k = j+1; k < n; k++)
                    {
                        vk = gsl_vector_view_array(T + k*d, d);
                        gsl_vector_memcpy(vik, &vi.vector);
                        gsl_vector_sub(vik, &vk.vector);
                        gsl_vector_memcpy(vjk, &vj.vector);
                        gsl_vector_sub(vjk, &vk.vector);

                        if(fabs(gsl_blas_dnrm2(vik)-ig) <= PRE && fabs(gsl_blas_dnrm2(vjk)-ig) <= PRE)
                        {
                            f++;
                            flux << 3 << "\t" << i << "\t" << j << "\t" << k << endl;
                            for(m = k+1; m < n; m++)
                            {
                                vm = gsl_vector_view_array(T + m*d, d);
                                gsl_vector_memcpy(vim, &vi.vector);
                                gsl_vector_sub(vim, &vm.vector);
                                gsl_vector_memcpy(vjm, &vj.vector);
                                gsl_vector_sub(vjm, &vm.vector);
                                gsl_vector_memcpy(vkm, &vk.vector);
                                gsl_vector_sub(vkm, &vm.vector);

                                if(fabs(gsl_blas_dnrm2(vim)-ig) <= PRE && fabs(gsl_blas_dnrm2(vjm)-ig) <= PRE && fabs(gsl_blas_dnrm2(vkm)-ig) <= PRE)
                                {
                                    c++;
                                    flux << 4 << "\t" << i << "\t" << j << "\t" << k << "\t" << m << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
        return -1;
    }

    cout << e << "\t" << f << "\t" << c << endl;

    flux.close();
    return 0;
}
