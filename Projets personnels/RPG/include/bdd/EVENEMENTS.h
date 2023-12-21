#ifndef EVENEMENTS_H_INCLUDED
#define EVENEMENTS_H_INCLUDED

for (i = 0; i < NOMBRE_EVENEMENTS+1; ++i)
    evenements[i] = 0;

if ((taille = PreparerBDD(BDD_EVENEMENTS))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_EVENEMENTS, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nEvenements : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        evenements[i] = new Evenement(i);
        p_fbuf = evenements[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        evenements[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_EVENEMENTS));
#endif //PRINTIN

#endif // EVENEMENTS_H_INCLUDED
