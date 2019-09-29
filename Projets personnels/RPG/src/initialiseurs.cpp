#include "initialiseurs.h"

using namespace std;


Effet* effets[NOMBRE_EFFETS+1];
Capacite* capacites[NOMBRE_CAPACITES+1];
Objet* objets[NOMBRE_OBJETS+1];
Evenement* evenements[NOMBRE_EVENEMENTS+1];
Carte* cartes[NOMBRE_CARTES+1];
Monstre* monstres[NOMBRE_MONSTRES+1];
GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
Heros* heross[NOMBRE_HEROS+1];
Tileset* tilesets[NOMBRE_TILESETS+1];
Script* scripts[NOMBRE_SCRIPTS+1];
Magasin* magasins[NOMBRE_MAGASINS+1];
Alteration* alterations[NOMBRE_ALTERATIONS+1];

void initialiser()
{
#include <EFFETS.h>
#include <OBJETS.h>
#include <MAGASINS.h>
#include <HEROSS.h>
#include <GROUPESMONSTRES.h>
#include <CARTES.h>
#include <CAPACITES.h>
#include <ALTERATIONS.h>
#include <GRAPHISMES.h>
}
