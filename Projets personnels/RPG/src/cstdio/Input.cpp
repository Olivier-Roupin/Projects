#include "Input.h"
// #include <moteur_graphique.h> //changePleinEcran
#include <conio.h> //kbhit, getch
#include <cstdlib> //exit

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
    int c = 0;
    if (_kbhit()) {
        c = _getch();
        switch (c) {
            case 'w':
                exit(0);
                break;
            case 'f':
                // changePleinEcran(false);
                break;
            case 'H':
                setHaut(true);
                break;
            case 'P':
                setBas(true);
                break;
            case 'M':
                setDroite(true);
                break;
            case 'K':
                setGauche(true);
                break;
            case '\033':
                _getch(); // '['
                switch (_getch()) {
                    case 'A':
                        setHaut(true);
                        break;
                    case 'B':
                        setBas(true);
                        break;
                    case 'C':
                        setDroite(true);
                        break;
                    case 'D':
                        setGauche(true);
                        break;
                }
                break;
            case 224:
                switch (_getch()) {
                    case 'H':
                        setHaut(true);
                        break;
                    case 'P':
                        setBas(true);
                        break;
                    case 'M':
                        setDroite(true);
                        break;
                    case 'K':
                        setGauche(true);
                        break;
                }
                break;
            case 'z':
                setHaut(true);
                break;
            case 'd':
                setDroite(true);
                break;
            case 's':
                setBas(true);
                break;
            case 'q':
                setGauche(true);
                break;
            case 'a':
                setA(true);
                break;
            case 'b':
                setB(true);
                break;
            case 'x':
                setX(true);
                break;
            case 'y':
                setY(true);
                break;
            case 'l':
                setL(true);
                break;
            case 'r':
                setR(true);
                break;
            case '\n':
            case '\r':
                setStart(true);
                break;
            case '\b':
                setSelect(true);
                break;
            default:
                Vider();
                break;
        }
    } else
        Vider();
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
