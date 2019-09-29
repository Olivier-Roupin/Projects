#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include "Donnees.h"

#define NOMBRECRITERES 4

int ouvrir(std::string nom, Donnees* donnees);
int sauver(std::string nom, Donnees* donnees);

#endif // FICHIER_H_INCLUDED
