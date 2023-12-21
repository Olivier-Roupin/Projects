#ifndef MAGASINS_D_H_INCLUDED
#define MAGASINS_D_H_INCLUDED

// #include <lib/Magasin.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_MAGASINS+1; ++i)
    if (magasins[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/magasins2.txt", nombre);
fichier_ecrireb("beta/bdd/magasins2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_MAGASINS+1; ++i) {
#ifdef EXPORTOUT
    if (magasins[i]) {
        fichier_ajouter("beta/bdd/magasins2.txt", "\n");
        magasins[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/magasins2.txt", str2);

        if (&p_secteur[magasins[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/magasins2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = magasins[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete magasins[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/magasins2.txt",
    "\nnombre_objets id...");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/magasins2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // MAGASINS_D_H_INCLUDED
