#include "scenes/Menu_Sauver.h"
#include <affichage/Menu_Sauver.h>
#include <scenes/Ecran_titre.h> //ChargerPartie
#include <moteur_graphique.h> //horloge
#include <Input.h>
#include <fichierES.h>
#include <conversions.h>

#define NOMBRE_CHOIX_MENU_SAUVER 2

int Sauver(Partie* partie) {
    Input* input = partie->GetInput();
    int situation(SITUATION_CHOIX_SAUVEGARDE);
    char choix = 0;
    // int id = 0;
    unsigned char id = partie->GetId() % NOMBRE_SAUVEGARDES; //basé sur la sauvegarde chargée
    unsigned char i;
    char fichier[] = "sauvegarde0.txt";
    char* nom_cartes[NOMBRE_SAUVEGARDES];
    char* nom_heros[NOMBRE_SAUVEGARDES];
    char* temps[NOMBRE_SAUVEGARDES];

    char animation;
    for (animation = 0; animation < 6; ++animation) {
        AfficherSauverAnimation(animation); //frames 0-5
        afficherEcran();
        syncEcran(frameLimit);
    }

    //Chargement des informations
    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
        if (fichier_existe(fichier)) {
            Partie partie;
            ChargerPartie(i, partie);
            if (partie.GetCarte()) {
                nom_cartes[i] = new char[TAILLE_NOM_CARTE+1];
                int j = 0;
                LIRE_CHAINE_(j,partie.GetCarte()->GetNom(),nom_cartes[i],TAILLE_NOM_CARTE);
            } else
                nom_cartes[i] = 0;
            nom_heros[i] = 0;
            if (partie.GetEquipe()) {
                for (unsigned char k = 0; k < MAX_HEROS_EQUIPE; ++k) {
                    if (partie.GetEquipe()->GetHeros(k)) {
                        nom_heros[i] = new char[TAILLE_NOM_CARTE+1];
                        int j = 0;
                        LIRE_CHAINE_(j,partie.GetEquipe()->GetHeros(k)->GetNom(),nom_heros[i],TAILLE_NOM_PERSONNAGE);
                        break;
                    }
                }
            }
            temps[i] = new char[9];
            Int2Temps(partie.GetTemps(), temps[i]);
        } else
            temps[i] = 0;
        ++fichier[10];
    }

    while (!input->getB()) {
        AfficherSauverChoix(nom_heros, nom_cartes, temps, id);
        switch (situation) {
        case SITUATION_CHOIX_SAUVEGARDE:
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
            if (input->takeHaut())
                id = AVANT(id,NOMBRE_SAUVEGARDES);
            if (input->takeBas())
                id = APRES(id,NOMBRE_SAUVEGARDES);
            if (input->takeA())
                situation = SITUATION_VALIDATION;
            break;
        case SITUATION_VALIDATION:
            AfficherSauverValider(choix);
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
            if (input->takeGauche())
                choix = AVANT(choix, NOMBRE_CHOIX_MENU_SAUVER);
            if (input->takeDroite())
                choix = APRES(choix, NOMBRE_CHOIX_MENU_SAUVER);
            if (input->takeA()) {
                if (choix) {
                    //mettre à jour l'id
                    partie->SetId(partie->GetId()-partie->GetId()%NOMBRE_SAUVEGARDES+id);
                    fichier[10] = '0'+id;
                    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
                        if (nom_cartes[i]) delete nom_cartes[i];
                        if (nom_heros[i])  delete nom_heros[i];
                        if (temps[i])      delete temps[i];
                    }
                    char* fbuf = new char[1024];
                    partie->SetTempsActif(horloge());
                    fbuf[partie->Ecrire(fbuf)] = '\0';
                    fichier_ecrire(fichier, fbuf);
                    delete[] fbuf;
                    for (animation = 0; animation < 6; ++animation) {
                        AfficherSauverAnimation(5-animation);
                        afficherEcran();
                        syncEcran(frameLimit);
                    }
                    return 0;
                }
                else
                    situation = SITUATION_CHOIX_SAUVEGARDE;
            }
            if (input->takeB())
                situation = SITUATION_CHOIX_SAUVEGARDE;
            break;
        default:
            for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
                if (nom_cartes[i]) delete nom_cartes[i];
                if (nom_heros[i])  delete nom_heros[i];
                if (temps[i])      delete temps[i];
            }
            for (animation = 0; animation < 6; ++animation) {
                AfficherSauverAnimation(5-animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            return -1;
        }
    }
    input->setB(0);
    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
        if (nom_cartes[i]) delete nom_cartes[i];
        if (nom_heros[i])  delete nom_heros[i];
        if (temps[i])      delete temps[i];
    }
    for (animation = 0; animation < 6; ++animation) {
        AfficherSauverAnimation(6-animation); //frames 6-1
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}
