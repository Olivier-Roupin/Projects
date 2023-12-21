#ifndef EVENEMENTS_D_H_INCLUDED
#define EVENEMENTS_D_H_INCLUDED

#include <lib/Evenement.h>

nombre = 0;
for (i = 0; i < NOMBRE_EVENEMENTS+1; i++)
    if (evenements[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/evenements.dat", nombre);
for (i = 0; i < NOMBRE_EVENEMENTS+1; i++) {
    if (evenements[i]) {
        if (&p_secteur[evenements[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/evenements.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = evenements[i]->EcrireD(p_secteur);
    }
    delete evenements[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/evenements.dat", secteur, p_secteur);

#endif // EVENEMENTS_D_H_INCLUDED
