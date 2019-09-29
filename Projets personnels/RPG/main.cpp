#include <iostream>

using namespace std;

//Test Scenes
#include <Equipable.h>
#include <Utilisable.h>
#include <Ecran_titre.h>
#include <Terrain.h>

#include <moteur_graphique.h>
//#include <BoiteTexte.h>
#include <Input.h>

#define NOMBRE_EFFETS 200
#define NOMBRE_CAPACITES 100
#define NOMBRE_OBJETS 100
#define NOMBRE_EVENEMENTS 1000
#define NOMBRE_CARTES 100
#define NOMBRE_MONSTRES 100
#define NOMBRE_GROUPES_MONSTRES 100
#define NOMBRE_HEROS 8
#define NOMBRE_TILESETS 100
#define NOMBRE_SCRIPTS 1000
#define NOMBRE_MAGASINS 50
#define NOMBRE_ALTERATIONS 20

Effet* effets[NOMBRE_EFFETS+1];
Capacite* capacites[NOMBRE_CAPACITES+1];
Objet* objets[NOMBRE_OBJETS+1];
Evenement* evenements[NOMBRE_EVENEMENTS+1];
Carte* cartes[NOMBRE_CARTES+1];
Monstre* monstres[NOMBRE_MONSTRES+1];
GroupeMonstres* groupes_monstres[NOMBRE_GROUPES_MONSTRES+1];
Heros* heross[NOMBRE_HEROS+1];
Tileset* tilesets[NOMBRE_TILESETS+1];
Script* scripts[NOMBRE_SCRIPTS+1];
Magasin* magasins[NOMBRE_MAGASINS+1];
Alteration* alterations[NOMBRE_ALTERATIONS+1];

int main(int argc, char *argv[])
{
    ifstream flux;
#include <EFFETS.h>
#include <OBJETS.h>
#include <MAGASINS.h>
#include <HEROSS.h>
#include <GROUPESMONSTRES.h>
#include <CARTES.h>
#include <CAPACITES.h>
#include <ALTERATIONS.h>
    init((char*)"JeuOne");
#include <GRAPHISMES.h>
    int choix(0);
    do
    {
        choix = Ecran_titre();
        if(choix != QUITTER)
        {
            Partie partie(choix);
            partie.SetTemps(partie.GetTemps() - (double)clock()/CLOCKS_PER_SEC);
            Terrain(&partie);
        }
    }
    while(choix != QUITTER);
#include <ALTERATIONS_D.h>
#include <MAGASINS_D.h>
#include <HEROSS_D.h>
#include <GROUPESMONSTRES_D.h>
#include <OBJETS_D.h>
#include <CAPACITES_D.h>
#include <EFFETS_D.h>
    cout << "On quitte" << endl;
    flush(cout);
    return 0;
}

//Test magasin
/*
int main(int argc, char *argv[])
{
#include <OBJETS.h>
#include <HEROSS.h>
#include <GROUPESMONSTRES.h>
#include <CARTES.h>
#include <EFFETS.h>
#include <CAPACITES.h>
    init((char*)"JeuOne");
#include <GRAPHISMES.h>

    Magasin* magasin = new Magasin(0, 3);
    magasin->AjouterObjet(objets[1]);
    magasin->AjouterObjet(objets[2]);
    magasin->AjouterObjet(objets[3]);

    int choix(0);
    do
    {
        choix = Ecran_titre();
        if(choix != QUITTER)
        {
            Partie partie(choix);
            partie.SetTemps(partie.GetTemps() - (double)clock()/CLOCKS_PER_SEC);
            //Terrain(&partie);
            partie.SetOr(1000);
            int Or = partie.GetOr();
            Magasins(partie.GetInventaire(), partie.GetEquipe(), magasin, Or);
        }
    }
    while(choix != QUITTER);
#include <HEROSS_D.h>
#include <GROUPESMONSTRES_D.h>
#include <OBJETS_D.h>
#include <CAPACITES_D.h>
#include <EFFETS_D.h>
    cout << "On quitte" << endl;
    flush(cout);
    return 0;
}
*/
//Test Scripts
/*
int main(int argc, char *argv[])
{
#include<OBJETS.h>
#include<HEROSS.h>
#include<GROUPESMONSTRES.h>
#include<CARTES.h>
#include<CAPACITES.h>
    init("JeuOne");
#include<GRAPHISMES.h>
    int choix(0);
    choix = Ecran_titre();
    Partie partie(choix);
    //cout << "On quitte" << endl;
    Script script11(&script0,0);
    while(1)
    {
        SDL_Delay(1);
        script11.Executer(&partie,0);
    }
#include<HEROSS_D.h>
#include<GROUPESMONSTRES_D.h>
#include<OBJETS_D.h>
#include<CAPACITES_D.h>
    return 0;
}
*/

//Test Graphismes
/*
int main(int argc, char *argv[])
{
    #include<OBJETS.h>
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input input1;

    init("JeuOne");
    #include<GRAPHISMES.h>
    //BoiteTexte boite1("Hello World",8,8,6,2);
    while (1)
    {
        elements_graphiques[0]->Afficher(16,32);
        elements_graphiques[1]->Afficher(72,72);
        //boite1.Afficher();
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1.Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }

    exit(0);
}
*/

//Test Scripts
/*
#include <Script.h>
int main(int argc, char *argv[])
{
    cout << "Hello world!" << endl;
    Script script1("bdd/script1.txt",0);
    cout << "Script OK" << endl;
    return 0;
}
*/

//Test Cartes
/*
#include <Arme.h>
#include <Bouclier.h>
#include <Armure.h>
#include <Casque.h>
#include <Accessoire.h>
#include <Utilisable.h>
#include <Carte.h>
#include "Ecran_titre.h"
#include "Menu.h"

int main()
{
    cout << "Hello world!" << endl;
#include <OBJETS.h>
#include <CARTES.h>
    cout << "include OK" << endl;
    for(int j = 1; j < NOMBRE_CARTES+1 ; j++)
    {
        for(int i = 0; i < cartes[j]->GetTaille() ; i++)
        {
            cout << cartes[j]->GetTileset()->GetImage(cartes[j]->GetTableau(i));
            if ((i+1) % cartes[j]->GetLargeur() == 0)
            {
                cout << endl;
            }
        }
    }
    cout << "get OK" << endl;
#include <CARTES_D.h>
#include <OBJETS_D.h>
    cout << "delete OK" << endl;
    return 0;
}
*/

//Test Capacités
/*
#include <Capacite.h>
int main()
{
    cout << "Hello world!" << endl;
#include <OBJETS.h>
#include <CAPACITES.h>
    cout << "include OK" << endl;
    for(int i(1); i < NOMBRE_CAPACITES + 1; i++)
    {
        if (capacites[i])
        {
            cout << capacites[i]->GetNom() << " " << capacites[i]->GetDescription() << endl;
        }
    }

    cout << "get OK" << endl;
#include <CAPACITES_D.h>
#include <OBJETS_D.h>
    cout << "delete OK" << endl;
    return 0;
}
*/

//Test Partie
/*
int main()
{
cout << "Hello world!" << endl;
    #include <HEROSS.h>
cout << "include OK" << endl;
    Partie partie(NOUVELLE_PARTIE);
cout << "partie OK" << endl;
    partie.GetEquipe()->AjouterHeros(olivier);
cout << "ajouter/retirer OK" << endl << endl;

for(int i = 0; i < 1 ; i++)
{
cout << partie.GetEquipe()->GetHeros(0)->GetNom() << endl;
cout << "" << endl;
cout << "" << endl << endl;
}
for(int i = 0; i < 3800 ; i++)
{
    cout << partie.GetHeures() << ":" << partie.GetMinutes() << ":" << partie.GetSecondes() << endl;
    partie.AjouterTemps();
}
cout << "get OK" << endl;
    #include <HEROSS_D.h>
cout << "delete OK" << endl;


    //Inventaire copie0 = *partie.GetInventaire();
    //Equipe copie1 = *partie.GetEquipe();
    //copie0.AjouterObjets(objets[1],3);
    //copie0.AjouterObjets(objets[3],3);
    //partie.SetInventaire(&copie0);
    //olivier->SetTete(casque);
    //cout << olivier->GetTete()->GetNom() << endl;
    //copie1.AjouterHeros(heros[1]);
    //copie1.GetHeros(0)->SetEquipement(objets[3],TETE);
    //partie.SetEquipe(&copie1);
    //partie.ChangerOr(100);
    //cout << "set ok" << endl;
    //cout << "get ok" << endl;

    return 0;
}
*/

//Test Groupes Monstres
/*
#include <Arme.h>
#include <Bouclier.h>
#include <Armure.h>
#include <Casque.h>
#include <Accessoire.h>
#include <Utilisable.h>
#include "Ecran_titre.h"
#include "Menu.h"

int main()
{
    cout << "Hello world!" << endl;
#include <OBJETS.h>
#include <GROUPESMONSTRES.h>
    cout << "include OK" << endl;
    for(int j = 1; j < NOMBRE_GROUPES_MONSTRES+1 ; j++)
    {
        for(int i = 0; i < groupes_monstres[j]->GetNombre() ; i++)
        {
            cout <<(groupes_monstres[j]->GetMonstres(i))->GetNom() << endl;
        }
    }
    cout << "get OK" << endl;
#include <GROUPESMONSTRES_D.h>
#include <OBJETS_D.h>
    cout << "delete OK" << endl;
    return 0;
}
*/

//Test Equipe
/*
int main()
{
cout << "Hello world!" << endl;
    Heros *heros;
    heros = new Heros("Coucou");
cout << "heros OK" << endl;
    Equipe equipe;
cout << "equipe OK" << endl;
    equipe.AjouterHeros(heros, RANG_AVANT);
cout << "ajouter/retirer OK" << endl << endl;

for(int i = 0; i < MAX_HEROS_EQUIPE ; i++)
{
cout << (equipe.GetHeros(i))->GetNom() << endl;
cout << equipe.GetRang(i) << endl;
cout << "" << endl;
cout << "" << endl << endl;
}

cout << "get OK" << endl;
    delete heros;
cout << "delete OK" << endl;
    return 0;
}
*/

//Test Inventaire
/*
int main()
{
cout << "Hello world!" << endl;
#include <OBJETS.h>
cout << "objet OK" << endl;
    Inventaire inventaire;
    GroupeObjets *groupe;
    groupe = new GroupeObjets(potion,5);
cout << "groupe OK" << endl;
    inventaire.AjouterObjets(groupe);
    inventaire.AjouterObjets(ether);
    inventaire.RetirerObjets(potion,3);
cout << "ajouter/retirer OK" << endl << endl;

for(int i=0;i<3;i++)
{
cout << ((inventaire.GetObjets(i))->GetObjet())->GetNom() << endl;
cout << ((inventaire.GetObjets(i))->GetObjet())->GetPrix() << endl;
cout << ((inventaire.GetObjets(i))->GetObjet())->GetDescription() << endl;
cout << (inventaire.GetObjets(i))->GetNombre() << endl << endl;
}

cout << "get OK" << endl;
#include <OBJETS_D.h>
    delete groupe;
cout << "delete OK" << endl;
    return 0;
}
*/
