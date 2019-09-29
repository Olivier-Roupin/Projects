#include "Menu_Configuration.h"

using namespace std;

int Configuration(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    while(not(input1.GetB()))
    {
        AfficherConfiguration(partie, choix);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Gethaut())
        {
            choix = (choix+NOMBRE_CHOIX_CONFIGURATION-1) % NOMBRE_CHOIX_CONFIGURATION;
            input1.Sethaut(0);
        }
        if(input1.Getbas())
        {
            choix = (choix+1) % NOMBRE_CHOIX_CONFIGURATION;
            input1.Setbas(0);
        }
        switch(choix)
        {
        case 0:
            if(input1.Getgauche())
            {
                partie->ChangerVitesseCombat(-1);
                input1.Setgauche(0);
            }
            if(input1.Getdroite())
            {
                partie->ChangerVitesseCombat(+1);
                input1.Setdroite(0);
            }
            break;
        case 1:
            if(input1.Getgauche())
            {
                partie->ChangerModeCombat(-1);
                input1.Setgauche(0);
            }
            if(input1.Getdroite())
            {
                partie->ChangerModeCombat(+1);
                input1.Setdroite(0);
            }
            break;
        case 2:
            if(input1.Getgauche())
            {
                partie->ChangerMemoriserCurseur();
                input1.Setgauche(0);
            }
            if(input1.Getdroite())
            {
                partie->ChangerMemoriserCurseur();
                input1.Setdroite(0);
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

void AfficherConfiguration(Partie* partie, int choix)
{
    int i;
    system("cls"); //efface l'écran
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    elements_graphiques[P_blank]->Afficher(0,0,0,1);
    AfficherCurseurEmplacement(choix,0);
    cout << "Vitesse des combats : ";
    BlocGraphique("Vitesse:").Afficher(0,0,1,1);
    for(i = MIN_VITESSE_COMBAT; i <= MAX_VITESSE_COMBAT; i++)
    {
        elements_graphiques[P_blank]->Afficher(0,0,9+2*(i-MIN_VITESSE_COMBAT),1);
        AfficherCurseurEmplacement(partie->GetVitesseCombat(),i);
        BlocGraphique(Int2String(i)).Afficher(0,0,10+2*(i-MIN_VITESSE_COMBAT),1);
        cout << i;
    }
    cout << endl;
    elements_graphiques[P_arrow]->Afficher(0,0,9+2*(partie->GetVitesseCombat()-MIN_VITESSE_COMBAT),1);


    elements_graphiques[P_blank]->Afficher(0,0,0,2);
    AfficherCurseurEmplacement(choix,1);
    cout << "Mode de combat : ";
    BlocGraphique("Combat:").Afficher(0,0,1,2);
    elements_graphiques[P_blank]->Afficher(0,0,8,2);
    AfficherCurseurEmplacement(partie->GetModeCombat(), MODE_ACTIF);
    cout << "Actif ";
    BlocGraphique("Actif").Afficher(0,0,9,2);
    elements_graphiques[P_blank]->Afficher(0,0,14,2);
    AfficherCurseurEmplacement(partie->GetModeCombat(), MODE_SEMI_ACTIF);
    cout << "Semi-actif ";
    BlocGraphique("Semi").Afficher(0,0,15,2);
    elements_graphiques[P_blank]->Afficher(0,0,20,2);
    AfficherCurseurEmplacement(partie->GetModeCombat(), MODE_PASSIF);
    cout << "Passif" << endl;
    BlocGraphique("Passif").Afficher(0,0,21,2);
    elements_graphiques[P_arrow]->Afficher(0,0,8+6*partie->GetModeCombat(),2);


    elements_graphiques[P_blank]->Afficher(0,0,0,3);
    AfficherCurseurEmplacement(choix,2);
    cout << "Mémoriser position curseur : ";
    BlocGraphique("Memoriser curseur:").Afficher(0,0,1,3);
    elements_graphiques[P_blank]->Afficher(0,0,19,3);
    AfficherCurseurEmplacement(partie->GetMemoriserCurseur(), false);
    cout << "Non ";
    BlocGraphique("Non").Afficher(0,0,20,3);
    elements_graphiques[P_blank]->Afficher(0,0,23,3);
    AfficherCurseurEmplacement(partie->GetMemoriserCurseur(), true);
    cout << "Oui" << endl;
    BlocGraphique("Oui").Afficher(0,0,24,3);
    elements_graphiques[P_arrow]->Afficher(0,0,19+partie->GetMemoriserCurseur()*4,3);


    elements_graphiques[P_arrow]->Afficher(0,0,0,1+choix);
}
