#include "fichiers.h"

using namespace std;

int ouvrir(string nom, Donnees* donnees)
{
    ifstream flux(nom.c_str());
    int d(0);
    int n(0);
    int a(0);
    int b(0);
    gsl_matrix* Points;
    double** H;
    int i,j;

    if(flux)
    {
        flux >> d;
        flux >> n;
        Points = gsl_matrix_calloc(n,d);
        for(i = 0; i < d*n; i++)
            flux >> Points->data[i];
        donnees->Points = Points;
        flux >> a;
        H = new double*[sizeof(double*)*a];
        donnees->a = a;
        for(i = 0; i < a; i++)
        {
            flux >> b;
            H[i] = new double[sizeof(double)*(b+1)];
            H[i][0] = b;
            for(j = 1; j < b+1; j++)
                flux >> H[i][j];
        }
        donnees->H = H;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        return -1;
    }
    flux.close();
    return 0;
}

int sauver(string nom, Donnees* donnees)
{
    ofstream flux(nom.c_str(), ios::out | ios::trunc);
    int n(donnees->Points->size1);
    int d(donnees->Points->size2);
    gsl_matrix* Points(donnees->Points);
    int a(donnees->a);
    double** H(donnees->H);
    int i,j;

    if(flux)
    {
        flux << d << "\t";
        flux << n << endl;
        for(i = 0; i < d*n; i++)
        {
            flux << Points->data[i];
            if((i+1)%d)
                flux << "\t";
            else
                flux << endl;
        }
        flux << a << endl;
        for(i = 0; i < a; i++)
        {
            for(j = 0; j < H[i][0]+1; j++)
            {
                flux << H[i][j];
                if(j!=H[i][0])
                    flux << "\t";
            }
            if(i!=a-1)
                flux << endl;
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
