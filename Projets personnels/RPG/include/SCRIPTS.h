#ifndef SCRIPTS_H_INCLUDED
#define SCRIPTS_H_INCLUDED

//#include <FONCTIONS.h>

using namespace std;

extern PtrFonction fonctions[];

for(int i = 0; i < NOMBRE_SCRIPTS+1; i++)
{
    scripts[i] = 0;
}

scripts[1] = new Script(fonctions[1],0);
scripts[2] = new Script(fonctions[2],0);
scripts[3] = new Script(fonctions[3],0);
scripts[4] = new Script(fonctions[4],0);
scripts[5] = new Script(fonctions[5],0);
scripts[6] = new Script(fonctions[6],0);
scripts[7] = new Script(fonctions[7],0);
scripts[8] = new Script(fonctions[8],0);
scripts[9] = new Script(fonctions[9],0);
scripts[10] = new Script(fonctions[10],0);
scripts[11] = new Script(fonctions[11],0);
scripts[12] = new Script(fonctions[12],0);
scripts[13] = new Script(fonctions[13],0);


#endif // SCRIPTS_H_INCLUDED
