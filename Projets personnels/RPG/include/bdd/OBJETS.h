#ifndef OBJETS_H_INCLUDED
#define OBJETS_H_INCLUDED

for (i = 0; i < NOMBRE_OBJETS+1; ++i)
    objets[i] = 0;

if ((taille = PreparerBDD(BDD_OBJETS))) {
    fbuf = new char[2048*taille];
    ChargerBDD(BDD_OBJETS, taille, fbuf);
    nombre = (unsigned char)fbuf[0];
    const char* p_fbuf = &fbuf[1];
#ifdef PRINTIN
    printf("\nObjets : %d\n", nombre);
#endif //PRINTIN
    int type = 0;
    for (i = 1; i < nombre+1; ++i) {
        type = (unsigned char)p_fbuf[0];
        p_fbuf = &p_fbuf[1];
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
        p_fbuf = objets[i]->LireD(p_fbuf); //peut dépasser le buffer ?
        objets[i]->SetType(type);
#ifdef PRINTIN
        objets[i]->Ecrire(str);
        printf("%s\\0\n", str);
#endif //PRINTIN
    }
    delete[] fbuf;
}
#ifdef PRINTIN
else
    printf("ERREUR: Impossible d'ouvrir %s en lecture\n", NomBDD(BDD_OBJETS));
#endif //PRINTIN

#endif // OBJETS_H_INCLUDED
