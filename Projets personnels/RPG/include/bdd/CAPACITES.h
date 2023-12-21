#ifndef CAPACITES_H_INCLUDED
#define CAPACITES_H_INCLUDED

for (i = 0; i < NOMBRE_CAPACITES+1; ++i)
    capacites[i] = 0;

if ((taille = PreparerBDD(BDD_CAPACITES))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_CAPACITES, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nCapacites : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        capacites[i] = new Capacite(i);
        p_fbuf = capacites[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        capacites[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_CAPACITES));
#endif //PRINTIN

#endif // CAPACITES_H_INCLUDED
