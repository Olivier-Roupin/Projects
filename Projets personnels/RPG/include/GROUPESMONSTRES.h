#ifndef GROUPESMONSTRES_H_INCLUDED
#define GROUPESMONSTRES_H_INCLUDED

#include <MONSTRES.h>

using namespace std;

for(int i = 0; i < NOMBRE_GROUPES_MONSTRES+1; i++)
{
    groupes_monstres[i] = 0;
}

flux.open("bdd/groupesmonstres.txt");

if(flux)
{
    int nombre(0);
    int nombre_monstres(0);
    int id(0);
    int X(0);
    int Y(0);

    flux >> nombre;
    for(int i(1); i < nombre+1; i++)
    {
        flux >> nombre_monstres;
        groupes_monstres[i] = new GroupeMonstres(i, nombre_monstres);
        for(int j(0); j < nombre_monstres; j++)
        {
            flux >> id;
            flux >> X;
            flux >> Y;
            groupes_monstres[i]->AjouterMonstres(monstres[id],X,Y);
        }
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // GROUPESMONSTRES_H_INCLUDED
