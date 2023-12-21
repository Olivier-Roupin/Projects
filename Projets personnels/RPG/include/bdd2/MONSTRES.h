#ifndef MONSTRES_H_INCLUDED
#define MONSTRES_H_INCLUDED

for (i = 0; i < NOMBRE_MONSTRES+1; ++i)
    monstres[i] = 0;

#ifdef PRINTIN
    nombre = 3;
    printf("Monstres : %d\n", nombre);
#endif //PRINTIN
{
    int j = 0;
    monstres[1] = new Monstre(1);
    monstres[1]->Lire(j,"Goblin 40 0 40 4 24 0 0 10 5 90 50 0 50 2 1 0 100 4 0 0");
    j = 0;
    monstres[2] = new Monstre(2);
    monstres[2]->Lire(j,"Lapin 20 0 20 3 15 0 0 12 7 90 70 0 45 1 0 0 80 4 0 0");
    j = 0;
    monstres[3] = new Monstre(3);
    monstres[3]->Lire(j,"Soldat 500 0 500 8 24 0 0 10 6 95 40 0 150 5 3 0 500 4 7 2");
}
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        monstres[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // MONSTRES_H_INCLUDED
