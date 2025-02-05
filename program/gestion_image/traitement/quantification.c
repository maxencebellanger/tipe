#include "quantification.h"

void sous_echantillonnage_bloc(double complex** source, double complex** resultat, void* arg){
    double complex moyenne;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC - 1; j+=2){
            moyenne = (source[i][j] + source[i][j+1]) / 2.0;
            resultat[i][j] = moyenne;
            resultat[i][j+1] = moyenne; 
        }
    }
}

void selection_seuil_bloc(double complex** source, double complex** resultat, void* arg){
    double seuil = (*(double*)arg)*source[0][0]; //On prend seuil*la moyenne du bloc

    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            if(cabs(source[i][j]) >= seuil){
                resultat[i][j] = source[i][j];
            }else{
                resultat[i][j] = 0.0;
            }
        }
    }
}

void selection_zone_bloc(double complex** source, double complex** resultat, void* arg){
    int taille = *(int*)arg;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            if(i < taille && j < taille){
                resultat[i][j] = source[i][j];
            }else{
                resultat[i][j] = 0.0;
            }
        }
    }
}

void seuillage_bloc(double complex** source){
    double max = 0; //on calcul le module max du bloc
    double module = 0;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            module = cabs(source[i][j]);
            max = (module > max)?module : max;
        }
    }
    //on ajuste si le max est trop grand
    module = (max > 255) ? 255.0/max : 1.0;
    multiplication_scalaire(module + 0i, source, source);
}

void quantification_bloc(double complex** source, double complex** resultat, void* arg){
    double complex** Q = (double complex**)arg;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            //printf("%f ", cabs(Q[i][j]));
            resultat[i][j] = floor(creal(source[i][j]/Q[i][j]));
        }
    }
}

void dequantification_bloc(double complex** source, double complex** resultat, void* arg){
    double complex** Q = (double complex**)arg;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            resultat[i][j] = source[i][j] * Q[i][j];
        }
    }
}

image quantification_matrice(image source, double complex** Q){
    return map_blocs(quantification_bloc, Q, source);
}

image dequantification_matrice(image source, double complex** Q){
    return map_blocs(dequantification_bloc, Q, source);
}


image selection_seuil(image source, double seuil){
    return map_blocs(selection_seuil_bloc, &seuil, source);
}

image selection_zone(image source, int taille){
    return map_blocs(selection_zone_bloc, &taille, source);
}