#include "Input.h"
#include <moteur_graphique.h> //changePleinEcran
#include <SDL2/SDL.h>

Input::Input() {
    Vider();
}

Input::~Input() {
}

bool Input::GetBouton(unsigned char id) const {
    return m_Boutons[id];
}

void Input::SetBouton(bool val, unsigned char id) {
    m_Boutons[id] = val;
}

bool Input::TakeBouton(unsigned char id) {
    if (m_Boutons[id]) {
        m_Boutons[id] = false;
        return true;
    }
    return false;
}

void Input::Actualiser() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        exit(0);
                        break;
                    case SDLK_f:
                        changePleinEcran(false);
                        break;
                    case SDLK_UP:
                        setHaut(true);
                        break;
                    case SDLK_RIGHT:
                        setDroite(true);
                        break;
                    case SDLK_DOWN:
                        setBas(true);
                        break;
                    case SDLK_LEFT:
                        setGauche(true);
                        break;
                    case SDLK_a:
                        setA(true);
                        break;
                    case SDLK_b:
                        setB(true);
                        break;
                    case SDLK_x:
                        setX(true);
                        break;
                    case SDLK_y:
                        setY(true);
                        break;
                    case SDLK_l:
                        setL(true);
                        break;
                    case SDLK_r:
                        setR(true);
                        break;
                    case SDLK_RETURN:
                        setStart(true);
                        break;
                    case SDLK_DELETE:
                        setSelect(true);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        setHaut(false);
                        break;
                    case SDLK_RIGHT:
                        setDroite(false);
                        break;
                    case SDLK_DOWN:
                        setBas(false);
                        break;
                    case SDLK_LEFT:
                        setGauche(false);
                        break;
                    case SDLK_a:
                        setA(false);
                        break;
                    case SDLK_b:
                        setB(false);
                        break;
                    case SDLK_x:
                        setX(false);
                        break;
                    case SDLK_y:
                        setY(false);
                        break;
                    case SDLK_l:
                        setL(false);
                        break;
                    case SDLK_r:
                        setR(false);
                        break;
                    case SDLK_RETURN:
                        setStart(false);
                        break;
                    case SDLK_DELETE:
                        setSelect(false);
                    default:
                        break;
                }
                break;
        }
    }
}

void Input::Vider() {
    setHaut(false);
    setDroite(false);
    setBas(false);
    setGauche(false);
    setA(false);
    setB(false);
    setX(false);
    setY(false);
    setL(false);
    setR(false);
    setStart(false);
    setSelect(false);
}
