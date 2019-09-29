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
    string nom("/home/olivier/programmes/fichiers/input/cell");

    nom.append(".in");

    sauvercell(nom);

    return 0;
}
