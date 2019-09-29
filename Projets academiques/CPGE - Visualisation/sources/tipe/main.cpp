#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string.h>

#include "fichiers.h"
#include "maxcut.h"
#include "simple.h"
#include "perspective.h"
#include "fjlt.h"

#define CD1 0.5
#define CD2 0.4
#define CD3 0.3

using namespace std;

/*Donnees* dichotomie2(int k, int e, Donnees* entree)
{
    int a(entree->d),b(k),c;
    Donnees* sortie;
    while(a-b)
    {
        c = (a+b+1)/2;
        sortie = fjlt(entree,c,e);
        if(distortion(entree, sortie, e))
        {
            b = c;
        }
        else
        {
            a = c;
        }
        cout << c << endl;
    }
    delete sortie;
    return fjlt(entree,a,e);
}*/

Donnees* dichotomie(int k, int e, Donnees* entree)
{
    int a(entree->d),b(k),c;
    Donnees* sortie;
    while(a>b+1)
    {
        c = (a+b+1)/2;
        sortie = fjlt(entree,c,e);
        if(distances_aretes(entree,sortie) < CD1 || surfaces_aretes(entree,sortie) < CD2 || volumes_aretes(entree,sortie) < CD3)
        {
            b = c;
        }
        else
        {
            a = c;
        }
        cout << c << "\t" << distances_aretes(entree,sortie) << "\t" << surfaces_aretes(entree,sortie) << "\t" <<volumes_aretes(entree,sortie) << endl;
    }
    delete sortie;
    return fjlt(entree,a,e);
}

int main(int argc,char *argv[])
{
    Donnees* entree;
    Donnees* inter;
    Donnees* sortie;
    //Donnees* base;
    double* base;
    entree = new Donnees();
    //base = new Donnees();
    string nom(argv[1]);
    string methode(argv[2]);
    string dimension(argv[3]);
    int d(atoi(argv[3]));
    string nomEntree,nomSortie,nomErreur;

    double erreur[NOMBRECRITERES];

    //sprintf(nomSortie., "%s-%s-%d.out",nom,methode,dimension);

    nomSortie.append(nom);
    nomSortie.append("-");
    nomSortie.append(methode);
    nomSortie.append("-");
    nomSortie.append(dimension);
    nomSortie.append("D");

    nomEntree.append(nom);
    nomErreur.append(nomSortie);

    nomEntree.append(".in");
    nomSortie.append(".out");
    nomErreur.append(".eval");


    //long int top_chrono;
    //long int arret_chrono;

    double e = 1.0;
    int i,j;

    ouvrir(nomEntree, entree);
    base = new double[sizeof(double)*d*entree->d];

    //ouvrir("base", base);
    /*for(j=0; j < entree->d; j++)
    {
        for(i=0; i < d; i++)
        {
            base[i*entree->d + j] = 1*(i == j);
        }
    }*/

    base = genbase(entree->d,d);
    base = genbase(entree->d,d);

    if(strcmp(methode.c_str(), "GW") == 0)
    {
        sortie = maxcut(entree,d);
    }
    else if(strcmp(methode.c_str(), "JL") == 0)
    {
        sortie = fjlt(entree,d,e);
    }
    else if(strcmp(methode.c_str(), "PS") == 0)
    {
        sortie = simple(entree,d,base);
    }
    else if(strcmp(methode.c_str(), "PP") == 0)
    {
        sortie = perspective(entree,d,base,1);
    }
    else if(strcmp(methode.c_str(), "HY") == 0)
    {
        inter = dichotomie(d, e, entree);
        //cout << inter->d << endl;
        //sauver("inter",inter);
        sortie = maxcut(inter,d);
    }
    else
    {
        return -1;
    }

    sauver(nomSortie,sortie);

    /*erreur[0] = distances(entree,sortie);
    erreur[1] = surfaces(entree,sortie);
    erreur[2] = volumes(entree,sortie);
    erreur[3] = distances_aretes(entree,sortie);
    erreur[4] = surfaces_aretes(entree,sortie);
    erreur[5] = volumes_aretes(entree,sortie);*/

    erreur[0] = distances_aretes(entree,sortie);
    cout << erreur[0] << "\t";
    erreur[1] = surfaces_aretes(entree,sortie);
    cout << erreur[1] << "\t";
    erreur[2] = volumes_aretes(entree,sortie);
    cout << erreur[2] << "\t";
    erreur[3] = fusion(entree,sortie);
    cout << erreur[3] << endl;

    sauvererreur(nomErreur,erreur);

    //top_chrono = clock();

    //arret_chrono = clock();

    //cout << (float)(arret_chrono - top_chrono) / CLOCKS_PER_SEC << " s" << endl;

    return 0;
}
