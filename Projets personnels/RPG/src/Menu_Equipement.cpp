#include "Menu_Equipement.h"

using namespace std;

int Equipements(Inventaire *inventaire, Equipe* equipe)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix_heros(0);
    while(not(input1.GetB()))
    {
        AfficherEquipement(equipe, choix_heros);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Getgauche())
        {
            choix_heros = (choix_heros + MAX_HEROS_EQUIPE - 1) % MAX_HEROS_EQUIPE;
            input1.Setgauche(0);
        }
        if(input1.Getdroite())
        {
            choix_heros = (choix_heros + 1) % MAX_HEROS_EQUIPE;
            input1.Setdroite(0);
        }
        if(input1.GetA())
        {
            if(equipe->GetHeros(choix_heros))
                ChoixEquipements(inventaire,equipe,choix_heros);
            input1.SetA(0);
        }
    }
    return 0;
}

void ChoixEquipements(Inventaire *inventaire, Equipe* equipe, int &choix_heros)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix_equipement(0);
    int choix_objet(0);
    int type1(-1);
    int type2(-1);
    while(not(input1.GetB()))
    {
        system("cls"); //efface l'écran
        cout << equipe->GetHeros(choix_heros)->GetNom() << endl;
        AfficherChoixEquipement(equipe->GetHeros(choix_heros), choix_equipement);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Gethaut())
        {
            choix_equipement = (choix_equipement + NOMBRE_CHOIX_EQUIPEMENT - 1) % NOMBRE_CHOIX_EQUIPEMENT;
            input1.Sethaut(0);
        }
        if(input1.Getbas())
        {
            choix_equipement = (choix_equipement + 1) % NOMBRE_CHOIX_EQUIPEMENT;
            input1.Setbas(0);
        }
        if(input1.GetX())
        {
            inventaire->AjouterObjets(equipe->GetHeros(choix_heros)->GetEquipement(choix_equipement));
            equipe->GetHeros(choix_heros)->SetEquipement(0,choix_equipement);
            input1.SetX(0);
        }
        if(input1.GetL())
        {
            choix_heros = (choix_heros + MAX_HEROS_EQUIPE - 1) % MAX_HEROS_EQUIPE;
            input1.SetL(0);
        }
        if(input1.GetR())
        {
            choix_heros = (choix_heros + 1) % MAX_HEROS_EQUIPE;
            input1.SetR(0);
        }
        if(input1.GetA())
        {
            inventaire->AjouterObjets(equipe->GetHeros(choix_heros)->GetEquipement(choix_equipement));
            switch(choix_equipement)
            {
            case EQUIPEMENT_MAINGAUCHE:
            case EQUIPEMENT_MAINDROITE:
                type1 = EQUIPABLE_ARME;
                type2 = EQUIPABLE_BOUCLIER;
                break;
            case EQUIPEMENT_TETE:
                type1 = EQUIPABLE_CASQUE;
                break;
            case EQUIPEMENT_CORPS:
                type1 = EQUIPABLE_ARMURE;
                break;
            case EQUIPEMENT_ACCESSOIRE1:
            case EQUIPEMENT_ACCESSOIRE2:
                type1 = EQUIPABLE_ACCESSOIRE;
                break;
            default:
                break;
            }
            choix_objet = Objets_Reduit(inventaire, type1, type2);
            if(choix_objet > 0 && choix_objet < MAX_OBJETS+1)
            {
                //if (equipe->GetHeros(choix_heros)->SetEquipement(inventaire->GetObjets(choix_objet)->GetObjet(),choix_equipement) == 0)
                //{
                //inventaire->RetirerObjets(inventaire->GetObjets(choix_objet)->GetObjet());
                //}
                equipe->GetHeros(choix_heros)->SetEquipement(inventaire->GetObjets(choix_objet)->GetObjet(),choix_equipement);
            }
            inventaire->RetirerObjets(equipe->GetHeros(choix_heros)->GetEquipement(choix_equipement));
            input1.SetA(0);
        }
    }
}

int Objets_Reduit(Inventaire* inventaire, int type1, int type2)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(ChercherObjetSuivant(inventaire, -1, type1, type2));
    if(choix != -1)
    {
        while(not(input1.GetB()))
        {
            AfficherObjets_Reduit(inventaire, choix, type1, type2);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
            input1.Actualiser();
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
            if(input1.Gethaut())
            {
                if(choix > 0)
                    choix = ChercherObjetPrecedent(inventaire, choix, type1, type2);
                input1.Sethaut(0);
            }
            if(input1.Getbas())
            {
                if(choix < MAX_OBJETS - 1)
                    choix = ChercherObjetSuivant(inventaire, choix, type1, type2);
                input1.Setbas(0);
            }
            if(input1.GetA())
                return choix;
        }
    }
    return 0;
}

void AfficherEquipement(Equipe* equipe, int choix)
{
    system("cls"); //efface l'écran
    //Effacer écran ?
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        elements_graphiques[P_blank]->Afficher(0,0,14,i+1);
        AfficherCurseurEmplacement(choix, i);
        cout << equipe->GetHeros(i)->GetNom();
    }
    elements_graphiques[P_arrow]->Afficher(0,0,14,choix+1);
    cout << endl;
}

void AfficherChoixEquipement(Heros* heros, int choix)
{
    AfficherCurseurEmplacement(choix, 0);
    cout << "Main Gauche : " << heros->GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetNom() << endl;
    AfficherCurseurEmplacement(choix, 1);
    cout << "Main Droite : " << heros->GetEquipement(EQUIPEMENT_MAINDROITE)->GetNom() << endl;
    AfficherCurseurEmplacement(choix, 2);
    cout << "Tete : " << heros->GetEquipement(EQUIPEMENT_TETE)->GetNom() << endl;
    AfficherCurseurEmplacement(choix, 3);
    cout << "Corps : " << heros->GetEquipement(EQUIPEMENT_CORPS)->GetNom() << endl;
    AfficherCurseurEmplacement(choix, 4);
    cout << "Accessoire 1 : " << heros->GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetNom() << endl;
    AfficherCurseurEmplacement(choix, 5);
    cout << "Accessoire 2 : " << heros->GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetNom() << endl;
}

void AfficherObjets_Reduit(Inventaire* inventaire, int choix, int type1, int type2)
{
    int premier(PremierObjetAffiche(choix));
    int i;
    for(i = premier; i < premier + NOMBRE_OBJETS_AFFICHES; i++)
    {
        if(inventaire->GetObjets(i) && (inventaire->GetObjets(i)->GetObjet()->GetType() == type1 || inventaire->GetObjets(i)->GetObjet()->GetType() == type2))
        {
            AfficherCurseurEmplacement(choix,i);
            cout<<i<<": "<<inventaire->GetObjets(i)->GetObjet()->GetNom()<<" "<<inventaire->GetObjets(i)->GetNombre()<< endl;
        }
    }
}
