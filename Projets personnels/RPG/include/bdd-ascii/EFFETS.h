#ifndef EFFETS_H_INCLUDED
#define EFFETS_H_INCLUDED

for (i = 0; i < NOMBRE_EFFETS+1; ++i)
    effets[i] = 0;

if ((taille = PreparerASCII(BDD_EFFETS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_EFFETS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Effets : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        effets[i] = new Effet(i);
        effets[i]->Lire(j, fbuf);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        effets[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir effets.txt en lecture\n");
#endif //PRINTIN

#endif // EFFETS_H_INCLUDED
