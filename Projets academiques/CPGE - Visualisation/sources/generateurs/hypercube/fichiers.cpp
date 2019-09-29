#include "fichiers.h"

using namespace std;

int sauvercube(string nom, int d)
{
    ofstream flux(nom.c_str(), ios::out | ios::trunc);
    int i,j,k,m,n;
    n = (int)pow(2,d);
    flux << d << "\t" << n << endl;
    if (flux)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < d; j++)
            {
                flux << 2*((i & (int)pow(2,j)) != 0)-1;
                if(j<d-1)
                    flux << "\t";
            }
            flux << endl;
        }
        flux << (n*d)/2 + (n*d*(d-1))/2 + (n*d*(d-1)*(d-2))/6 << endl;//n points, n*(d/2) arêtes, n*d*(d-1)/2 sufaces, n*d*(d-1)*(d-2)/6 volumes
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < d; j++)
            {
                if ((i & (int)pow(2,j)) == 0)
                {
                    flux << 2 << "\t" << i << "\t" << i + (int)pow(2,j) << endl;
                }
            }
        }
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < d; j++)
            {
                for(k = j+1; k < d; k++)
                {
                    flux << 3 << "\t" << i << "\t" << (i ^ (int)pow(2,j)) << "\t" << (i ^ (int)pow(2,k)) << endl;
                }
            }
        }
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < d; j++)
            {
                for(k = j+1; k < d; k++)
                {
                    for(m = k+1; m < d; m++)
                    {
                        flux << 4 << "\t" << i << "\t" << (i ^ (int)pow(2,j)) << "\t" << (i ^ (int)pow(2,k)) << "\t" << (i ^ (int)pow(2,m)) << endl;
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
    flux.close();
    return 0;
}
