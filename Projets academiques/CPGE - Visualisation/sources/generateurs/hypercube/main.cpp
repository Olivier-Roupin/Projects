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
    string dimension(argv[1]);
    int d(atoi(argv[1]));
    string nom("/home/olivier/programmes/fichiers/input/cube");

    nom.append(dimension);
    nom.append(".in");
    sauvercube(nom,d);

    return 0;
}