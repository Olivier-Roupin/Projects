#ifndef MAGASINS_H_INCLUDED
#define MAGASINS_H_INCLUDED

for (i = 0; i < NOMBRE_MAGASINS+1; ++i)
    magasins[i] = 0;

if ((taille = PreparerBDD(BDD_MAGASINS))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_MAGASINS, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nMagasins : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        magasins[i] = new Magasin(i);
        p_fbuf = magasins[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        magasins[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_MAGASINS));
#endif //PRINTIN

#endif // MAGASINS_H_INCLUDED
