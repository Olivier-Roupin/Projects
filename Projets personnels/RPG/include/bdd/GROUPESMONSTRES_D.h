#ifndef GROUPESMONSTRES_D_H_INCLUDED
#define GROUPESMONSTRES_D_H_INCLUDED

// #include <lib/GroupeMonstres.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i)
    if (groupes_monstres[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/groupesmonstres2.txt", nombre);
fichier_ecrireb("beta/bdd/groupesmonstres2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i) {
#ifdef EXPORTOUT
    if (groupes_monstres[i]) {
        fichier_ajouter("beta/bdd/groupesmonstres2.txt", "\n");
        groupes_monstres[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/groupesmonstres2.txt", str2);

        if (&p_secteur[groupes_monstres[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/groupesmonstres2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = groupes_monstres[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete groupes_monstres[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/groupesmonstres2.txt",
    "\nnombre_monstres id X Y...");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/groupesmonstres2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // GROUPESMONSTRES_D_H_INCLUDED
