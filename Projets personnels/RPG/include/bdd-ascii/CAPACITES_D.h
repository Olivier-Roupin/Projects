#ifndef CAPACITES_D_H_INCLUDED
#define CAPACITES_D_H_INCLUDED

#include <lib/Capacite.h>

nombre = 0;
for (i = 0; i < NOMBRE_CAPACITES+1; ++i)
    if (capacites[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/capacites.dat", nombre);
for (i = 0; i < NOMBRE_CAPACITES+1; ++i) {
    if (capacites[i]) {
        if (&p_secteur[capacites[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/capacites.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = capacites[i]->EcrireD(p_secteur);
    }
    delete capacites[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/capacites.dat", secteur, p_secteur);

#endif // CAPACITES_D_H_INCLUDED
