#include "itf.h"

void ecrit_coeffs_itf(){
    FILE * fcoeff;
    double complex coeff;
    
    fcoeff = fopen(itf_chemin, "w");
    if(fcoeff == NULL)return;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            coeff = cexp(2i*M_PI*i*j/TAILLE_BLOC)/sqrt((double)TAILLE_BLOC);
            fprintf(fcoeff, "%lf+i%lf ", creal(coeff), cimag(coeff));
        }
        fprintf(fcoeff,"\n");
    }
    fclose(fcoeff);
}

void lit_coeffs_itf(double complex** coeffs){
    FILE * fcoeff;
    double real, imag;
    int taille;

    ecrit_coeffs_itf();

    fcoeff = fopen(itf_chemin, "r");
    if(fcoeff == NULL)return;

    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            fscanf(fcoeff, "%lf+i%lf ", &real, &imag);
            coeffs[i][j] = real + 1i*imag;
        }
        fscanf(fcoeff,"\n");
    }
    fclose(fcoeff);
}

void init_itf_coeffs(){
    itf_coeffs = initialise_bloc();
    itf_t_coeffs = initialise_bloc();

    lit_coeffs_itf(itf_coeffs);

    transposee(itf_coeffs, itf_t_coeffs);
}

void libere_itf_coeffs(){
    libere_bloc(itf_coeffs);
    libere_bloc(itf_t_coeffs);
}

//réalise l'inverse de la tf sur source et ecris le résultat dans sortie (un bloc seulement)
void itf_bloc(double complex** source, double complex** resultat, void* arg){
    //Algo semi-naif : produit matriciel avec séparation
    produit_matriciel(source, itf_t_coeffs, temp);
    produit_matriciel(itf_coeffs, temp, resultat);
    seuillage_bloc(resultat);
}

image itf_image(image source){
    return map_blocs(itf_bloc, NULL, source);
}