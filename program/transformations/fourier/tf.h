#define _TF_H_
#ifdef _TF_H_

#include "../calcul_matriciel/calcul_matriciel.h"

#define tf_chemin "transformations/fourier/tf_coeffs"

static double complex** tf_coeffs;
static double complex** tf_t_coeffs;

void init_tf_coeffs();

void libere_tf_coeffs();

//réalise une tcd sur un bloc
//Complexité O(TAILLE_BLOC^3) : Algorithme avec produit matriciel et séparabilité
void tf_bloc(double complex** source, double complex** resultat, void* arg);

//réalise une tf sur une image entière (on suppose que les dimensions de l'image sont multiple de TAILLE_BLOC)
image tf_image(image source);

#endif