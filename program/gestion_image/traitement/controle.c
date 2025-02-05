#include "controle.h"

double distance(image im1, image im2){
    int haut = im1.hauteur, larg = im1.largeur;
    double resultat = 0.0;
    double dx, dy, dz;

    for(int i = 0; i < haut; i++){
        for(int j = 0; j < larg; j++){
            dx = (creal(im1.x[i*larg + j]) - creal(im2.x[i*larg + j])) * (creal(im1.x[i*larg + j]) - creal(im2.x[i*larg + j]));
            dx += (cimag(im1.x[i*larg + j]) - cimag(im2.x[i*larg + j])) * (cimag(im1.x[i*larg + j]) - cimag(im2.x[i*larg + j]));

            dy = (creal(im1.y[i*larg + j]) - creal(im2.y[i*larg + j])) * (creal(im1.y[i*larg + j]) - creal(im2.y[i*larg + j]));
            dy += (cimag(im1.y[i*larg + j]) - cimag(im2.y[i*larg + j])) * (cimag(im1.y[i*larg + j]) - cimag(im2.y[i*larg + j]));

            dz = (creal(im1.z[i*larg + j]) - creal(im2.z[i*larg + j])) * (creal(im1.z[i*larg + j]) - creal(im2.z[i*larg + j]));
            dz += (cimag(im1.z[i*larg + j]) - cimag(im2.z[i*larg + j])) * (cimag(im1.z[i*larg + j]) - cimag(im2.z[i*larg + j]));

            resultat += dx + dy + dz;
        }
    }

    return resultat;
}

double EQM(image im1, image im2){
    return distance(im1, im2)/(double)(im1.hauteur*im1.largeur);
}

int distance_percue(image im1, image im2){
    int haut = im1.hauteur, larg = im1.largeur;
    int resultat = 0;
    int dx, dy, dz;

    for(int i = 0; i < larg; i++){
        for(int j = 0; j < haut; j++){
            dx = (int)cabs(im1.x[i*larg + j]) - (int)cabs(im2.x[i*larg + j]);
            dy = (int)cabs(im1.y[i*larg + j]) - (int)cabs(im2.y[i*larg + j]);
            dz = (int)cabs(im1.z[i*larg + j]) - (int)cabs(im2.z[i*larg + j]);
            resultat += dx + dy + dz;
        }
    }

    return resultat;
}

void affiche(image img){
    //affiche bloc par bloc
    int k = 0, l = 0;
    for(int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            printf("(%.1f + i%.1f, %.1f + i%.1f, %.1f + i%.1f) ", creal(img.x[i*img.largeur+j]), cimag(img.x[i*img.largeur+j]), creal(img.y[i*img.largeur+j]), cimag(img.y[i*img.largeur+j]), creal(img.z[i*img.largeur+j]), cimag(img.z[i*img.largeur+j]));
            k++;
            if(k == 8){
                printf("\n");
                k = 0;
                l++;
            }
            if(l == 8){
                printf("\n");
                l = 0;
            }
        }
    }  
}

void faffiche(FILE* file, image img){
    //affiche bloc par bloc
    int k = 0, l = 0;
    for(int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            fprintf(file, "(%.1f + i%.1f, %.1f + i%1.f, %.1f + i%.1f) ", creal(img.x[i*img.largeur+j]), cimag(img.x[i*img.largeur+j]), creal(img.y[i*img.largeur+j]), cimag(img.y[i*img.largeur+j]), creal(img.z[i*img.largeur+j]), cimag(img.z[i*img.largeur+j]));
            k++;
            if(k == 8){
                fprintf(file, "\n");
                k = 0;
                l++;
            }
            if(l == 8){
                fprintf(file, "\n");
                l = 0;
            }
        }
    }  
}

void faffiche_plan(FILE* file, double complex* plan, int haut, int larg){
    //affiche bloc par bloc
    int k = 0, l = 0;
    for(int i = 0; i < haut; i++){
        for(int j = 0; j < larg; j++){
            fprintf(file, "%.0f + %.0fi & ", creal(plan[i*larg+j]), cimag(plan[i*larg+j]));
            k++;
            if(k == 8){
                fprintf(file, "\\\\ \n");
                k = 0;
                l++;
            }
            if(l == 8){
                fprintf(file, "\n");
                l = 0;
            }
        }
    }  
}

void faffiche_module(FILE* file, image img){
     //affiche bloc par bloc
    int k = 0, l = 0;
    for(int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            fprintf(file, "(%.1f, %.1f, %.1f) ", cabs(img.x[i*img.largeur+j]), cabs(img.y[i*img.largeur+j]), cabs(img.z[i*img.largeur+j]));
            k++;
            if(k == 8){
                fprintf(file, "\n");
                k = 0;
                l++;
            }
            if(l == 8){
                fprintf(file, "\n");
                l = 0;
            }
        }
    }
}

void affiche_module(image img){
    //affiche bloc par bloc
    int k = 0, l = 0;
    for(int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            printf("(%.1f, %.1f, %.1f) ", cabs(img.x[i*img.largeur+j]), cabs(img.y[i*img.largeur+j]), cabs(img.z[i*img.largeur+j]));
            k++;
            if(k == 8){
                printf("\n");
                k = 0;
                l++;
            }
            if(l == 8){
                printf("\n");
                l = 0;
            }
        }
    }
}