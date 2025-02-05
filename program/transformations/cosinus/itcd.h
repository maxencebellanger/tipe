#define _ITCD_H_
#ifdef _ITCD_H_

#include "../../gestion_image/traitement/quantification.h"

#define itcd_chemin "transformations/cosinus/itcd_coeffs"

static double complex** itcd_coeffs;
static double complex** itcd_t_coeffs;

void init_itcd_coeffs();

void libere_itcd_coeffs();

//réalise une itcd sur un bloc
//Complexité O(TAILLE_BLOC^3) : Algorithme avec produit matriciel et séparabilité
void itcd_bloc(double complex** source, double complex** resultat, void* arg);

//réalise une dct sur une image entière (on suppose que les dimensions de l'image sont multiple de TAILLE_BLOC)
image itcd_image(image source);

#endif