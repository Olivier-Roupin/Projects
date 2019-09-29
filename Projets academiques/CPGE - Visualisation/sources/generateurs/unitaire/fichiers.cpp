#include "fichiers.h"

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

int sauvervect(std::string nom, int d, int n)
{

    ofstream flux(nom.c_str(), ios::out | ios::trunc);
    int i,j;
    double* u;
    u = new double[sizeof(double)*d];
    flux << d << "\t" << n << endl;
    if (flux)
    {
        for(i = 0; i < n; i++)
        {
            genunit(d, u);
            for(j = 0; j < d; j++)
            {
                flux << setprecision(8) << u[j];
                if(j < d-1)
                    flux << "\t";
            }
            flux << endl;
        }
        flux << 0;//0 hyper-arête
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
        return -1;
    }
    flux.close();
    return 0;
}
