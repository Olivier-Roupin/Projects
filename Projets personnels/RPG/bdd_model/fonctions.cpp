#include <iostream>

#include <Equipable.h>
#include <Utilisable.h>
#include <Terrain.h>

#include <moteur_graphique.h>
#include <Input.h>

#include <ctime>
#include <cstdlib>

using namespace std;

int fonction1(Partie* partie, int curseur) //exemple déplacement
{
    switch(curseur)
    {
    case 0:
        return curseur+DeplacerEvenement(partie->GetCarte(), 0, 1, 0, partie->GetX(), partie->GetY()); //un pas vers la droite
    case 32:
        return curseur+DeplacerEvenement(partie->GetCarte(), 0, -1, 0, partie->GetX(), partie->GetY()); //un pas vers la gauche
    case 64:
        return 0; //recommencer
    default:
        return curseur+1; //attendre
    }
    return 0;
}

int fonction2(Partie* partie, int curseur) //exemple effet
{
    int i,n;
    switch(curseur)
    {
    case 0:
        n = partie->GetLanceur_selection()->GetNombreCibles();
        for(i = 0; i < partie->GetLanceur_selection()->GetNombreCibles(); i++)
        {
            if(partie->GetLanceur_selection()->GetCible(i))
            {
                partie->GetLanceur_selection()->GetCible(i)->ChangerVie(-10/n);
                partie->GetLanceur_selection()->GetCible(i)->AjouterAlteration(alterations[1]);
            }
        }
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction3(Partie* partie, int curseur) //exemple choix
{
    switch(curseur)
    {
    case 0:
        partie->SetChoix(0);
        return 1;
    case 1:
        return curseur+AfficherChoix(partie, 2, "oui", "non");
    case 2:
        switch(partie->GetChoix())
        {
        case 0:
            return curseur+AfficherMessage(partie, "vous dites oui");
        case 1:
            return curseur+2*AfficherMessage(partie, "vous dites non");
        }
        return 1;
    case 3:
        DeplacerEvenement(partie->GetCarte(), 1, -1, 0, partie->GetX(), partie->GetY());
        DeplacerEvenement(partie->GetCarte(), 1, 0, -1, partie->GetX(), partie->GetY());
        return curseur+1;
    case 4:
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction4(Partie* partie, int curseur) //exemple monstre
{
    switch(curseur)
    {
    case 0:
    {
        int cible(0);
        Personnage** cibles;
        while(not(partie->GetEquipe()->GetHeros(cible)->estEnVie()))
        {
            cible = (cible + 1) % MAX_HEROS_EQUIPE;
        }
        //partie->GetGroupeCombat()->GetMonstres(partie->GetLanceur())->Attaquer(partie->GetEquipe()->GetHeros(partie->GetCibleMonstre()));
        cibles = new Personnage*[sizeof(Personnage*)*1];
        cibles[0] = partie->GetEquipe()->GetHeros(cible);
        partie->GetLanceur_selection()->SetCibles(cibles);
        partie->GetLanceur_selection()->Attaquer();
        partie->GetLanceur_selection()->SetCibles(0);
        return 0;
    }
    case 1:
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction5(Partie* partie, int curseur) //exemple message
{
    switch(curseur)
    {
    case 0:
        return curseur+AfficherMessage(partie, "Bonjour.");
    case 1:
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction6(Partie* partie, int curseur) //exemple téléportation 1
{
    switch(curseur)
    {
    case 0:
        TeleporterEquipe(partie,cartes[2],5,8,ORIENTATION_HAUT);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction7(Partie* partie, int curseur) //exemple téléportation 2
{
    switch(curseur)
    {
    case 0:
        TeleporterEquipe(partie,cartes[1],7,4,ORIENTATION_BAS);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction8(Partie* partie, int curseur) //exemple automatique
{
    switch(curseur)
    {
    case 0:
        return curseur+AfficherMessage(partie, "Ah, vous voilà enfin.");
    case 1:
        partie->SetSituation(SITUATION_RECHERCHE);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction9(Partie* partie, int curseur) //exemple téléportation
{
    switch(curseur)
    {
    case 0:
        TeleporterEquipe(partie,cartes[1],5,8,ORIENTATION_HAUT);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction10(Partie* partie, int curseur) //exemple téléportation
{
    switch(curseur)
    {
    case 0:
        TeleporterEquipe(partie,cartes[3],5,5,ORIENTATION_BAS);
        partie->SetSituation(SITUATION_INITIALISATION);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction11(Partie* partie, int curseur) //exemple alteration : alterations[1]
{
    switch(curseur)
    {
    case 32: //Au boût de 32 frames
        partie->GetLanceur_selection()->ChangerVie(-10);
        return (curseur+1)*(rand() % 2);//+random(0,1)
    case 33:
        //Retirer alteration
        partie->GetLanceur_selection()->RetirerAlteration(alterations[1]);
        return 0;
    default:
        return curseur+1; //attendre
    }
    return 0;
}

int fonction12(Partie* partie, int curseur) //exemple magasin
{
    switch(curseur)
    {
    case 0:
        return curseur+AfficherMessage(partie, "Bienvenue !");
    case 1:
        OuvrirMagasin(partie,magasins[1]);
        partie->SetSituation(SITUATION_DEPLACEMENT);
        return 0;
    default:
        return 0;
    }
    return 0;
}

int fonction13(Partie* partie, int curseur) //exemple effet utilisable : potion
{
    switch(curseur)
    {
    case 0:
        if(partie->GetLanceur_selection()->GetCible(0)->estEnVie())
            partie->GetLanceur_selection()->GetCible(0)->ChangerVie(100);
        return 0;
    default:
        return 0;
    }
    return 0;
}

PtrFonction fonctions[14] = {0,&fonction1,&fonction2,&fonction3,&fonction4,&fonction5,&fonction6,&fonction7,
                             &fonction8,&fonction9,&fonction10,&fonction11,&fonction12,&fonction13};
