#ifndef EVENEMENTS_H_INCLUDED
#define EVENEMENTS_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_EVENEMENTS+1; i++)
{
    evenements[i] = 0;
}

flux.open("bdd/evenements.txt");

if(flux)
{
    int nombre(0);
    int nombre_scripts(0);
    int script(0);
    string image("_");

    flux >> nombre;
    for(int i(1); i < nombre+1; i++)
    {
        flux >> image;
        flux >> nombre_scripts;
        evenements[i] = new Evenement(i,nombre_scripts,image);
        for(int j(0); j < evenements[i]->GetNombre(); j++)
        {
            flux >> script;
            evenements[i]->SetScripts(scripts[script],j);
        }
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // EVENEMENTS_H_INCLUDED
