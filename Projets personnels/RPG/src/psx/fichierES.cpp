#include "fichierES.h"
#include <psxcd.h>
#include <stdlib.h> // malloc/free

bool fichier_existe(const char* nom) {
    return true;
}

unsigned int fichier_lire(const char* nom, char* buffer) {
    CdlFILE filePos;
    int     numsecs;
    buffer = 0;
    /* locate the file on the CD */
    if (CdSearchFile(&filePos, nom)) {
        /* calculate number of sectors to read for the file */
        numsecs = (filePos.size+2047)/2048;
        /* allocate buffer for the file (replace with malloc3() for PsyQ) */
        buffer = (char*)malloc(2048*numsecs);
        /* set read target to the file */
        CdControl(CdlSetloc, (u_char*)&filePos.pos, 0);
        /* start read operation */
        CdRead(numsecs, (u_long*)buffer, CdlModeSpeed);
        /* wait until the read operation is complete */
        CdReadSync(0, 0);
    } else
      return 0;

    return 2048*numsecs;
}

const char* fichiers_bdds[NOMBRE_BDDS] = {
      "\\EFFETS.TXT;1",
      "\\OBJETS.TXT;1",
    "\\MAGASINS.TXT;1",
       "\\HEROS.TXT;1",
    "\\MONSTRES.TXT;1",
     "\\GROUPES.TXT;1",
    "\\TILESETS.TXT;1",
    "\\EVENEMEN.TXT;1",
      "\\CARTES.TXT;1",
    "\\CAPACITE.TXT;1",
    "\\ALTERATI.TXT;1"
};

unsigned int PreparerBDD(unsigned char bdd) {
    CdlFILE filePos;
    if (CdSearchFile(&filePos, fichiers_bdds[bdd])) {
        CdControl(CdlSetloc, (u_char*)&filePos.pos, 0);
        return (filePos.size+2047)/2048;
    }
    return 0;
}

bool ChargerBDD(unsigned char bdd, unsigned int taille, char* buffer) {
    if (taille) {
        CdRead(taille, (u_long*)buffer, CdlModeSpeed);
        CdReadSync(0, 0);
        return true;
    }
    return false;
}

const char* fichiers_sauvegardes[NOMBRE_SAUVEGARDES+1] = {
    "\\NOUVELLE.TXT;1",
       "\\SAUV0.TXT;1",
       "\\SAUV1.TXT;1",
       "\\SAUV2.TXT;1",
       "\\SAUV3.TXT;1"
};

unsigned int PreparerSauvegarde(unsigned char id) {
    CdlFILE filePos;
    if (CdSearchFile(&filePos, fichiers_sauvegardes[id])) {
        CdControl(CdlSetloc, (u_char*)&filePos.pos, 0);
        return (filePos.size+2047)/2048;
    }
    return 0;
}

bool ChargerSauvegarde(unsigned char id, unsigned int taille, char* buffer) {
    if (taille) {
        CdRead(taille, (u_long*)buffer, CdlModeSpeed);
        CdReadSync(0, 0);
        return true;
    }
    return false;
}

unsigned int fichier_ecrire(const char* nom, const char* buffer) {
    return 0;
}

#ifdef EXPORTOUT
unsigned int fichier_ecrire(const char* nom, int n) {
    return 0;
}

unsigned int fichier_ajouter(const char* nom, const char* buffer) {
    return 0;
}

unsigned int fichier_ajouter(const char* nom, int n) {
    return 0;
}
#endif //EXPORTOUT