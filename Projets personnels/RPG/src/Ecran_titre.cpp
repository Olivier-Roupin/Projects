#include "Ecran_titre.h"

using namespace std;

int Ecran_titre()
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int situation(SITUATION_ECRAN_TITRE);
    int choix(0);
    int id(0);
    int i;
    Partie* parties[NOMBRE_SAUVEGARDES];

    while(not(input1.GetA()))
    {
        switch(situation)
        {
        case SITUATION_ECRAN_TITRE:
            AfficherEcran_Titre(choix);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
            input1.Actualiser();
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
            if(input1.Getgauche())
            {
                choix = (choix + NOMBRE_CHOIX_ECRAN_TITRE - 1) % NOMBRE_CHOIX_ECRAN_TITRE;
                input1.Setgauche(0);
            }
            if(input1.Getdroite())
            {
                choix = (choix + 1) % NOMBRE_CHOIX_ECRAN_TITRE;
                input1.Setdroite(0);
            }
            if(input1.GetA())
            {
                if(choix == -NOUVELLE_PARTIE)
                {
                    return NOUVELLE_PARTIE;
                }
                if(choix == -QUITTER)
                {
                    return QUITTER;
                }
                string fichier;

                for(i = 0; i < NOMBRE_SAUVEGARDES; i++)
                {
                    fichier = "sauvegarde";
                    fichier += Int2String(i);
                    fichier += ".txt";
                    ifstream flux(fichier.c_str(), ios::in);
                    if(flux)
                    {
                        parties[i] = new Partie(i);
                    }
                    else
                    {
                        parties[i] = 0;
                    }
                    flux.close();
                }
                situation = SITUATION_CHARGER;
                input1.SetA(0);
            }
            break;
        case SITUATION_CHARGER:
            AfficherCharger(parties, id);
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
                input1.SetA(0);
                if(parties[id])
                {
                    for(i = 0; i < NOMBRE_SAUVEGARDES; i++)
                    {
                        if(parties[i])
                        {
                            delete parties[i];
                        }
                    }
                    return id;
                }
            }
            if(input1.GetB())
            {
                for(i = 0; i < NOMBRE_SAUVEGARDES; i++)
                {
                    if(parties[i])
                    {
                        delete parties[i];
                    }
                }
                situation = SITUATION_ECRAN_TITRE;
                input1.SetB(0);
            }
            break;
        default:
            return NOUVELLE_PARTIE;
        }
    }
    return NOUVELLE_PARTIE;
}

void AfficherEcran_Titre(int choix)
{
    system("cls"); //efface l'écran
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255); // Select the color for drawing.
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    cout << "JeuOne" << endl;
    BlocGraphique("JeuOne").Afficher(0,0);
    AfficherCurseurEmplacement(choix,0);
    elements_graphiques[P_blank]->Afficher(0,0,0,2);
    cout << "Charger";
    BlocGraphique("Charger").Afficher(0,0,1,2);
    AfficherCurseurEmplacement(choix,1);
    elements_graphiques[P_blank]->Afficher(0,0,10,2);
    cout << "Nouvelle";
    BlocGraphique("Nouvelle").Afficher(0,0,11,2);
    AfficherCurseurEmplacement(choix,2);
    elements_graphiques[P_blank]->Afficher(0,0,20,2);
    cout << "Quitter" << endl;
    BlocGraphique("Quitter").Afficher(0,0,21,2);
    elements_graphiques[P_arrow]->Afficher(0,0,10*choix,2);
}

void AfficherCharger(Partie** parties, int id)
{
    system("cls"); //efface l'écran
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    int i;
    for(i = 0; i < NOMBRE_SAUVEGARDES; i++)
    {
        AfficherCurseurEmplacement(id, i);
        elements_graphiques[P_blank]->Afficher(0,0,0,2+i);
        cout << ":" << parties[i]->GetEquipe()->GetHeros(0)->GetNom() << " Temps " << parties[i]->GetTemps() << endl;
        BlocGraphique(":" + parties[i]->GetEquipe()->GetHeros(0)->GetNom() + " Temps " + Int2String(parties[i]->GetTemps()) ).Afficher(0,0,1,2+i);
    }
    elements_graphiques[P_arrow]->Afficher(0,0,0,2+id);

}
