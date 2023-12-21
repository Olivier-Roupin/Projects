#ifndef EFFETS_H_INCLUDED
#define EFFETS_H_INCLUDED

for (i = 0; i < NOMBRE_EFFETS+1; ++i)
    effets[i] = 0;

#ifdef PRINTIN
    nombre = 4;
    printf("Effets : %d\n", nombre);
#endif //PRINTIN
    effets[1] = new Effet(1, scripts[ 2], 1, false, true, true,  true, false,  true, false);
    effets[2] = new Effet(2, scripts[13], 6, false, true, true, false, false, false, false);
    effets[3] = new Effet(3, scripts[16], 7, false, true, true, false, false,  true, false);
    effets[4] = new Effet(4, scripts[17], 7, false, true, true, false, false,  true, false);
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        effets[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // EFFETS_H_INCLUDED
