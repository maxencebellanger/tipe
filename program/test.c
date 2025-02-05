#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>

void affiche_tab(double complex** t, int taille){
    for(int i = 0; i < taille; i++){
        for(int j = 0; j < taille; j++){
            printf("(%.0f + i%.0f)", creal(t[i][j]), cimag(t[i][j]));
        }
        printf("\n");
    }
}

double complex** initialise_bloc(){
    double complex** bloc = (double complex**)malloc(8*sizeof(double complex*));
    for(int i = 0; i < 8; i++)bloc[i] = calloc(8, sizeof(double complex));

    return bloc;
}

double complex** matrice_de_quantification(){
    double complex** Q = initialise_bloc();
    double coeff;

    FILE* fq = fopen("gestion_image/traitement/matrice_Q.config", "r");
    

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            fscanf(fq, "%lf ", &coeff);
            Q[i][j] = coeff + 0i;
        }
        fscanf(fq, "\n");
    }

    fclose(fq);
    return Q;
}

void sous_echantillonnage_bloc(double complex** source, double complex** resultat, void* arg){
    double complex moyenne;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8 - 1; j+=2){
            moyenne = (source[i][j] + source[i][j+1]) / 2.0;
            resultat[i][j] = moyenne;
            resultat[i][j+1] = moyenne; 
        }
    }
}

int main(void){
    double complex** Q = matrice_de_quantification();

    double complex** Q_moyenne = initialise_bloc();
    sous_echantillonnage_bloc(Q, Q_moyenne, NULL);  

    affiche_tab(Q, 8);
    printf("\n\n");
    affiche_tab(Q_moyenne, 8);
}



