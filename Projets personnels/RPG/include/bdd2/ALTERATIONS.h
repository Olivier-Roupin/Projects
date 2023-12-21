#ifndef ALTERATIONS_H_INCLUDED
#define ALTERATIONS_H_INCLUDED

for (i = 0; i < NOMBRE_ALTERATIONS+1; ++i)
    alterations[i] = 0;

#ifdef PRINTIN
    nombre = 2;
    printf("Alterations : %d\n", nombre);
#endif //PRINTIN
    alterations[1] = new Alteration(1,  "Poison", scripts[11], false, false, 1);
    alterations[2] = new Alteration(2, "Toxines", scripts[11],  true, false, 2, scripts[19]);
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        alterations[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // ALTERATIONS_H_INCLUDED
