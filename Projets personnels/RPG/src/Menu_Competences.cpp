#include "Menu_Competences.h"

using namespace std;

int Competences(Equipe* equipe, Carte* carte)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix_heros(0);
    while(not(input1.GetB()))
    {
        AfficherCompetences(equipe, choix_heros);
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
            {
                ChoixCompetences(equipe,carte,choix_heros);
            }
            input1.SetA(0);
        }
    }
    return 0;
}

void ChoixCompetences(Equipe* equipe, Carte* carte, int &choix_heros)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix_competences(0);
    while(not(input1.GetB()))
    {
        AfficherChoixCompetences(equipe->GetHeros(choix_heros), choix_competences);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Gethaut())
        {
            if(choix_competences > 0)
                choix_competences--;
            input1.Sethaut(0);
        }
        if(input1.Getbas())
        {
            if(choix_competences < MAX_SORTS - 1)
                choix_competences++;
            input1.Setbas(0);
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
            if(equipe->GetHeros(choix_heros)->GetMagie() >= equipe->GetHeros(choix_heros)->GetSorts(choix_competences)->GetCoutMagie() && equipe->GetHeros(choix_heros)->GetVie() > 0)
            {
                UtiliserCompetence(equipe, carte, equipe->GetHeros(choix_heros)->GetSorts(choix_competences), choix_heros);
            }
            input1.SetA(0);
        }
    }
}

void AfficherCompetences(Equipe* equipe, int choix) //Déplacer dans Menu() ?
{
    system("cls"); //efface l'écran
    //AfficherMenu(Partie* partie, 2, 0);
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

void AfficherChoixCompetences(Heros* heros, int choix)
{
    system("cls"); //efface l'écran
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    int i;
    int premier(PremiereCompetenceAffiche(choix));
    cout << heros->GetNom() << endl;
    BlocGraphique(heros->GetNom()).Afficher(0,0,0,0);
    for(i = premier; i < premier + NOMBRE_OBJETS_AFFICHES; i++)
    {
        elements_graphiques[P_blank]->Afficher(0,0,0,i-premier+1);
        AfficherCurseurEmplacement(choix,i);
        cout<< i << ": " << heros->GetSorts(i)->GetNom() << endl;
        BlocGraphique(Int2String(i)+": "+heros->GetSorts(i)->GetNom()).Afficher(0,0,1,i-premier+1);
    }
    elements_graphiques[P_arrow]->Afficher(0,0,0,choix-premier+1);
}

int PremiereCompetenceAffiche(int choix)
{
    if(choix < NOMBRE_OBJETS_AFFICHES/2)
        return 0;
    if(choix > MAX_SORTS - NOMBRE_OBJETS_AFFICHES + 1)
        return MAX_SORTS - NOMBRE_OBJETS_AFFICHES;
    return choix - NOMBRE_OBJETS_AFFICHES/2;
}

int UtiliserCompetence(Equipe* equipe, Carte* carte, Capacite* capacite, int choix_heros)
{
    if(capacite->GetEffet()->GetDisponibilite() == TOUJOURS || capacite->GetEffet()->GetDisponibilite() == MENU)
    {
        if(capacite->GetEffet()->GetDefaut_Quantite() == QUANTITE_FACTION || capacite->GetEffet()->GetDefaut_Cible() == CIBLE_TOUS)
        {
            UtiliserCompetence(capacite, equipe);
            equipe->GetHeros(choix_heros)->ChangerMagie(-capacite->GetCoutMagie());
            equipe->GetHeros(choix_heros)->ChangerVie(-capacite->GetCoutVie());
            equipe->GetHeros(choix_heros)->ChangerMagieP(-capacite->GetCoutMagieP());
            equipe->GetHeros(choix_heros)->ChangerVieP(-capacite->GetCoutVieP());
        }
        else if(capacite->GetEffet()->GetDefaut_Cible() == CIBLE_LANCEUR || capacite->GetEffet()->GetDefaut_Cible() >= 0)
        {
            int choix(-1);
            choix = Equipe_Reduit(equipe);
            if(choix != -1 && equipe->GetHeros(choix))
            {
                UtiliserCompetence(capacite, equipe->GetHeros(choix));
                equipe->GetHeros(choix_heros)->ChangerMagie(-capacite->GetCoutMagie());
                equipe->GetHeros(choix_heros)->ChangerVie(-capacite->GetCoutVie());
                equipe->GetHeros(choix_heros)->ChangerMagieP(-capacite->GetCoutMagieP());
                equipe->GetHeros(choix_heros)->ChangerVieP(-capacite->GetCoutVieP());
            }
        }
        return 0;
    }
    return -1;
}

int UtiliserCompetence(Capacite* capacite, Personnage* cible)
{
    Effet* effet(0);
    effet = capacite->GetEffet();
    if(cible)
    {
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

int UtiliserCompetence(Capacite* capacite, Equipe* cible)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        UtiliserCompetence(capacite,cible->GetHeros(i));
    }
    return 0;
}
