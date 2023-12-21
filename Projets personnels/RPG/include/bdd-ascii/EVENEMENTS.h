#ifndef EVENEMENTS_H_INCLUDED
#define EVENEMENTS_H_INCLUDED

for (i = 0; i < NOMBRE_EVENEMENTS+1; ++i)
    evenements[i] = 0;

if ((taille = PreparerASCII(BDD_EVENEMENTS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_EVENEMENTS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Evenements : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        evenements[i] = new Evenement(i);
        evenements[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        evenements[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir evenements.txt en lecture\n");
#endif //PRINTIN

#endif // EVENEMENTS_H_INCLUDED
