#include "scenes/Ecran_titre.h"
// #include <lib/Partie.h>
#include <affichage/Ecran_titre.h>
#include <moteur_graphique.h>
#include <fichierES.h>
#include <conversions.h>
#include <cstdlib>     // rand

#define NOMBRE_CHOIX_ECRAN_TITRE 3

void ChargerPartie(char choix, Partie& partie) {
    unsigned int taille = PreparerSauvegarde(choix+1);
    if (taille) {
        char* fbuf = new char[taille*2048];
        ChargerSauvegarde(choix+1, taille, fbuf);
        int i = 0;
        partie.Lire(i, fbuf);
        //TODO: vérifier que l'id n'est pas celui d'une autre sauvegarde ?
        if (choix == NOUVELLE_PARTIE) // générer un id aléatoirement
            partie.SetId((unsigned char)(rand()%(256/NOMBRE_SAUVEGARDES)*NOMBRE_SAUVEGARDES));
        delete[] fbuf;
    }
}

/*void ChargerPartie(int choix, Partie& partie) {
    char* fbuf = new char[1024];
    unsigned int longueur;
    if (choix != NOUVELLE_PARTIE) {
        char fichier[] = "sauvegarde0.txt";
        fichier[10] += choix;
        longueur = fichier_lire(fichier, fbuf);
    } else
        longueur = fichier_lire("nouvelle.txt", fbuf);
    if (longueur) {
        int i = 0;
        partie.Lire(i, fbuf);
        //TODO: vérifier que l'id n'est pas celui d'une autre sauvegarde ?
        if (choix == NOUVELLE_PARTIE) // générer un id aléatoirement
            partie.SetId((unsigned char)(rand()%(256/NOMBRE_SAUVEGARDES)*NOMBRE_SAUVEGARDES));
    }
    delete[] fbuf;
}*/

/*void ChargerPartie(int choix, Partie& partie) {
        int i = 0;
        partie.Lire(i, "0 100 0 0  1 0 1  2 4 4 3 0\n\
0 0\n1 5\n0 0\n2 1\n3 2\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n\
0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n\
0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n\
0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n\
0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n\
0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n0 0\n\
0 0\n0 0\n0 0\n0 0\n\
1 Richard 99 49 99 4 5 49 10 10 20 50 50 0 0 1 0 0 0 0 2 2 3 0 0 0\n1 2 0 0 0 0 0 0 0 0 \n0 0 0 0 0 \n\
2 Johnny 49 99 49 6 3 99 15 15 20 50 50 0 0 1 0 0 0 0 2 2 3 0 0 0\n0 0 3 0 0 0 0 0 0 0 \n0 0 0 0 0 \n\
0 _ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 \n\
0 _ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 ");
        //TODO: vérifier que l'id n'est pas celui d'une autre sauvegarde ?
        if (choix == NOUVELLE_PARTIE) // générer un id aléatoirement
            partie.SetId((unsigned char)(rand()%(256/NOMBRE_SAUVEGARDES)*NOMBRE_SAUVEGARDES));
}*/

int Ecran_titre(Input* input) {
    char situation = SITUATION_ECRAN_TITRE;
    char choix = 0;
    unsigned char id = 0;
    unsigned char i;
    char* nom_cartes[NOMBRE_SAUVEGARDES];
    char* nom_heros[NOMBRE_SAUVEGARDES];
    char* temps[NOMBRE_SAUVEGARDES];

    while (!input->getA()) {
        switch (situation) {
        case SITUATION_ECRAN_TITRE:
            AfficherEcran_Titre(choix);
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
            if (input->takeHaut())
                choix = AVANT(choix, NOMBRE_CHOIX_ECRAN_TITRE);
            if (input->takeBas())
                choix = APRES(choix, NOMBRE_CHOIX_ECRAN_TITRE);
            if (input->takeA()) {
                if (choix == -NOUVELLE_PARTIE)
                    return NOUVELLE_PARTIE;
                if (choix == -QUITTER)
                    return QUITTER;
                // CHARGER_PARTIE
                char fichier[] = "sauvegarde0.txt";
                for (i = 0; i < NOMBRE_SAUVEGARDES; i++) {
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
                situation = SITUATION_CHARGER;
            }
            break;
        case SITUATION_CHARGER:
            AfficherCharger(nom_heros, nom_cartes, temps, id);
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
            if (input->takeHaut())
                id = AVANT(id, NOMBRE_SAUVEGARDES);
            if (input->takeBas())
                id = APRES(id, NOMBRE_SAUVEGARDES);
            if (input->takeA())
                if (temps[id]) {
                    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
                        if (nom_cartes[i]) delete nom_cartes[i];
                        if (nom_heros[i])  delete nom_heros[i];
                        if (temps[i])      delete temps[i];
                    }
                    return id;
                }
            if (input->takeB()) {
                situation = SITUATION_ECRAN_TITRE;
            }
            break;
        default:
            for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
                if (nom_cartes[i]) delete nom_cartes[i];
                if (nom_heros[i])  delete nom_heros[i];
                if (temps[i])      delete temps[i];
            }
            return NOUVELLE_PARTIE;
        }
    }
    input->setA(0);
    for (i = 0; i < NOMBRE_SAUVEGARDES; ++i) {
        if (nom_cartes[i]) delete nom_cartes[i];
        if (nom_heros[i])  delete nom_heros[i];
        if (temps[i])      delete temps[i];
    }
    return NOUVELLE_PARTIE;
}
