#ifndef HEROSS_D_H_INCLUDED
#define HEROSS_D_H_INCLUDED

#include <lib/Heros.h>

nombre = 0;
for (i = 0; i < NOMBRE_HEROS+1; ++i)
    if (heross[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/heros.dat", nombre);
for (i = 0; i < NOMBRE_HEROS+1; ++i) {
    if (heross[i]) {
        if (&p_secteur[heross[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/heros.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = heross[i]->EcrireD(p_secteur);
    }
    delete heross[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/heros.dat", secteur, p_secteur);

#endif // HEROSS_D_H_INCLUDED
