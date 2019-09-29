#ifndef TILESETS_H_INCLUDED
#define TILESETS_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_TILESETS+1; i++)
{
    tilesets[i] = 0;
}

flux.open("bdd/tilesets.txt");

if(flux)
{
    int nombre(0);
    int nb_tiles(0);
    string image("");
    int traversable(0);

    flux >> nombre;
    for(int i(1); i < nombre+1; i++)
    {
        flux >> nb_tiles;
        tilesets[i] = new Tileset(i, nb_tiles);
        for(int j(0); j < tilesets[i]->GetNombre(); j++)
        {
            flux >> image;
            flux >> traversable;
            tilesets[i]->SetImage(image, j);
            tilesets[i]->SetTraversable(traversable, j);
        }
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // TILESETS_H_INCLUDED
