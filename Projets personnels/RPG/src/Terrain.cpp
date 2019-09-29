#include "Terrain.h"

using namespace std;

int Terrain(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input* input1(partie->GetInput());
    partie->SetTerrain(1);
    int combat(0); //un combat se lance si vaut 1
    int meneur(0); //indice dans l'équipe du personnage affiché à l'écran
    partie->SetSituation(SITUATION_INITIALISATION);
    int e(-1);
    int dX(0);
    int dY(0);
    while(partie->GetTerrain())
    {
        AfficherTerrain(partie,meneur);
        input1->Actualiser();
        ActualiserEvenements(partie);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        switch(partie->GetSituation())
        {
        case SITUATION_DEPLACEMENT:
            partie->SetOrientation(OrientationHeros(input1));
            DeplacementHeros(dX,dY,input1);
            if(DeplacerHeros(partie,dX,dY)) //si le personnage se déplace
            {
                e = TestContact(partie);
                if(e != -1)
                {
                    partie->SetSituation(SITUATION_CONTACT);
                }
                else if(partie->GetCarte()->GetRencontres(partie->GetX(),partie->GetY()))
                {
                    combat = not(rand() % 10); //1 chance sur 10 d'avoir un combat
                }
            }
            if(combat)
            {
                combat = 0;
                input1->Vider();
                DemarrerCombat(partie,partie->GetCarte()->GetRencontreset()->GetGroupes(partie->GetCarte()->GetRencontres(partie->GetX(),partie->GetY()),rand()%\
                               partie->GetCarte()->GetRencontreset()->GetNombreGroupes(partie->GetCarte()->GetRencontres(partie->GetX(),partie->GetY()))));
            }
            if(input1->GetY())
            {
                do
                {
                    meneur = (meneur+1) % MAX_HEROS_EQUIPE;
                }
                while(not(partie->GetEquipe()->GetHeros(meneur)));
                input1->SetY(0);
            }
            if(input1->GetX())
            {
                input1->Vider();
                if(Menu(partie))
                    return 0; //Quitter la partie et retour à l'écran titre
            }
            if(input1->GetA())
            {
                e = TestEvenement(partie->GetCarte(),partie->GetX()+partie->GetOrientationX(),partie->GetY()+partie->GetOrientationY());
                if(partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_INTERACTION)) //e!=-1 ?
                {
                    partie->SetSituation(SITUATION_INTERACTION);
                }
                input1->SetA(0);
            }
            break;
        case SITUATION_INTERACTION:
            partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_INTERACTION)->Executer(partie);
            break;
        case SITUATION_CONTACT:
            partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT)->Executer(partie);
            break;
        case SITUATION_AUTOMATIQUE:
            partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_AUTOMATIQUE)->Executer(partie);
            break;
        case SITUATION_RECHERCHE:
            e = TestAutomatique(partie->GetCarte(), e);
            if(e == -1)
            {
                partie->SetSituation(SITUATION_DEPLACEMENT);
            }
            else
            {
                partie->SetSituation(SITUATION_AUTOMATIQUE);
            }
            break;
        case SITUATION_INITIALISATION:
            e = -1;
            partie->SetSituation(SITUATION_RECHERCHE);
            break;
        }
    }
    return 0;
}

void AfficherTerrain(Partie* partie, int meneur)
{
    system("cls"); //efface l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 32, 255); // Select the color for drawing.
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.
    AfficherCarte(partie->GetCarte(), partie->GetX(), partie->GetY(), partie->GetOrientation());
    AfficherHeros(partie, meneur);
    AfficherEvenements(partie->GetCarte(), partie->GetX(), partie->GetY());
}

void AfficherHeros(Partie *partie, int meneur)
{
    cout << partie->GetEquipe()->GetHeros(meneur)->GetNom() << " X: " << partie->GetX() << " Y: " << partie->GetY() << " Orientation: " << partie->GetOrientation() << endl;
    //elements_graphiques[P_blank]->Afficher(0,0,20,2);
    BlocGraphique(partie->GetEquipe()->GetHeros(meneur)->GetNom()).Afficher(0,0,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2);
}

void AfficherEvenements(Carte* carte, int X, int Y)
{
    int Xe(0);
    int Ye(0);
    int i;
    for(i = 0; i < carte->GetNombre(); i++)
    {
        if(carte->GetEvenements(i))
        {
            Xe = carte->GetEvenements(i)->GetX() - X + LARGEUR_FENETRE/2;
            Ye = carte->GetEvenements(i)->GetY() - Y + HAUTEUR_FENETRE/2;
            if(Xe >= 0 && Xe < LARGEUR_FENETRE && Ye >= 0 && Ye < HAUTEUR_FENETRE)
            {
                cout << carte->GetEvenements(i)->GetImage() << " X: " << Xe << " Y: " << Ye << endl;
            }
            else
            {
                cout << endl;
            }
        }
    }
}

void ActualiserEvenements(Partie* partie)
{
    int i;
    Carte* carte(partie->GetCarte());
    for(i = 0; i < carte->GetNombre(); i++)
    {
        if(carte->GetEvenements(i)->GetScripts(SCRIPT_CONTINU))
        {
            carte->GetEvenements(i)->GetScripts(SCRIPT_CONTINU)->Executer(partie);
        }
    }
}

void AfficherCarte(Carte* carte, int X, int Y, int Orientation)
{
    int i,j;
    if(carte->GetRepetition())
    {
        for(i = 0; i < HAUTEUR_FENETRE; i++)
        {
            for(j = 0; j < LARGEUR_FENETRE; j++)
            {
                AfficherTile(carte, X, Y, Orientation, (j+X-LARGEUR_FENETRE/2+carte->GetLargeur())%carte->GetLargeur(), (i+Y-HAUTEUR_FENETRE/2+carte->GetHauteur())%carte->GetHauteur());
            }
            cout << endl;
        }
    }
    else
    {
        for(i = 0; i < HAUTEUR_FENETRE; i++)
        {
            for(j = 0; j < LARGEUR_FENETRE; j++)
            {
                if(j+X-LARGEUR_FENETRE/2 < carte->GetLargeur() && j+X-LARGEUR_FENETRE/2 >= 0 && i+Y-HAUTEUR_FENETRE/2 < carte->GetHauteur() && i+Y-HAUTEUR_FENETRE/2 >= 0)
                {
                    AfficherTile(carte, X, Y, Orientation, j+X-LARGEUR_FENETRE/2, i+Y-HAUTEUR_FENETRE/2);
                }
                else
                {
                    cout << carte->GetTileset()->GetImage(0);
                }
            }
            cout << endl;
        }
    }
}

void AfficherImage(string image, int j, int i)
{
    cout << image;
}

void AfficherTile(Carte* carte, int X, int Y, int Orientation, int j, int i)
{
    int e(-1);
    for(int k(0); k < carte->GetNombre(); k++)
    {
        if(carte->GetEvenements(k))
        {
            if(i == carte->GetEvenements(k)->GetY() && j == carte->GetEvenements(k)->GetX())
            {
                e = k;
                k = carte->GetNombre();
            }
        }
    }
    if(carte->GetHaut(j,i))
    {
        cout << carte->GetTileset()->GetImage(carte->GetHaut(j,i));
        //BlocGraphique(carte->GetTileset()->GetImage(carte->GetHaut(j,i))).Afficher(0,0,j-X+LARGEUR_FENETRE/2,i-Y+HAUTEUR_FENETRE/2);
        BlocGraphique(carte->GetTileset()->GetImage(carte->GetHaut(j,i)),2).Afficher(0,0,j-X+LARGEUR_FENETRE/2,i-Y+HAUTEUR_FENETRE/2);
    }
    else if(e!=-1 && carte->GetEvenements(e)->GetZ()==Z_HAUT)
    {
        cout << carte->GetEvenements(e)->GetImage();
    }
    else if(i == Y && j == X)
    {
        switch(Orientation)
        {
        case ORIENTATION_DROITE:
            cout << ">";
            break;
        case ORIENTATION_HAUT:
            cout << "^";
            break;
        case ORIENTATION_GAUCHE:
            cout << "<";
            break;
        case ORIENTATION_BAS:
            cout << "v";
            break;
        default:
            cout << "o";
        }
    }
    else if(e!=-1 && carte->GetEvenements(e)->GetZ()==Z_MILIEU)
    {
        cout << carte->GetEvenements(e)->GetImage();
    }
    else if(carte->GetMoyen(j,i))
    {
        cout << carte->GetTileset()->GetImage(carte->GetMoyen(j,i));
        BlocGraphique(carte->GetTileset()->GetImage(carte->GetMoyen(j,i))).Afficher(0,0,j-X+LARGEUR_FENETRE/2,i-Y+HAUTEUR_FENETRE/2);
    }
    else if(e!=-1 && carte->GetEvenements(e)->GetZ()==Z_BAS)
    {
        cout << carte->GetEvenements(e)->GetImage();
    }
    else
    {
        cout << carte->GetTileset()->GetImage(carte->GetBas(j,i));
        BlocGraphique(carte->GetTileset()->GetImage(carte->GetBas(j,i))).Afficher(0,0,j-X+LARGEUR_FENETRE/2,i-Y+HAUTEUR_FENETRE/2);
    }
}

int OrientationHeros(Input* input)
{
    if(input->Getbas())
    {
        return ORIENTATION_BAS;
    }
    if(input->Getdroite())
    {
        return ORIENTATION_DROITE;
    }
    if(input->Getgauche())
    {
        return ORIENTATION_GAUCHE;
    }
    if(input->Gethaut())
    {
        return ORIENTATION_HAUT;
    }
    return -1;
}

void DeplacementHeros(int &dX, int &dY, Input* input)
{
    dX = 0;
    dY = 0;
    if(input->Getbas())
    {
        dX = 0;
        dY = 1;
        input->Setbas(0);
    }
    if(input->Getdroite())
    {
        dX = 1;
        dY = 0;
        input->Setdroite(0);
    }
    if(input->Getgauche())
    {
        dX = -1;
        dY = 0;
        input->Setgauche(0);
    }
    if(input->Gethaut())
    {
        dX = 0;
        dY = -1;
        input->Sethaut(0);
    }
}

bool DeplacerHeros(Partie* partie, int dX, int dY)
{
    if((dX||dY) && TestCollision(partie->GetCarte(),partie->GetX()+dX,partie->GetY()+dY, Z_MILIEU)) //si le personnage se déplace
    {
        partie->ChangerX(dX);
        partie->ChangerY(dY);
        partie->AjouterPas();
        return 1;
    }
    return 0;
}

int TestEvenement(Carte* carte, int X, int Y, int Z)
{
    int k;
    if(carte->GetRepetition())
    {
        X = (X+carte->GetLargeur()) % carte->GetLargeur();
        Y = (Y+carte->GetHauteur()) % carte->GetHauteur();
    }
    for(k = 0; k < carte->GetNombre(); k++)
    {
        if(carte->GetEvenements(k))
        {
            if(X==carte->GetEvenements(k)->GetX() && Y==carte->GetEvenements(k)->GetY() && (Z==-1||Z==carte->GetEvenements(k)->GetZ()))
            {
                return k;
            }
        }
    }
    return -1;
}

int TestContact(Partie* partie)
{
    int e(-1);
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),Z_BAS);
    if(partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
    {
        return e;
    }
    e = TestEvenement(partie->GetCarte(),partie->GetX(),partie->GetY(),Z_HAUT);
    if(partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
    {
        return e;
    }
    e = TestEvenement(partie->GetCarte(),partie->GetX()+partie->GetOrientationX(),partie->GetY()+partie->GetOrientationY(), Z_MILIEU);
    if(partie->GetCarte()->GetEvenements(e)->GetScripts(SCRIPT_CONTACT))
    {
        return e;
    }
    return -1;
}

bool TestCollision(Carte* carte, int X, int Y, int Z)
{
    int e;
    if(carte->GetRepetition())
    {
        X = (X+carte->GetLargeur()) % carte->GetLargeur();
        Y = (Y+carte->GetHauteur()) % carte->GetHauteur();
    }
    e = TestEvenement(carte,X,Y);
    return carte->GetTileset()->GetTraversable(carte->GetBas(X,Y)) &&\
           carte->GetTileset()->GetTraversable(carte->GetMoyen(X,Y)) &&\
           carte->GetTileset()->GetTraversable(carte->GetHaut(X,Y)) &&\
           (e==-1 || carte->GetEvenements(e)->GetZ()!=Z);
}

int TestAutomatique(Carte* carte, int e)
{
    int k;
    for(k = e+1; k < carte->GetNombre(); k++) //on cherche les événemetns automatiques suivants (après e)
    {
        if(carte->GetEvenements(k)->GetScripts(SCRIPT_AUTOMATIQUE))
        {
            return k;
        }
    }
    return -1; //on retourne -1 si e est trop grand ou si on ne trouve pas d'événement automatique
}

int AfficherMessage(Partie* partie, string val)
{
    cout << val << endl;
    if(partie->GetInput()->GetA())
    {
        partie->GetInput()->SetA(0);
        return 1;
    }
    return 0;
}

int AfficherChoix(Partie* partie, int nombre, string val1, string val2, string val3, string val4)
{
    int i;
    string val[NOMBRE_CHOIX_TERRAIN] = {val1, val2, val3, val4};
    Input* input(partie->GetInput());
    if(input->Getbas())
    {
        partie->SetChoix((partie->GetChoix() + nombre - 1) % nombre);
        input->Setbas(0);
    }
    if(input->Gethaut())
    {
        partie->SetChoix((partie->GetChoix() + 1) % nombre);
        input->Sethaut(0);
    }
    for(i = 0; i < nombre; i++)
    {
        AfficherCurseurEmplacement(partie->GetChoix(),i);
        cout << val[i] << endl;
    }
    if(input->GetA())
    {
        input->SetA(0);
        return 1;
    }
    return 0;
}

void TeleporterEquipe(Partie* partie, Carte* carte, int x, int y, int orientation)
{
    partie->SetCarte(carte);
    partie->SetX(x);
    partie->SetY(y);
    partie->SetOrientation(orientation);
}

int DeplacerEvenement(Carte* carte, int id, int dX, int dY, int Xheros, int Yheros)
{
    Evenement* evenement(carte->GetEvenements(id));
    if(TestCollision(carte, evenement->GetX()+dX, evenement->GetY()+dY, evenement->GetZ()) && (evenement->GetX()+dX!=Xheros || evenement->GetY()+dY!=Yheros || evenement->GetZ()!=Z_MILIEU))
    {
        evenement->ChangerX(dX);
        evenement->ChangerY(dY);
        if(carte->GetRepetition())
        {
            evenement->SetX((evenement->GetX()+carte->GetLargeur()) % carte->GetLargeur());
            evenement->SetY((evenement->GetY()+carte->GetHauteur()) % carte->GetHauteur());
        }
        return 1;
    }
    return 0;
}

void OuvrirMagasin(Partie* partie, Magasin* magasin)
{
    if(magasin)
    {
        int Or(partie->GetOr());
        Magasins(partie->GetInventaire(), partie->GetEquipe(), magasin, Or);
        partie->SetOr(Or);
    }
}

void DemarrerCombat(Partie* partie, GroupeMonstres* groupe, bool gameover)
{
    if(groupe)
    {
        partie->SetGroupeCombat(groupe);
        if(Combat(partie) && gameover) //si on perd le combat et que ce n'est pas prévu, on perd le jeu
        {
            partie->SetTerrain(0);
        }
    }
}
