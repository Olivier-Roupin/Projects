#ifndef MENU_MAGASIN_H_INCLUDED
#define MENU_MAGASIN_H_INCLUDED

#include <Menu_Objets.h>
#include <Magasin.h>

#define NOMBRE_CHOIX_MAGASIN 3

#define MAGASIN_ACHETER 0
#define MAGASIN_VENDRE 1
#define MAGASIN_QUITTER 2

int Magasins(Inventaire* inventaire, Equipe* equipe, Magasin* magasin, int &Or);
int Magasins_Acheter(Inventaire* inventaire, Magasin* magasin, int &Or);
int Magasins_Vendre(Inventaire* inventaire, Magasin* magasin, int &Or);

void AfficherMagasins(Inventaire* inventaire, int choix, int Or);
void AfficherMagasins_Acheter(Magasin* magasin, Inventaire* inventaire, int choix, int Or);
void AfficherMagasins_Vendre(Inventaire* inventaire, int choix, int Or);


#endif // MENU_MAGASIN_H_INCLUDED
