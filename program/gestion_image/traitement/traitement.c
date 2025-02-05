#include "traitement.h"

#include <stdlib.h>

double complex** temp;

void copie_bloc(double complex** source, double complex** resultat, void* arg){
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            resultat[i][j] = source[i][j];
        }
    }
}

void multiplie_bloc(double complex** source, double complex** resultat, void* arg){
    double complex scalaire = *(double complex*)arg;
    for(int i = 0; i < TAILLE_BLOC; i++){
        for(int j = 0; j < TAILLE_BLOC; j++){
            resultat[i][j] = scalaire*source[i][j];
        }
    }
}


double complex** initialise_bloc(){
    double complex ** bloc = (double complex**)malloc(TAILLE_BLOC*sizeof(double complex*));
    for(int i = 0; i < TAILLE_BLOC; i++){
        bloc[i] = calloc(TAILLE_BLOC, sizeof(double complex));
    }   
    return bloc;
}

void libere_bloc(double complex** bloc){
    for(int i = 0; i < TAILLE_BLOC; i++){
        free(bloc[i]);
    }
    free(bloc);
}


void map_bloc_plan(void (*f)(double complex** source, double complex** resultat, void* arg), void* arg, double complex* source, int haut , int larg, double complex* resultat){
    //Un bloc est tel que à l'indice k on a un pointeur vers la kieme ligne
    double complex** bcs = (double complex**)malloc(TAILLE_BLOC*sizeof(double complex*)); //bloc courrant source 
    double complex** bcr = (double complex**)malloc(TAILLE_BLOC*sizeof(double complex*)); //bloc courrant resultat
    
    for(int i = 0; i < haut; i+=TAILLE_BLOC){
            //On avance de bloc en bloc
        for(int j = 0; j < larg; j+=TAILLE_BLOC){
            //On fixe les adresses des blocs
            for(int k = 0; k < TAILLE_BLOC; k++){
                bcs[k] = &source[(i+k) * larg + j];
                bcr[k] = &resultat[(i+k) * larg + j];
            }
            f(bcs, bcr, arg); //on applique f
        }
    }

    free(bcr);
    free(bcs);
}

image map_blocs(void (*f)(double complex** source, double complex** resultat, void* arg), void* arg, image source){
    int haut = source.hauteur, larg = source.largeur; 

    image resultat = image_vierge(haut, larg);

    map_bloc_plan(f, arg, source.x, haut, larg, resultat.x);
    map_bloc_plan(f, arg, source.y, haut, larg, resultat.y);
    map_bloc_plan(f, arg, source.z, haut, larg, resultat.z);

    return resultat;
}