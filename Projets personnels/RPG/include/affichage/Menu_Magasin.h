#ifndef MENU_MAGASIN_AFFICHAGE_H_INCLUDED
#define MENU_MAGASIN_AFFICHAGE_H_INCLUDED

#include <lib/Inventaire.h>
#include <lib/Equipe.h>
#include <lib/Magasin.h>

#define MAGASIN_ACHETER 0
#define MAGASIN_VENDRE  1
#define MAGASIN_QUITTER 2

void AfficherMagasinsAnimation(char animation);
void AfficherMagasins(char choix, unsigned int Or, bool choisi = false);
void AfficherMagasins_AcheterAnimation(char animation);
void AfficherMagasins_Acheter(const Magasin* magasin, const Inventaire* inventaire,
                              const Equipe* equipe, char choix, unsigned int Or);
void AfficherMagasins_VendreAnimation(char animation);
void AfficherMagasins_Vendre(const Inventaire* inventaire,
                             const Equipe* equipe, int choix);

#endif // MENU_MAGASIN_AFFICHAGE_H_INCLUDED
