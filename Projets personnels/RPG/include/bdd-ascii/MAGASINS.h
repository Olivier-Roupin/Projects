#ifndef MAGASINS_H_INCLUDED
#define MAGASINS_H_INCLUDED

for (i = 0; i < NOMBRE_MAGASINS+1; ++i)
    magasins[i] = 0;

if ((taille = PreparerASCII(BDD_MAGASINS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_MAGASINS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Magasins : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        magasins[i] = new Magasin(i);
        magasins[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        magasins[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir magasins.txt en lecture\n");
#endif //PRINTIN

#endif // MAGASINS_H_INCLUDED
