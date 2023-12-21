#ifndef EVENEMENTS_H_INCLUDED
#define EVENEMENTS_H_INCLUDED

for (i = 0; i < NOMBRE_EVENEMENTS+1; ++i)
    evenements[i] = 0;

#ifdef PRINTIN
    nombre = 9;
    printf("Evenements : %d\n", nombre);
#endif //PRINTIN
    evenements[1] = new Evenement(1,3,"v");
    evenements[1]->SetScripts(scripts[1],0);
    evenements[1]->SetScripts(scripts[5],1);
    evenements[1]->SetScripts(scripts[0],2);
    evenements[2] = new Evenement(2,3,"e");
    evenements[2]->SetScripts(scripts[0],0);
    evenements[2]->SetScripts(scripts[3],1);
    evenements[2]->SetScripts(scripts[0],2);
    evenements[3] = new Evenement(3,3,"_");
    evenements[3]->SetScripts(scripts[0],0);
    evenements[3]->SetScripts(scripts[0],1);
    evenements[3]->SetScripts(scripts[6],2);
    evenements[4] = new Evenement(4,3,"_");
    evenements[4]->SetScripts(scripts[0],0);
    evenements[4]->SetScripts(scripts[0],1);
    evenements[4]->SetScripts(scripts[7],2);
    evenements[5] = new Evenement(5,4,"b");
    evenements[5]->SetScripts(scripts[0],0);
    evenements[5]->SetScripts(scripts[12],1);
    evenements[5]->SetScripts(scripts[0],2);
    evenements[5]->SetScripts(scripts[8],3);
    evenements[6] = new Evenement(6,3,"H");
    evenements[6]->SetScripts(scripts[0],0);
    evenements[6]->SetScripts(scripts[0],1);
    evenements[6]->SetScripts(scripts[9],2);
    evenements[7] = new Evenement(7,3,"_");
    evenements[7]->SetScripts(scripts[0],0);
    evenements[7]->SetScripts(scripts[0],1);
    evenements[7]->SetScripts(scripts[10],2);
    evenements[8] = new Evenement(8,3,"b");
    evenements[8]->SetScripts(scripts[0],0);
    evenements[8]->SetScripts(scripts[15],1);
    evenements[8]->SetScripts(scripts[0],2);
    evenements[9] = new Evenement(9,3,"e");
    evenements[9]->SetScripts(scripts[0],0);
    evenements[9]->SetScripts(scripts[18],1);
    evenements[9]->SetScripts(scripts[0],2);
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        evenements[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // EVENEMENTS_H_INCLUDED
