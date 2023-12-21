#include "scenes/Menu_Competences.h"
#include <affichage/Menu_Competences.h>
#include <moteur_graphique.h>
#include <affichage/Menu_Objets.h> //AfficherEquipe_Reduit
#include <Input.h>
#include <scenes/Menu_Equipement.h> //ChercherHerosPrecedent, ChercherHerosSuivant

bool Equipe_Reduit(const Heros* heros, const char choix_competence,
    Equipe* equipe, Input* input, char& choix, bool multiple) {
    bool quantite = QUANTITE_UNE;
    while (!input->getB()) {
        AfficherCompetences(heros, choix_competence);
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

//TODO: information dupliquée entre affichage et exécution ?
int UtiliserCompetence(Partie* partie, Capacite* capacite, char choix_heros, const char choix_competence) {
    Equipe* equipe = partie->GetEquipe();
    Heros* heros = equipe->GetHeros(choix_heros);
    //Carte* carte = partie->GetCarte(); // sorts de téléportation etc...
    //TODO: revoir l'impact des cibles par défaut
    const Effet* effet = capacite->GetEffet();
    if (effet == 0)
        return -1;
    if (effet->GetDefaut_Quantite() == QUANTITE_FACTION
    || effet->GetDefaut_Cible() == CIBLE_TOUS) {
        partie->SetLanceur(choix_heros);
        partie->SetFactionLanceur(FACTION_EQUIPE);
        //partie->SetCible(0); // inutile
        partie->SetFaction(FACTION_EQUIPE);
        partie->SetQuantite(QUANTITE_FACTION);
        partie->SetHeros(choix_heros); // qui lance le sort
        partie->ApplyCible_selection(); // mettre la cible au heros
        partie->GetLanceur_selection()->SetCapacite(capacite); // pour l'élement, TODO
        if (effet->GetScript())
            effet->GetScript()->Executer(partie);
        // Remettre valeurs par défaut ?
        for (unsigned char i = 0; i < heros->GetNombreCibles(); ++i) {
            if (heros->GetCible(i)) {
                heros->GetCible(i)->SetMessage(0);
                heros->GetCible(i)->SetTempsMessage(0);
                heros->GetCible(i)->SetAnimation(ACTION_INACTIF);
                heros->GetCible(i)->SetTempsAnimation(0);
                //Retirer les altérations hors terrain
                for (unsigned char j = 0; j < MAX_ALTERATIONS; ++j) {
                    if (heros->GetAlterations(j)
                    && !heros->GetAlterations(j)->GetPostCombat())
                        heros->SetAlterations(0, j);
                }
            }

        }
        heros->SetCibles(0);
        partie->GetLanceur_selection()->SetCapacite(0); // pour l'élement, TODO

        heros->ChangerMagie(-capacite->GetCoutMagie());
        heros->ChangerVie(-capacite->GetCoutVie());
        heros->ChangerMagieP(-capacite->GetCoutMagieP());
        heros->ChangerVieP(-capacite->GetCoutVieP());
    } else if (effet->GetDefaut_Cible() == CIBLE_LANCEUR
            || effet->GetDefaut_Cible() >= 0) {
        char choix = 0;
        bool quantite;
        do { // tant que le choix n'est pas valide ou qu'on ne quitte pas
            quantite = Equipe_Reduit(heros, choix_competence, equipe, partie->GetInput(), choix, effet->GetChoix_Quantite());
        } while (choix != -1 && !equipe->GetHeros(choix)
                    && quantite == QUANTITE_UNE); // risqué pour affichage ?
        if (quantite == QUANTITE_FACTION
            || (choix != -1 && equipe->GetHeros(choix))) {
            // Lanceur du sort
            partie->SetHeros(choix_heros);
            // Simulation d'un curseur de combat
            partie->SetLanceur(choix_heros); // pour le calcul des cibles
            partie->SetFactionLanceur(FACTION_EQUIPE);
            partie->SetCible(choix);
            partie->SetFaction(FACTION_EQUIPE);
            partie->SetQuantite(quantite);
            partie->ApplyCible_selection(); // mettre la cible au heros
            partie->GetLanceur_selection()->SetCapacite(capacite); // pour l'élement, TODO
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
                    //Retirer les altérations hors terrain
                    for (unsigned char j = 0; j < MAX_ALTERATIONS; ++j) {
                        if (heros->GetAlterations(j)
                        && !heros->GetAlterations(j)->GetPostCombat())
                            heros->SetAlterations(0, j);
                    }
                }
            }
            heros->SetCibles(0);
            partie->GetLanceur_selection()->SetCapacite(0); // pour l'élement, TODO
            heros->ChangerMagie(-capacite->GetCoutMagie());
            heros->ChangerVie(-capacite->GetCoutVie());
            heros->ChangerMagieP(-capacite->GetCoutMagieP());
            heros->ChangerVieP(-capacite->GetCoutVieP());
        }
    } else
        return -1; // autres cas ?
    return 0;
}

void Competences(Partie* partie, char &choix_heros) {
    Input* input = partie->GetInput();
    char choix_competence = 0;
    Equipe* equipe = partie->GetEquipe();
    char animation;
    for (animation = 0; animation < 6; ++animation) {
        AfficherCompetencesAnimation(equipe->GetHeros(choix_heros), choix_heros, animation); //frames 0-5
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        Heros* heros = equipe->GetHeros(choix_heros);
        AfficherCompetences(heros,
                                 choix_competence);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeHaut())
            if (choix_competence > 0)
                --choix_competence;
        if (input->takeBas())
            if (choix_competence < MAX_SORTS - 1)
                ++choix_competence;
        if (input->takeL()) {
            for (animation = 0; animation < 6; ++animation) {
                AfficherCompetencesTransition(animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            choix_heros = ChercherHerosPrecedent(equipe, choix_heros);
        }
        if (input->takeR()) {
            for (animation = 0; animation < 6; ++animation) {
                AfficherCompetencesTransition(5-animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            choix_heros = ChercherHerosSuivant(equipe, choix_heros);
        }
        if (input->takeA()) {
            Capacite* capacite = heros->GetSorts(choix_competence);
            if (capacite && heros->GetVie() > 0 && (
                capacite->GetEffet()->GetDisponibilite() == TOUJOURS
                || capacite->GetEffet()->GetDisponibilite() == MENU) &&
                heros->GetMagie() >= capacite->GetCoutMagie())
                UtiliserCompetence(partie, capacite, choix_heros, choix_competence);
                // Mettre le code ici pour boucler sur Equipe_Reduit()
        }
    }
    for (animation = 0; animation < 6; ++animation) {
        AfficherCompetencesAnimation(equipe->GetHeros(choix_heros), choix_heros, 6-animation); //frames 6-1
        afficherEcran();
        syncEcran(frameLimit);
    }
}
