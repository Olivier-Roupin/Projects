#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>

#include "fichiers.h"

using namespace std;

//d : dimension de départ
//k : dimension de sortie
//n : nombre de points

int main(int argc,char *argv[])
{
    Donnees* entree;
    Donnees* sortie;
    entree = new Donnees();
    string nom(argv[1]);
    string dimension(argv[2]);
    int d(atoi(argv[2]));
    string nomEntree("/home/olivier/programmes/fichiers/objets/");
    string nomSortie("/home/olivier/programmes/fichiers/input/");

    nomEntree.append(nom);
    //nomEntree.append(".in");

    nomSortie.append(nom);
    nomSortie.append("rot");
    nomSortie.append(dimension);
    nomSortie.append(".in");

    ouvrir(nomEntree, entree);
    sortie = rotation(entree,d);
    sauver(nomSortie,sortie);

    return 0;
}
