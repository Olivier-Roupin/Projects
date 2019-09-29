#ifndef MAGASINS_H_INCLUDED
#define MAGASINS_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_MAGASINS+1; i++)
{
    magasins[i] = 0;
}

flux.open("bdd/magasins.txt");

if(flux)
{
    int nombre(0);
    int nombre_objets(0);
    int id(0);

    flux >> nombre;
    for(int i(1); i < nombre+1; i++)
    {
        flux >> nombre_objets;
        magasins[i] = new Magasin(i, nombre_objets);
        for(int j(0); j < nombre_objets; j++)
        {
            flux >> id;
            magasins[i]->AjouterObjet(objets[id]);
        }
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // MAGASINS_H_INCLUDED
