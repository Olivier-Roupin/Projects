#ifndef GROUPESMONSTRES_H_INCLUDED
#define GROUPESMONSTRES_H_INCLUDED

for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i)
    groupes_monstres[i] = 0;

#ifdef PRINTIN
    nombre = 4;
    printf("Groupes monstres : %d\n", nombre);
#endif //PRINTIN
{
    int j = 0;
    groupes_monstres[1] = new GroupeMonstres(1);
    groupes_monstres[1]->Lire(j,"2 1 5 10 1 15 15");
    j = 0;
    groupes_monstres[2] = new GroupeMonstres(2);
    groupes_monstres[2]->Lire(j,"5 1 5 10 1 5 15 1 5 5 2 15 12 2 15 17");
    j = 0;
    groupes_monstres[3] = new GroupeMonstres(3);
    groupes_monstres[3]->Lire(j,"3 2 10 15 2 5 10 2 15 10");
    j = 0;
    groupes_monstres[4] = new GroupeMonstres(4);
    groupes_monstres[4]->Lire(j,"1 3 8 8");
}
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        groupes_monstres[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // GROUPESMONSTRES_H_INCLUDED
