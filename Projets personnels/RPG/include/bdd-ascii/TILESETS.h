#ifndef TILESETS_H_INCLUDED
#define TILESETS_H_INCLUDED

for (i = 0; i < NOMBRE_TILESETS+1; ++i)
    tilesets[i] = 0;

if ((taille = PreparerASCII(BDD_TILESETS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_TILESETS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Tilesets : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        tilesets[i] = new Tileset(i);
        tilesets[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        tilesets[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir tilesets.txt en lecture\n");
#endif //PRINTIN

#endif // TILESETS_H_INCLUDED
