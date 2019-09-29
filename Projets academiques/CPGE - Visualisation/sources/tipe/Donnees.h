#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <gsl/gsl_blas.h>

typedef struct Donnees Donnees;

struct Donnees
{
    int d; //dimension
    int n; //nombre de points
    double* T; //coordonnées des points
    int a; //nombre d'hyper-arêtes
    double** H; //hyper-arêtes
};

void proj(int d, double* u, double* v, double* p);
void genunit(int d, gsl_vector* u);
void proj(int d, gsl_vector* u, gsl_vector* v, gsl_vector* p);
double* genbase(int d, int k);

double distances(Donnees* entree, Donnees* sortie);
double surfaces(Donnees* entree, Donnees* sortie);
double volumes(Donnees* entree, Donnees* sortie);

double fusion(Donnees* entree, Donnees* sortie);

double distances_aretes(Donnees* entree, Donnees* sortie);
double surfaces_aretes(Donnees* entree, Donnees* sortie);
double volumes_aretes(Donnees* entree, Donnees* sortie);

double* GetPoint(Donnees* entree, int i);
double* GetPoint(double* T, int d, int i);
void SetPoint(Donnees* entree, int i, double* p);
void SetPoint(double* T, int d, int i, double* p);
double* Copie(double* T, int d, int n);
double* Copie(double* p, int d);
double* Tronquer(double* T, int d, int k, int n);

double degres2rad(int val);
double* normer(int dimension, double* p);
double angle(int d, double* p, double* q);

double* vecteur_nul(int d);

double* somme_vect(int d, double* p, double* q);
double* produit_externe_vect(int d, double* p, double a);
//double* produit_interne_vect(int d, double* p, double* q);
double produit_scalaire_vect(int d, double* p, double* q);
double norme_vect(int d, double* p);
double distance_vect(int d, double* p, double* q);

#endif // DONNEES_H_INCLUDED
