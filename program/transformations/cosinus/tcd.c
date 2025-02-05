#include "tcd.h"

void ecrit_coeffs_tcd(){
    FILE * fcoeff;
    double coeff;

    fcoeff = fopen(tcd_chemin, "w");
    if(fcoeff == NULL)return;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            if(i == 0) coeff = 1.0;
            else coeff = sqrt(2.0)*cos((2*j+1)*M_PI*i/(2.0*(double)TAILLE_BLOC));

            coeff *= 1.0/sqrt(TAILLE_BLOC);
            fprintf(fcoeff, "%lf ", coeff);
        }
        fprintf(fcoeff, "\n");
    }
    fclose(fcoeff);
}

void lit_coeffs_tcd(double complex** coeffs){
    FILE * fcoeff;
    double reel;

    ecrit_coeffs_tcd();

    fcoeff = fopen(tcd_chemin, "r");
    if(fcoeff == NULL)return;

    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            fscanf(fcoeff, "%lf ", &reel);
            coeffs[i][j] = reel;
        }
        fscanf(fcoeff, "\n");
    }
    fclose(fcoeff);    
}

void init_tcd_coeffs(){
    tcd_coeffs = initialise_bloc();
    tcd_t_coeffs = initialise_bloc();

    lit_coeffs_tcd(tcd_coeffs);

    transposee(tcd_coeffs, tcd_t_coeffs);
}

void libere_tcd_coeffs(){
    libere_bloc(tcd_coeffs);
    libere_bloc(tcd_t_coeffs);
}

void tcd_bloc(double complex** source, double complex** resultat, void* arg){
    //Algo semi-naif : produit matriciel avec séparation
    produit_matriciel(source, tcd_t_coeffs, temp);
    produit_matriciel(tcd_coeffs, temp, resultat);
}

image tcd_image(image source){
    return map_blocs(tcd_bloc, NULL, source);
}