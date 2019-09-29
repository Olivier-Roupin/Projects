#ifndef EFFETS_H_INCLUDED
#define EFFETS_H_INCLUDED

#include <SCRIPTS.h>

using namespace std;

for(int i(0); i < NOMBRE_EFFETS+1; i++)
{
    effets[i] = 0;
}

flux.open("bdd/effets.txt");
if(flux)
{
    int nombre(0);
    int in[NOMBRE_IN_EFFET];

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        for(int n(0); n < NOMBRE_IN_EFFET; n++)
        {
            flux >> in[n];
        }
        effets[i] = new Effet(scripts[in[IN_EFFET_ID_SCRIPT]],in[IN_EFFET_ELEMENT],in[IN_EFFET_DISPONIBILITE],\
                              in[IN_EFFET_CHOIX_CIBLE],in[IN_EFFET_CHOIX_FACTION],in[IN_EFFET_CHOIX_QUANTITE],\
                              in[IN_EFFET_DEFAUT_CIBLE],in[IN_EFFET_DEFAUT_FACTION],in[IN_EFFET_DEFAUT_QUANTITE]);
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // EFFETS_H_INCLUDED
