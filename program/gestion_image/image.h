#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <complex.h>
#include <math.h>

#define TAILLE_BLOC 8

typedef struct image
{
    int hauteur, largeur;
    //x = r; y = g; z = b (pour rgb)
    //x = Cb; y = y; z = Cr (pour yCbCr)
    double complex*  x;
    double complex*  y;
    double complex*  z;    
} image;

image fichier_vers_image(char* chemin);

//enregistre les coeffs complexes (arrondi les parties entière et imaginaires à l'entier le plus proche)
image fichier_compresse_vers_image(char* chemin);

//enregistre les coeffs reels (arrondi à l'entier le plus proche)
image fichier_compresse_reel_vers_image(char* chemin);

void image_vers_fichier(char* chemin, image img);

void image_vers_fichier_compresse(char* chemin, image img);

void image_vers_fichier_compresse_reel(char* chemin, image img);

image rgb_vers_ycbcr(image img);

image ycbcr_vers_rgb(image img);

image image_vierge(int haut, int larg);

//enregistre uniquement la luminance
void image_vers_fichier_luminance(char* chemin, image img);

//agrandi une image de telle sorte qu'on puisse la découper en bloc
//renvoie toujours une nouvelle image (meme une copie)
image formate(image img);

//decoupe l'image pour qu'elle rentre dans haut et larg
image decoupe(image img, int haut, int larg);

void libere_image(image img);

#endif