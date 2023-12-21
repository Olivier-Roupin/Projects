#ifndef MENU_MAGASIN_H_INCLUDED
#define MENU_MAGASIN_H_INCLUDED

#include <lib/Inventaire.h>
#include <lib/Equipe.h>
#include <lib/Magasin.h>
#include <Input.h>

int Magasins(Inventaire* inventaire, Equipe* equipe, Magasin* magasin,
             Input* input, unsigned int &Or);

#endif // MENU_MAGASIN_H_INCLUDED
