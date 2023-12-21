#ifndef MONSTRES_H_INCLUDED
#define MONSTRES_H_INCLUDED

for (i = 0; i < NOMBRE_MONSTRES+1; ++i)
    monstres[i] = 0;

if ((taille = PreparerBDD(BDD_MONSTRES))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_MONSTRES, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nMonstres : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        monstres[i] = new Monstre(i);
        p_fbuf = monstres[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        monstres[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_MONSTRES));
#endif //PRINTIN

#endif // MONSTRES_H_INCLUDED
