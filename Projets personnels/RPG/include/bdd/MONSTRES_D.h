#ifndef MONSTRES_D_H_INCLUDED
#define MONSTRES_D_H_INCLUDED

// #include <lib/Monstre.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_MONSTRES+1; ++i)
    if (monstres[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/monstres2.txt", nombre);
fichier_ecrireb("beta/bdd/monstres2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_MONSTRES+1; ++i) {
#ifdef EXPORTOUT
    if (monstres[i]) {
        fichier_ajouter("beta/bdd/monstres2.txt", "\n");
        monstres[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/monstres2.txt", str2);

        if (&p_secteur[monstres[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/monstres2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = monstres[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete monstres[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/monstres2.txt",
    "\nNom  Vie Magie  VieMax AttaqueP DefenseP  MagieMax AttaqueM DefenseM  Vitesse Precision Esquive  Statut Experience Niveau  Butin Objetporte Or  id_Script");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/monstres2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // MONSTRES_D_H_INCLUDED
