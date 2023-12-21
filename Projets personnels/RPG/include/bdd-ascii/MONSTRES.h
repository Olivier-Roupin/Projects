#ifndef MONSTRES_H_INCLUDED
#define MONSTRES_H_INCLUDED

for (i = 0; i < NOMBRE_MONSTRES+1; ++i)
    monstres[i] = 0;

if ((taille = PreparerASCII(BDD_MONSTRES))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_MONSTRES, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Monstres : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        monstres[i] = new Monstre(i);
        monstres[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        monstres[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir monstres.txt en lecture\n");
#endif //PRINTIN

#endif // MONSTRES_H_INCLUDED
