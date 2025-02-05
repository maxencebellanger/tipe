#ifndef _CALCUL_MATRICIEL_H_
#define _CALCUL_MATRICIEL_H_

#include "../../gestion_image/traitement/traitement.h"

//Opérations uniquement pour des blocs (donc des matrices de dimension TAILLE_BLOC)

//On suppose que A et B sont de même dimension
void produit_matriciel(double complex** A, double complex** B, double complex** resultat);

void transposee(double complex** A, double complex** resultat);

void multiplication_scalaire(double complex a, double complex** A, double complex** resultat);

#endif