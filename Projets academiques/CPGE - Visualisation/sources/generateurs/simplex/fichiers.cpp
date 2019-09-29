#include "fichiers.h"

using namespace std;

int sauversimplex(std::string nom, int d)
{
    ofstream flux(nom.c_str(), ios::out | ios::trunc);
    int i,j,k,m;
    double norm;
    norm = (1.0+sqrt(d+1))/d;
    flux << d << "\t" << d+1 << endl;
    if (flux)
    {
        for(i = 0; i < d; i++)
        {
            for(j = 0; j < d; j++)
            {
                flux << setprecision(8) << (i==j);
                if(j<d-1)
                    flux << "\t";
            }
            flux << endl;
        }
        for(j = 0; j < d; j++)
        {
            flux << setprecision(8) << norm;
            if(j<d-1)
                flux << "\t";
        }
        flux << endl;
        flux << (d*(d+1))/2 + ((d+1)*d*(d-1))/6 + ((d+1)*d*(d-1)*(d-2))/24 << endl;//d+1 points, (d+1)*d/2 arêtes, (d+1)*d*(d-1)/6 surfaces, (d+1)*d*(d-1)*(d-2)/24
        for(i = 0; i < d+1; i++)
        {
            for(j = i+1; j < d+1; j++)
            {
                flux << 2 << "\t" << i << "\t" << j << endl;
            }
        }
        for(i = 0; i < d+1; i++)
        {
            for(j = i+1; j < d+1; j++)
            {
                for(k = j+1; k < d+1; k++)
                {
                        flux << 3 << "\t" << i << "\t" << j << "\t" << k << endl;
                }
            }
        }
        for(i = 0; i < d+1; i++)
        {
            for(j = i+1; j < d+1; j++)
            {
                for(k = j+1; k < d+1; k++)
                {
                    for(m = k+1; m < d+1; m++)
                    {
                        flux << 4 << "\t" << i << "\t" << j << "\t" << k << "\t" << m << endl;
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
