#ifndef GROUPESMONSTRES_D_H_INCLUDED
#define GROUPESMONSTRES_D_H_INCLUDED

#include <lib/GroupeMonstres.h>

nombre = 0;
for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i)
    if (groupes_monstres[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/groupesmonstres.dat", nombre);
for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i) {
    if (groupes_monstres[i]) {
        if (&p_secteur[groupes_monstres[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/groupesmonstres.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = groupes_monstres[i]->EcrireD(p_secteur);
    }
    delete groupes_monstres[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/groupesmonstres.dat", secteur, p_secteur);

#endif // GROUPESMONSTRES_D_H_INCLUDED
