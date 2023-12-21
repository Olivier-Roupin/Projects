#ifndef EFFETS_D_H_INCLUDED
#define EFFETS_D_H_INCLUDED

#include <lib/Effet.h>

nombre = 0;
for (i = 0; i < NOMBRE_EFFETS+1; ++i)
    if (effets[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/effets.dat", nombre);
for (i = 0; i < NOMBRE_EFFETS+1; ++i) {
    if (effets[i]) {
        if (&p_secteur[effets[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/effets.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = effets[i]->EcrireD(p_secteur);
    }
    delete effets[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/effets.dat", secteur, p_secteur);

#endif // EFFETS_D_H_INCLUDED
