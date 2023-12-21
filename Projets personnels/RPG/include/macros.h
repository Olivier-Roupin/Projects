#ifndef MACROS_H
#define MACROS_H

#ifdef PRINTIN
#define TAILLE_DATA 64
#endif //PRINTIN

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define AVANT(i,n) ((i) + (n) - 1) % (n)
#define APRES(i,n) ((i) + 1) % (n)

//n charatères suivis d'un '\0'
#define LIRE_CHAINE(i,j,d,o,n)\
while ((d)[i]!='\0' && (d)[i]!=' ' && (d)[i]!='\n' && (j)<(n))\
{ (o)[j] = (d)[i]; (i)++; (j)++;}\
(o)[j] = '\0'; (i)++;

//n charatères suivis d'un '\0'
#define LIRE_CHAINE_(i,d,o,n)\
while ((d)[i]!='\0' && (d)[i]!=' ' && (d)[i]!='\n' && (i)<(n))\
{ (o)[i] = (d)[i]; (i)++; }\
(o)[i] = '\0'; (i)++;

//entier positif
#define LIRE_ENTIER(i,d,o)\
(o) = 0;\
while ((d)[i]>='0' && (d)[i]<='9') (o) = 10*(o) + (int)((d)[(i)++] - '0');\
(i)++;

//un charactère suivi d'un séparateur
#define LIRE_CHIFFRE(i,d,o)\
(o) = (d)[i] - '0';\
(i)+=2;

//deux caractères suivis d'un séparateur
#define LIRE_2CHIFFRES(i,d,o)\
(o) = (d)[(i)++] - '0';\
if ((d)[i]>='0' && (d)[i]<='9') (o) = 10*(o) + (int)((d)[i] - '0');\
(i)+=2;

//trois caractères suivis d'un séparateur
#define LIRE_3CHIFFRES(i,d,o)\
(o) = (d)[(i)++] - '0';\
if ((d)[i]>='0' && (d)[i]<='9') (o) = 10*(o) + (int)((d)[(i)++] - '0');\
if ((d)[i]>='0' && (d)[i]<='9') (o) = 10*(o) + (int)((d)[i] - '0');\
(i)+=2;

//un charactère suivi d'un séparateur
#define LIRE_BOOLEEN(i,d,o)\
(o) = (d)[i] != '0';\
(i)+=2;

// 33=='!' 126=='~'
#define LIRE_SUIVANT(i,d)\
while ((d)[i]<33 || (d)[i]>126) i++;

#define ECRIRE_CHAINE(i,j,d,o,n)\
for ((j) = 0; (j) < (n); (i)++, (j)++) {\
    if ((o)[j] == '\0') break;\
    (d)[i] = (o)[j];\
}

#define ECRIRE_BOOLEEN(i,d,o)\
(d)[(i)++] = '0'+(char)(o);

#define ECRIRE_CHIFFRE(i,d,o)\
(d)[(i)++] = '0'+((o)%10);

#define ECRIRE_2CHIFFRES(i,d,o)\
if ((o) > 9) (d)[(i)++] = '0'+((o)%100-(o)%10)/10;\
(d)[(i)++] = '0'+((o)%10);

#define ECRIRE_3CHIFFRES(i,d,o)\
if ((o) > 99) (d)[(i)++] = '0'+((o)-(o)%100)/100;\
if ((o) > 9)  (d)[(i)++] = '0'+((o)%100-(o)%10)/10;\
(d)[(i)++] = '0'+((o)%10);

#endif // MACROS_H
