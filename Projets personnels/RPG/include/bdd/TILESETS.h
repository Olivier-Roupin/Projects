#ifndef TILESETS_H_INCLUDED
#define TILESETS_H_INCLUDED

for (i = 0; i < NOMBRE_TILESETS+1; ++i)
    tilesets[i] = 0;

if ((taille = PreparerBDD(BDD_TILESETS))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_TILESETS, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nTilesets : %d\n", nombre);
#endif //PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        tilesets[i] = new Tileset(i);
        p_fbuf = tilesets[i]->LireD(p_fbuf); //peut dépasser le buffer ?
#ifdef PRINTIN
        tilesets[i]->Ecrire(str);
        printf("%s\\0", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_TILESETS));
#endif //PRINTIN

#endif // TILESETS_H_INCLUDED
