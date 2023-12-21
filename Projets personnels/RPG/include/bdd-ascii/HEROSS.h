#ifndef HEROSS_H_INCLUDED
#define HEROSS_H_INCLUDED

for (i = 0; i < NOMBRE_HEROS+1; ++i)
    heross[i] = 0;

if ((taille = PreparerASCII(BDD_HEROS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_HEROS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Heros : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        heross[i] = new Heros(i);
        heross[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        heross[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir heros.txt en lecture\n");
#endif //PRINTIN

#endif // HEROSS_H_INCLUDED
