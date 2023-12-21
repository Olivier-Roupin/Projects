#ifndef OBJETS_D_H_INCLUDED
#define OBJETS_D_H_INCLUDED

// #include <lib/Objet.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_OBJETS+1; ++i)
    if (objets[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/objets2.txt", nombre);
fichier_ecrireb("beta/bdd/objets2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_OBJETS+1; ++i) {
#ifdef EXPORTOUT
    if (objets[i]) {
        fichier_ajouter("beta/bdd/objets2.txt", "\n");
        objets[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/objets2.txt", str2);

        if (&p_secteur[objets[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/objets2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = objets[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete objets[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/objets2.txt",
    "\ntype nom prix description...\n\
...illimité id_effet\n\
...vie atkp defp magie atkm defm vit pre esq poids ratio element");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/objets2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // OBJETS_D_H_INCLUDED
