#ifndef MAGASINS_D_H_INCLUDED
#define MAGASINS_D_H_INCLUDED

#include <lib/Magasin.h>

nombre = 0;
for (i = 0; i < NOMBRE_MAGASINS+1; ++i)
    if (magasins[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/magasins.dat", nombre);
for (i = 0; i < NOMBRE_MAGASINS+1; ++i) {
    if (magasins[i]) {
        if (&p_secteur[magasins[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/magasins.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = magasins[i]->EcrireD(p_secteur);
    }
    delete magasins[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/magasins.dat", secteur, p_secteur);

#endif // MAGASINS_D_H_INCLUDED
