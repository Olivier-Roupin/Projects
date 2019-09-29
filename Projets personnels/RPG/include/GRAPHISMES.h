#ifndef GRAPHISMES_H_INCLUDED
#define GRAPHISMES_H_INCLUDED

#include <moteur_graphique.h>

using namespace std;

for(int i = 0; i < NOMBRE_TEXTURES; i++)
{
    textures[i] = 0;
}

flux.open("bdd/graphismes.txt");
if(flux)
{
    string fichier("_");
    for(int i(0); i < NOMBRE_TEXTURES; i++)
    {
        flux >> fichier;
        textures[i] = ChargerImage((char*)fichier.c_str());
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

for(int i(0); i < NOMBRE_TEXTURES*TAILLE_TEXTURE; i++)
{
    elements_graphiques[i] = new ElementGraphique(textures[i/TAILLE_TEXTURE], (i%TAILLE_TEXTURE)%LARGEUR_TEXTURE, (i%TAILLE_TEXTURE)/LARGEUR_TEXTURE);
}

#endif // GRAPHISMES_H_INCLUDED
