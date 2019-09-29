#include "Menu_Sauver.h"

using namespace std;

int Sauver(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int situation(SITUATION_CHOIX_SAUVEGARDE);
    int choix(0);
    int id(0);
    int i;
    string fichier;
    Partie* parties[NOMBRE_SAUVEGARDES];

    for(i = 0; i < NOMBRE_SAUVEGARDES; i++)
    {
        fichier = "sauvegarde";
        fichier += Int2String(i);
        fichier += ".txt";
        ifstream flux(fichier.c_str(), ios::in);
        if(flux)
            parties[i] = new Partie(i);
        else
            parties[i] = 0;
        flux.close();
    }

    while(not(input1.GetB()))
    {
        switch(situation)
        {
        case SITUATION_CHOIX_SAUVEGARDE:
            AfficherSauverChoix(parties, id);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
            input1.Actualiser();
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
            if(input1.Gethaut())
            {
                id = (id + NOMBRE_SAUVEGARDES - 1) % NOMBRE_SAUVEGARDES;
                input1.Sethaut(0);
            }
            if(input1.Getbas())
            {
                id = (id + 1) % NOMBRE_SAUVEGARDES;
                input1.Setbas(0);
            }
            if(input1.GetA())
            {
                situation = SITUATION_VALIDATION;
                input1.SetA(0);
            }
            break;
        case SITUATION_VALIDATION:
            AfficherSauverValider(choix);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
            input1.Actualiser();
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
            if(input1.Getgauche())
            {
                choix = (choix + NOMBRE_CHOIX_MENU_SAUVER - 1) % NOMBRE_CHOIX_MENU_SAUVER;
                input1.Setgauche(0);
            }
            if(input1.Getdroite())
            {
                choix = (choix + 1) % NOMBRE_CHOIX_MENU_SAUVER;
                input1.Setdroite(0);
            }
            if(input1.GetA())
            {
                if(choix)
                {
                    fichier = "sauvegarde";
                    fichier += Int2String(id);
                    fichier += ".txt";
                    ofstream flux(fichier.c_str(), ios::trunc);
                    if(not(flux))
                        return -1;
                    SauverInformations(partie, &flux);
                    SauverInventaire(partie->GetInventaire(), &flux);
                    SauverEquipe(partie->GetEquipe(), &flux);
                    flux.close();
                    return 0;
                }
                else
                    situation = SITUATION_CHOIX_SAUVEGARDE;
                input1.SetA(0);
            }
            if(input1.GetB())
            {
                situation = SITUATION_CHOIX_SAUVEGARDE;
                input1.SetB(0);
            }
            break;
        default:
            return -1;
        }
    }
    return 0;
}

void AfficherSauverChoix(Partie** parties, int id)
{
    system("cls"); //efface l'écran
    int i;
    for(i = 0; i < NOMBRE_SAUVEGARDES; i++)
    {
        AfficherCurseurEmplacement(id, i);
        cout << ":" << parties[i]->GetEquipe()->GetHeros(0)->GetNom() << " Temps " << parties[i]->GetTemps() << endl;
    }

}

void AfficherSauverValider(int choix)
{
    system("cls"); //efface l'écran
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    cout << "Etes vous sur ?" << endl;

    elements_graphiques[P_blank]->Afficher(0,0,0,10);
    AfficherCurseurEmplacement(choix, 0);
    cout << "Non";
    BlocGraphique("Non").Afficher(0,0,1,10);
    elements_graphiques[P_blank]->Afficher(0,0,5,10);
    AfficherCurseurEmplacement(choix, 1);
    cout << "Oui" << endl;
    BlocGraphique("Oui").Afficher(0,0,6,10);
    elements_graphiques[P_arrow]->Afficher(0,0,5*choix,10);
}

void SauverInformations(Partie* partie, ofstream* flux)
{
    *flux<<partie->GetOr()<<" "<<partie->GetTempsJeu()<<" "<<partie->GetPas()<<"  "\
         <<partie->GetVitesseCombat()<<" "<<partie->GetModeCombat()<<" "<<partie->GetMemoriserCurseur()<<"  "\
         <<(partie->GetCarte())->GetId()<<" "<<partie->GetX()<<" "<<partie->GetY()<<" "<<partie->GetOrientation()<<endl;
}

void SauverInventaire(Inventaire* inventaire, ofstream* flux)
{
    int i;
    for(i = 0; i < MAX_OBJETS; i++)
        *flux<<inventaire->GetObjets(i)->GetObjet()->GetId()<<" "<<inventaire->GetObjets(i)->GetNombre()<<endl;
}

void SauverEquipe(Equipe* equipe, ofstream* flux)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
        SauverHeros(equipe->GetHeros(i),flux);
}

void SauverHeros(Heros* heros, ofstream* flux)
{
    int i;
    //Stats :
    *flux<<heros->GetId()<<" "<<heros->GetNom()<<" "<<heros->GetVie()<<" "<<heros->GetMagie()<<" "\
         <<heros->GetVieMax()<<" "<<heros->GetAttaqueP()<<" "<<heros->GetDefenseP()<<" "\
         <<heros->GetMagieMax()<<" "<<heros->GetAttaqueM()<<" "<<heros->GetDefenseM()<<" "\
         <<heros->GetVitesse()<<" "<<heros->GetPrecision()<<" "<<heros->GetEsquive()<<" "\
         <<heros->GetStatut()<<" "<<heros->GetExperience()<<" "<<heros->GetNiveau()<<" "\
         <<heros->GetForce()<<" "<<heros->GetIntelligence()<<" "<<heros->GetAgilite()<<" "<<heros->GetRang()<<" ";
    //Equipement :
    *flux<<heros->GetEquipement(EQUIPEMENT_MAINGAUCHE)->GetId()<<" "<<heros->GetEquipement(EQUIPEMENT_MAINDROITE)->GetId()<<" "\
         <<heros->GetEquipement(EQUIPEMENT_TETE)->GetId()<<" "<<heros->GetEquipement(EQUIPEMENT_CORPS)->GetId()<<" "\
         <<heros->GetEquipement(EQUIPEMENT_ACCESSOIRE1)->GetId()<<" "<<heros->GetEquipement(EQUIPEMENT_ACCESSOIRE2)->GetId()<<endl;
    //Capacités - Magies :
    for(i = 0; i < MAX_SORTS; i++)
        *flux<<heros->GetSorts(i)->GetId()<<" ";
    *flux<<endl;
}
