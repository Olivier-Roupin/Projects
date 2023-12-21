#ifndef CARTES_D_H_INCLUDED
#define CARTES_D_H_INCLUDED

// #include <lib/Carte.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_CARTES+1; ++i)
    if (cartes[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/cartes2.txt", nombre);
fichier_ecrireb("beta/bdd/cartes2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_CARTES+1; ++i) {
    if (cartes[i]) {
#ifdef EXPORTOUT
        fichier_ajouter("beta/bdd/cartes2.txt", "\n");
        char longue_str[MAX_TAILLE_DATA*64];
        cartes[i]->Ecrire(longue_str);
        fichier_ajouter("beta/bdd/cartes2.txt", longue_str);

        if (&p_secteur[cartes[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/cartes2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = cartes[i]->EcrireD(p_secteur);
#endif //EXPORTOUT
        delete cartes[i];
    }
    // delete cartes[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/cartes2.txt",
    "\nnom fond largeur hauteur répétition id_tileset\n\
nombre_evenements nombre_rencontres\n\
evenement X Y Z traversable\n\
:\n\
nombre_groupes groupes...\n\
:\n\
tuile sol...\n\
:\n\
tuile milieu...\n\
:\n\
tuile haut...\n\
:\n\
tuile monstres...\n\
:");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/cartes2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // CARTES_D_H_INCLUDED
