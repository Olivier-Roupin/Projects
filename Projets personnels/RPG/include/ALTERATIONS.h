#ifndef ALTERATIONS_H_INCLUDED
#define ALTERATIONS_H_INCLUDED

using namespace std;

for(int i(0); i < NOMBRE_ALTERATIONS+1; i++)
{
    alterations[i] = 0;
}

flux.open("bdd/alterations.txt");
if(flux)
{
    int nombre(0);
    string nom("");
    int id_script(0);
    bool postCombat(false);
    bool postDeces(false);
    int priorite(0);

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        flux >> nom;
        flux >> id_script;
        flux >> postCombat;
        flux >> postDeces;
        flux >> priorite;
        alterations[i] = new Alteration(i,nom,scripts[id_script],postCombat,postDeces,priorite);
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // ALTERATIONS_H_INCLUDED
