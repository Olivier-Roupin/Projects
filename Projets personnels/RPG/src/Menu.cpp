#include "Menu.h"

using namespace std;

int Menu(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    int choix2(-1);
    int choix3(-1);
    while(not(input1.GetB()) && not(input1.GetX()) && (choix != 6 || not(input1.GetA())))
    {
        AfficherMenu(partie, choix, choix2, choix3);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(choix2 == -1 && choix3 == -1)
        {
            if(input1.Getgauche() || input1.Gethaut())
            {
                choix = (choix+NOMBRE_CHOIX_MENU-1) % NOMBRE_CHOIX_MENU;
                input1.Setgauche(0);
                input1.Sethaut(0);
            }
            if(input1.Getdroite() || input1.Getbas())
            {
                choix = (choix+1) % NOMBRE_CHOIX_MENU;
                input1.Setdroite(0);
                input1.Setbas(0);
            }
            if(input1.GetA())
            {
                switch(choix)
                {
                case 0:
                    Objets(partie->GetInventaire(),partie->GetEquipe(),partie->GetCarte());
                    break;
                case 1:
                    choix3 = 0;
                    //Equipements(partie->GetInventaire(),partie->GetEquipe());
                    break;
                case 2:
                    choix3 = 0;
                    //Competences(partie->GetEquipe(),partie->GetCarte());
                    break;
                case 3:
                    choix3 = 0;
                    //Etat(partie->GetEquipe());
                    break;
                case 4:
                    Configuration(partie);
                    break;
                case 5:
                    Sauver(partie);
                    break;
                case 6:
                    choix2 = 0;
                    break;
                default:
                    break;
                }
                input1.SetA(0);
            }
        }
        else if (choix3 == -1)
        {
            if(input1.Getgauche() || input1.Gethaut())
            {
                choix2 = 1 - choix2;
                input1.Setgauche(0);
                input1.Sethaut(0);
            }
            if(input1.Getdroite() || input1.Getbas())
            {
                choix2 = 1 - choix2;
                input1.Setdroite(0);
                input1.Setbas(0);
            }
            if(input1.GetA())
            {
                if(choix2 == 1)
                    return 1;
                choix2 = -1;
                input1.SetA(0);
            }
            if(input1.GetB())
            {
                choix2 = -1;
                input1.SetB(0);
            }
        }
        else
        {
            if(input1.Getgauche() || input1.Gethaut())
            {
                choix3 = (choix3+MAX_HEROS_EQUIPE-1) % MAX_HEROS_EQUIPE;
                input1.Setgauche(0);
                input1.Sethaut(0);
            }
            if(input1.Getdroite() || input1.Getbas())
            {
                choix3 = (choix3+1) % MAX_HEROS_EQUIPE;
                input1.Setdroite(0);
                input1.Setbas(0);
            }
            if(input1.GetA())
            {
                if(partie->GetEquipe()->GetHeros(choix3))
                {
                    switch(choix)
                    {
                    case 1:
                        ChoixEquipements(partie->GetInventaire(),partie->GetEquipe(),choix3);
                        break;
                    case 2:
                        ChoixCompetences(partie->GetEquipe(),partie->GetCarte(),choix3);
                        break;
                    case 3:
                        Etat(partie->GetEquipe(),choix3);
                        break;
                    default:
                        break;
                    }
                }
                input1.SetA(0);
            }
            if(input1.GetB())
            {
                choix3 = -1;
                input1.SetB(0);
            }
        }
    }
    return 0;
}

void AfficherMenu(Partie* partie, int choix, int choix2, int choix3)
{
    system("cls"); //efface l'écran
    SDL_SetRenderDrawColor(renderer, 0, 32, 0, 255); // Select the color for drawing.
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    cout << "Or : " << partie->GetOr();
    BlocGraphique("Or :").Afficher(0,0,0,9);
    BlocGraphique(Int2String(partie->GetOr())).Afficher(0,0,5,9);

    cout << " Temps : " << partie->GetHeures() << ":" << partie->GetMinutes() << ":" << partie->GetSecondes();
    BlocGraphique("Temps :").Afficher(0,0,0,10);
    BlocGraphique(Int2String(partie->GetTempsJeu())).Afficher(0,0,8,10);

    cout << " Pas : " << partie->GetPas();
    BlocGraphique("Pas :").Afficher(0,0,0,11);
    BlocGraphique(Int2String(partie->GetPas())).Afficher(0,0,6,11);

    cout << " Carte : " << partie->GetCarte()->GetNom() << endl;
    BlocGraphique("Carte :").Afficher(0,0,0,12);
    BlocGraphique(partie->GetCarte()->GetNom()).Afficher(0,0,8,12);

    AfficherEquipe(partie->GetEquipe(),choix3);
    AfficherCurseurEmplacement(choix,0);
    elements_graphiques[P_blank]->Afficher(0,0,0,1);
    cout << "Objets";
    BlocGraphique("Objets").Afficher(0,0,1,1);
    AfficherCurseurEmplacement(choix,1);
    elements_graphiques[P_blank]->Afficher(0,0,0,2);
    cout << "Equipement";
    BlocGraphique("Equipement").Afficher(0,0,1,2);
    AfficherCurseurEmplacement(choix,2);
    elements_graphiques[P_blank]->Afficher(0,0,0,3);
    cout << "Competences";
    BlocGraphique("Competences").Afficher(0,0,1,3);
    AfficherCurseurEmplacement(choix,3);
    elements_graphiques[P_blank]->Afficher(0,0,0,4);
    cout << "Etat";
    BlocGraphique("Etat").Afficher(0,0,1,4);
    AfficherCurseurEmplacement(choix,4);
    elements_graphiques[P_blank]->Afficher(0,0,0,5);
    cout << "Config";
    BlocGraphique("Configuration").Afficher(0,0,1,5);
    AfficherCurseurEmplacement(choix,5);
    elements_graphiques[P_blank]->Afficher(0,0,0,6);
    cout << "Sauver";
    BlocGraphique("Sauver").Afficher(0,0,1,6);
    AfficherCurseurEmplacement(choix,6);
    elements_graphiques[P_blank]->Afficher(0,0,0,7);
    cout << "Quitter" << endl;
    BlocGraphique("Quitter").Afficher(0,0,1,7);
    elements_graphiques[P_arrow]->Afficher(0,0,0,1+choix);
    if(choix2 != -1)
        AfficherQuitter(choix2);
}

void AfficherEquipe(Equipe* equipe, int choix)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        if(equipe->GetHeros(i))
        {
            elements_graphiques[P_blank]->Afficher(0,0,14,i+1);
            AfficherCurseurEmplacement(choix, i);
            cout << i+1 << ": " << equipe->GetHeros(i)->GetNom();
            BlocGraphique(Int2String(i+1)+":").Afficher(0,0,15,i+1);
            if(equipe->GetHeros(i)->GetRang() == RANG_AVANT)
            {
                cout << " avant; ";
                BlocGraphique(equipe->GetHeros(i)->GetNom()).Afficher(0,0,18,i+1);
            }
            else
            {
                cout << " arrière; ";
                BlocGraphique(equipe->GetHeros(i)->GetNom()).Afficher(0,0,21,i+1);
            }
        }
    }
    if(choix >= 0)
        elements_graphiques[P_arrow]->Afficher(0,0,14,choix+1);
    cout << endl;
}

void AfficherQuitter(int choix)
{
    cout << "Vous êtes sûrs ?" << endl;
    BlocGraphique("Vous etes surs ?").Afficher(0,0,0,14);

    AfficherCurseurEmplacement(choix,0);
    elements_graphiques[P_blank]->Afficher(0,0,0,15);
    cout << "Non";
    BlocGraphique("Non").Afficher(0,0,1,15);

    AfficherCurseurEmplacement(choix,1);
    elements_graphiques[P_blank]->Afficher(0,0,5,15);
    cout << "Oui" << endl;
    BlocGraphique("Oui").Afficher(0,0,6,15);

    elements_graphiques[P_arrow]->Afficher(0,0,5*choix,15);
}
