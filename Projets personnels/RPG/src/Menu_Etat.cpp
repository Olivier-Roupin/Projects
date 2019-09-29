#include "Menu_Etat.h"

using namespace std;

int Etat(Equipe* equipe, int& choix_heros)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    //int choix(0);
    while(not(input1.GetB()))
    {
        AfficherEtat(equipe->GetHeros(choix_heros));
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
    }
    return 0;
}

void AfficherEtat(Heros* heros)
{
    system("cls"); //efface l'écran
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    cout << "Nom : " << heros->GetNom() << endl;
    BlocGraphique("Nom: " + heros->GetNom()).Afficher(0,0,0,0);
    cout << "Statut : " << heros->GetStatut() << endl;
    BlocGraphique("Statut:").Afficher(0,0,0,1);
    cout << "Vie : " << heros->GetVie() << " / " << heros->GetVieMax() << endl;
    BlocGraphique("Vie: " + Int2String(heros->GetVie()) + " / " + Int2String(heros->GetVieMax())).Afficher(0,0,0,2);
    cout << "Magie : " << heros->GetMagie() << " / "<< heros->GetMagieMax() << endl;
    BlocGraphique("Magie: " + Int2String(heros->GetMagie()) + " / " + Int2String(heros->GetMagieMax())).Afficher(0,0,0,3);
    cout << "Vitesse : " << heros->GetVitesse() << endl;
    BlocGraphique("Vitesse: " + Int2String(heros->GetVitesse())).Afficher(0,0,0,4);
    cout << "AttaqueP : " << heros->GetAttaqueP() << endl;
    BlocGraphique("Attaque P: " + Int2String(heros->GetAttaqueP())).Afficher(0,0,0,5);
    cout << "AttaqueM : " << heros->GetAttaqueM() << endl;
    BlocGraphique("Attaque M: " + Int2String(heros->GetAttaqueM())).Afficher(0,0,0,6);
    cout << "Precision : " << heros->GetPrecision() << endl;
    BlocGraphique("Precision: " + Int2String(heros->GetPrecision())).Afficher(0,0,0,7);
    cout << "DefenseP : " << heros->GetDefenseP() << endl;
    BlocGraphique("Defense P: " + Int2String(heros->GetDefenseP())).Afficher(0,0,0,8);
    cout << "DefenseM : " << heros->GetDefenseM() << endl;
    BlocGraphique("Defense M: " + Int2String(heros->GetDefenseM())).Afficher(0,0,0,9);
    cout << "Esquive : " << heros->GetEsquive() << endl;
    BlocGraphique("Esquive: " + Int2String(heros->GetEsquive())).Afficher(0,0,0,10);
    cout << "Niveau : " << heros->GetNiveau() << " Experience : " << heros->GetExperience() << endl;
    BlocGraphique("Niveau: " + Int2String(heros->GetNiveau())).Afficher(0,0,0,11);
    BlocGraphique("Experience: " + Int2String(heros->GetExperience())).Afficher(0,0,15,11);
    AfficherChoixEquipement(heros);
}
