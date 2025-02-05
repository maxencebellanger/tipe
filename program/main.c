#include "gestion_image/image.h"
#include "gestion_image/traitement/traitement.h"
#include "gestion_image/traitement/controle.h"
#include "gestion_image/traitement/quantification.h"
#include "transformations/fourier/tf.h"
#include "transformations/fourier/itf.h"
#include "transformations/cosinus/tcd.h"
#include "transformations/cosinus/itcd.h"

#include "test/test.h"

#include <time.h>

//initialise toutes les constantes
void init(){
    //Initialisation des matrices des transformées
    init_tf_coeffs();
    init_itf_coeffs();
    init_tcd_coeffs();
    init_itcd_coeffs();

    temp = initialise_bloc();
}

//libere toutes les constantes
void libere(){
    libere_bloc(temp);
    libere_tf_coeffs();
    libere_itf_coeffs();
    libere_tcd_coeffs();
    libere_itcd_coeffs();
}

double complex** matrice_de_quantification(){
    double complex** Q = initialise_bloc();
    double coeff;

    FILE* fq = fopen("gestion_image/traitement/matrice_Q.config", "r");
    

    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            fscanf(fq, "%lf ", &coeff);
            Q[i][j] = coeff + 0i;
        }
        fscanf(fq, "\n");
    }

    fclose(fq);

    return Q;
}

int main(int argc, char** argv){    
    clock_t t1, t2;
    t1 = clock();

    if(argc != 2){
        fprintf(stderr, "Tappez : './a.out \"nom_image\"' (sans le .ppm) pour tester votre image !\n");
        return 1;
    }

    init();
    double complex** Q = matrice_de_quantification();

    test_compression(argv[1], Q);

    libere_bloc(Q);
    libere();

    t2 = clock();
    printf("Durée d'exécution %lds\n", (t2 - t1)/CLOCKS_PER_SEC);
    
    return 0;
}