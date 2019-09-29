#ifndef INITIALISEURS_H_INCLUDED
#define INITIALISEURS_H_INCLUDED

#include <iostream>

//Test Scenes
#include <Equipable.h>
#include <Utilisable.h>
#include <Ecran_titre.h>
#include <Terrain.h>

#include <moteur_graphique.h>
//#include <BoiteTexte.h>
#include <Input.h>

#define NOMBRE_EFFETS 200
#define NOMBRE_CAPACITES 100
#define NOMBRE_OBJETS 100
#define NOMBRE_EVENEMENTS 1000
#define NOMBRE_CARTES 100
#define NOMBRE_MONSTRES 100
#define NOMBRE_GROUPES_MONSTRES 100
#define NOMBRE_HEROS 8
#define NOMBRE_TILESETS 100
#define NOMBRE_SCRIPTS 1000
#define NOMBRE_MAGASINS 50
#define NOMBRE_ALTERATIONS 20

extern Effet* effets[NOMBRE_EFFETS+1];
extern Capacite* capacites[NOMBRE_CAPACITES+1];
extern Objet* objets[NOMBRE_OBJETS+1];
extern Evenement* evenements[NOMBRE_EVENEMENTS+1];
extern Carte* cartes[NOMBRE_CARTES+1];
extern Monstre* monstres[NOMBRE_MONSTRES+1];
extern GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
extern Heros* heross[NOMBRE_HEROS+1];
extern Tileset* tilesets[NOMBRE_TILESETS+1];
extern Script* scripts[NOMBRE_SCRIPTS+1];
extern Magasin* magasins[NOMBRE_MAGASINS+1];
extern Alteration* alterations[NOMBRE_ALTERATIONS+1];

void initialiser();

#endif // INITIALISEURS_H_INCLUDED
