#include "scenes/Menu_Equipement.h"
#include <affichage/Menu_Equipement.h> //ChercherObjetPrecedent, ChercherObjetSuivant
#include <moteur_graphique.h>

#define NOMBRE_CHOIX_EQUIPEMENT NOMBRE_EQUIPEMENTS//6

//C'est l'inventaire réduit aux objets du type1 ou type2, retourne l'indice de l'objet choisi
int Objets_Reduit(Inventaire* inventaire, const Heros* heros, Input* input,
    unsigned char type1, unsigned char type2, char choix_equipement) {
    int choix = ChercherObjetSuivant(inventaire, -1, type1, type2);
    if (choix != -1) {
        while (!input->getB()) {
            AfficherEquipements(heros);
            AfficherChoixEquipement(heros, choix_equipement);
            AfficherObjetsEquipement(inventaire, heros->GetEquipement(choix_equipement), choix, type1, type2);
            afficherEcran();
            input->Actualiser();
            syncEcran(frameLimit);
            if (input->takeHaut())
                if (choix > 0)
                    choix = ChercherObjetPrecedent(inventaire, choix, type1, type2);
            if (input->takeBas())
                if (choix < MAX_OBJETS - 1)
                    choix = ChercherObjetSuivant(inventaire, choix, type1, type2);
            if (input->takeA())
                return choix;
        }
        input->setB(0);
    }
    return -1; //ne pas changer l'item par défaut
}

void Equipements(Inventaire *inventaire, Equipe* equipe, Input* input, char &choix_heros) {
    char choix_equipement = 0;
    int choix_objet = 0;
    unsigned char type1 = 0;
    unsigned char type2 = 0;
    char animation;
    for (animation = 0; animation < 6; ++animation) {
        AfficherEquipementsAnimation(equipe->GetHeros(choix_heros), choix_heros, animation); //frames 0-5
        afficherEcran();
        syncEcran(frameLimit);
    }
    while (!input->getB()) {
        Heros* heros = equipe->GetHeros(choix_heros); //non nul
        AfficherEquipements(heros);
        AfficherChoixEquipement(heros, choix_equipement);
        afficherEcran();
        input->Actualiser();
        syncEcran(frameLimit);
        if (input->takeHaut())
            choix_equipement = AVANT(choix_equipement,NOMBRE_CHOIX_EQUIPEMENT);
        if (input->takeBas())
            choix_equipement = APRES(choix_equipement,NOMBRE_CHOIX_EQUIPEMENT);
        if (input->takeY()) {
            inventaire->AjouterObjets(heros->GetEquipement(choix_equipement));
            heros->SetEquipement(0,choix_equipement);
        }
        if (input->takeL()) {
            for (animation = 0; animation < 6; ++animation) {
                AfficherEquipementsTransition(animation);
                AfficherChoixEquipementTransition(animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            choix_heros = ChercherHerosPrecedent(equipe, choix_heros);
        }
        if (input->takeR()) {
            for (animation = 0; animation < 6; ++animation) {
                AfficherEquipementsTransition(5-animation);
                AfficherChoixEquipementTransition(5-animation);
                afficherEcran();
                syncEcran(frameLimit);
            }
            choix_heros = ChercherHerosSuivant(equipe, choix_heros);
        }
        if (input->takeA()) {
            //TODO : bug sélection d'objet non équipés ? rajouter un if ?
            //TODO : élégant d'ajouter un objet dans l'inventaire ?
            inventaire->AjouterObjets(heros->GetEquipement(choix_equipement));
            switch (choix_equipement) {
            case EQUIPEMENT_MAINGAUCHE:
            case EQUIPEMENT_MAINDROITE:
                type1 = EQUIPABLE_ARME;
                type2 = EQUIPABLE_BOUCLIER;
                break;
            case EQUIPEMENT_TETE:
                type1 = EQUIPABLE_CASQUE;
                type2 = EQUIPABLE_CASQUE;
                break;
            case EQUIPEMENT_CORPS:
                type1 = EQUIPABLE_ARMURE;
                type2 = EQUIPABLE_ARMURE;
                break;
            case EQUIPEMENT_ACCESSOIRE1:
            case EQUIPEMENT_ACCESSOIRE2:
                type1 = EQUIPABLE_ACCESSOIRE;
                type2 = EQUIPABLE_ACCESSOIRE;
                break;
            default:
                break;
            }
            choix_objet = Objets_Reduit(inventaire, heros, input, type1, type2, choix_equipement);
            if (choix_objet >= 0 && choix_objet < MAX_OBJETS+1)
                heros->SetEquipement((Equipable*)(inventaire->GetObjet(choix_objet)),choix_equipement);
            inventaire->RetirerObjets(heros->GetEquipement(choix_equipement));
        }
    }
    for (animation = 0; animation < 6; ++animation) {
        AfficherEquipementsAnimation(equipe->GetHeros(choix_heros), choix_heros, 6-animation); //frames 6-1
        afficherEcran();
        syncEcran(frameLimit);
    }
}

char ChercherHerosPrecedent(const Equipe* equipe, char choix) {
    char choix0 = choix;
    do {
        choix = AVANT(choix,MAX_HEROS_EQUIPE);
        if (choix == choix0)
            return choix0; //sécurité
    } while (!equipe->GetHeros(choix));
    return choix;
}

char ChercherHerosSuivant(const Equipe* equipe, char choix) {
    char choix0 = choix;
    do {
        choix = APRES(choix,MAX_HEROS_EQUIPE);
        if (choix == choix0)
            return choix0;
    } while (!equipe->GetHeros(choix));
    return choix;
}
