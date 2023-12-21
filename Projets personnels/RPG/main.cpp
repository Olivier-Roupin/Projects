#include "CMakeConfig.h"

#include <lib/Equipable.h>
#include <lib/Utilisable.h>
#include <scenes/Ecran_titre.h> //Ecran_titre
#include <scenes/Menu_Nom.h> //ChoixNom
#include <scenes/Terrain.h> //Terrain

// #define PRINTIN //afficher la lecture des fichiers
#include <moteur_graphique.h> //horloge
#include <fichierES.h>
#include <cstdlib> // srand

#ifdef PRINTIN
#include <cstdio>  // printf
#define MAX_TAILLE_DATA 8192
#endif //PRINTIN

#ifdef EXPORTOUT
#define MAX_TAILLE_DATA 8192
#endif //EXPORTOUT

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
#ifdef PRINTIN
        printf("%s Version %d.%d\n", argv[0], JeuOne_VERSION_MAJOR,
                                              JeuOne_VERSION_MINOR);
#endif //PRINTIN
        return 1;
    }
#ifdef PRINTIN
    char str[MAX_TAILLE_DATA*2];
#endif //PRINTIN
    allumerEcran("JeuOne");
    //changePleinEcran(false);
    unsigned int i, nombre;
    char* fbuf = 0;
    unsigned int taille = 0;
#include <bdd/GRAPHISMES.h>
#include <bdd/SCRIPTS.h>
#include <bdd/EFFETS.h>
#include <bdd/OBJETS.h>
#include <bdd/MAGASINS.h>
#include <bdd/HEROSS.h>
#include <bdd/MONSTRES.h>
#include <bdd/GROUPESMONSTRES.h>
#include <bdd/TILESETS.h>
#include <bdd/EVENEMENTS.h>
#include <bdd/CARTES.h>
#include <bdd/CAPACITES.h>
#include <bdd/ALTERATIONS.h>
    int choix = 0;
    do {
        Input input;
        srand(horloge());
        choix = Ecran_titre(&input);
        if (choix != QUITTER) {
            Partie partie(&input);
            ChargerPartie(choix, partie);
            partie.SetTemps(partie.GetTemps() - horloge());
            if (partie.GetEquipe()) {
                if (choix == NOUVELLE_PARTIE && partie.GetEquipe()->GetHeros(0))
                    ChoixNom(partie.GetEquipe()->GetHeros(0),partie.GetInput());
            }
            Terrain(&partie);
        }
    } while (choix != QUITTER);
#ifdef EXPORTOUT
    char str2[MAX_TAILLE_DATA*2];
    char secteur[2048];
    char* p_secteur;
#endif //EXPORTOUT
#include <bdd/ALTERATIONS_D.h>
#include <bdd/MAGASINS_D.h>
#include <bdd/HEROSS_D.h>
#include <bdd/CAPACITES_D.h>
#include <bdd/EFFETS_D.h>
#include <bdd/CARTES_D.h> // doit être avant Tileset et Evenement
#include <bdd/TILESETS_D.h>
#include <bdd/EVENEMENTS_D.h> // doit être avant Script
#include <bdd/SCRIPTS_D.h>
#include <bdd/GROUPESMONSTRES_D.h> // doit être avant Monstre
#include <bdd/MONSTRES_D.h>
#include <bdd/OBJETS_D.h>

#ifdef PRINTIN
    printf("On quitte\n");
#endif //PRINTIN
    return 0;
}
