#include "scenes/Menu_Objets.h"
#include <affichage/Menu_Objets.h>
#include <moteur_graphique.h>
#include <lib/Utilisable.h>
#include <Input.h>

bool Equipe_Reduit(const Inventaire* inventaire, char choix_objet, Equipe* equipe, Input* input, char& choix, bool multiple) {
    bool quantite = QUANTITE_UNE;
    while (!input->getB()) {
        AfficherObjets(inventaire, choix_objet);
        AfficherEquipe_Reduit(equipe, choix, quantite, 1, 16);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (multiple && (input->takeL() || input->takeR()))
            quantite = !quantite;
        if (input->takeHaut()) {
            if (multiple)
                quantite = QUANTITE_UNE;
            if (choix > 0)
                --choix;
        }
        if (input->takeBas()) {
            if (multiple)
                quantite = QUANTITE_UNE;
            if (choix < MAX_HEROS_EQUIPE - 1)
                ++choix;
        }
        if (input->takeA())
            return quantite; // validé
    }
    input->setB(0);
    choix = -1; // annulé
    return QUANTITE_UNE;
}

int UtiliserObjet(Partie* partie, Utilisable* objet, char choix_heros, char choix_objet) {
    Equipe* equipe = partie->GetEquipe();
    Heros* heros = equipe->GetHeros(choix_heros);
    //Carte* carte = partie->GetCarte(); // sorts de téléportation etc...
    //TODO: revoir l'impact des cibles par défaut
    const Effet* effet = objet->GetEffet();
    if (effet == 0)
        return -1;
    if (effet->GetDefaut_Quantite() == QUANTITE_FACTION
    || effet->GetDefaut_Cible() == CIBLE_TOUS) {
        partie->SetLanceur(choix_heros);
        partie->SetFactionLanceur(FACTION_EQUIPE);
        //partie->SetCible(0); // inutile
        partie->SetFaction(FACTION_EQUIPE);
        partie->SetQuantite(QUANTITE_FACTION);
        partie->SetHeros(choix_heros); // qui utilise l'objet
        partie->ApplyCible_selection(); // mettre la cible au heros
        if (effet->GetScript())
            effet->GetScript()->Executer(partie);
        // Remettre valeurs par défaut ?
        for (unsigned char i = 0; i < heros->GetNombreCibles(); ++i) {
            if (heros->GetCible(i)) {
                heros->GetCible(i)->SetMessage(0);
                heros->GetCible(i)->SetTempsMessage(0);
                heros->GetCible(i)->SetAnimation(ACTION_INACTIF);
                heros->GetCible(i)->SetTempsAnimation(0);
            }
        }
        heros->SetCibles(0);

        partie->GetInventaire()->RetirerObjets(objet);
    } else if (effet->GetDefaut_Cible() == CIBLE_LANCEUR
            || effet->GetDefaut_Cible() >= 0) {
        char choix = 0; //choix de la cible
        bool quantite;
        do { // tant que le choix n'est pas valide ou qu'on ne quitte pas
            quantite = Equipe_Reduit(partie->GetInventaire(), choix_objet, equipe, partie->GetInput(), choix, effet->GetChoix_Quantite());
        } while (choix != -1 && !equipe->GetHeros(choix)
                    && quantite == QUANTITE_UNE); // risqué pour affichage ?
        if (quantite == QUANTITE_FACTION
            || (choix != -1 && equipe->GetHeros(choix))) {
            // Utilisateur de l'objet
            partie->SetHeros(choix_heros);
            // Simulation d'un curseur de combat
            partie->SetLanceur(choix_heros); // pour le calcul des cibles
            partie->SetFactionLanceur(FACTION_EQUIPE);
            partie->SetCible(choix);
            partie->SetFaction(FACTION_EQUIPE);
            partie->SetQuantite(quantite);
            partie->ApplyCible_selection(); // mettre la cible au heros
            // Execution
            if (effet->GetScript())
                effet->GetScript()->Executer(partie);
            // Remettre valeurs par défaut ?
            for (unsigned char i = 0; i < heros->GetNombreCibles(); ++i) {
                if (heros->GetCible(i)) {
                    heros->GetCible(i)->SetMessage(0);
                    heros->GetCible(i)->SetTempsMessage(0);
                    heros->GetCible(i)->SetAnimation(ACTION_INACTIF);
                    heros->GetCible(i)->SetTempsAnimation(0);
                }
            }
            heros->SetCibles(0);

            partie->GetInventaire()->RetirerObjets(objet);
        }
    } else
        return -1; // autres cas ?
    return 0;
}

int Objets(Partie* partie) {
    Input* input = partie->GetInput();
    char choix = 0;
    char choix2 = -1; // pour l'échange d'objets
    Inventaire* inventaire = partie->GetInventaire();
    //Equipe* equipe = partie->GetEquipe();
    //Carte* carte = partie->GetCarte();
    char animation;
    for (animation = 0; animation < 6; ++animation) {
        AfficherObjetsAnimation(animation); //frames 0-5
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        AfficherObjets(inventaire, choix, choix2);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeHaut())
            if (choix > 1)
                choix -= 2;
            // if (choix > 0) {
            //     choix--;
            //     if (choix > 0)
            //         choix--;
            // }
        if (input->takeBas())
            if (choix < MAX_OBJETS - 2)
                choix += 2;
            // if (choix < MAX_OBJETS - 1) {
            //     choix++;
            //     if (choix < MAX_OBJETS - 1)
            //         choix++;
            // }
        if (input->takeGauche())
            // choix = choix + (choix ? -1 : 1);
            choix = choix - choix%2;
        if (input->takeDroite())
            // choix = choix + (choix ? -1 : 1);
            choix = choix - choix%2 + 1;
        if (input->takeA()) {
            if (choix2 == -1) {
                if (inventaire->GetObjets(choix) && inventaire->GetType(choix
                                        ) == UTILISABLE) {
                    Utilisable* objet = (Utilisable*)inventaire->GetObjet(choix);
                    if (objet->GetEffet() && partie->GetEquipe()) {
                        if (objet->GetEffet()->GetDisponibilite() == TOUJOURS
                        ||  objet->GetEffet()->GetDisponibilite() == MENU) {
                            //Le premier personnage en vie utilise l'objet
                            char i;
                            for (i = 1; i < MAX_HEROS_EQUIPE+1; ++i) { //TODO: pourquoi +1 ?
                                if (partie->GetEquipe()->GetHeros(i) && partie->GetEquipe()->GetHeros(i)->estEnVie())
                                    break;
                            }
                            UtiliserObjet(partie, objet, i, choix);
                        }
                    }
                }
            } else {
                inventaire->EchangerObjets(choix2, choix);
                choix2 = -1;
            }
        }
        if (input->takeY()) {
            if (choix2 == -1)
                choix2 = choix;
            else
                choix2 = -1;
        }
        if (choix2 != -1 && input->getB()) {
            choix2 = -1;
            input->setB(0);
        }

    }
    input->setB(0);
    for (animation = 0; animation < 6; ++animation) {
        AfficherObjetsAnimation(6-animation); //frames 6-1
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}
