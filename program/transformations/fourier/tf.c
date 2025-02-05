#include "tf.h"

void ecrit_coeffs_tf(){
    FILE * fcoeff;
    double complex coeff;
    
    fcoeff = fopen(tf_chemin, "w");
    if(fcoeff == NULL)return;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            coeff = cexp(-2i*M_PI*i*j/TAILLE_BLOC)/sqrt((double)TAILLE_BLOC);
            fprintf(fcoeff, "%lf+i%lf ", creal(coeff), cimag(coeff));
        }
        fprintf(fcoeff, "\n");
    }
    fclose(fcoeff);
}

void lit_coeffs_tf(double complex** coeffs){
    FILE * fcoeff;
    double real, imag;

    ecrit_coeffs_tf();

    fcoeff = fopen(tf_chemin, "r");
    if(fcoeff == NULL)return;

    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            fscanf(fcoeff, "%lf+i%lf ", &real, &imag);
            coeffs[i][j] = real + 1i*imag;
        }
        fscanf(fcoeff, "\n");
    }
    fclose(fcoeff);
}

void init_tf_coeffs(){
    tf_coeffs = initialise_bloc();
    tf_t_coeffs = initialise_bloc();

    lit_coeffs_tf(tf_coeffs);

    transposee(tf_coeffs, tf_t_coeffs);
}

void libere_tf_coeffs(){
    libere_bloc(tf_coeffs);
    libere_bloc(tf_t_coeffs);
}

//réalise une tf sur source et ecris le résultat dans sortie (un bloc seulement)
void tf_bloc(double complex** source, double complex** resultat, void* arg){
    //Algo semi-naif : produit matriciel avec séparation
    produit_matriciel(source, tf_t_coeffs, temp);
    produit_matriciel(tf_coeffs, temp, resultat);
}

image tf_image(image source){
    return map_blocs(tf_bloc, NULL, source);
}