#ifndef CAPACITES_H_INCLUDED
#define CAPACITES_H_INCLUDED

for (i = 0; i < NOMBRE_CAPACITES+1; ++i)
    capacites[i] = 0;

if ((taille = PreparerASCII(BDD_CAPACITES))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_CAPACITES, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Capacites : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        capacites[i] = new Capacite(i);
        capacites[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        capacites[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir capacites.txt en lecture\n");
#endif //PRINTIN

#endif // CAPACITES_H_INCLUDED
