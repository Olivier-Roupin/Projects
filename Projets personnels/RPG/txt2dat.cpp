#include <lib/Equipable.h>
#include <lib/Utilisable.h>
#include <lib/Partie.h>

#define EXPORTOUT
#include <fichierES.h>

#define PRINTIN //afficher la lecture des fichiers
#include <cstdio>  // printf

#define MAX_TAILLE_DATA 8192

Effet*          effets[NOMBRE_EFFETS+1];
Capacite*       capacites[NOMBRE_CAPACITES+1];
Objet*          objets[NOMBRE_OBJETS+1];
Evenement*      evenements[NOMBRE_EVENEMENTS+1];
Carte*          cartes[NOMBRE_CARTES+1];
Monstre*        monstres[NOMBRE_MONSTRES+1];
GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
Heros*          heross[NOMBRE_HEROS+1];
Tileset*        tilesets[NOMBRE_TILESETS+1];
Script*         scripts[NOMBRE_SCRIPTS+1];
Magasin*        magasins[NOMBRE_MAGASINS+1];
Alteration*     alterations[NOMBRE_ALTERATIONS+1];

int main(int argc, char *argv[]) {
    if (argc > 1) { //ce n'est pas normal
        printf("%s ne prend pas d'arguments\n", argv[0]);
        return 1;
    }
    char str[MAX_TAILLE_DATA*2];
    unsigned int i, nombre;
    char* fbuf = 0;
    unsigned int taille = 0;
#include <bdd-ascii/SCRIPTS.h>
#include <bdd-ascii/EFFETS.h>
#include <bdd-ascii/OBJETS.h>
#include <bdd-ascii/MAGASINS.h>
#include <bdd-ascii/HEROSS.h>
#include <bdd-ascii/MONSTRES.h>
#include <bdd-ascii/GROUPESMONSTRES.h>
#include <bdd-ascii/TILESETS.h>
#include <bdd-ascii/EVENEMENTS.h>
#include <bdd-ascii/CARTES.h>
#include <bdd-ascii/CAPACITES.h>
#include <bdd-ascii/ALTERATIONS.h>
    char secteur[2048];
    char* p_secteur;
#include <bdd-ascii/ALTERATIONS_D.h>
#include <bdd-ascii/MAGASINS_D.h>
#include <bdd-ascii/HEROSS_D.h>
#include <bdd-ascii/CAPACITES_D.h>
#include <bdd-ascii/CARTES_D.h> // doit être avant Tileset et Evenement
#include <bdd-ascii/TILESETS_D.h>
#include <bdd-ascii/EVENEMENTS_D.h> // doit être avant Script
#include <bdd-ascii/GROUPESMONSTRES_D.h> // doit être avant Monstre
#include <bdd-ascii/MONSTRES_D.h>
#include <bdd-ascii/OBJETS_D.h>
#include <bdd-ascii/EFFETS_D.h>
#include <bdd-ascii/SCRIPTS_D.h>
    printf("Fini\n");
    return 0;
}
