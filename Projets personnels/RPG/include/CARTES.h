#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

#include <TILESETS.h>
#include <EVENEMENTS.h>

using namespace std;

for(int i = 0; i < NOMBRE_CARTES+1; i++)
{
    cartes[i] = 0;
}

flux.open("bdd/cartes.txt");

if(flux)
{
    int nombre(0);
    string nom("");
    string fond("");
    int evenement(0);
    int X(0);
    int Y(0);
    int Z(0);
    int tile(0);

    Rencontreset* rencontre;
    int nombre_rencontres(0);
    int nombre_groupes(0);
    int groupe(0);

    int in[NOMBRE_IN_CARTE];

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        flux >> nom;
        flux >> fond;
        for(int j(0); j < NOMBRE_IN_CARTE; j++)
        {
            flux >> in[j];
        }
        rencontre = 0;
        flux >> nombre_rencontres;
        if(nombre_rencontres)
        {
            rencontre = new Rencontreset(nombre_rencontres);
        }
        cartes[i] = new Carte(i, nom, in[IN_CARTE_LARGEUR], in[IN_CARTE_HAUTEUR], in[IN_CARTE_REPETITION],\
                              tilesets[in[IN_CARTE_ID_TILESET]], in[IN_CARTE_NOMBRE], rencontre, fond);
        for(int j(0); j < cartes[i]->GetNombre(); j++)
        {
            flux >> evenement;
            flux >> X;
            flux >> Y;
            flux >> Z;
            evenements[evenement]->SetX(X);
            evenements[evenement]->SetY(Y);
            evenements[evenement]->SetZ(Z);
            cartes[i]->SetEvenements(evenements[evenement],j);
        }
        if(cartes[i]->GetRencontreset()->GetNombre())
        {
            for(int j(1); j < cartes[i]->GetRencontreset()->GetNombre()+1; j++)
            {
                flux >> nombre_groupes;
                cartes[i]->GetRencontreset()->SetNombreGroupes(nombre_groupes, j);
                for(int k(0); k < cartes[i]->GetRencontreset()->GetNombreGroupes(j); k++)
                {
                    flux >> groupe;
                    cartes[i]->GetRencontreset()->SetGroupes(groupes_monstres[groupe],j,k);
                }
            }
        }
        for(int j(0); j < cartes[i]->GetTaille(); j++)
        {
            flux >> tile;
            cartes[i]->SetBas(tile, j);
        }
        for(int j(0); j < cartes[i]->GetTaille(); j++)
        {
            flux >> tile;
            cartes[i]->SetMoyen(tile, j);
        }
        for(int j(0); j < cartes[i]->GetTaille(); j++)
        {
            flux >> tile;
            cartes[i]->SetHaut(tile, j);
        }
        if(cartes[i]->GetRencontreset()->GetNombre())
        {
            for(int j(0); j < cartes[i]->GetTaille(); j++)
            {
                flux >> tile;
                cartes[i]->SetRencontres(tile, j);
            }
        }
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // CARTES_H_INCLUDED
