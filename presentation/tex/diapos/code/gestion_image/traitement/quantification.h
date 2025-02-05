#ifndef _QUANTIFICATION_H_
#define _QUANTIFICATION_H_

#include "../../transformations/calcul_matriciel/calcul_matriciel.h"


void sous_echantillonnage_bloc(double complex** source, double complex** resultat, void* arg);

//renvoie une image dont on ne conserve que les coefficients dont le module et au dessus de seuil
image selection_seuil(image source, double seuil);

void selection_seuil_bloc(double complex** source, double complex** resultat, void* arg);

//renvoie une image dont on ne conserve que les coefficients dans une zone taille*taille dans chaque bloc
//on suppose taille < TAILLE_BLOC
image selection_zone(image source, int taille);

void selection_zone_bloc(double complex** source, double complex** resultat, void* arg);

//réalise un seuillage (en place) sur le bloc pour que les valeurs n'éxcèdent pas 255
//necessaire pour les méthodes de compression avec les matrices de quantification
void seuillage_bloc(double complex** source);

//On diminue le poids des coefficiants grâce à une matrice de quantification
image quantification_matrice(image source, double complex** Q);

void quantification_bloc(double complex** source, double complex** resultat, void* arg);

//réalise une quantification inverse pour pouvoir décompresser
image dequantification_matrice(image source, double complex** Q);

void dequantification_bloc(double complex** source, double complex** resultat, void* arg);

#endif