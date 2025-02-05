#include "calcul_matriciel.h"

//produit matriciel naif
void produit_matriciel(double complex** A, double complex** B, double complex** resultat){
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            resultat[i][j] = 0.0;
            for(int k = 0; k < TAILLE_BLOC; k++){
                resultat[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}

void transposee(double complex** A, double complex** resultat){
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            resultat[i][j] = A[j][i];
        }
    }
}

void multiplication_scalaire(double complex a, double complex** A, double complex** resultat){
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            resultat[i][j] = a*A[i][j];
        }
    }
}