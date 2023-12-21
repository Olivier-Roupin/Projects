#ifndef EFFETS_H_INCLUDED
#define EFFETS_H_INCLUDED

for (i = 0; i < NOMBRE_EFFETS+1; ++i)
    effets[i] = 0;

if ((taille = PreparerBDD(BDD_EFFETS))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_EFFETS, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nEffets : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        effets[i] = new Effet(i);
        p_fbuf = effets[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        effets[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_EFFETS));
#endif //PRINTIN

#endif // EFFETS_H_INCLUDED
