#ifndef FICHIERES_H
#define FICHIERES_H

#define NOMBRE_BDDS 11
#define BDD_EFFETS       0
#define BDD_OBJETS       1
#define BDD_MAGASINS     2
#define BDD_HEROS        3
#define BDD_MONSTRES     4
#define BDD_GROUPES      5
#define BDD_TILESETS     6
#define BDD_EVENEMENTS   7
#define BDD_CARTES       8
#define BDD_CAPACITES    9
#define BDD_ALTERATIONS 10

#define NOMBRE_SAUVEGARDES 4 //dupliqué

#ifdef PRINTIN
const char* NomBDD(unsigned char bdd);
#endif //PRINTIN
unsigned int PreparerBDD(unsigned char bdd);
bool ChargerBDD(unsigned char bdd, unsigned int taille, char* buffer);

unsigned int PreparerSauvegarde(unsigned char id);
bool ChargerSauvegarde(unsigned char id, unsigned int taille, char* buffer);

// #define EXPORTOUT //enregistre les bdds en sortie

bool         fichier_existe( const char* nom);
// unsigned int fichier_lire(   const char* nom, char* buffer);
unsigned int fichier_ecrire( const char* nom, const char* buffer);
#ifdef EXPORTOUT
unsigned int fichier_ecrire( const char* nom, int n);
unsigned int fichier_ajouter(const char* nom, const char* buffer);
// unsigned int fichier_ajouter(const char* nom, int n);

unsigned int fichier_ecrireb( const char* nom, const char n);
// unsigned int fichier_ecrireb( const char* nom, const char* buffer, const char* fin);
unsigned int fichier_ajouterb(const char* nom, const char* buffer, const char* fin);

unsigned int PreparerASCII(unsigned char bdd);
bool ChargerASCII(unsigned char bdd, unsigned int taille, char* buffer);
#endif //EXPORTOUT

#endif // FICHIERES_H
