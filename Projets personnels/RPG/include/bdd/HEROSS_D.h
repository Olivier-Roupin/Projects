#ifndef HEROSS_D_H_INCLUDED
#define HEROSS_D_H_INCLUDED

// #include <lib/Heros.h>

#ifdef EXPORTOUT
nombre = 0;
for (i = 0; i < NOMBRE_HEROS+1; ++i)
    if (heross[i])
        ++nombre;
p_secteur = &secteur[0];

fichier_ecrire("beta/bdd/heros2.txt", nombre);
fichier_ecrireb("beta/bdd/heros2.dat", nombre);
#endif //EXPORTOUT
for (i = 0; i < NOMBRE_HEROS+1; ++i) {
#ifdef EXPORTOUT
    if (heross[i]) {
        fichier_ajouter("beta/bdd/heros2.txt", "\n");
        heross[i]->Ecrire(str2);
        fichier_ajouter("beta/bdd/heros2.txt", str2);

        if (&p_secteur[heross[i]->TailleD()] > &secteur[2048]) {
            fichier_ajouterb("beta/bdd/heros2.dat", secteur, p_secteur);
            p_secteur = &secteur[0];
        }
        p_secteur = heross[i]->EcrireD(p_secteur);
    }
#endif //EXPORTOUT
    delete heross[i];
}
#ifdef EXPORTOUT
fichier_ajouter("beta/bdd/heros2.txt",
    "\nNom  Vie Magie  VieMax AttaqueP DefenseP  MagieMax AttaqueM DefenseM  Vitesse Precision Esquive  Statut Experience Niveau  Force Intelligence Agilite Rang MAINGAUCHE MAINDROITE TETE CORPS ACCESSOIRE1 ACCESSOIRE2");
 if (p_secteur != secteur)
    fichier_ajouterb("beta/bdd/heros2.dat", secteur, p_secteur);
#endif //EXPORTOUT

#endif // HEROSS_D_H_INCLUDED
