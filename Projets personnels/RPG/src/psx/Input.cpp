#include "Input.h"
#include <psxpad.h> // defines and structs for controller

#include <stdlib.h>

extern unsigned char padbuff[2][34];
extern unsigned char paddelai;

#define DELAI_INPUT 8

Input::Input() {
    Vider();
}

Input::~Input() {
}

bool Input::GetBouton(unsigned char id) const {
    if (paddelai)
        return false;
    return m_Boutons[id];
}

void Input::SetBouton(bool val, unsigned char id) {
    paddelai = DELAI_INPUT;
    m_Boutons[id] = val;
}

bool Input::TakeBouton(unsigned char id) {
    if (m_Boutons[id]) {
        m_Boutons[id] = false;
        if (paddelai)
            return false;
        paddelai = DELAI_INPUT;
        return true;
    }
    return false;
}

void Input::Actualiser() {
    Vider();
    if (paddelai)
        --paddelai;
    PADTYPE* pad = (PADTYPE*)padbuff[0];
    // Only parse inputs when a controller is connected
    if (pad->stat == 0) {
      // Only parse when a digital pad,
      // dual-analog and dual-shock is connected
      if (pad->type == 0x4 || pad->type == 0x5 || pad->type == 0x7) {
        // if (~pad->btn) { // un bouton est pressé
        if (pad->btn != 65535) { // un bouton est pressé
            if (!(pad->btn & PAD_UP))            // test UP
                m_Boutons[BOUTON_HAUT] = true;//setHaut(true);
            else if (!(pad->btn & PAD_DOWN))     // test DOWN
                m_Boutons[BOUTON_BAS] = true; //setBas(true);
            if (!(pad->btn & PAD_LEFT))          // test UP
                m_Boutons[BOUTON_GAUCHE] = true; //setGauche(true);
            else if (!(pad->btn & PAD_RIGHT))    // test DOWN
                m_Boutons[BOUTON_DROITE] = true; //setDroite(true);
            if (!(pad->btn & PAD_CROSS))
                m_Boutons[BOUTON_A] = true; //setA(true);
            if (!(pad->btn & PAD_CIRCLE))
                m_Boutons[BOUTON_B] = true; //setB(true);
            if (!(pad->btn & PAD_TRIANGLE))
                m_Boutons[BOUTON_X] = true; //setX(true);
            if (!(pad->btn & PAD_SQUARE))
                m_Boutons[BOUTON_Y] = true; //setY(true);
            if (!(pad->btn & PAD_L1) || !(pad->btn & PAD_R2))
                m_Boutons[BOUTON_L] = true; //setL(true);
            if (!(pad->btn & PAD_R1) || !(pad->btn & PAD_L2))
                m_Boutons[BOUTON_R] = true; //setR(true);
            if (!(pad->btn & PAD_START))
                m_Boutons[BOUTON_START] = true; //setStart(true);
            if (!(pad->btn & PAD_SELECT))
                m_Boutons[BOUTON_SELECT] = true; //setSelect(true);
            if (!(pad->btn & (PAD_L1 | PAD_R1 | PAD_START | PAD_SELECT)))
                return;
        }
      }
    }
}

void Input::Vider() {
    m_Boutons[BOUTON_HAUT] = false; //setHaut(false);
    m_Boutons[BOUTON_BAS] = false; //setDroite(false);
    m_Boutons[BOUTON_GAUCHE] = false; //setBas(false);
    m_Boutons[BOUTON_DROITE] = false; //setGauche(false);
    m_Boutons[BOUTON_A] = false; //setA(false);
    m_Boutons[BOUTON_B] = false; //setB(false);
    m_Boutons[BOUTON_X] = false; //setX(false);
    m_Boutons[BOUTON_Y] = false; //setY(false);
    m_Boutons[BOUTON_L] = false; //setL(false);
    m_Boutons[BOUTON_R] = false; //setR(false);
    m_Boutons[BOUTON_START] = false; //setStart(false);
    m_Boutons[BOUTON_SELECT] = false; //setSelect(false);
}
