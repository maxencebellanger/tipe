#include "itcd.h"

void ecrit_coeffs_itcd(){
    FILE * fcoeff;
    double coeff;

    fcoeff = fopen(itcd_chemin, "w");
    if(fcoeff == NULL)return;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            if(j == 0) coeff = 1.0;
            else coeff = sqrt(2.0)*cos((2*i+1)*M_PI*j/(2.0*(double)TAILLE_BLOC));

            coeff *= sqrt(1.0/TAILLE_BLOC);
            fprintf(fcoeff, "%lf ", coeff);
        }
        fprintf(fcoeff, "\n");
    }
    fclose(fcoeff);
}

void lit_coeffs_itcd(double complex** coeffs){
    FILE * fcoeff;
    double reel;

    ecrit_coeffs_itcd();

    fcoeff = fopen(itcd_chemin, "r");
    if(fcoeff == NULL)return;

    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            fscanf(fcoeff, "%lf ", &reel);
            coeffs[i][j] = reel + 0i;
        }
        fscanf(fcoeff, "\n");
    }
    fclose(fcoeff);    
}

void init_itcd_coeffs(){
    itcd_coeffs = initialise_bloc();
    itcd_t_coeffs = initialise_bloc();

    lit_coeffs_itcd(itcd_coeffs);

    transposee(itcd_coeffs, itcd_t_coeffs);
}

void libere_itcd_coeffs(){
    libere_bloc(itcd_coeffs);
    libere_bloc(itcd_t_coeffs);
}

void itcd_bloc(double complex** source, double complex** resultat, void* arg){
    //Algo semi-naif : produit matriciel avec séparation
    produit_matriciel(source, itcd_t_coeffs, temp);
    produit_matriciel(itcd_coeffs, temp, resultat);
    seuillage_bloc(resultat);
}

image itcd_image(image source){
    return map_blocs(itcd_bloc, NULL, source);
}