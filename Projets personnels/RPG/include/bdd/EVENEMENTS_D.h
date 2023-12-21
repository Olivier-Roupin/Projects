#ifndef EVENEMENTS_D_H_INCLUDED
#define EVENEMENTS_D_H_INCLUDED

// #include <lib/Evenement.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_EVENEMENTS+1; i++)
    if (evenements[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/evenements2.txt", nombre);
fichier_ecrireb("beta/bdd/evenements2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_EVENEMENTS+1; i++) {
#ifdef EXPORTOUT
    if (evenements[i]) {
        fichier_ajouter("beta/bdd/evenements2.txt", "\n");
        evenements[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/evenements2.txt", str2);

        if (&p_secteur[evenements[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/evenements2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = evenements[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete evenements[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/evenements2.txt",
    "\nimage nombre_scripts  script...");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/evenements2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // EVENEMENTS_D_H_INCLUDED
