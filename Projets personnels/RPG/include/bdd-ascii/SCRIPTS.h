#ifndef SCRIPTS_H_INCLUDED
#define SCRIPTS_H_INCLUDED

scripts[0] = 0;
for (i = 1; i < 19+1; ++i)
    scripts[i] = new Script(i, 0, 0);
for (; i < NOMBRE_SCRIPTS+1; ++i)
    scripts[i] = 0;

#endif // SCRIPTS_H_INCLUDED