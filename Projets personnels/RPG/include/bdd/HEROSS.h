#ifndef HEROSS_H_INCLUDED
#define HEROSS_H_INCLUDED

for (i = 0; i < NOMBRE_HEROS+1; ++i)
    heross[i] = 0;

if ((taille = PreparerBDD(BDD_HEROS))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_HEROS, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nHeros : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        heross[i] = new Heros(i);
        p_fbuf = heross[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        heross[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_HEROS));
#endif //PRINTIN

#endif // HEROSS_H_INCLUDED
