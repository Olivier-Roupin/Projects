#ifndef MONSTRES_D_H_INCLUDED
#define MONSTRES_D_H_INCLUDED

#include <lib/Monstre.h>

nombre = 0;
for (i = 0; i < NOMBRE_MONSTRES+1; ++i)
    if (monstres[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/monstres.dat", nombre);
for (i = 0; i < NOMBRE_MONSTRES+1; ++i) {
    if (monstres[i]) {
        if (&p_secteur[monstres[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/monstres.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = monstres[i]->EcrireD(p_secteur);
    }
    delete monstres[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/monstres.dat", secteur, p_secteur);

#endif // MONSTRES_D_H_INCLUDED
