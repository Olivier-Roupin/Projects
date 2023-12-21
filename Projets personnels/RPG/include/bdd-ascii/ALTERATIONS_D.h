#ifndef ALTERATIONS_D_H_INCLUDED
#define ALTERATIONS_D_H_INCLUDED

#include <lib/Alteration.h>

nombre = 0;
for (i = 0; i < NOMBRE_ALTERATIONS+1; ++i)
    if (alterations[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/alterations.dat", nombre);
for (i = 0; i < NOMBRE_ALTERATIONS+1; ++i) {
    if (alterations[i]) {
        if (&p_secteur[alterations[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/alterations.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = alterations[i]->EcrireD(p_secteur);
    }
    delete alterations[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/alterations.dat", secteur, p_secteur);

#endif // ALTERATIONS_D_H_INCLUDED
