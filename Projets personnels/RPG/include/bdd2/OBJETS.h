#ifndef OBJETS_H_INCLUDED
#define OBJETS_H_INCLUDED

for (i = 0; i < NOMBRE_OBJETS+1; ++i)
    objets[i] = 0;

#ifdef PRINTIN
    nombre = 12;
    printf("Objets : %d\n", nombre);
#endif //PRINTIN
{
    int j = 0;
    objets[1] = new Utilisable(1);
    objets[1]->Lire(j, "potion 100 soigne_les_blessures 0 2");
    objets[1]->SetType(UTILISABLE);
    j = 0;
    objets[2] = new Equipable(2);
    objets[2]->Lire(j, "epee 80 tranche_les_membres 0 4 0 0 0 0 0 20 0 10 11 0");
    objets[2]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[3] = new Equipable(3);
    objets[3]->Lire(j, "casque 50 protege_la_tete 0 0 3 0 0 0 0 0 10 12 9 0");
    objets[3]->SetType(EQUIPABLE_CASQUE);
    j = 0;
    objets[4] = new Equipable(4);
    objets[4]->Lire(j, "hache 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[4]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[5] = new Equipable(5);
    objets[5]->Lire(j, "arc 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[5]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[6] = new Equipable(6);
    objets[6]->Lire(j, "massue 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[6]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[7] = new Equipable(7);
    objets[7]->Lire(j, "septre 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[7]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[8] = new Equipable(8);
    objets[8]->Lire(j, "dague 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[8]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[9] = new Equipable(9);
    objets[9]->Lire(j, "baton 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[9]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[10] = new Equipable(10);
    objets[10]->Lire(j, "sabre 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 0");
    objets[10]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[11] = new Equipable(11);
    objets[11]->Lire(j, "sabfeu 80 tranche_aussi_les_membres 0 15 0 0 0 0 0 10 0 15 14 1");
    objets[11]->SetType(EQUIPABLE_ARME);
    j = 0;
    objets[12] = new Equipable(12);
    objets[12]->Lire(j, "casqeau 50 protege_la_tete 0 0 3 0 0 0 0 0 10 12 9 2");
    objets[12]->SetType(EQUIPABLE_CASQUE);
}
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        switch (objets[i]->GetType()) {
        case OBJET:
            objets[i]->Ecrire(str);
            break;
        case UTILISABLE:
            ((Utilisable*)objets[i])->Ecrire(str);
            break;
        case EQUIPABLE:
        case EQUIPABLE_ACCESSOIRE:
        case EQUIPABLE_ARME:
        case EQUIPABLE_ARMURE:
        case EQUIPABLE_BOUCLIER:
        case EQUIPABLE_CASQUE:
            ((Equipable*)objets[i])->Ecrire(str);
            break;
        }
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // OBJETS_H_INCLUDED
