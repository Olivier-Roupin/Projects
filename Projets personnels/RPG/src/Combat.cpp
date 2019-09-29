#include "Combat.h"

using namespace std;

int Combat(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    unsigned int frame(0);
    Input* input1(partie->GetInput());
    int combat;
    partie->SetMenu(-1);
    partie->SetHeros(-1);
    //partie->SetAction(ACTION_ATTAQUER);
    partie->SetCible(-1);
    partie->SetFaction(-1);
    if(!partie->GetMemoriserCurseur())
    {
        partie->SetObjet(0);
        partie->SetCapacite(0);
    }

    combat = CombatEnCours(COMBAT_EN_COURS,partie->GetEquipe(),partie->GetGroupeCombat());
    while(combat == COMBAT_EN_COURS) //Tant que le combat est en cours
    {
        AfficherCombat(partie);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        input1->Actualiser();
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        ChoixHeros(partie, input1); //prend en compte l'appui de la touche Y
        switch(partie->GetMenu())
        {
        case CHOIX_ACTION:
            ChoixAction(partie, input1);
            if(input1->GetA()) //exécuter l'action du héros
            {
                switch(partie->GetAction())
                {
                case ACTION_ATTAQUER:
                    partie->SetCible_Defaut();
                    partie->SetMenu(CHOIX_CIBLE);
                    break;
                case ACTION_DEFENSE:
                case ACTION_RANG:
                case ACTION_FUITE:
                    partie->SetMenu(AGIR);
                    break;
                case ACTION_OBJETS:
                    if(!partie->GetMemoriserCurseur())
                        partie->SetObjet(0);
                    partie->SetMenu(CHOIX_OBJET);
                    break;
                case ACTION_CAPACITE:
                    if(!partie->GetMemoriserCurseur())
                        partie->SetCapacite(0);
                    partie->SetMenu(CHOIX_CAPACITE);
                    break;
                default:
                    break;
                }
                input1->SetA(0);
            }
            break;
        case CHOIX_OBJET:
            ChoixObjet(partie, input1);
            if(input1->GetA())
            {
                if(partie->GetObjet_selection()->GetType() == UTILISABLE)
                {
                    partie->GetHeros_selection()->SetObjet(partie->GetObjet_selection());
                    partie->SetCible_Defaut();
                    partie->SetMenu(CHOIX_CIBLE);
                    input1->SetA(0);
                }
            }
            else if(input1->GetB())
            {
                if(!partie->GetMemoriserCurseur())
                    partie->SetObjet(0);
                partie->SetMenu(CHOIX_ACTION);
                input1->SetB(0);
            }
            break;
        case CHOIX_CAPACITE:
            ChoixCapacite(partie, input1);
            if(input1->GetA())
            {
                if(partie->GetHeros_selection()->GetSorts(partie->GetCapacite()))
                {
                    if(partie->GetHeros_selection()->GetMagie() >= partie->GetHeros_selection()->GetSorts(partie->GetCapacite())->GetCoutMagie()) //Si le héros a assez de magie
                    {
                        partie->GetHeros_selection()->SetCapacite(partie->GetCapacite_selection());
                        partie->SetCible_Defaut();
                        partie->SetMenu(CHOIX_CIBLE);
                    }
                    input1->SetA(0);
                }
            }
            else if(input1->GetB())
            {
                if(!partie->GetMemoriserCurseur())
                    partie->SetCapacite(0);
                partie->SetMenu(CHOIX_ACTION);
                input1->SetB(0);
            }
            break;
        case CHOIX_CIBLE:
            ChoixCible(partie, input1);
            if(input1->GetA())
            {
                partie->GetHeros_selection()->SetCibles(partie->GetCible_selection());
                partie->GetHeros_selection()->SetNombreCibles(partie->GetCible_nombre());
                partie->SetMenu(AGIR);
                input1->SetA(0);
            }
            else if(input1->GetB())
            {
                partie->SetCible(-1);
                partie->SetFaction(-1);
                switch(partie->GetAction())
                {
                case ACTION_ATTAQUER:
                    partie->SetMenu(CHOIX_ACTION);
                    break;
                case ACTION_OBJETS:
                    if(!partie->GetMemoriserCurseur()) //?
                        partie->SetObjet(0);
                    partie->SetMenu(CHOIX_OBJET);
                    break;
                case ACTION_CAPACITE:
                    if(!partie->GetMemoriserCurseur()) //?
                        partie->SetCapacite(0);
                    partie->SetMenu(CHOIX_CAPACITE);
                    break;
                default:
                    partie->SetMenu(CHOIX_ACTION); //Si on ne sait pas pourquoi on est là, on revient au choix de l'action
                    break;
                }
                input1->SetB(0);
            }
            break;
        case AGIR:
            partie->GetHeros_selection()->SetAction(partie->GetAction());
            partie->SetCible(-1);
            partie->SetFaction(-1);
            partie->SetHeros(-1);
            partie->SetMenu(-1);
            if(!partie->GetMemoriserCurseur())
            {
                partie->SetObjet(0);
                partie->SetCapacite(0);
            }
            break;
        default:
            if(partie->GetHeros() != -1) //Dès qu'un héros est prêt
            {
                partie->SetAction(ACTION_ATTAQUER);
                partie->SetMenu(CHOIX_ACTION);
            }
            break;
        }
        if(partie->GetModeCombat() == MODE_ACTIF ||\
                (partie->GetModeCombat() == MODE_SEMI_ACTIF && partie->GetMenu() == CHOIX_ACTION) ||\
                partie->GetMenu() == -1)
            frame++;
        if(frame >= partie->GetVitesseCombat())
        {
            ActualiserJauges(partie->GetEquipe(),partie->GetGroupeCombat()); //Augmenter le temps
            ActionHeros(partie, combat);
            ActionMonstres(partie);
            frame = 0;
        }
        combat = CombatEnCours(combat,partie->GetEquipe(),partie->GetGroupeCombat());
    }
    switch(combat)
    {
    case COMBAT_DEFAITE:
        Game_Over(partie);
        return 1;
        break;
    case COMBAT_FUITE:
        cout << "Fuite" << endl;
        cout << "Vous avez perdu 10 d'or..." << endl;
        partie->ChangerOr(-10);
        break;
    case COMBAT_VICTOIRE:
        cout << "Vous gagnez " << partie->GetGroupeCombat()->GetExperience() << " Exp !" << endl;
        for(int i(0); i < MAX_HEROS_EQUIPE; i++)
        {
            if(partie->GetEquipe()->GetHeros(i)->estEnVie())
                partie->GetEquipe()->GetHeros(i)->ChangerExperience(partie->GetGroupeCombat()->GetExperience());
        }
        cout << "Vous gagnez " << partie->GetGroupeCombat()->GetOr() << " Or !" << endl;
        partie->ChangerOr(partie->GetGroupeCombat()->GetOr());
    default:
        break;
    }
    ViderJauges(partie->GetEquipe());
    return 0;
}

void AfficherCombat(Partie* partie)
{
    system("cls"); //efface l'écran
    AfficherFond(partie->GetCarte(),partie->GetGroupeCombat());
    AfficherMonstres(partie->GetGroupeCombat(), partie->GetCible(), partie->GetFaction(), partie->GetQuantite());
    AfficherEquipeCombat(partie->GetEquipe(), partie->GetCible(), partie->GetFaction(), partie->GetQuantite());
    switch(partie->GetMenu())
    {
    case CHOIX_HEROS:
        break;
    case CHOIX_ACTION:
        if(partie->GetHeros() != -1)
            AfficherCommandes(partie->GetHeros_selection(), partie->GetAction());
        break;
    case CHOIX_OBJET:
        AfficherObjetsCombat(partie->GetInventaire(), partie->GetObjet());
        break;
    case CHOIX_CAPACITE:
        AfficherCompetencesCombat(partie->GetHeros_selection(), partie->GetCapacite());
        break;
    case CHOIX_CIBLE:
        break;
    default:
        break;
    }
}

void AfficherFond(Carte* carte, GroupeMonstres* groupe)
{
    if(groupe->GetFond() != "_")
        cout << groupe->GetFond() << endl;
    else
        cout << carte->GetFond() << endl;
}

void AfficherEquipeCombat(Equipe* equipe, int cible, bool faction, bool quantite)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        if(cible >= 0 && faction == FACTION_EQUIPE && quantite == QUANTITE_UNE) //Un héros est sélectionné
            AfficherCurseurEmplacement(cible,i);
        else if(cible >= 0 && faction == FACTION_EQUIPE && quantite == QUANTITE_FACTION || cible == CIBLE_TOUS) //Tous les héros sont sélectionnés
            AfficherCurseurEmplacement(i,i);
        else
            AfficherCurseurEmplacement(-1,i);
        AfficherHerosCombat(equipe->GetHeros(i));
    }
}

void AfficherHerosCombat(Heros* choix_heros)
{
    if(choix_heros)
    {
        if(choix_heros->GetRang() == RANG_ARRIERE)
            cout << "    ";
        cout << choix_heros->GetNom() << " ";
        if(choix_heros->GetGarde())
            cout << "(garde) ";
        cout << choix_heros->GetVie() << "/" << choix_heros->GetVieMax() << endl;
        AfficherJauge(choix_heros->GetJauge());
    }
    else
        cout << endl << endl;
}

void AfficherJauge(int jauge)
{
    int i;
    cout << "+";
    int n(10.*jauge/TAILLE_JAUGE);
    for(i = 0; i < n; i++)
        cout << "=";
    for(i = n; i < 10; i++)
        cout << " ";
    cout << "+" << endl;
}

void AfficherMonstres(GroupeMonstres* groupe, int cible, bool faction, bool quantite)
{
    int i;
    for(i = 0; i < groupe->GetNombre(); i++)
    {
        if(groupe->GetMonstres(i)->GetVie())
        {
            if(cible >= 0 && faction == FACTION_MONSTRES && quantite == QUANTITE_UNE) //Un monstre est séléctionné
                AfficherCurseurEmplacement(cible,i);
            else if(cible >= 0 && faction == FACTION_MONSTRES && quantite == QUANTITE_FACTION || cible == CIBLE_TOUS) //Tous les monstres sont sélectionnés
                AfficherCurseurEmplacement(i,i);
            else
                AfficherCurseurEmplacement(-1,i);
            cout << groupe->GetMonstres(i)->GetNom() << " (" <<\
                 groupe->GetMonstres(i)->GetX() << "," <<\
                 groupe->GetMonstres(i)->GetY() << ") " <<\
                 groupe->GetMonstres(i)->GetVie() << " ";
        }
    }
    cout << endl;
}

void AfficherCommandes(Heros *choix_heros, int id)
{
    cout << choix_heros->GetNom() << endl;
    AfficherCurseurEmplacement(id,ACTION_ATTAQUER);
    cout << "Attaquer" << endl;
    AfficherCurseurEmplacement(id,ACTION_DEFENSE);
    cout << "Defense" << endl;
    AfficherCurseurEmplacement(id,ACTION_RANG);
    cout << "Rang" << endl;
    AfficherCurseurEmplacement(id,ACTION_OBJETS);
    cout << "Objets" << endl;
    AfficherCurseurEmplacement(id,ACTION_CAPACITE);
    cout << "Capacite" << endl;
    AfficherCurseurEmplacement(id,ACTION_FUITE);
    cout << "Fuite" << endl;
}

void AfficherObjetsCombat(Inventaire* inventaire, int choix)
{
    int i;
    int premier(PremierObjetAfficheCombat(choix));
    for(i = premier; i < premier + NOMBRE_OBJETS_AFFICHES; i++)
    {
        AfficherCurseurEmplacement(choix,i);
        cout<<i<<": "<<inventaire->GetObjets(i)->GetNom()<<" "<<inventaire->GetObjets(i)->GetNombre()<< endl;
    }
}

void AfficherCompetencesCombat(Heros* heros, int choix)
{
    int i;
    int premier(PremiereCompetenceAfficheCombat(choix));
    cout<<heros->GetMagie()<<"/"<<heros->GetMagieMaxTotal()<<endl;
    for(i = premier; i < premier + NOMBRE_OBJETS_AFFICHES; i++)
    {
        AfficherCurseurEmplacement(choix,i);
        cout<<i<<": "<<heros->GetSorts(i)->GetNom()<<" "<<heros->GetSorts(i)->GetCoutMagie()<< endl;
    }
}

int PremierObjetAfficheCombat(int choix)
{
    if(choix < NOMBRE_OBJETS_AFFICHES/2)
        return 0;
    if(choix > MAX_OBJETS - NOMBRE_OBJETS_AFFICHES + 1)
        return MAX_OBJETS - NOMBRE_OBJETS_AFFICHES;
    return choix - NOMBRE_OBJETS_AFFICHES/2;
}

int PremiereCompetenceAfficheCombat(int choix)
{
    if(choix < NOMBRE_OBJETS_AFFICHES/2)
        return 0;
    if(choix > MAX_SORTS - NOMBRE_OBJETS_AFFICHES + 1)
        return MAX_SORTS - NOMBRE_OBJETS_AFFICHES;
    return choix - NOMBRE_OBJETS_AFFICHES/2;
}

void ChoixHeros(Partie* partie, Input* input)
{
    int i;
    if(partie->GetHeros() != -1 && partie->GetHeros_selection()->estOccupe())
    {
        partie->SetCible(-1);
        partie->SetFaction(-1);
        partie->SetMenu(-1);
        partie->SetHeros(-1);
    }
    if(partie->GetHeros() == -1 || input->GetY())
    {
        for(i = 1; i < MAX_HEROS_EQUIPE + 1; i++)
        {
            if(!partie->GetEquipe()->GetHeros((i + partie->GetHeros()) % MAX_HEROS_EQUIPE)->estOccupe())
            {
                partie->SetHeros((i + partie->GetHeros()) % MAX_HEROS_EQUIPE);
                i = MAX_HEROS_EQUIPE;
            }
        }
        input->SetY(0);
    }
}

void ChoixAction(Partie* partie, Input* input)
{
    if(input->Gethaut())
    {
        partie->SetAction((partie->GetAction() + NOMBRE_ACTIONS - 1) % NOMBRE_ACTIONS);
        input->Sethaut(0);
    }
    if(input->Getbas())
    {
        partie->SetAction((partie->GetAction() + 1) % NOMBRE_ACTIONS);
        input->Setbas(0);
    }
}

void ChoixCible(Partie* partie, Input* input) //Toujours de la perspective de l'équipe
{
    if(partie->GetChoix_Cible_selection())
    {
        if(partie->GetFaction() == FACTION_EQUIPE)
        {
            if(partie->GetCible() < 0 || partie->GetCible() >= MAX_HEROS_EQUIPE) //sécurité
                partie->SetCible(0);
            //NE PAS SELECTIONNER PERSONNAGE ABSENT
            if(input->Getgauche())
            {
                if(partie->GetChoix_Quantite_selection() && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                do
                {
                    partie->SetCible((partie->GetCible() + MAX_HEROS_EQUIPE - 1) % MAX_HEROS_EQUIPE);
                }
                while(partie->GetCible_selection()[0] == 0);
                input->Setgauche(0);
            }
            if(input->Getdroite())
            {
                if(partie->GetChoix_Quantite_selection() && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                do
                {
                    partie->SetCible((partie->GetCible() + 1) % MAX_HEROS_EQUIPE);
                }
                while(partie->GetCible_selection()[0] == 0);
                input->Setdroite(0);
            }
        }
        else
        {
            if(partie->GetCible() < 0 || partie->GetCible() >= partie->GetGroupeCombat()->GetNombre()) //sécurité
                partie->SetCible(0);
            while(not(partie->GetGroupeCombat()->GetMonstres(partie->GetCible())->GetVie())) //les monstres morts sont invisibles (?)
            {
                partie->SetCible((partie->GetCible() + 1) % partie->GetGroupeCombat()->GetNombre());
            }
            if(input->Getgauche())
            {
                if(partie->GetChoix_Quantite_selection() && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                do
                {
                    partie->SetCible((partie->GetCible() + partie->GetGroupeCombat()->GetNombre() - 1) % partie->GetGroupeCombat()->GetNombre());
                }
                while(not(partie->GetGroupeCombat()->GetMonstres(partie->GetCible())->GetVie())); //les monstres morts sont invisibles (?)
                input->Setgauche(0);
            }
            if(input->Getdroite())
            {
                if(partie->GetChoix_Quantite_selection() && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                do
                {
                    partie->SetCible((partie->GetCible() + 1) % partie->GetGroupeCombat()->GetNombre());
                }
                while(not(partie->GetGroupeCombat()->GetMonstres(partie->GetCible())->GetVie())); //les monstres morts sont invisibles (?)
                input->Setdroite(0);
            }
        }
    }
    if(partie->GetChoix_Faction_selection())
    {
        if(input->Gethaut())
        {
            if(partie->GetFaction() == FACTION_EQUIPE) //FACTION_LANCEUR == FACTION_EQUIPE == false
                partie->SetFaction(FACTION_MONSTRES); //FACTION_ADVERSE == FACTION_MONSTRE == true
            input->Sethaut(0);
        }
        if(input->Getbas())
        {
            if(partie->GetFaction() == FACTION_MONSTRES) //FACTION_ADVERSE == FACTION_MONSTRE == true
                partie->SetFaction(FACTION_EQUIPE); //FACTION_LANCEUR == FACTION_EQUIPE == false
            input->Setbas(0);
        }
    }
    if(partie->GetChoix_Quantite_selection())
    {
        if(input->GetL() || input->GetR())
        {
            partie->SetQuantite(!partie->GetQuantite());
            input->SetL(0);
            input->SetR(0);
        }
    }
}

void ChoixObjet(Partie* partie, Input* input)
{
    if(input->Gethaut())
    {
        if(partie->GetObjet() > 0)
            partie->SetObjet(partie->GetObjet()-1);
        input->Sethaut(0);
    }
    if(input->Getbas())
    {
        if(partie->GetObjet() < MAX_OBJETS - 1)
            partie->SetObjet(partie->GetObjet()+1);
        input->Setbas(0);
    }
}

void ChoixCapacite(Partie* partie, Input* input)
{
    if(input->Gethaut())
    {
        if(partie->GetCapacite() > 0)
            partie->SetCapacite(partie->GetCapacite()-1);
        input->Sethaut(0);
    }
    if(input->Getbas())
    {
        if(partie->GetCapacite() < MAX_APTITUDES - 1)
            partie->SetCapacite(partie->GetCapacite()+1);
        input->Setbas(0);
    }
}

void ActionHeros(Partie* partie, int &combat)
{
    int i;
    Heros* heros;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        heros = partie->GetEquipe()->GetHeros(i);
        partie->SetLanceur(i); //Déplacé pour utiliser les altérations : faut-il créer une fonction dédiée ?
        partie->SetFactionLanceur(FACTION_EQUIPE);
        int j;
        for(j = 0; j < MAX_ALTERATIONS; j++)
        {
            heros->GetAlterations(j)->GetScript()->Executer(partie);
        }
        if(heros->GetAction() != -1)
        {
            //partie->SetLanceur(i);
            //partie->SetFactionLanceur(FACTION_EQUIPE);
            switch(heros->GetAction())
            {
            case ACTION_ATTAQUER:
                if(not(heros->GetCibles()[0]->estEnVie())) //Si l'ennemi est déjà mort
                {
                    heros->SetCibles(0);
                    heros->SetAction(ACTION_INACTIF);
                    //Coder changement de cible automatique
                    return;
                }
                heros->Attaquer();
                heros->SetCibles(0);
                break;
            case ACTION_DEFENSE:
                heros->SetGarde(true);
                break;
            case ACTION_RANG:
                heros->ChangerRang();
                break;
            case ACTION_OBJETS:
                //Utiliser objet
                //Fusionner le test de présence de l'objet avec son effacement de l'inventaire ?
                if(partie->GetInventaire()->ChercherObjet(heros->GetObjet()) != -1) //Si l'objet est bien dans l'invenataire
                {
                    ((Utilisable*)heros->GetObjet())->GetEffet()->GetScript()->Executer(partie); //On s'intéresse à l'objet du héros
                    partie->GetInventaire()->RetirerObjets(heros->GetObjet()); //Retirer l'objet de l'inventaire
                }
                heros->SetCibles(0);
                break;
            case ACTION_CAPACITE:
                //Utiliser capacité
                //Fusionner le test de coût de magie avec la modification de la magie ?
                if(heros->GetMagie() >= heros->GetCapacite()->GetCoutMagie()) //Si le héros a assez de magie
                {
                    heros->GetCapacite()->GetEffet()->GetScript()->Executer(partie); //On s'intéresse à la capacité du héros
                    heros->ChangerMagie(-heros->GetCapacite()->GetCoutMagie());
                }
                heros->SetCibles(0);
                break;
            case ACTION_FUITE:
                if(not(rand() % 5)) //1 chance sur 5
                    combat = COMBAT_FUITE;
                break;
            default:
                break;
            }
            if(heros->GetAction() != ACTION_DEFENSE)
                heros->SetGarde(false);
            heros->ViderJauge();
            heros->SetAction(ACTION_INACTIF);
            i = MAX_HEROS_EQUIPE;
        }
    }
}

void ActionMonstres(Partie* partie)
{
    int i;
    Monstre* monstre;
    for(i = 0; i < partie->GetGroupeCombat()->GetNombre(); i++)
    {
        monstre = partie->GetGroupeCombat()->GetMonstres(i);
        partie->SetLanceur(i); //Déplacé pour tester les altérations
        partie->SetFactionLanceur(FACTION_MONSTRES);
        int j;
        for(j = 0; j < MAX_ALTERATIONS; j++)
        {
            monstre->GetAlterations(j)->GetScript()->Executer(partie);
        }
        if(partie->GetGroupeCombat()->GetMonstres(i)->Jauge_estpleine())
        {
            //partie->SetLanceur(i);
            //partie->SetFactionLanceur(FACTION_MONSTRES);
            partie->GetGroupeCombat()->GetMonstres(i)->GetScript()->Executer(partie);
            partie->GetGroupeCombat()->GetMonstres(i)->ViderJauge();
            i = partie->GetGroupeCombat()->GetNombre();
        }
    }
}

void ActualiserJauges(Equipe* equipe, GroupeMonstres* groupe)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        if(equipe->GetHeros(i)->GetVie())
            equipe->GetHeros(i)->ActualiserJauge();
    }
    for(i = 0; i < groupe->GetNombre(); i++)
    {
        if(groupe->GetMonstres(i)->GetVie())
            groupe->GetMonstres(i)->ActualiserJauge();
    }
}

void ViderJauges(Equipe* equipe)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        if(equipe->GetHeros(i)->GetVie())
            equipe->GetHeros(i)->ViderJauge();
    }
}

int CombatEnCours(int combat, Equipe* equipe, GroupeMonstres* groupe)
{
    int i;
    for(i = 0; i < MAX_HEROS_EQUIPE; i++)
    {
        if(equipe->GetHeros(i)->GetVie())
        {
            for(i = 0; i < groupe->GetNombre(); i++)
            {
                if(groupe->GetMonstres(i)->GetVie())
                {
                    if(combat == COMBAT_FUITE)
                        return COMBAT_FUITE;
                    return COMBAT_EN_COURS;
                }
            }
            return COMBAT_VICTOIRE;
        }
    }
    return COMBAT_DEFAITE;
}
