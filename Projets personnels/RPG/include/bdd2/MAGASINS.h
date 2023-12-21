#ifndef MAGASINS_H_INCLUDED
#define MAGASINS_H_INCLUDED

for (i = 0; i < NOMBRE_MAGASINS+1; ++i)
    magasins[i] = 0;

#ifdef PRINTIN
    nombre = 2;
    printf("Magasins : %d\n", nombre);
#endif //PRINTIN
    magasins[1] = new Magasin(1,4);
    magasins[1]->SetObjets(objets[2],0);
    magasins[1]->SetObjets(objets[3],1);
    magasins[1]->SetObjets(objets[1],2);
    magasins[1]->SetObjets(objets[4],3);
    magasins[2] = new Magasin(2,1);
    magasins[2]->SetObjets(objets[1],0);
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        magasins[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // MAGASINS_H_INCLUDED
