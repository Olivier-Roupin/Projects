#include "lib/Elements.h"

int ModificateurElement(int val, char element1, char element2) {
    if (val < 0) {
        const char modificateursElements[NOMBRE_ELEMENTS*NOMBRE_ELEMENTS] = {
            2, 2, 2, 2, 2, 2, 2, 2,  //ELEMENT_NEUTRE
            2, 4, 1, 2, 2, 2, 2, 2,  //ELEMENT_FEU
            2,-2, 4, 1, 2, 2, 2, 2,  //ELEMENT_EAU
            2, 2,-2, 4, 0,-2, 2, 2,  //ELEMENT_FOUDRE
            2, 2, 2, 2, 2, 0, 2, 2,  //ELEMENT_SOL
            2, 2, 2, 1,-2, 2, 2, 2,  //ELEMENT_VENT
            2, 2, 2, 2, 2, 2, 4,-2,  //ELEMENT_LUMIERE
            2, 2, 2, 2, 2, 2,-2, 4}; //ELEMENT_TENEBRES

        return val*modificateursElements[NOMBRE_ELEMENTS*element1+element2];// /2;
    } else {
        const char modificateursElements[NOMBRE_ELEMENTS*NOMBRE_ELEMENTS] = {
            2, 2, 2, 2, 2, 2, 2, 2,  //ELEMENT_NEUTRE
            2,-2, 1, 2, 2, 2, 2, 2,  //ELEMENT_FEU
            2, 4,-2, 1, 2, 2, 2, 2,  //ELEMENT_EAU
            2, 2, 4,-2, 0, 4, 2, 2,  //ELEMENT_FOUDRE
            2, 2, 2, 4, 2, 0, 2, 2,  //ELEMENT_SOL
            2, 2, 2, 1, 4, 2, 2, 2,  //ELEMENT_VENT
            2, 2, 2, 2, 2, 2,-2, 4,  //ELEMENT_LUMIERE
            2, 2, 2, 2, 2, 2, 4,-2}; //ELEMENT_TENEBRES

        return val*modificateursElements[NOMBRE_ELEMENTS*element1+element2];// /2;
    }
}
