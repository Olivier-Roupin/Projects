#ifndef EFFETS_D_H_INCLUDED
#define EFFETS_D_H_INCLUDED

// #include <lib/Effet.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_EFFETS+1; ++i)
    if (effets[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/effets2.txt", nombre);
fichier_ecrireb("beta/bdd/effets2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_EFFETS+1; ++i) {
#ifdef EXPORTOUT
    if (effets[i]) {
        fichier_ajouter("beta/bdd/effets2.txt", "\n");
        effets[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/effets2.txt", str2);

        if (&p_secteur[effets[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/effets2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = effets[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete effets[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/effets2.txt",
    "\nid_script element disponibilite  ChoixCible ChoixFaction ChoixQuantite  DefautCible DefautFaction DefautQuantite");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/effets2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // EFFETS_D_H_INCLUDED
