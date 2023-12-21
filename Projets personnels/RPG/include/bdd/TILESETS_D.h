#ifndef TILESETS_D_H_INCLUDED
#define TILESETS_D_H_INCLUDED

// #include <lib/Tileset.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_TILESETS+1; ++i)
    if (tilesets[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/tilesets2.txt", nombre);
fichier_ecrireb("beta/bdd/tilesets2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_TILESETS+1; ++i) {
#ifdef EXPORTOUT
    if (tilesets[i]) {
        fichier_ajouter("beta/bdd/tilesets2.txt", "\n");
        tilesets[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/tilesets2.txt", str2);

        if (&p_secteur[tilesets[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/tilesets2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = tilesets[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete tilesets[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/tilesets2.txt",
    "\nnombre\nimage traversable...");

// fichier_ecrireb("beta/bdd/tilesets2.dat", secteur, p_secteur);
 if (p_secteur != secteur) // quelque chose à écrire ?
    fichier_ajouterb("beta/bdd/tilesets2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // TILESETS_D_H_INCLUDED
