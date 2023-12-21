#ifndef TILESETS_D_H_INCLUDED
#define TILESETS_D_H_INCLUDED

#include <lib/Tileset.h>

nombre = 0;
for (i = 0; i < NOMBRE_TILESETS+1; ++i)
    if (tilesets[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/tilesets.dat", nombre);
for (i = 0; i < NOMBRE_TILESETS+1; ++i) {
    if (tilesets[i]) {
        if (&p_secteur[tilesets[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/tilesets.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = tilesets[i]->EcrireD(p_secteur);
    }
    delete tilesets[i];
}
if (p_secteur != secteur) // quelque chose à écrire ?
    fichier_ajouterb("bdd/tilesets.dat", secteur, p_secteur);

#endif // TILESETS_D_H_INCLUDED
