#include "scenes/Menu_Magasin.h"
#include <affichage/Menu_Magasin.h>
#include <moteur_graphique.h>
#include <lib/Partie.h> //MAX_OR

#define NOMBRE_CHOIX_MAGASIN 3

int Magasins_Acheter(Inventaire* inventaire, Equipe* equipe, Magasin* magasin,
                     Input* input, unsigned int &Or) {
    char choix = 0;
    char animation;
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMagasins(MAGASIN_ACHETER, Or, true);
        AfficherMagasins_AcheterAnimation(animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        AfficherMagasins(MAGASIN_ACHETER, Or, true);
        AfficherMagasins_Acheter(magasin, inventaire, equipe, choix, Or);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeHaut())
            if (choix > 0)
                --choix;
        if (input->takeBas())
            if (choix < magasin->GetNombre() - 1)
                ++choix;
        if (input->takeA())
            if (magasin->GetObjets(choix)) {
                if (Or >= magasin->GetPrix(choix)) {
                    inventaire->AjouterObjets(magasin->GetObjets(choix));
                    Or -= magasin->GetPrix(choix);
                }
            }
    }
    input->setB(0);
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMagasins(MAGASIN_ACHETER, Or);
        AfficherMagasins_AcheterAnimation(6-animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}

int Magasins_Vendre(Inventaire* inventaire, Equipe* equipe,
                    Input* input, unsigned int &Or) {
    int choix = 0;
    char animation;
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMagasins(MAGASIN_VENDRE, Or, true);
        AfficherMagasins_VendreAnimation(animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        AfficherMagasins(MAGASIN_VENDRE, Or, true);
        AfficherMagasins_Vendre(inventaire, equipe, choix);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeHaut())
            if (choix > 0)
                choix--;
        if (input->takeBas())
            if (choix < MAX_OBJETS - 1)
                choix++;
        if (input->takeA()) {
            if (Or <= MAX_OR - inventaire->GetPrix(choix)) {
                Or += inventaire->GetPrix(choix);
                //On retire l'objet après sinon le prix est nul
                inventaire->RetirerObjets(inventaire->GetObjet(choix));
            }
            else
                Or = MAX_OR;
        }
    }
    input->setB(0);
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMagasins(MAGASIN_VENDRE, Or);
        AfficherMagasins_VendreAnimation(6-animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}

int Magasins(Inventaire* inventaire, Equipe* equipe, Magasin* magasin,
             Input* input, unsigned int &Or) {
    char choix = 0;
    char animation;
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMagasinsAnimation(animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        AfficherMagasins(choix, Or);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeGauche())
            if (choix > 0)
                choix--;
        if (input->takeDroite())
            if (choix < NOMBRE_CHOIX_MAGASIN - 1)
                choix++;
        if (input->takeA())
            switch (choix) {
            case MAGASIN_ACHETER:
                if (inventaire && equipe && magasin)
                    Magasins_Acheter(inventaire, equipe, magasin, input, Or);
                break;
            case MAGASIN_VENDRE:
                if (inventaire && equipe)
                    Magasins_Vendre(inventaire, equipe, input, Or);
                break;
            case MAGASIN_QUITTER:
                for (animation = 0; animation <= 6; ++animation) {
                    AfficherMagasinsAnimation(6-animation);
                    afficherEcran();
                    syncEcran(frameLimit);
                }
                return 0;
            default:
                for (animation = 0; animation <= 6; ++animation) {
                    AfficherMagasinsAnimation(6-animation);
                    afficherEcran();
                    syncEcran(frameLimit);
                }
                return -1;
            }
    }
    input->setB(0);
    for (animation = 0; animation <= 6; ++animation) {
        AfficherMagasinsAnimation(6-animation);
        afficherEcran();
        syncEcran(frameLimit);
    }
    return 0;
}
