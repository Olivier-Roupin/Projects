#ifndef OBJETS_H_INCLUDED
#define OBJETS_H_INCLUDED

for (i = 0; i < NOMBRE_OBJETS+1; ++i)
    objets[i] = 0;

if ((taille = PreparerASCII(BDD_OBJETS))) {
    fbuf = new char[2048*taille];
    ChargerASCII(BDD_OBJETS, taille, fbuf);
    int j = 0;
    LIRE_ENTIER(j,fbuf,nombre); LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
    printf("Objets : %d\n", nombre);
#endif //PRINTIN
    int type = 0;
    for (i = 1; i < nombre+1; ++i) {
        LIRE_ENTIER(j,fbuf,type);
        switch (type) {
        case OBJET:
        default:
            objets[i] = new Objet(i);
            break;
        case UTILISABLE:
            objets[i] = new Utilisable(i);
            break;
        case EQUIPABLE:
        case EQUIPABLE_ACCESSOIRE:
        case EQUIPABLE_ARME:
        case EQUIPABLE_ARMURE:
        case EQUIPABLE_BOUCLIER:
        case EQUIPABLE_CASQUE:
            objets[i] = new Equipable(i);
            break;
        }
        objets[i]->Lire(j, fbuf);
        objets[i]->SetType(type);
        LIRE_SUIVANT(j,fbuf);
#ifdef PRINTIN
        objets[i]->Ecrire(str);
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
    printf("ERREUR: Impossible d'ouvrir objets.txt en lecture\n");
#endif //PRINTIN

#endif // OBJETS_H_INCLUDED
