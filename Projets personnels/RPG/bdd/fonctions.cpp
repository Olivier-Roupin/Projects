#include <lib/Equipable.h>
#include <lib/Utilisable.h>
#include <scenes/Terrain.h>

#include <cstdlib> //rand, RAND_MAX

#define LONGUEUR_MESSAGE 31

int fonction1(Partie* partie, int curseur) { //exemple déplacement
    switch (curseur) {
    case 0: //un pas vers la droite
        return curseur+DeplacerEvenement(partie->GetCarte(), partie->GetEvenement(), 1, 0, //0
                                         partie->GetX(), partie->GetY());
    case 32: //un pas vers la gauche
        return curseur+DeplacerEvenement(partie->GetCarte(), partie->GetEvenement(), -1, 0, //0
                                         partie->GetX(),partie->GetY());
    case 64:
        return 0; //recommencer
    default:
        return curseur+1; //attendre
    }
    // return 0;
}

int fonction2(Partie* partie, int curseur) { //exemple effet : feu
    unsigned char i, n;
    switch (curseur) {
    case 0:
        if (partie->GetLanceur_selection()) {
            Personnage* lanceur = partie->GetLanceur_selection();
            n = lanceur->GetNombreCibles();
            for (i = 0; i < n; ++i) {
                if (lanceur->GetCible(i)) {
                    Personnage* cible = lanceur->GetCible(i);
                    const int atkm = lanceur->GetAttributTotal(ATTRIBUT_ATKM);
                    const int defm =   cible->GetAttributTotal(ATTRIBUT_DEFM);
                    const int plage =        2*atkm*atkm/(atkm+defm);
                    const int degats = -2*atkm*atkm*atkm/(atkm+defm)
                                    + (plage ? (rand()%(2*plage)-plage) : 0);
                    
                    // const int modif = 1;
                    const int modif = cible->GetModificateurElementaire(ATTRIBUT_DEFM,
                        lanceur->GetCapacite()->GetEffet()->GetElement()); //TODO: pas idéal
                    cible->ChangerVie(modif*degats/n/2);
                    cible->AjouterAlteration(alterations[1]);
                    cible->SetMessage(modif*degats/n/2);
                    cible->SetTempsMessage(30);
                }
            }
        }
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction3(Partie* partie, int curseur) { //exemple choix
    switch (curseur) {
    case 0:
        partie->SetChoix(0);
        return 0+OrienterEvenement(partie->GetCarte(), partie->GetEvenement(), -1, partie->GetX(), partie->GetY()); //1
    case 1:
        return curseur+Choix(partie, 2, "oui", "non");
    case 2:
        switch (partie->GetChoix()) {
        case 0:
            return curseur+Message(partie, "vous dites oui");
        case 1:
            return curseur+3*Message(partie, "vous dites non");
        }
        return 1;
    case 3:
        return curseur+DeplacerEvenement(partie->GetCarte(), partie->GetEvenement(), -1, 0, //1
                                         partie->GetX(), partie->GetY(),
                                         true, false, true); // mouvement optionnel
    case 4:
        return curseur+DeplacerEvenement(partie->GetCarte(), partie->GetEvenement(), 0, -1, //1
                                         partie->GetX(), partie->GetY(),
                                         true, false, true); // mouvement optionnel
    case 5:
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction4(Partie* partie, int curseur) { //exemple monstre
    switch (curseur) {
    case 0: {
        if (partie->GetEquipe() == 0)
            return 0;
        unsigned char cible = 0;
        Personnage** cibles;
        while (partie->GetEquipe()->GetHeros(cible) == 0
           || !partie->GetEquipe()->GetHeros(cible)->estEnVie())
            cible = (cible + 1) % MAX_HEROS_EQUIPE;
        //partie->GetMonstre(partie->GetLanceur()
        //)->Attaquer(partie->GetEquipe()->GetHeros(partie->GetCibleMonstre()));
        cibles = new Personnage*[1];
        cibles[0] = partie->GetEquipe()->GetHeros(cible);
        partie->GetLanceur_selection()->SetCibles(cibles);
        partie->GetLanceur_selection()->SetNombreCibles(1);
        partie->GetLanceur_selection()->Attaquer(rand(), RAND_MAX);
        partie->GetLanceur_selection()->SetCibles(0); //deleting cibles
        partie->GetLanceur_selection()->SetNombreCibles(0);
        return 0;
    }
    case 1:
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction5(Partie* partie, int curseur) {//exemple message
    switch (curseur) {
    case 0:
        return 0+OrienterEvenement(partie->GetCarte(), partie->GetEvenement(),
                                   -1, partie->GetX(), partie->GetY()); //0
    case 1:
    // case 2:
    // case 3:
    // case 4:
    // case 5:
    // case 6:
    //     return MessageTransition(curseur-1-6)+6+1;
    // case 7:
        return curseur+Message(partie, "Bonjour.");
    // case 8:
    case 2:
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction6(Partie* partie, int curseur) {//exemple téléportation 1 (nova->maison)
    switch (curseur) {
    case 0:
        ChangerTuile(partie,6,partie->GetX(),
                              partie->GetY()-1, Z_MILIEU);
        return curseur+1;
    case 1:
        return curseur+DeplacerHeros(partie,0,-1,true);
    case 2:
        return curseur+FonduSortant(8);
    case 3:
    // case 2:
        ChangerTuile(partie,2,partie->GetX(),
                              partie->GetY(), Z_MILIEU);
        // TeleporterEquipe(partie,2,5,8,ORIENTATION_HAUT);
        TeleporterEquipe(partie,cartes[2],5,8,ORIENTATION_HAUT);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction7(Partie* partie, int curseur) {//exemple téléportation 2 (maison->nova)
    switch (curseur) {
    case 0:
        ChangerTuile(partie,6,partie->GetX()+partie->GetOrientationX(),
                              partie->GetY()+partie->GetOrientationY(), Z_MILIEU);
        return curseur+1;
    case 1:
        return curseur+DeplacerHeros(partie,partie->GetOrientationX(),
                                            partie->GetOrientationY(),true);
    case 2:
        return curseur+FonduSortant(8);
    case 3:
    // case 2:
        ChangerTuile(partie,2,partie->GetX(),
                              partie->GetY(), Z_MILIEU);
        // TeleporterEquipe(partie,1,7,4,ORIENTATION_BAS);
        TeleporterEquipe(partie,cartes[1],7,4,ORIENTATION_BAS);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction8(Partie* partie, int curseur) {//exemple automatique
    char message[LONGUEUR_MESSAGE+1] = "Ah, vous voila enfin \\0_____.";
    int i;
    unsigned char j;
    switch (curseur) {
    case 0:
        return 0+OrienterEvenement(partie->GetCarte(), partie->GetEvenement(), -1, partie->GetX(), partie->GetY()); //1
    case 1:
        for (i = 0; i < LONGUEUR_MESSAGE; ++i) //remplacement des caractères spéciaux
            if (message[i] == '\\' && partie->GetEquipe()) {
                //décalage de la ponctuation
                char c = message[i+TAILLE_NOM_PERSONNAGE]; //le caractère effacé
                message[i+TAILLE_NOM_PERSONNAGE] = ' ';
                // j = (int)(message[i+1]-'0');
                j = message[i+1]-'0';
                while (!partie->GetEquipe()->GetHeros(j))
                    j = APRES(j, MAX_HEROS_EQUIPE);
                const char* nom = partie->GetEquipe()->GetHeros(j)->GetNom();
                j = 0;
                LIRE_CHAINE(j,i,nom,message,LONGUEUR_MESSAGE);
                message[i] = c; //retirer le \0
            }
        return curseur+Message(partie, message);
    case 2:
        partie->SetSituation(SITUATION_RECHERCHE);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction9(Partie* partie, int curseur) {//exemple téléportation 3 (world->nova)
    switch (curseur) {
    case 0:
        return FonduSortant(8);
    case 1:
        // TeleporterEquipe(partie,1,5,8,ORIENTATION_HAUT);
        TeleporterEquipe(partie,cartes[1],5,8,ORIENTATION_HAUT);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction10(Partie* partie, int curseur) {//exemple téléportation 4 (nova->world)
    switch (curseur) {
    case 0:
        ChangerTuile(partie,6,partie->GetX()+partie->GetOrientationX(),
                              partie->GetY()+partie->GetOrientationY(), Z_MILIEU);
        return curseur+1;
    case 1:
        return curseur+DeplacerHeros(partie,partie->GetOrientationX(),
                                            partie->GetOrientationY(),true);
    case 2:
        return curseur+FonduSortant(8);
    case 3:
        ChangerTuile(partie,2,partie->GetX(),
                              partie->GetY(), Z_MILIEU);
        // TeleporterEquipe(partie,3,5,5,ORIENTATION_NEUTRE); //ORIENTATION == -1
        TeleporterEquipe(partie,cartes[3],5,5,ORIENTATION_NEUTRE); //ORIENTATION == -1
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction11(Partie* partie, int curseur) { //exemple alteration : alterations[1]
    switch (curseur) {
    case 32: //Au bout de 32 frames
        partie->GetLanceur_selection()->ChangerVie(-10);
        return (curseur+1)*(rand() % 2);//+random(0,1)
    case 33:
        //Retirer alteration
        partie->GetLanceur_selection()->RetirerAlteration(alterations[1]);
        return 0;
    default:
        return curseur+1; //attendre
    }
    // return 0;
}

int fonction12(Partie* partie, int curseur) { //exemple magasin
    switch (curseur) {
    case 0:
        return 0+OrienterEvenement(partie->GetCarte(), partie->GetEvenement(),
                                   -1, partie->GetX(), partie->GetY()); //1
    case 1:
        return curseur+Message(partie, "Bienvenue !");
    case 2:
        return curseur+FonduSortant(16);
    // case 2:
    //     OuvrirMagasin(partie,magasins[1]);
    //     partie->SetSituation(SITUATION_DEPLACEMENT);
    //     return 0;
    case 3:
        OuvrirMagasin(partie,magasins[1]);
        return curseur+1;
    case 4:
        return curseur+FonduEntrant(32);
    case 5:
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction13(Partie* partie, int curseur) { //exemple effet utilisable : potion
    switch (curseur) {
    case 0:
        if (partie->GetLanceur_selection()
         && partie->GetLanceur_selection()->GetCible(0)
         && partie->GetLanceur_selection()->GetCible(0)->estEnVie()) {
            Personnage* cible = partie->GetLanceur_selection()->GetCible(0);
            cible->ChangerVie(100);
            cible->SetMessage(100);
            cible->SetTempsMessage(30);
        }
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction14(Partie* partie, int curseur) { //exemple monstre 2
    switch (curseur) {
    case 0: {
        if (partie->GetEquipe() == 0)
            return 0;
        unsigned char cible = 0;
        Personnage** cibles;
        while (partie->GetEquipe()->GetHeros(cible) == 0
           || !partie->GetEquipe()->GetHeros(cible)->estEnVie())
            cible = (cible + 1) % MAX_HEROS_EQUIPE;
        //partie->GetMonstre(partie->GetLanceur()
        //)->Attaquer(partie->GetEquipe()->GetHeros(partie->GetCibleMonstre()));
        cibles = new Personnage*[1];
        cibles[0] = partie->GetEquipe()->GetHeros(cible);
        partie->GetLanceur_selection()->SetCibles(cibles);
        partie->GetLanceur_selection()->SetNombreCibles(1);
        partie->GetLanceur_selection()->Attaquer(rand(), RAND_MAX);
        partie->GetLanceur_selection()->SetCibles(0); //deleting cibles
        partie->GetLanceur_selection()->SetNombreCibles(0);
        return 0;
    }
    case 1:
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction15(Partie* partie, int curseur) { //exemple combat
    switch (curseur) {
    case 0:
        return 0+OrienterEvenement(partie->GetCarte(), partie->GetEvenement(),
                                   -1, partie->GetX(), partie->GetY());
    case 1:
        return curseur+Message(partie, "A mort !");
    case 2:
        partie->GetInput()->Vider();
        DemarrerCombat(partie, groupes_monstres[4]);
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    // return 0;
}

int fonction16(Partie* partie, int curseur) { //exemple effet : demi
    switch (curseur) {
    case 0:
        if (partie->GetLanceur_selection()) {
            if (partie->GetLanceur_selection()->GetCible(0)) {
                Personnage* cible = partie->GetLanceur_selection()->GetCible(0);
                const int degats = cible->ChangerVieP(-50);
                cible->SetMessage(degats);
                cible->SetTempsMessage(30);
            }
        }
        return 0;
    default:
        return 0;
    }
}

int fonction17(Partie* partie, int curseur) { //exemple effet : mort
    switch (curseur) {
    case 0:
        if (partie->GetLanceur_selection()) {
            if (partie->GetLanceur_selection()->GetCible(0)) {
                Personnage* cible = partie->GetLanceur_selection()->GetCible(0);
                const int degats = (rand()%3) ? 0 : cible->ChangerVieP(-100);
                cible->SetMessage(degats);
                cible->SetTempsMessage(30);
            }
        }
        return 0;
    default:
        return 0;
    }
}

int fonction18(Partie* partie, int curseur) { //exemple auberge
    unsigned char i;
    switch (curseur) {
    case 0:
        return 0+OrienterEvenement(partie->GetCarte(), partie->GetEvenement(),
                                   -1, partie->GetX(), partie->GetY());
    case 1:
        return curseur+Message(partie, "Je vais guerir ton equipe !");
    case 2:
        return curseur+FonduSortant(8);
    case 3:
        for (i = 0; i < MAX_HEROS_EQUIPE; ++i) {
            if (partie->GetEquipe()->GetHeros(i)) {
                partie->GetEquipe()->GetHeros(i)->SetVieP(100);
                partie->GetEquipe()->GetHeros(i)->SetMagieP(100);
                partie->GetEquipe()->GetHeros(i)->RetirerAlterations();
            }
        }
        return curseur+1;
    case 4:
        return curseur+FonduEntrant(16);
    case 5:
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
}

int fonction19(Partie* partie, int curseur) { //exemple alteration terrain : alterations[1]
    switch (curseur) {
    case 3: //Au boût de 4 pas
        if (partie->GetLanceur_selection()) {
            if (partie->GetLanceur_selection()->GetVie() > 5)
                partie->GetLanceur_selection()->ChangerVie(-5);
            else if (partie->GetLanceur_selection()->GetVie() != 1)
                partie->GetLanceur_selection()->SetVie(1);
        }
        //TODO: lancer animation
        return 0;
    default:
        return curseur+1; //attendre
    }
    // return 0;
}

PtrFonction fonctions[20] = {0,&fonction1, &fonction2, &fonction3, &fonction4,
                               &fonction5, &fonction6, &fonction7, &fonction8,
                               &fonction9, &fonction10,&fonction11,&fonction12,
                               &fonction13,&fonction14,&fonction15,&fonction16,
                               &fonction17,&fonction18,&fonction19};
