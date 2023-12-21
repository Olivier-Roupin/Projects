#ifndef CAPACITES_D_H_INCLUDED
#define CAPACITES_D_H_INCLUDED

// #include <lib/Capacite.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_CAPACITES+1; ++i)
    if (capacites[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/capacites2.txt", nombre);
fichier_ecrireb("beta/bdd/capacites2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_CAPACITES+1; ++i) {
#ifdef EXPORTOUT
    if (capacites[i]) {
        fichier_ajouter("beta/bdd/capacites2.txt", "\n");
        capacites[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/capacites2.txt", str2);

        if (&p_secteur[capacites[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/capacites2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = capacites[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete capacites[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/capacites2.txt",
    "\nnom description  coutmagie coutmagiep coutvie coutviep  id_effet");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/capacites2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // CAPACITES_D_H_INCLUDED
