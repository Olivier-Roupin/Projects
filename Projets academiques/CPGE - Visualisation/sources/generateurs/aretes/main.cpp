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
    string nomEntree("/home/olivier/programmes/fichiers/objets/");
    string nomSortie("/home/olivier/programmes/fichiers/objets/");

    nomEntree.append(nom);
    //nomEntree.append(".in");

    nomSortie.append(nom);
    nomSortie.append("are3");

    ouvrir(nomEntree, entree);
    sortie = aretes(entree);
    sauver(nomSortie,sortie);

    return 0;
}
