#ifndef CARTES_D_H_INCLUDED
#define CARTES_D_H_INCLUDED

#include <lib/Carte.h>

nombre = 0;
for (i = 0; i < NOMBRE_CARTES+1; ++i)
    if (cartes[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/cartes.dat", nombre);
for (i = 0; i < NOMBRE_CARTES+1; ++i) {
    if (cartes[i]) {
        if (&p_secteur[cartes[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/cartes.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = cartes[i]->EcrireD(p_secteur);
        delete cartes[i];
    }
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/cartes.dat", secteur, p_secteur);

#endif // CARTES_D_H_INCLUDED
