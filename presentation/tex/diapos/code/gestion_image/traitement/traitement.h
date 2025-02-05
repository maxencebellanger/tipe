#define _TRAITEMENT_H_
#ifdef _TRAITEMENT_H_

#include "../image.h"

extern double complex** temp;

double complex** initialise_bloc();

void libere_bloc(double complex** bloc);

void copie_bloc(double complex** source, double complex** resultat, void* arg);

void multiplie_bloc(double complex** source, double complex** resultat, void* arg);

//applique f sur tout les blocs de source et stock dans résultat.
//On suppose que source est le plan d'une image avec hauteur et largeur la taille de l'image
void map_bloc_plan(void (*f)(double complex** source, double complex** resultat, void* arg), void* arg, double complex* source, int haut , int larg, double complex* resultat);

//applique f sur tout les blocs de l'image (et renvoie la nouvelle image)
//arg est l'argument de f si il existe
image map_blocs(void (*f)(double complex** source, double complex** resultat, void* arg), void* arg, image source);

#endif