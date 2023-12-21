#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

for (i = 0; i < NOMBRE_CARTES+1; ++i)
    cartes[i] = 0;

if ((taille = PreparerBDD(BDD_CARTES))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_CARTES, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nCartes : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        cartes[i] = new Carte(i);
        p_fbuf = cartes[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        char longue_str[MAX_TAILLE_DATA*64];
        cartes[i]->Ecrire(longue_str);
        printf("%s\\0\n", longue_str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_CARTES));
#endif //PRINTIN

#endif // CARTES_H_INCLUDED
