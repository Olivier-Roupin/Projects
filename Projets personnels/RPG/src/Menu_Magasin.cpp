#include "Menu_Magasin.h"

using namespace std;

int Magasins(Inventaire* inventaire, Equipe* equipe, Magasin* magasin, int &Or)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    while(not(input1.GetB()))
    {
        AfficherMagasins(inventaire, choix, Or);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1.Getgauche())
        {
            if (choix > 0)
                choix--;
            input1.Setgauche(0);
        }
        if(input1.Getdroite())
        {
            if (choix < NOMBRE_CHOIX_MAGASIN - 1)
                choix++;
            input1.Setdroite(0);
        }
        if(input1.GetA())
        {
            switch(choix)
            {
            case MAGASIN_ACHETER:
                Magasins_Acheter(inventaire,magasin, Or);
                break;
            case MAGASIN_VENDRE:
                Magasins_Vendre(inventaire,magasin, Or);
                break;
            case MAGASIN_QUITTER:
                input1.SetA(0);
                return 0;
                break;
            default:
                input1.SetA(0);
                return -1;
                break;
            }
            input1.SetA(0);
        }
    }
    return 0;
}

int Magasins_Acheter(Inventaire* inventaire, Magasin* magasin, int &Or)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    while(not(input1.GetB()))
    {
        AfficherMagasins_Acheter(magasin, inventaire, choix, Or);
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
            if(choix < magasin->GetNombre() - 1)
                choix++;
            input1.Setbas(0);
        }
        if(input1.GetA())
        {
            if(Or >= magasin->GetObjets(choix)->GetPrix())
            {
                inventaire->AjouterObjets(magasin->GetObjets(choix));
                Or -= magasin->GetObjets(choix)->GetPrix();
            }
            input1.SetA(0);
        }
    }
    return 0;
}

int Magasins_Vendre(Inventaire* inventaire, Magasin* magasin, int &Or)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;
    int choix(0);
    while(not(input1.GetB()))
    {
        AfficherMagasins_Vendre(inventaire, choix, Or);
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
            if(Or <= MAX_OR - inventaire->GetObjets(choix)->GetPrix())
            {
                Or += inventaire->GetObjets(choix)->GetPrix();
                inventaire->RetirerObjets(inventaire->GetObjets(choix)->GetObjet()); //On retire l'objet après sinon le prix est nul
            }
            else
                Or = MAX_OR;
            input1.SetA(0);
        }
    }
    return 0;
}

void AfficherMagasins(Inventaire* inventaire, int choix, int Or)
{
    system("cls"); //efface l'écran
    cout << "Magasin" << endl;
    cout << "Or: " << Or << endl;
    AfficherCurseurEmplacement(choix,MAGASIN_ACHETER);
    cout << "Acheter";
    AfficherCurseurEmplacement(choix,MAGASIN_VENDRE);
    cout << "Vendre";
    AfficherCurseurEmplacement(choix,MAGASIN_QUITTER);
    cout << "Quitter" << endl;
}

void AfficherMagasins_Acheter(Magasin* magasin, Inventaire* inventaire, int choix, int Or)
{
    system("cls"); //efface l'écran
    int premier(PremierObjetAffiche(choix));
    int i;
    cout << "Acheter" << endl;
    for(i = premier; i < min(premier + NOMBRE_OBJETS_AFFICHES, magasin->GetNombre()); i++)
    {
        AfficherCurseurEmplacement(choix,i);
        cout<<i<<": "<<magasin->GetNom(i)<<" Prix: "<<magasin->GetPrix(i)<<" Inventaire: "<<inventaire->GetNombreObjets(magasin->GetObjets(i))<<endl;
    }
}

void AfficherMagasins_Vendre(Inventaire* inventaire, int choix, int Or)
{
    system("cls"); //efface l'écran
    int premier(PremierObjetAffiche(choix));
    int i;
    cout << "Vendre" << endl;
    for(i = premier; i < premier + NOMBRE_OBJETS_AFFICHES; i++)
    {
        AfficherCurseurEmplacement(choix,i);
        cout<<i<<": "<<inventaire->GetNom(i)<<" Prix: "<<inventaire->GetPrix(i)<<" Reste: "<<inventaire->GetNombre(i)<<endl;
    }
}
