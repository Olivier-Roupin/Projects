#ifndef CAPACITES_H_INCLUDED
#define CAPACITES_H_INCLUDED

for (i = 0; i < NOMBRE_CAPACITES+1; ++i)
    capacites[i] = 0;

#ifdef PRINTIN
    nombre = 4;
    printf("Capacites : %d\n", nombre);
#endif //PRINTIN
    capacites[1] = new Capacite(1, "soin",        "soigne_un_membre_de_l\'equipe", 10, 0, 0, 0, effets[2]);
    capacites[2] = new Capacite(2,  "feu",                      "brule_un_ennemi", 15, 0, 0, 0, effets[1]);
    capacites[3] = new Capacite(3, "demi", "reduit_de_moitie_les_pv_d\'un_ennemi", 25, 0, 0, 0, effets[3]);
    capacites[4] = new Capacite(4, "mort",                       "tue_en_un_coup", 40, 0, 0, 0, effets[4]);
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        capacites[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // CAPACITES_H_INCLUDED
