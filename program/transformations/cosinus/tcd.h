#define _TCD_H_
#ifdef _TCD_H_

#include "../calcul_matriciel/calcul_matriciel.h"

#define tcd_chemin "transformations/cosinus/tcd_coeffs"

static double complex** tcd_coeffs;
static double complex** tcd_t_coeffs;

void init_tcd_coeffs();

void libere_tcd_coeffs();

//réalise une tcd sur un bloc
//Complexité O(TAILLE_BLOC^3) : Algorithme avec produit matriciel et séparabilité
void tcd_bloc(double complex** source, double complex** resultat, void* arg);

//réalise une dct sur une image entière (on suppose que les dimensions de l'image sont multiple de TAILLE_BLOC)
image tcd_image(image source);

#endif