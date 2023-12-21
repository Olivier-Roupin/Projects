#ifndef OBJETS_D_H_INCLUDED
#define OBJETS_D_H_INCLUDED

#include <lib/Objet.h>

nombre = 0;
for (i = 0; i < NOMBRE_OBJETS+1; ++i)
    if (objets[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrireb("bdd/objets.dat", nombre);
for (i = 0; i < NOMBRE_OBJETS+1; ++i) {
    if (objets[i]) {
        if (&p_secteur[objets[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("bdd/objets.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = objets[i]->EcrireD(p_secteur);
    }
    delete objets[i];
}
if (p_secteur != secteur)
    fichier_ajouterb("bdd/objets.dat", secteur, p_secteur);

#endif // OBJETS_D_H_INCLUDED
