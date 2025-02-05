#include "image.h"

double min(double a, double b){
    return (a < b) ? a : b;
}

image fichier_vers_image(char* chemin){
    image img;
    uint8_t couleur;
    FILE *img_file = fopen(chemin, "r");
    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return img;
    }
    fscanf(img_file, "P6\n%d %d\n255\n", &img.largeur, &img.hauteur);

    img.x = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    img.y = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    img.z = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));

    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            fscanf(img_file, "%c", &couleur);
            img.x[i*img.largeur + j] = (double complex)couleur;
            
            fscanf(img_file, "%c", &couleur);
            img.y[i*img.largeur + j] = (double complex)couleur;

            fscanf(img_file, "%c", &couleur);
            img.z[i*img.largeur + j] = (double complex)couleur;
        }
    }

    fclose(img_file);

    return img;
}

image fichier_compresse_vers_image(char* chemin){
    image img;
    int real, imag;
    FILE *img_file = fopen(chemin, "r");
    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return img;
    }
    fscanf(img_file, "P6\n%d %d\n255\n", &img.largeur, &img.hauteur);

    img.x = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    img.y = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    img.z = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));

    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            fscanf(img_file, "%d %d ", &real, &imag);
            img.x[i*img.largeur + j] = (double)real + 1i*(double)imag;
            
            fscanf(img_file, "%d %d ", &real, &imag);
            img.y[i*img.largeur + j] = (double)real + 1i*(double)imag;

            fscanf(img_file, "%d %d ", &real, &imag);
            img.z[i*img.largeur + j] = (double)real + 1i*(double)imag;

        }
    }

    fclose(img_file);

    return img;
}

image fichier_compresse_reel_vers_image(char* chemin){
    image img;
    int real;
    FILE *img_file = fopen(chemin, "r");
    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return img;
    }
    fscanf(img_file, "P6\n%d %d\n255\n", &img.largeur, &img.hauteur);

    img.x = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    img.y = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    img.z = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));

    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            fscanf(img_file, "%d " , &real);
            img.x[i*img.largeur + j] = (double)real + 0i;
            
            fscanf(img_file, "%d ", &real);
            img.y[i*img.largeur + j] = (double)real + 0i;

            fscanf(img_file, "%d ", &real);
            img.z[i*img.largeur + j] = (double)real + 0i;

        }
    }

    fclose(img_file);

    return img;
}

void image_vers_fichier(char* chemin, image img){
    FILE *img_file = fopen(chemin, "w");
    uint8_t x,y,z;

    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return;
    }

    fprintf(img_file, "P6\n%d %d\n255\n", img.largeur, img.hauteur);

    
    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            x = (uint8_t)cabs(img.x[i*img.largeur + j]);
            y = (uint8_t)cabs(img.y[i*img.largeur + j]);
            z = (uint8_t)cabs(img.z[i*img.largeur + j]);

            fprintf(img_file, "%c", x);
            fprintf(img_file, "%c", y);
            fprintf(img_file, "%c", z);
        }
    }

    fclose(img_file);
}

void image_vers_fichier_compresse(char* chemin, image img){
    FILE *img_file = fopen(chemin, "w");
    double complex x,y,z;

    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return;
    }

    fprintf(img_file, "P6\n%d %d\n255\n", img.largeur, img.hauteur);
    
    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            x = img.x[i*img.largeur + j];
            y = img.y[i*img.largeur + j];
            z = img.z[i*img.largeur + j];

            fprintf(img_file, "%d %d ", (int)creal(x), (int)cimag(x));
            fprintf(img_file, "%d %d ", (int)creal(y), (int)cimag(y));
            fprintf(img_file, "%d %d ", (int)creal(z), (int)cimag(z));
        }
    }

    fclose(img_file);
}

void image_vers_fichier_compresse_reel(char* chemin, image img){
    FILE *img_file = fopen(chemin, "w");
    int x,y,z;

    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return;
    }

    fprintf(img_file, "P6\n%d %d\n255\n", img.largeur, img.hauteur);
    
    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            x = (int) creal(img.x[i*img.largeur + j]);
            y = (int) creal(img.y[i*img.largeur + j]);
            z = (int) creal(img.z[i*img.largeur + j]);

            fprintf(img_file, "%d ", x);
            fprintf(img_file, "%d ", y);
            fprintf(img_file, "%d ", z);
        }
    }

    fclose(img_file);
}

void image_vers_fichier_luminance(char* chemin, image img){
    FILE *img_file = fopen(chemin, "w");
    uint8_t x;

    if(img_file == NULL){
        fprintf(stderr, "Mauvais chemin ou permissions insuffisantes:\n%s\n", chemin);
        exit(1);
        return;
    }

    fprintf(img_file, "P6\n%d %d\n255\n", img.largeur, img.hauteur);
    
    for (int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            x = (uint8_t)cabs(img.y[i*img.largeur + j]);
            if(x > 10 && x < 40) x+= 30;

            fprintf(img_file, "%c", x);
            fprintf(img_file, "%c", x);
            fprintf(img_file, "%c", x);
        }
    }

    fclose(img_file);
}

image rgb_vers_ycbcr(image img){
    image rez;
    rez.hauteur = img.hauteur;
    rez.largeur = img.largeur;

    rez.x = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    rez.y = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    rez.z = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));


    for(int i = 0; i < img.hauteur*img.largeur; i++){
        rez.y[i]  = 0.299*img.x[i] + 0.587*img.y[i] + 0.114*img.z[i] + 0i;
        rez.x[i] = -0.1687*img.x[i] -0.3313*img.y[i] + 0.5*img.z[i] + 128.0 + 0i;
        rez.z[i] = 0.5*img.x[i] - 0.4187*img.y[i] - 0.0813*img.z[i] + 128.0 + 0i;
    }

    return rez;
}

image ycbcr_vers_rgb(image img){
    image rez;
    rez.hauteur = img.hauteur;
    rez.largeur = img.largeur;

    rez.x = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    rez.y = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));
    rez.z = (double complex*)malloc(img.largeur*img.hauteur*sizeof(double complex));

    for(int i = 0; i < img.hauteur*img.largeur; i++){
        rez.x[i] = min(img.y[i] + 1.402*(img.z[i] - 128.0), 255.0);
        rez.y[i] = min(img.y[i] - 0.34414*(img.x[i] - 128.0) - 0.71414*(img.z[i] - 128.0), 255.0);
        rez.z[i] = min(img.y[i] + 1.772*(img.x[i] - 128.0), 255.0);
    }

    return rez;
}

image image_vierge(int haut, int larg){
    image rez;
    rez.hauteur = haut;
    rez.largeur = larg;

    rez.x = (double complex*)calloc(larg*haut, sizeof(double complex));
    rez.y = (double complex*)calloc(larg*haut, sizeof(double complex));
    rez.z = (double complex*)calloc(larg*haut, sizeof(double complex));

    return rez;
}

image formate(image img){
    image rez;
    int haut = img.hauteur; 
    int larg = img.largeur;

    if(haut % TAILLE_BLOC != 0)haut += TAILLE_BLOC - img.hauteur % TAILLE_BLOC;
    if(larg % TAILLE_BLOC != 0)larg += TAILLE_BLOC - img.largeur % TAILLE_BLOC;

    rez = image_vierge(haut, larg);

    for(int i = 0; i < img.hauteur; i++){
        for(int j = 0; j < img.largeur; j++){
            rez.x[i*larg + j] = img.x[i*img.largeur + j];
            rez.y[i*larg + j] = img.y[i*img.largeur + j];
            rez.z[i*larg + j] = img.z[i*img.largeur + j];
        }
    }
    return rez;
}

image decoupe(image img, int haut, int larg){
    image rez;
    rez.hauteur = haut;
    rez.largeur = larg;

    rez.x = (double complex*)malloc(rez.largeur*rez.hauteur*sizeof(double complex));
    rez.y = (double complex*)malloc(rez.largeur*rez.hauteur*sizeof(double complex));
    rez.z = (double complex*)malloc(rez.largeur*rez.hauteur*sizeof(double complex));

    for(int i = 0; i < haut; i++){
        for(int j = 0; j < larg; j++){
            rez.x[i*rez.largeur + j] = img.x[i*img.largeur + j];
            rez.y[i*rez.largeur + j] = img.y[i*img.largeur + j];
            rez.z[i*rez.largeur + j] = img.z[i*img.largeur + j];
        }
    }
    return rez;
}

void libere_image(image img){
    free(img.x);
    free(img.y);
    free(img.z);
}