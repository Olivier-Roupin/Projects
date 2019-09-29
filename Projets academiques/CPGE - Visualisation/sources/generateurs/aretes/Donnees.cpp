#include "Donnees.h"

using namespace std;
/*
Donnees* aretes(Donnees* entree)
{
    int a(0),b,x,y,z,w;
    double** H;

    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = entree->d;
    sortie->n = entree->n;
    sortie->T = entree->T;

    int i,j,k(0);

    //calcul de a
    for(i = 0; i < entree->a; i++)
    {
        b = entree->H[i][0];
        a += b*(b-1)/2;
        a += b*(b-1)*(b-2)/6;
        a += b*(b-1)*(b-2)*(b-3)/24;
    }

    H = new double*[sizeof(double*)*a];

    for(i = 0; i < entree->a; i++)
    {
        b = entree->H[i][0];
        for(j = 2; j < min(5,b+1); j++)
        {
            H[k] = new double[sizeof(double)*j];
            H[k][0] = j;
            for(x = 0; x < b+1; x++)
            {
                H[k][1] = entree->H[i][x+1];
                cout << k << "\t" << entree->H[i][x+1] << endl;
                for(y = x+1; y < b+1; y++)
                {
                    H[k][2] = entree->H[i][y+1];
                    cout << k << "\t" << entree->H[i][y+1] << endl;
                    if(j > 2)
                    {
                        for(z = y+1; z < b+1; z++)
                        {
                            H[k][3] = entree->H[i][z+1];
                            cout << k << "\t" << entree->H[i][z+1] << endl;
                            if(j == 4)
                            {
                                for(w = z+1; w < b+1; w++)
                                {
                                    H[k][4] = entree->H[i][w+1];
                                    cout << k << "\t" << entree->H[i][w+1] << endl;
                                    k++;
                                    H[k] = new double[sizeof(double)*j];
                                }
                            }
                            k++;
                            H[k] = new double[sizeof(double)*j];
                        }
                    }
                    k++;
                    H[k] = new double[sizeof(double)*j];
                }
                k++;
                H[k] = new double[sizeof(double)*j];
            }
            k++;
        }
    }

    sortie->a = a;
    sortie->H = H;

    return sortie;

}*/


Donnees* aretes(Donnees* entree)
{
    int a(0),b,x,y,z,w;
    double** H;

    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = entree->d;
    sortie->n = entree->n;
    sortie->T = entree->T;

    int i,j,k(0);

    //calcul de a
    for(i = 0; i < entree->a; i++)
    {
        b = entree->H[i][0];
        a += b*(b-1)/2;
        a += b*(b-1)*(b-2)/6;
        a += b*(b-1)*(b-2)*(b-3)/24;
    }

    H = new double*[sizeof(double*)*a];

    for(i = 0; i < entree->a; i++)
    {
        b = entree->H[i][0];
        cout << i << "\t" << k << endl;
        for(j = 2; j < min(5,b+1); j++)
        {
            for(x = 0; x < b; x++)
            {
                for(y = x+1; y < b; y++)
                {
                    if(j == 3 || j == 4)
                    {
                        for(z = y+1; z < b; z++)
                        {
                            if(j == 4)
                            {
                                for(w = z+1; w < b; w++)
                                {
                                    H[k] = new double[sizeof(double)*(j+1)];
                                    H[k][0] = j;
                                    H[k][1] = entree->H[i][x+1];
                                    H[k][2] = entree->H[i][y+1];
                                    H[k][3] = entree->H[i][z+1];
                                    H[k][4] = entree->H[i][w+1];
                                    //cout << k << "\t" << entree->H[i][x+1] << "\t" << entree->H[i][y+1] << "\t" << entree->H[i][z+1] << "\t" << entree->H[i][w+1] << endl;
                                    k++;
                                }
                            }
                            else
                            {
                                H[k] = new double[sizeof(double)*(j+1)];
                                H[k][0] = j;
                                H[k][1] = entree->H[i][x+1];
                                H[k][2] = entree->H[i][y+1];
                                H[k][3] = entree->H[i][z+1];
                                //cout << k << "\t" << entree->H[i][x+1] << "\t" << entree->H[i][y+1] << "\t" << entree->H[i][z+1] << endl;
                                k++;
                            }
                        }
                    }
                    else
                    {
                        H[k] = new double[sizeof(double)*(j+1)];
                        H[k][0] = j;
                        H[k][1] = entree->H[i][x+1];
                        H[k][2] = entree->H[i][y+1];
                        //cout << k << "\t" << entree->H[i][x+1] << "\t" << entree->H[i][y+1] << endl;
                        k++;
                    }
                }
            }
        }
    }
cout << j << endl;
    sortie->a = a;
    sortie->H = H;

    return sortie;

}
