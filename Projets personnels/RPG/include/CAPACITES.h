#ifndef CAPACITES_H_INCLUDED
#define CAPACITES_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_CAPACITES+1; i++)
{
    capacites[i] = 0;
}

flux.open("bdd/capacites.txt");
if(flux)
{
    int nombre(0);
    string nom("_");
    string description("_");

    int in[NOMBRE_IN_CAPACITE];

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        flux >> nom;
        flux >> description;
        for(int j(0); j < NOMBRE_IN_CAPACITE; j++)
        {
            flux >> in[j];
        }
        capacites[i] = new Capacite(i,nom,description,in[0],in[1],in[2],in[3],effets[in[4]]);
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // CAPACITES_H_INCLUDED
