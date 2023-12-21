#ifndef GROUPESMONSTRES_H_INCLUDED
#define GROUPESMONSTRES_H_INCLUDED

for (i = 0; i < NOMBRE_GROUPES_MONSTRES+1; ++i)
    groupes_monstres[i] = 0;

if ((taille = PreparerBDD(BDD_GROUPES))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_GROUPES, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nGroupes monstres : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        groupes_monstres[i] = new GroupeMonstres(i);
        p_fbuf = groupes_monstres[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        groupes_monstres[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_GROUPES));
#endif //PRINTIN

#endif // GROUPESMONSTRES_H_INCLUDED
