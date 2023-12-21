#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

for (i = 0; i < NOMBRE_CARTES+1; ++i)
    cartes[i] = 0;

if ((taille = PreparerASCII(BDD_CARTES))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_CARTES, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Cartes : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        cartes[i] = new Carte(i);
        cartes[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        char longue_str[MAX_TAILLE_DATA*64];
        cartes[i]->Ecrire(longue_str);
        printf("%s\\0", longue_str);
#endif //PRINTIN
    }
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir cartes.txt en lecture\n");
#endif //PRINTIN

#endif // CARTES_H_INCLUDED
