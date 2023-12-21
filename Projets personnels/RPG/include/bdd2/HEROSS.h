#ifndef HEROSS_H_INCLUDED
#define HEROSS_H_INCLUDED

for (i = 0; i < NOMBRE_HEROS+1; ++i)
    heross[i] = 0;

#ifdef PRINTIN
    nombre = 2;
    printf("Heros : %d\n", nombre);
#endif //PRINTIN
{
    int j = 0;
    heross[1] = new Heros(1);
    heross[1]->Lire(j, "Richard 99 49 99 4 5 49 10 10 20 50 50 0 0 1 0 0 0 0 0 0 0 0 0 0");
    j = 0;
    heross[2] = new Heros(2);
    heross[2]->Lire(j, "Johnny 49 99 49 6 3 99 15 15 20 50 50 0 0 1 0 0 0 0 0 0 0 0 0 0");
}
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        heross[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // HEROSS_H_INCLUDED
