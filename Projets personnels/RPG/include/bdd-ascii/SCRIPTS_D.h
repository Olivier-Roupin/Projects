#ifndef SCRIPTS_D_H_INCLUDED
#define SCRIPTS_D_H_INCLUDED

#include <lib/Script.h>

for (i = 0; i < NOMBRE_SCRIPTS+1; i++)
    if (scripts[i])
        delete scripts[i];

#endif // SCRIPTS_D_H_INCLUDED
