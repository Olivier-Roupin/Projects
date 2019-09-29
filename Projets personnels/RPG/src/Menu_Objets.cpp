#include "Menu_Objets.h"

using namespace std;

int Objets(Inventaire* inventaire, Equipe* equipe, Carte* carte)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    while(not(input1.GetB()))
    {
        AfficherObjets(inventaire, choix);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Gethaut())
        {
            if(choix > 0)
                choix--;
            input1.Sethaut(0);
        }
        if(input1.Getbas())
        {
            if(choix < MAX_OBJETS - 1)
                choix++;
            input1.Setbas(0);
        }
        if(input1.GetA())
        {
            if(inventaire->GetObjets(choix) && inventaire->GetObjets(choix)->GetObjet()->GetType() == UTILISABLE)
            {
                //UtiliserObjet((Utilisable*)inventaire->GetObjets(choix)->GetObjet(), equipe->GetHeros(0));
                //inventaire->RetirerObjets(inventaire->GetObjets(choix)->GetObjet());
                UtiliserObjet(inventaire, equipe, carte, (Utilisable*)inventaire->GetObjets(choix)->GetObjet(), MENU);
            }
            input1.SetA(0);
        }
        if(input1.GetY())
        {
            inventaire->EchangerObjets(0,1);
            input1.SetY(0);
        }
    }
    return 0;
}

int Objets(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    Inventaire* inventaire = partie->GetInventaire();
    Equipe* equipe = partie->GetEquipe();
    Carte* carte = partie->GetCarte();
    while(not(input1.GetB()))
    {
        AfficherObjets(inventaire, choix);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Gethaut())
        {
            if(choix > 0)
                choix--;
            input1.Sethaut(0);
        }
        if(input1.Getbas())
        {
            if(choix < MAX_OBJETS - 1)
                choix++;
            input1.Setbas(0);
        }
        if(input1.GetA())
        {
            if(inventaire->GetObjets(choix) && inventaire->GetObjets(choix)->GetObjet()->GetType() == UTILISABLE)
            {
                Utilisable* objet = (Utilisable*)inventaire->GetObjets(choix)->GetObjet();
                if(objet->GetEffet()->GetDisponibilite() == TOUJOURS || objet->GetEffet()->GetDisponibilite() == MENU)
                {

                    //UtiliserObjet((Utilisable*)inventaire->GetObjets(choix)->GetObjet(), equipe->GetHeros(0));
                    //inventaire->RetirerObjets(inventaire->GetObjets(choix)->GetObjet());

                    //Le premier personnage en vie utilise l'objet
                    int i;
                    for(i = 1; i < MAX_HEROS_EQUIPE + 1; i++)
                    {
                        if(partie->GetEquipe()->GetHeros((i + partie->GetHeros()) % MAX_HEROS_EQUIPE)->estEnVie())
                        {
                            partie->SetHeros((i + partie->GetHeros()) % MAX_HEROS_EQUIPE);
                            i = MAX_HEROS_EQUIPE;
                        }
                    }
                    partie->SetAction(ACTION_OBJETS);
                    partie->GetHeros_selection()->SetAction(partie->GetAction());

                    partie->SetObjet(choix);
                    partie->GetHeros_selection()->SetObjet(partie->GetObjet_selection());

                    partie->SetCible_Defaut();
                    partie->GetHeros_selection()->SetCibles(partie->GetCible_selection());
                    partie->GetHeros_selection()->SetNombreCibles(partie->GetCible_nombre());
                    ((Utilisable*)partie->GetHeros_selection()->GetObjet())->GetEffet()->GetScript()->Executer(partie); //On s'intéresse à l'objet du héros
                    partie->GetInventaire()->RetirerObjets(partie->GetHeros_selection()->GetObjet()); //Retirer l'objet de l'inventaire
                }
                //UtiliserObjet(inventaire, equipe, carte, (Utilisable*)inventaire->GetObjets(choix)->GetObjet(), MENU);
            }
            input1.SetA(0);
        }
        if(input1.GetY())
        {
            inventaire->EchangerObjets(0,1);
            input1.SetY(0);
        }
    }
    return 0;
}

int Equipe_Reduit(Equipe* equipe)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    while(not(input1.GetB()))
    {
        AfficherEquipe_Reduit(equipe, choix);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Gethaut())
        {
            if(choix > 0)
                choix--;
            input1.Sethaut(0);
        }
        if(input1.Getbas())
        {
            if(choix < MAX_HEROS_EQUIPE - 1)
                choix++;
            input1.Setbas(0);
        }
        if(input1.GetA())
        {
            return choix;
        }
    }
    return -1;
}

void AfficherObjets(Inventaire* inventaire, int choix)
{
    system("cls"); //efface l'écran
    int i;
    int premier(PremierObjetAffiche(choix));
    for(i = premier; i < premier + NOMBRE_OBJETS_AFFICHES; i++)
    {
        AfficherCurseurEmplacement(choix,i);
        cout<<i<<": "<<inventaire->GetObjets(i)->GetObjet()->GetNom()<<" "<<inventaire->GetObjets(i)->GetNombre()<< endl;
    }
}

void AfficherEquipe_Reduit(Equipe* equipe, int choix)
{
    system("cls"); //efface l'écran
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        AfficherCurseurEmplacement(choix,i);
        cout << i+1 << ": " << equipe->GetHeros(i)->GetNom()<< endl;
    }
}

int PremierObjetAffiche(int choix)
{
    if(choix < NOMBRE_OBJETS_AFFICHES/2)
        return 0;
    if(choix > MAX_OBJETS - NOMBRE_OBJETS_AFFICHES + 1)
        return MAX_OBJETS - NOMBRE_OBJETS_AFFICHES;
    return choix - NOMBRE_OBJETS_AFFICHES/2;
}

int ChercherObjetPrecedent(Inventaire* inventaire, int choix, int type1, int type2)
{
    int i(choix-1);
    while(i >= 0 && inventaire->GetObjets(i)->GetObjet()->GetType() != type1 && inventaire->GetObjets(i)->GetObjet()->GetType() != type2)
        i--;
    if(i < 0)
        return choix;
    return i;
}

int ChercherObjetSuivant(Inventaire* inventaire, int choix, int type1, int type2)
{
    int i(choix+1);
    while(i < MAX_OBJETS && inventaire->GetObjets(i)->GetObjet()->GetType() != type1 && inventaire->GetObjets(i)->GetObjet()->GetType() != type2)
        i++;
    if(i >= MAX_OBJETS)
        return choix;
    return i;
}

int UtiliserObjet(Inventaire* inventaire, Equipe* equipe, Carte* carte, Utilisable* objet, int Situation)
{
    int choix(-1);
    if(objet->GetEffet()->GetDisponibilite() == TOUJOURS || objet->GetEffet()->GetDisponibilite() == Situation)
    {
        if(objet->GetEffet()->GetDefaut_Quantite() == QUANTITE_FACTION || objet->GetEffet()->GetDefaut_Cible() == CIBLE_TOUS)
        {
            UtiliserObjet(objet, equipe);
            inventaire->RetirerObjets(objet);
        }
        else if(objet->GetEffet()->GetDefaut_Cible() == CIBLE_LANCEUR || objet->GetEffet()->GetDefaut_Cible() >= 0)
        {
            choix = Equipe_Reduit(equipe);
            if(choix != -1 && equipe->GetHeros(choix))
            {
                UtiliserObjet(objet, equipe->GetHeros(choix));
                inventaire->RetirerObjets(objet);
            }
        }
        return 0;
    }
    return -1;
}
/*
int UtiliserObjet(Partie* partie, Utilisable* objet, int Situation)
{
    int choix(-1);
    int i;
    Inventaire* inventaire = partie->GetInventaire();
    Equipe* equipe = partie->GetEquipe();
    Carte* carte = partie->GetCarte();
    if(objet->GetEffet()->GetDisponibilite() == TOUJOURS || objet->GetEffet()->GetDisponibilite() == Situation)
    {

        partie->GetHeros_selection()->SetAction(ACTION_OBJETS);
        partie->GetHeros_selection()->SetObjet(objet);


        partie->SetCible_Defaut();

        partie->GetHeros_selection()->SetCibles(partie->GetCible_selection());
        partie->GetHeros_selection()->SetNombreCibles(partie->GetCible_nombre());

        if(objet->GetEffet()->GetDefaut_Quantite() == QUANTITE_FACTION || objet->GetEffet()->GetDefaut_Cible() == CIBLE_TOUS)
        {
            UtiliserObjet(objet, equipe);
            inventaire->RetirerObjets(objet);
        }
        else if(objet->GetEffet()->GetDefaut_Cible() == CIBLE_LANCEUR || objet->GetEffet()->GetDefaut_Cible() >= 0)
        {
            choix = Equipe_Reduit(equipe);
            if(choix != -1 && equipe->GetHeros(choix))
            {
                UtiliserObjet(objet, equipe->GetHeros(choix));
                inventaire->RetirerObjets(objet);
            }
        }
        return 0;
    }
    return -1;
}*/

int UtiliserObjet(Utilisable* objet, Personnage* cible)
{
    Effet* effet(0);
    effet = objet->GetEffet();
    if(cible)
    {
        //effet->GetScript()->Executer();
        /*if(effet->GetType() == EFFET_PERSONNAGE)
        {
            cible->ChangerVie(((EffetPersonnage*)effet)->GetEffetVie());
            cible->ChangerMagie(((EffetPersonnage*)effet)->GetEffetMagie());
            cible->ChangerVieP(((EffetPersonnage*)effet)->GetEffetVieP());
            cible->ChangerMagieP(((EffetPersonnage*)effet)->GetEffetMagieP());
            return 0;
        }*/
    }
    return -1;
}

int UtiliserObjet(Utilisable* objet, Equipe* cible)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        UtiliserObjet(objet,cible->GetHeros(i));
    }
    return 0;
}
