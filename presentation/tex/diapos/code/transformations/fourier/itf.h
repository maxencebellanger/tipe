#define _ITF_H_
#ifdef _ITF_H_

#include "../../gestion_image/traitement/quantification.h"

#define itf_chemin "transformations/fourier/itf_coeffs"

static double complex** itf_coeffs;
static double complex** itf_t_coeffs;

void init_itf_coeffs();

void libere_itf_coeffs();

//réalise une itf sur un bloc
//Complexité O(TAILLE_BLOC^3) : Algorithme avec produit matriciel et séparabilité
void itf_bloc(double complex** source, double complex** resultat, void* arg);

//réalise l'inverse de la tf sur une image entière (on suppose que les dimensions de l'image sont multiple de TAILLE_BLOC)
image itf_image(image source);

#endif