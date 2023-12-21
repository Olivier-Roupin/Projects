#include "scenes/Combat.h"
#include <affichage/Combat.h>
#include <moteur_graphique.h>
#include <cstdlib> //rand, RAND_MAX
#include <scenes/Game_Over.h> //Game_Over, Input
#include <lib/Utilisable.h>

void ChoixHeros(Partie* partie, Input* input); //BETA Change le héros qui a ses actions affichées
void ChoixAction(Partie* partie, Input* input);
void ChoixCible(Partie* partie, Input* input);
void ChoixObjet(Partie* partie, Input* input);
void ChoixCapacite(Partie* partie, Input* input);

void ActionHeros(Partie* partie, int &combat);
void ActionMonstres(Partie* partie);

void ActualiserJauges(Equipe* equipe, GroupeMonstres* groupe); //BETA Actualise les jauges de tous les personnages en combat
void ViderJauges(Equipe* equipe); //BETA Vide les jauges de tous les héros

int CombatEnCours(int combat, Equipe* equipe, GroupeMonstres* groupe);

void VictoireEquipe(Equipe* equipe) {
    for (unsigned char i = 0; i < MAX_HEROS_EQUIPE; ++i) {
        if (equipe->GetHeros(i))
            if (equipe->GetHeros(i)->GetTempsAnimation() <= 1) { //changer d'animation avant le reset
                equipe->GetHeros(i)->SetAnimation(
                    equipe->GetHeros(i)->GetAnimation()==ACTION_INACTIF?
                        ACTION_CAPACITE : ACTION_INACTIF);
                equipe->GetHeros(i)->SetTempsAnimation(16);
            }
    }
}

void PauseCombat(unsigned char frames, Partie* partie) {
    for (unsigned char i = 0; i < frames; ++i) {
        VictoireEquipe(partie->GetEquipe());
        AfficherCombat(partie);
        afficherEcran();
        syncEcran(frameLimit);
    }
}

int Combat(Partie* partie) {
    unsigned int frame = 0;
    Input* input = partie->GetInput();
    int combat;
    partie->SetMenu(-1);
    partie->SetHeros(-1);
    //partie->SetAction(ACTION_ATTAQUER); //nécessaire ?
    partie->SetCible(-1);
    partie->SetFaction(-1);
    // if (!partie->GetMemoriserCurseur()) { //nécessaire ?
    //     partie->SetObjet(0);
    //     partie->SetCapacite(0);
    // }

    //Désynchroniser monstres
    if (partie->GetGroupeCombat())
        for (unsigned char i = 0; i < partie->GetGroupeCombat()->GetNombre(); ++i)
            if (partie->GetMonstre(i))
                partie->GetMonstre(i)->SetJauge((i*63) % (TAILLE_JAUGE-63)); //63 et 1024 premiers entre eux

    combat = CombatEnCours(COMBAT_EN_COURS, partie->GetEquipe(),
                           partie->GetGroupeCombat());
    while (combat == COMBAT_EN_COURS) {//Tant que le combat est en cours
        AfficherCombat(partie);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        ChoixHeros(partie, input); //prend en compte l'appui de la touche Y
        switch (partie->GetMenu()) {
        case CHOIX_ACTION:
            ChoixAction(partie, input);
            if (input->takeA()) {//exécuter l'action du héros
                switch (partie->GetAction()) {
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
                    if (!partie->GetMemoriserCurseur())
                        partie->SetObjet(0);
                    partie->SetMenu(CHOIX_OBJET);
                    break;
                case ACTION_CAPACITE:
                    if (!partie->GetMemoriserCurseur())
                        partie->SetCapacite(0);
                    partie->SetMenu(CHOIX_CAPACITE);
                    break;
                default:
                    break;
                }
            }
            break;
        case CHOIX_OBJET:
            ChoixObjet(partie, input);
            if (input->takeA()) {
                if (partie->GetObjet_selection()) {
                    if (partie->GetObjet_selection()->GetType() == UTILISABLE) {
                        partie->ApplyObjet_selection();
                        partie->SetCible_Defaut();
                        partie->SetMenu(CHOIX_CIBLE);
                    }
                }
            } else if (input->takeB()) {
                if (!partie->GetMemoriserCurseur())
                    partie->SetObjet(0);
                partie->SetMenu(CHOIX_ACTION);
            }
            break;
        case CHOIX_CAPACITE:
            ChoixCapacite(partie, input);
            if (input->takeA()) {
                if (partie->GetHeros_selection()
                 && partie->GetHeros_selection()->GetSorts(
                                                        partie->GetCapacite()))
                    //Si le héros a assez de magie
                    if (partie->GetHeros_selection()->GetMagie() >=
                    partie->GetHeros_selection()->GetSorts(
                    partie->GetCapacite())->GetCoutMagie()) {
                        partie->ApplyCapacite_selection();
                        partie->SetCible_Defaut();
                        partie->SetMenu(CHOIX_CIBLE);
                    }
            } else if (input->takeB()) {
                if (!partie->GetMemoriserCurseur())
                    partie->SetCapacite(0);
                partie->SetMenu(CHOIX_ACTION);
            }
            break;
        case CHOIX_CIBLE:
            ChoixCible(partie, input);
            if (input->takeA()) {
                partie->ApplyCible_selection();
                partie->SetMenu(AGIR);
            } else if (input->takeB()) {
                partie->SetCible(-1);
                partie->SetFaction(-1);
                switch (partie->GetAction()) {
                case ACTION_ATTAQUER:
                    partie->SetMenu(CHOIX_ACTION);
                    break;
                case ACTION_OBJETS:
                    if (!partie->GetMemoriserCurseur()) //?
                        partie->SetObjet(0);
                    partie->SetMenu(CHOIX_OBJET);
                    break;
                case ACTION_CAPACITE:
                    if (!partie->GetMemoriserCurseur()) //?
                        partie->SetCapacite(0);
                    partie->SetMenu(CHOIX_CAPACITE);
                    break;
                default:
                    //Si on ne sait pas pourquoi on est là
                    //on revient au choix de l'action
                    partie->SetMenu(CHOIX_ACTION);
                    break;
                }
            }
            break;
        case AGIR:
            partie->ApplyAction_selection();
            partie->SetCible(-1);
            partie->SetFaction(-1);
            partie->SetHeros(-1);
            partie->SetMenu(-1);
            if (!partie->GetMemoriserCurseur()) {
                partie->SetObjet(0);
                partie->SetCapacite(0);
            }
            break;
        default:
            if (partie->GetHeros() != -1) {//Dès qu'un héros est prêt
                partie->SetAction(ACTION_ATTAQUER);
                partie->SetMenu(CHOIX_ACTION);
            }
            break;
        }
        if (partie->GetModeCombat() == MODE_ACTIF ||\
           (partie->GetModeCombat() == MODE_SEMI_ACTIF &&\
                  partie->GetMenu() == CHOIX_ACTION) ||\
                  partie->GetMenu() == -1) // MODE_PASSIF
            ++frame;
        if (frame >= (unsigned int)partie->GetVitesseCombat()) {
            //Augmenter le temps
            ActualiserJauges(partie->GetEquipe(), partie->GetGroupeCombat());
            ActionHeros(partie, combat);
            if (partie->GetGroupeCombat())
                ActionMonstres(partie);
            frame = 0;
        }
        combat = CombatEnCours(combat, partie->GetEquipe(),
                               partie->GetGroupeCombat());
    }
    switch (combat) {
    case COMBAT_DEFAITE:
        Game_Over(input);
        return 1;
        break;
    case COMBAT_FUITE:
        partie->ChangerOr(-10);
        while (!input->takeA()) {
            AfficherCombat(partie);
            AfficherFuite(10);
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
        }
        break;
    case COMBAT_VICTOIRE:
        for (unsigned char i = 0; i < MAX_HEROS_EQUIPE; ++i) {
            if (partie->GetEquipe()->GetHeros(i)) {
                partie->GetEquipe()->GetHeros(i)->SetAnimation(ACTION_CAPACITE);
                partie->GetEquipe()->GetHeros(i)->SetTempsAnimation(16);
            }
        }
        while (!input->takeA()) {
            VictoireEquipe(partie->GetEquipe());
            AfficherCombat(partie);
            AfficherVictoireExp(partie->GetGroupeCombat()->GetExperience());
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
        }
        PauseCombat(4, partie);
        for (unsigned char i = 0; i < MAX_HEROS_EQUIPE; ++i) {
            if (partie->GetEquipe()->GetHeros(i)
             && partie->GetEquipe()->GetHeros(i)->estEnVie()) {
                int nombre = partie->GetEquipe()->GetHeros(i)->GagnerExperience(
                                    partie->GetGroupeCombat()->GetExperience());
                if (nombre) {
                    while (!input->takeA()) {
                        VictoireEquipe(partie->GetEquipe());
                        AfficherCombat(partie);
                        AfficherVictoireNiveau(
                            partie->GetEquipe()->GetHeros(i)->GetNom(), nombre);
                        afficherEcran();
                        input->Actualiser();
                        syncEcran(frameLimit);
                    }
                    PauseCombat(4, partie);
                }
            }
        }
        partie->ChangerOr(partie->GetGroupeCombat()->GetOr());
        while (!input->takeA()) {
            VictoireEquipe(partie->GetEquipe());
            AfficherCombat(partie);
            AfficherVictoireOr(partie->GetGroupeCombat()->GetOr());
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
        }
        PauseCombat(4, partie);
        for (unsigned char i=0; i < partie->GetGroupeCombat()->GetNombre(); ++i)
            if (partie->GetGroupeCombat()->GetMonstres(i)
             && partie->GetGroupeCombat()->GetMonstres(i)->GetButin()) {
                Objet* butin = partie->GetGroupeCombat()->GetMonstres(i)->GetButin();
                partie->GetInventaire()->AjouterObjets(butin);
                while (!input->takeA()) {
                    VictoireEquipe(partie->GetEquipe());
                    AfficherCombat(partie);
                    AfficherVictoireObjet(butin->GetNom());
                    afficherEcran();
                    input->Actualiser();
                    syncEcran(frameLimit);
                }
                PauseCombat(4, partie);
            }
    default:
        break;
    }
    ViderJauges(partie->GetEquipe());
    for (unsigned char i = 0; i < MAX_HEROS_EQUIPE; ++i) {
        if (partie->GetEquipe()->GetHeros(i)) {
            partie->GetEquipe()->GetHeros(i)->SetAnimation(ACTION_INACTIF);
            partie->GetEquipe()->GetHeros(i)->SetTempsAnimation(0);
            partie->GetEquipe()->GetHeros(i)->SetMessage(0); //utile?
            partie->GetEquipe()->GetHeros(i)->SetTempsMessage(0); //utile?
        }
    }
    return 0;
}

void ChoixHeros(Partie* partie, Input* input) {
    char i;
    if (partie->GetHeros() != -1 && partie->GetHeros_selection() && partie->GetHeros_selection()->estOccupe()) {
        partie->SetCible(-1);
        partie->SetFaction(-1);
        partie->SetMenu(-1);
        partie->SetHeros(-1);
    }
    if (partie->GetHeros() == -1 || input->takeY())
        for (i = 1; i < MAX_HEROS_EQUIPE + 1; i++)
            if (partie->GetEquipe()->GetHeros(
                    (i + partie->GetHeros()) % MAX_HEROS_EQUIPE)
             && !partie->GetEquipe()->GetHeros(
                    (i + partie->GetHeros()) % MAX_HEROS_EQUIPE)->estOccupe()) {
                partie->SetHeros((i + partie->GetHeros()) % MAX_HEROS_EQUIPE);
                i = MAX_HEROS_EQUIPE;
            }
}

void ChoixAction(Partie* partie, Input* input) {
    if (input->takeHaut())
        partie->SetAction(AVANT(partie->GetAction(),NOMBRE_ACTIONS));
    if (input->takeBas())
        partie->SetAction(APRES(partie->GetAction(),NOMBRE_ACTIONS));
}

//Toujours de la perspective de l'équipe
void ChoixCible(Partie* partie, Input* input) {
    partie->SetLanceur(partie->GetHeros());
    partie->SetFactionLanceur(FACTION_EQUIPE);
    //Curseur libre
    if (partie->GetChoix_Cible_selection()) {
        if (partie->GetFaction() == FACTION_EQUIPE) {
            if (partie->GetCible() < 0 || partie->GetCible() >= MAX_HEROS_EQUIPE)
                partie->SetCible(0); //sécurité
            //NE PAS SELECTIONNER PERSONNAGE ABSENT
            if (input->takeHaut()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                do {
                    partie->DecCible(MAX_HEROS_EQUIPE);
                } while (partie->GetCible_selection()[0] == 0);
            }
            if (input->takeBas()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                do {
                    partie->IncCible(MAX_HEROS_EQUIPE);
                } while (partie->GetCible_selection()[0] == 0);
            }
            if (input->takeDroite()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
            }
            if (input->takeGauche()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                //On change la quantité si on change de faction ?
                if (partie->GetChoix_Faction_selection()) {
                    //FACTION_LANCEUR == FACTION_EQUIPE == false
                    //FACTION_ADVERSE == FACTION_MONSTRE == true
                    partie->SetFaction(FACTION_MONSTRES);
                    partie->SetCible(partie->GetGroupeCombat()->GetDroite());
                }
                // else if (partie->GetChoix_Quantite_selection()
                //    && partie->GetQuantite() == QUANTITE_FACTION)
                //     partie->SetQuantite(QUANTITE_UNE);
            }   
        } else { //sélection de monstres
            if (partie->GetCible() < 0
               || partie->GetCible() >= partie->GetGroupeCombat()->GetNombre())
                partie->SetCible(0); //sécurité
            //les monstres morts sont invisibles (?)
            while (partie->GetMonstre(partie->GetCible()) == 0 || !partie->GetMonstre(partie->GetCible())->estEnVie())
                partie->IncCible(partie->GetGroupeCombat()->GetNombre());

            if (input->takeHaut()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                partie->SetCible(partie->GetGroupeCombat()->GetHaut(
                    partie->GetCible()));
            }
            if (input->takeBas()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                partie->SetCible(partie->GetGroupeCombat()->GetBas(
                    partie->GetCible()));

            }
            if (input->takeGauche()) {
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                partie->SetCible(partie->GetGroupeCombat()->GetGauche(
                    partie->GetCible()));

            }
            if (input->takeDroite()) { //gère le changement de faction
                if (partie->GetChoix_Quantite_selection()
                   && partie->GetQuantite() == QUANTITE_FACTION)
                    partie->SetQuantite(QUANTITE_UNE);
                //On change la quantité si on change de faction ?
                if (partie->GetGroupeCombat()->GetDroite(
                    // partie->GetCible()) < 0) {
                    partie->GetCible()) >= partie->GetGroupeCombat()->GetNombre()) {
                        //FACTION_ADVERSE == FACTION_MONSTRE == true
                        //FACTION_LANCEUR == FACTION_EQUIPE == false
                        partie->SetFaction(FACTION_EQUIPE);
                        partie->SetCible(0); //nécessaire ? ok ?
                } else {
                    partie->SetCible(partie->GetGroupeCombat()->GetDroite(
                    partie->GetCible()));
                //    if (partie->GetChoix_Quantite_selection()
                //    && partie->GetQuantite() == QUANTITE_FACTION)
                //     partie->SetQuantite(QUANTITE_UNE);
                }
            }
        }
    } else if (partie->GetChoix_Faction_selection()) { //Curseur non-libre
        //plus flexible que nécessaire, surtout utile pour quantité multiple
        if (input->takeGauche())
            //FACTION_LANCEUR == FACTION_EQUIPE == false
            if (partie->GetFaction() == FACTION_EQUIPE)
                //FACTION_ADVERSE == FACTION_MONSTRE == true
                partie->SetFaction(FACTION_MONSTRES);
        if (input->takeDroite())
            //FACTION_ADVERSE == FACTION_MONSTRE == true
            if (partie->GetFaction() == FACTION_MONSTRES)
                //FACTION_LANCEUR == FACTION_EQUIPE == false
                partie->SetFaction(FACTION_EQUIPE);
    }
    if (partie->GetChoix_Quantite_selection())
        if (input->takeL() || input->takeR())
            partie->SetQuantite(!partie->GetQuantite());
}

void ChoixObjet(Partie* partie, Input* input) {
    if (input->takeHaut())
        if (partie->GetObjet() > 0)
            partie->SetObjet(partie->GetObjet()-1);
    if (input->takeBas())
        if (partie->GetObjet() < MAX_OBJETS-1)
            partie->SetObjet(partie->GetObjet()+1);
}

void ChoixCapacite(Partie* partie, Input* input) {
    if (input->takeHaut())
        if (partie->GetCapacite() > 0)
            partie->SetCapacite(partie->GetCapacite()-1);
    if (input->takeBas())
        if (partie->GetCapacite() < MAX_SORTS-1)
            partie->SetCapacite(partie->GetCapacite()+1);
}

void ActionHeros(Partie* partie, int &combat) {
    unsigned char i;
    Heros* heros;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i) {
        heros = partie->GetEquipe()->GetHeros(i);
        if (heros) {
            //faut-il créer une fonction dédiée ?
            partie->SetLanceur(i); //"Lanceur" des altérations et actions
            partie->SetFactionLanceur(FACTION_EQUIPE);
            unsigned char j;
            for (j = 0; j < MAX_ALTERATIONS; ++j)
                if (heros->GetAlterations(j))
                    if (heros->GetAlterations(j)->GetScript())
                        heros->GetAlterations(j)->GetScript()->Executer(partie);
            //Attention : on boucle également sur les héros absents
            if (heros->GetAction() != ACTION_INACTIF) {
                heros->SetAnimation(heros->GetAction());
                switch (heros->GetAction()) {
                case ACTION_ATTAQUER:
                    heros->SetTempsAnimation(15);
                    //Si l'ennemi est déjà mort
                    if (!heros->GetCibles()[0]->estEnVie()) {
                        heros->SetCibles(0);
                        heros->SetAction(ACTION_INACTIF);
                        //TODO: Coder changement de cible automatique
                        return;
                    }
                    heros->Attaquer(rand(), RAND_MAX);
                    heros->SetCibles(0);
                    break;
                case ACTION_DEFENSE:
                    heros->SetTempsAnimation(20);
                    heros->SetGarde(true);
                    break;
                case ACTION_RANG:
                    heros->SetTempsAnimation(20);
                    heros->ChangerRang();
                    break;
                case ACTION_OBJETS:
                    //Utiliser objet
                    //TODO: Fusionner le test de présence de l'objet
                    //avec son effacement de l'inventaire ?
                    if (heros->GetObjet()) {
                        heros->SetTempsAnimation(60);
                        Objet* objet = heros->GetObjet();
                        //Si l'objet est bien dans l'inventaire
                        if (partie->GetInventaire()->ChercherObjet(objet)
                        != MAX_OBJETS) {
                            //On s'intéresse à l'objet du héros
                            if (((Utilisable*)objet)->GetEffet())
                                if (((Utilisable*)objet)->GetEffet()->GetScript())
                                    ((Utilisable*)objet)->GetEffet()->GetScript(
                                                                )->Executer(partie);
                            //Retirer l'objet de l'inventaire
                            partie->GetInventaire()->RetirerObjets(objet);
                        }
                    }
                    heros->SetCibles(0);
                    break;
                case ACTION_CAPACITE:
                    //Utiliser capacité
                    //TODO: Fusionner le test de coût de magie
                    //avec la modification de la magie ?
                    if (heros) {
                        if (heros->GetCapacite()) {
                            heros->SetTempsAnimation(60);
                            //Si le héros a assez de magie
                            if (heros->GetMagie() >= heros->GetCapacite()->GetCoutMagie()) {
                                //On s'intéresse à la capacité du héros
                                if (heros->GetCapacite()->GetEffet())
                                    if (heros->GetCapacite()->GetEffet()->GetScript())
                                        heros->GetCapacite()->GetEffet()->GetScript(
                                                                            )->Executer(partie);
                                heros->ChangerMagie(-heros->GetCapacite()->GetCoutMagie());
                            }
                        }
                        heros->SetCibles(0);
                    }
                    break;
                case ACTION_FUITE:
                    if (!(rand() % 2)) { //1 chance sur 2
                        heros->SetTempsAnimation(20);
                        combat = COMBAT_FUITE;
                    }
                    break;
                default:
                    break;
                }
                if (heros->GetAction() != ACTION_DEFENSE)
                    heros->SetGarde(false);
                heros->ViderJauge();
                heros->SetAction(ACTION_INACTIF);
                i = MAX_HEROS_EQUIPE;
            }
        }
    }
}

void ActionMonstres(Partie* partie) {
    unsigned char i;
    Monstre* monstre;
    for (i = 0; i < partie->GetGroupeCombat()->GetNombre(); ++i) {
        monstre = partie->GetMonstre(i);
        if (monstre) {
            partie->SetLanceur(i); //Déplacé pour tester les altérations
            //Attention à bien remettre sur la bonne faction
            partie->SetFactionLanceur(FACTION_MONSTRES);
            unsigned char j;
            for (j = 0; j < MAX_ALTERATIONS; ++j)
                if (monstre->GetAlterations(j))
                    if (monstre->GetAlterations(j)->GetScript())
                        monstre->GetAlterations(j)->GetScript()->Executer(partie);
            if (monstre->Jauge_estpleine()) {
                //partie->SetLanceur(i);
                //partie->SetFactionLanceur(FACTION_MONSTRES);
                monstre->SetTempsAnimation(10);
                if (monstre->GetScript())
                    monstre->GetScript()->Executer(partie);
                monstre->ViderJauge();
                //Un seul monstre doit agir par frame
                i = partie->GetGroupeCombat()->GetNombre();
            }
        }
    }
}

void ActualiserJauges(Equipe* equipe, GroupeMonstres* groupe) {
    unsigned char i;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        if (equipe->GetHeros(i) && equipe->GetHeros(i)->estEnVie())
            equipe->GetHeros(i)->ActualiserJauge();
    if (groupe)
        for (i = 0; i < groupe->GetNombre(); ++i)
            if (groupe->GetMonstres(i) && groupe->GetMonstres(i)->estEnVie())
                groupe->GetMonstres(i)->ActualiserJauge();
}

void ViderJauges(Equipe* equipe) {
    unsigned char i;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        if (equipe->GetHeros(i) && equipe->GetHeros(i)->estEnVie())
            equipe->GetHeros(i)->ViderJauge();
}

int CombatEnCours(int combat, Equipe* equipe, GroupeMonstres* groupe) {
    unsigned char i;
    for (i = 0; i < MAX_HEROS_EQUIPE; ++i)
        if (equipe->GetHeros(i) && equipe->GetHeros(i)->GetVie()) {
            if (groupe)
                for (i = 0; i < groupe->GetNombre(); ++i)
                    if (groupe->GetMonstres(i) && groupe->GetMonstres(i)->GetVie()) {
                        if (combat == COMBAT_FUITE)
                            return COMBAT_FUITE;
                        return COMBAT_EN_COURS;
                    }
            return COMBAT_VICTOIRE;
        }
    return COMBAT_DEFAITE;
}
