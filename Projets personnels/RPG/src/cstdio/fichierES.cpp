#include "fichierES.h"
#include <cstdio>

bool fichier_existe(const char* nom) {
    // FILE* fp = fopen(nom, "r"); //"rb"
    FILE* fp = fopen(nom, "rb");
    if (fp == NULL)
        return false;
    fclose(fp);
    return true;
}

/*unsigned int fichier_longueur(const char* nom) {
    FILE* fp = fopen(nom, "r"); //"rb"
    if (fp == NULL)
        return 0;

    unsigned int longueur = 0;
    while (fgetc(fp) != EOF)
        ++longueur;
    fclose(fp);
    return longueur;
}*/

// unsigned int fichier_longueurb(const char* nom) {
unsigned int fichier_longueur(const char* nom) {
    FILE* fp = fopen(nom, "rb");
    if (fp == NULL)
        return 0;

    unsigned int longueur = 0;
    while (fgetc(fp) != EOF)
        ++longueur;
    fclose(fp);
    return longueur;
}

/*unsigned int fichier_lire(const char* nom, char* buffer) {
    FILE* fp = fopen(nom, "r"); //"rb"
    if (fp == NULL)
        return 0;

    char c;
    unsigned int longueur = 0;
    while ((c = fgetc(fp)) != EOF)
        buffer[longueur++] = c;
    buffer[longueur] = '\0';
    fclose(fp);
    return longueur;
}*/

// unsigned int fichier_lireb(const char* nom, char* buffer) {
unsigned int fichier_lire(const char* nom, char* buffer) {
    FILE* fp = fopen(nom, "rb");
    if (fp == NULL)
        return 0;

    char c;
    unsigned int longueur = 0;
    while ((c = fgetc(fp)) != EOF)
        buffer[longueur++] = c;
    buffer[longueur] = '\0';
    fclose(fp);
    return longueur;
}

unsigned int fichier_ecrire(const char* nom, const char* buffer) {
    // FILE* fp = fopen(nom, "w");
    FILE* fp = fopen(nom, "wb");
    if (fp == NULL)
        return 0;

    unsigned int longueur = fputs(buffer, fp);
    fclose(fp);
    return longueur;
}

const char* fichiers_ascii[NOMBRE_BDDS] = {
    "bdd/effets.txt",
    "bdd/objets.txt",
    "bdd/magasins.txt",
    "bdd/heros.txt",
    "bdd/monstres.txt",
    "bdd/groupesmonstres.txt",
    "bdd/tilesets.txt",
    "bdd/evenements.txt",
    "bdd/cartes.txt",
    "bdd/capacites.txt",
    "bdd/alterations.txt"
};

unsigned int PreparerASCII(unsigned char bdd) {
    if (fichier_existe(fichiers_ascii[bdd])) {
        return (fichier_longueur(fichiers_ascii[bdd])+2047)/2048;
    }
    return 0;
}

bool ChargerASCII(unsigned char bdd, unsigned int taille, char* buffer) {
    if (taille) {
        fichier_lire(fichiers_ascii[bdd], buffer);
        return true;
    }
    return false;
}

const char* fichiers_bdds[NOMBRE_BDDS] = {
    "bdd/effets.dat",
    "bdd/objets.dat",
    "bdd/magasins.dat",
    "bdd/heros.dat",
    "bdd/monstres.dat",
    "bdd/groupesmonstres.dat",
    "bdd/tilesets.dat",
    "bdd/evenements.dat",
    "bdd/cartes.dat",
    "bdd/capacites.dat",
    "bdd/alterations.dat"
};

const char* NomBDD(unsigned char bdd) {
    return fichiers_bdds[bdd];
}

unsigned int PreparerBDD(unsigned char bdd) {
    if (fichier_existe(fichiers_bdds[bdd])) {
        // return (fichier_longueurb(fichiers_bdds[bdd])+2047)/2048;
        return (fichier_longueur(fichiers_bdds[bdd])+2047)/2048;
    }
    return 0;
}

bool ChargerBDD(unsigned char bdd, unsigned int taille, char* buffer) {
    if (taille) {
        // fichier_lireb(fichiers_bdds[bdd], buffer);
        fichier_lire(fichiers_bdds[bdd], buffer);
        return true;
    }
    return false;
}

const char* fichiers_sauvegardes[NOMBRE_SAUVEGARDES+1] = {
    "nouvelle.txt",
    "sauvegarde0.txt",
    "sauvegarde1.txt",
    "sauvegarde2.txt",
    "sauvegarde3.txt"
};

unsigned int PreparerSauvegarde(unsigned char id) {
    if (fichier_existe(fichiers_sauvegardes[id])) {
        return (fichier_longueur(fichiers_sauvegardes[id])+2047)/2048;
    }
    return 0;
}

bool ChargerSauvegarde(unsigned char id, unsigned int taille, char* buffer) {
    if (taille) {
        fichier_lire(fichiers_sauvegardes[id], buffer);
        return true;
    }
    return false;
}

// #ifdef EXPORTOUT
unsigned int fichier_ecrire(const char* nom, int n) {
    // FILE* fp = fopen(nom, "w");
    FILE* fp = fopen(nom, "wb");
    if (fp == NULL)
        return 0;

    unsigned int longueur = fprintf(fp, "%d", n);
    fclose(fp);
    return longueur;
}

unsigned int fichier_ajouter(const char* nom, const char* buffer) {
    // FILE* fp = fopen(nom, "a");
    FILE* fp = fopen(nom, "ab");
    if (fp == NULL)
        return 0;

    unsigned int longueur = fputs(buffer, fp);
    fclose(fp);
    return longueur;
}

unsigned int fichier_ajouter(const char* nom, int n) {
    // FILE* fp = fopen(nom, "a");
    FILE* fp = fopen(nom, "ab");
    if (fp == NULL)
        return 0;

    unsigned int longueur = fprintf(fp, "%d", n);
    fclose(fp);
    return longueur;
}

unsigned int fichier_ecrireb(const char* nom, const char n) {
    FILE* fp = fopen(nom, "wb");
    if (fp == NULL)
        return 0;

    char c = fputc(n, fp);
    fclose(fp);
    return n == c;
}

/*unsigned int fichier_ecrireb(const char* nom, const char* buffer, const char* fin) {
    FILE* fp = fopen(nom, "wb");
    if (fp == NULL)
        return 0;

    unsigned int longueur = fwrite(buffer, sizeof(char), (size_t)(fin-buffer), fp);
    fclose(fp);
    return longueur;
}*/

unsigned int fichier_ajouterb(const char* nom, const char* buffer, const char* fin) {
    FILE* fp = fopen(nom, "ab");
    if (fp == NULL)
        return 0;

    unsigned int longueur = fwrite(buffer, sizeof(char), (size_t)(fin-buffer), fp);
    fclose(fp);
    return longueur;
}
// #endif //EXPORTOUT

/* int main() {
   FILE * pFile;
   char buffer [100];

   pFile = fopen ("myfile.txt" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     while (! feof (pFile)) {
       if (fgets (buffer , 100 , pFile) == NULL) break;
       fputs (buffer , stdout);
     }
     fclose (pFile);
   }
   return 0;
} */