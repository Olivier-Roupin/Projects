#ifndef GROUPESMONSTRES_H_INCLUDED
#define GROUPESMONSTRES_H_INCLUDED

for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i)
    groupes_monstres[i] = 0;

if ((taille = PreparerASCII(BDD_GROUPES))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_GROUPES, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Groupes monstres : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        groupes_monstres[i] = new GroupeMonstres(i);
        groupes_monstres[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        groupes_monstres[i]->Ecrire(str);
        printf("%s\\0", str);
#endif //PRINTIN
    }
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir groupesmonstres.txt en lecture\n");
#endif //PRINTIN

#endif // GROUPESMONSTRES_H_INCLUDED
