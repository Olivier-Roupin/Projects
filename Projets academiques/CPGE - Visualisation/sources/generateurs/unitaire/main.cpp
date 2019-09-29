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
    int d(atoi(argv[1]));
    int n(atoi(argv[2]));
    sauvervect("unit",d,n);

    return 0;
}
