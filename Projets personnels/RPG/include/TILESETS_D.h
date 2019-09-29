#ifndef TILESETS_D_H_INCLUDED
#define TILESETS_D_H_INCLUDED

#include <TILESETS.h>

for (int i = 1; i < NOMBRE_TILESETS+1; ++i)
{
    delete tilesets[i];
}

#endif // TILESETS_D_H_INCLUDED
