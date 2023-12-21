#ifndef ALTERATIONS_H_INCLUDED
#define ALTERATIONS_H_INCLUDED

for (i = 0; i < NOMBRE_ALTERATIONS+1; ++i)
    alterations[i] = 0;

if ((taille = PreparerASCII(BDD_ALTERATIONS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_ALTERATIONS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Alterations : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        alterations[i] = new Alteration(i);
        alterations[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        alterations[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir alterations.txt en lecture\n");
#endif //PRINTIN

#endif // ALTERATIONS_H_INCLUDED
