#include "scenes/Menu_Nom.h"
#include <affichage/Menu_Nom.h>
#include <moteur_graphique.h>

int ChoixNom(Heros* heros, Input* input) {
    const char* nom_defaut = heros->GetNom();
    char image[2];
    heros->RenduCombat(image);
    char nom[TAILLE_NOM_PERSONNAGE+1];
    unsigned char i;
    for (i = 0; i < TAILLE_NOM_PERSONNAGE; ++i) {
        if (nom_defaut[i] == '\0')
            break;
        nom[i] = nom_defaut[i];
    }
    nom[i] = '\0';
    unsigned char x = 0, y = NOMBRE_LIGNES_CLAVIER, j = i;
    while (1) {
        AfficherChoixNom(image, nom, x, y, j);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeGauche()) {
            if (y < NOMBRE_LIGNES_CLAVIER) {
                x = AVANT(x,2*NOMBRE_COLONNES_CLAVIER);
                if (y == NOMBRE_LIGNES_CLAVIER-1
                && (x ==   NOMBRE_COLONNES_CLAVIER-1
                 || x ==   NOMBRE_COLONNES_CLAVIER-2
                 || x == 2*NOMBRE_COLONNES_CLAVIER-1
                 || x == 2*NOMBRE_COLONNES_CLAVIER-2))
                    x = AVANT(x,2*NOMBRE_COLONNES_CLAVIER);
            } else
                x = (x+NOMBRE_COLONNES_CLAVIER)%(2*NOMBRE_COLONNES_CLAVIER);
        }
        if (input->takeDroite()) {
            if (y < NOMBRE_LIGNES_CLAVIER) {
                x = APRES(x,2*NOMBRE_COLONNES_CLAVIER);
                if (y == NOMBRE_LIGNES_CLAVIER-1
                && (x ==   NOMBRE_COLONNES_CLAVIER-1
                 || x == 2*NOMBRE_COLONNES_CLAVIER-1))
                    x = APRES(x,2*NOMBRE_COLONNES_CLAVIER);
            } else
                x = (x+NOMBRE_COLONNES_CLAVIER)%(2*NOMBRE_COLONNES_CLAVIER);
        }
        if (input->takeL())
            x = (x+NOMBRE_COLONNES_CLAVIER)%(2*NOMBRE_COLONNES_CLAVIER);
        if (input->takeR())
            x = (x+NOMBRE_COLONNES_CLAVIER)%(2*NOMBRE_COLONNES_CLAVIER);
        if (input->takeHaut())
            y = AVANT(y,NOMBRE_LIGNES_CLAVIER+1);
        if (input->takeBas())
            y = APRES(y,NOMBRE_LIGNES_CLAVIER+1);
        if (input->takeA()) {
            if (y < NOMBRE_LIGNES_CLAVIER) {
                if (y == NOMBRE_LIGNES_CLAVIER-1
                 && x >= 2*NOMBRE_COLONNES_CLAVIER-2) {
                    if (j > 0) {
                        --j; // le caractère précédent est effacé
                        nom[j] = '\0'; // caractère actuel (invalide)
                    }
                } else if (j < TAILLE_NOM_PERSONNAGE) {
                    if (x < NOMBRE_COLONNES_CLAVIER)
                        nom[j] = 'A'+(char)(y*NOMBRE_COLONNES_CLAVIER+x);
                    else
                        nom[j] = 'a'+(char)(y*NOMBRE_COLONNES_CLAVIER+
                                            (x-NOMBRE_COLONNES_CLAVIER));
                    if ((nom[j] < 'A' || nom[j] > 'z' ||
                    (nom[j] > 'Z' && nom[j] < 'a'))) {// caractère invalide/espace
                        if (j > 0) {
                            nom[j] = '_';
                            ++j;
                            nom[j] = '\0';
                        }
                        //le nom ne peut pas commencer par un espace
                    } else {
                        ++j;
                        nom[j] = '\0';
                    }
                    // if (nom[j] > 'Z' && nom[j] < 'a') { // espace
                    //     nom[j] = '_';
                    //     ++j;
                    // } else if (nom[j] < 'A' || nom[j] > 'z') { // effacer
                    //     // if (j > 0 && j < TAILLE_NOM_PERSONNAGE-1) {
                    //     if (j > 0) {
                    //         nom[j] = '\0'; // caractère actuel (invalide)
                    //         --j; // le caractère précédent est effacé
                    //     }
                    // } else
                    //     ++j;
                    // nom[j] = '\0';
                } else {
                        y = NOMBRE_LIGNES_CLAVIER;
                        if (x < NOMBRE_COLONNES_CLAVIER)
                            x += NOMBRE_COLONNES_CLAVIER;
                }
            } else {
                if (x < NOMBRE_COLONNES_CLAVIER) { // nom par défaut
                    for (i = 0; i < TAILLE_NOM_PERSONNAGE; ++i) {
                        if (nom_defaut[i] == '\0')
                            break;
                        nom[i] = nom_defaut[i];
                    }
                    nom[i] = '\0';
                    j = i;
                } else { // confirmer
                    //Vérification du nom
                    if (j > 0) { // le nom n'est pas vide
                        // retirer les espaces à la fin
                        for (i = j-1; i > 0; --i) { //nom[0] != '_'
                            if (nom[i] != '_')
                                break;
                        }
                        if (i > 0) {
                            nom[i+1] = '\0'; //peut être redondant
                            for (i = 0; i < TAILLE_NOM_PERSONNAGE; ++i) {
                                if (nom[i] != nom_defaut[i]) { //le nom a changé
                                    heros->SetNom(nom);
                                    return 1;
                                }
                                if (nom_defaut[i] == '\0') // nom[i] == '\0'
                                    break;
                            }
                            return 0; //le nom n'a pas changé
                        }
                    }
                }
            }
        }
        if (input->takeB()) {
            if (j > 0) {
                --j;
                nom[j] = '\0';
            }
        }
        if (input->takeSelect()) { // nom par défaut ?
            y = NOMBRE_LIGNES_CLAVIER;
            if (x >= NOMBRE_COLONNES_CLAVIER)
                x -= NOMBRE_COLONNES_CLAVIER;
        }
        if (input->takeStart()) { // confirmer ?
            y = NOMBRE_LIGNES_CLAVIER;
            if (x < NOMBRE_COLONNES_CLAVIER)
                x += NOMBRE_COLONNES_CLAVIER;
        }
    }
    return 0; //le nom n'a pas changé
}
