#ifndef GRAPHISMES_H_INCLUDED
#define GRAPHISMES_H_INCLUDED

#include <moteur_graphique.h>

ChargerPage(PAGE_POLICE,   "graphics/page_police256.gif"  , 0x00, 0xFF, 0x00);
ChargerPage(PAGE_TUILES,   "graphics/page_tuiles256.gif"  , 0x00, 0xFF, 0x00);
ChargerPage(PAGE_SPRITES,  "graphics/page_sprites256.gif" , 0x00, 0xFF, 0x00);
ChargerPage(PAGE_HEROS,    "graphics/page_heros256.gif"   , 0x00, 0xFF, 0x00);
ChargerPage(PAGE_MONSTRES, "graphics/page_monstres256.gif", 0x00, 0xFF, 0x00);

// ChargerPage(PAGE_POLICE,   "\\POLICE.TIM;1"  , 0x00, 0xFF, 0x00);
// ChargerPage(PAGE_TUILES,   "\\TUILES.TIM;1"  , 0x00, 0xFF, 0x00);
// ChargerPage(PAGE_SPRITES,  "\\SPRITES.TIM;1" , 0x00, 0xFF, 0x00);
// ChargerPage(PAGE_HEROS,    "\\HEROS.TIM;1"   , 0x00, 0xFF, 0x00);
// ChargerPage(PAGE_MONSTRES, "\\MONSTRES.TIM;1", 0x00, 0xFF, 0x00);

#endif // GRAPHISMES_H_INCLUDED
