#ifndef ALTERATIONS_D_H_INCLUDED
#define ALTERATIONS_D_H_INCLUDED

// #include <lib/Alteration.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_ALTERATIONS+1; ++i)
    if (alterations[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/alterations2.txt", nombre);
fichier_ecrireb("beta/bdd/alterations2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_ALTERATIONS+1; ++i) {
#ifdef EXPORTOUT
    if (alterations[i]) {
        fichier_ajouter("beta/bdd/alterations2.txt", "\n");
        alterations[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/alterations2.txt", str2);

        if (&p_secteur[alterations[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/alterations2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = alterations[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete alterations[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/alterations2.txt",
    "\nnom id_script postCombat postDeces priorite id_script_terrain");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/alterations2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // ALTERATIONS_D_H_INCLUDED
