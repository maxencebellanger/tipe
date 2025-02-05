#define _CONTROLE_H_
#ifdef _CONTROLE_H_

#include "traitement.h"

//renvoie la distance algébrique entre im1 et im2
//on suppose que im1 et im2 sont de meme taille
double distance(image im1, image im2);

double EQM(image im1, image im2);

//renvoie la distance entres les images telles qu'elles sont enregistrees
int distance_percue(image im1, image im2);

void affiche_module(image img);

void affiche(image img);

//NE FERME PAS LE FICHIER
void faffiche_plan(FILE* file, double complex* plan, int haut, int larg);

//NE FERME PAS LE FICHIER
void faffiche_module(FILE* file, image img);

//NE FERME PAS LE FICHIER
void faffiche(FILE* file, image img);



#endif