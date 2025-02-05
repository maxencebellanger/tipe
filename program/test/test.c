#include "test.h"

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//concatene s2 dans s1
char* concat(char** chaines, int n){
    int len = 0;
    char* rez;
    for(int i = 0; i < n; i++) len += strlen(chaines[i]);

    rez = (char*)malloc((len + 1)*sizeof(char)); 
    rez[0] = '\0';

    for(int i = 0; i < n; i++) strcat(rez, chaines[i]);

    return rez;
}

void test_compression(char* image_source, double complex** Q){
    int haut_orig, larg_orig, haut, larg;
    int taille_zone_chrom = 6, taille_zone_lum = 4; //Taille de la zone des coefficiants que l'on garde
    double seuil_chrom = 0.85, seuil_lum = 0.50;

    //multiplication_scalaire(10, Q, Q);

    //Affectation des chemins pour enregistrer les images.
    char *dir, *im_source, *resultat, *im_tf, *im_tcd, *tf_comp_seuil, *tf_comp_zone, *tf_comp_matrice;
    char *tcd_comp_seuil, *tcd_comp_zone, *tcd_comp_matrice, *tf_comp_seuil_finale, *tf_comp_zone_finale, *tf_comp_matrice_finale;
    char *tcd_comp_seuil_finale, *tcd_comp_zone_finale, *tcd_comp_matrice_finale, *tf_id_finale, *tcd_id_finale;
    
    //chemin_mot_clefs(image_source, dir, im_source, resultat, im_tf, im_tcd, tf_comp, tcd_comp, tf_comp_finale, tcd_comp_finale, tf_id_finale, tcd_id_finale);

    char* keyword[9] = {"tf", "tcd", "comp", "img", "id", "finale", "seuil", "zone", "matrice"};

    char* dir_mot[3] = {chemin_resultat, image_source, "_test/"};
    dir = concat(dir_mot, 3);

    mkdir(dir, 0777);

    char* source[3] = {chemin_source, image_source, ".ppm"};
    im_source = concat(source, 3);
    
    source[0] = dir;
    source[2] = "_resultats.txt";
    resultat = concat(source, 3);

    char* resultat_1[7] = {dir, image_source, "_", keyword[0], "_", keyword[3], ".ppm"};
    im_tf = concat(resultat_1, 7);
    
    resultat_1[3] = keyword[1];
    im_tcd = concat(resultat_1, 7);

    resultat_1[5] = keyword[6];
    tcd_comp_seuil = concat(resultat_1, 7);
    
    resultat_1[3] = keyword[0];
    tf_comp_seuil = concat(resultat_1, 7);

    resultat_1[5] = keyword[7];
    tf_comp_zone = concat(resultat_1, 7);

    resultat_1[3] = keyword[1];
    tcd_comp_zone = concat(resultat_1, 7);

    resultat_1[5] = keyword[8];
    tcd_comp_matrice = concat(resultat_1, 7);
    
    resultat_1[3] = keyword[0];
    tf_comp_matrice = concat(resultat_1, 7);


    char* resultat_2[9] = {dir, image_source, "_", keyword[0], "_", keyword[6], "_", keyword[5], ".ppm"};
    tf_comp_seuil_finale  = concat(resultat_2, 9);

    resultat_2[3] = keyword[1];
    tcd_comp_seuil_finale  = concat(resultat_2, 9);

    resultat_2[5] = keyword[7];
    tcd_comp_zone_finale  = concat(resultat_2, 9);

    resultat_2[3] = keyword[0];
    tf_comp_zone_finale  = concat(resultat_2, 9);

    resultat_2[5] = keyword[8];
    tf_comp_matrice_finale  = concat(resultat_2, 9);

    resultat_2[3] = keyword[1];
    tcd_comp_matrice_finale  = concat(resultat_2, 9);

    resultat_2[5] = keyword[4];
    tcd_id_finale  = concat(resultat_2, 9);

    resultat_2[3] = keyword[0];
    tf_id_finale  = concat(resultat_2, 9);


    //création de l'image originel
    image img = fichier_vers_image(im_source);
    haut_orig = img.hauteur;
    larg_orig = img.largeur;

    //ajustement de la taille de l'image
    image ajuste = formate(img);
    haut = ajuste.hauteur;
    larg = ajuste.largeur;

    //Changement de modèle de couleur vers ycbcr
    //On peut filtrer de manière plus stricte le cb et le cr sans pertes d'informations visuelles significatives
    image ajuste_ycbcr = rgb_vers_ycbcr(ajuste);
    libere_image(ajuste);

    //On effectue une tcd et une tf sur l'image (pour tester la tcd/tf)
    image tf_img = tf_image(ajuste_ycbcr);
    image tcd_img = tcd_image(ajuste_ycbcr);

    //enregistrement des images
    image_vers_fichier(im_tf, tf_img);
    image_vers_fichier(im_tcd, tcd_img);

    //Compression de l'image
    //Sous echantillonage de la chrominance
    image ycbcr_echantillonne = image_vierge(haut, larg);
    map_bloc_plan(sous_echantillonnage_bloc, NULL, ajuste_ycbcr.x, haut, larg, ycbcr_echantillonne.x);
    map_bloc_plan(sous_echantillonnage_bloc, NULL, ajuste_ycbcr.z, haut, larg, ycbcr_echantillonne.z);
    map_bloc_plan(copie_bloc, NULL, ajuste_ycbcr.y, haut, larg, ycbcr_echantillonne.y);

    //Transformation TF/TCD
    image tf_img_comp = tf_image(ycbcr_echantillonne);
    image tcd_img_com = tcd_image(ycbcr_echantillonne);
    libere_image(ajuste_ycbcr);
    libere_image(ycbcr_echantillonne);

    image compression_seuil_tf = image_vierge(haut, larg);
    image compression_zone_tf = image_vierge(haut, larg);
    image compression_matrice_tf = image_vierge(haut, larg);

    image compression_seuil_tcd = image_vierge(haut, larg);
    image compression_zone_tcd = image_vierge(haut, larg);
    image compression_matrice_tcd = image_vierge(haut, larg);

     //Selection par seuil :
    map_bloc_plan(selection_seuil_bloc, &seuil_chrom, tf_img.x, haut, larg, compression_seuil_tf.x);
    map_bloc_plan(selection_seuil_bloc, &seuil_lum, tf_img.y, haut, larg, compression_seuil_tf.y);
    map_bloc_plan(selection_seuil_bloc, &seuil_chrom, tf_img.z, haut, larg, compression_seuil_tf.z);

    map_bloc_plan(selection_seuil_bloc, &seuil_chrom, tcd_img.x, haut, larg, compression_seuil_tcd.x);
    map_bloc_plan(selection_seuil_bloc, &seuil_lum, tcd_img.y, haut, larg, compression_seuil_tcd.y);
    map_bloc_plan(selection_seuil_bloc, &seuil_chrom, tcd_img.z, haut, larg, compression_seuil_tcd.z);

    //Selection par zone :
    map_bloc_plan(selection_zone_bloc, &taille_zone_chrom, tf_img.x, haut, larg, compression_zone_tf.x);
    map_bloc_plan(selection_zone_bloc, &taille_zone_lum, tf_img.y, haut, larg, compression_zone_tf.y);
    map_bloc_plan(selection_zone_bloc, &taille_zone_chrom, tf_img.z, haut, larg, compression_zone_tf.z);

    map_bloc_plan(selection_zone_bloc, &taille_zone_chrom, tcd_img.x, haut, larg, compression_zone_tcd.x);
    map_bloc_plan(selection_zone_bloc, &taille_zone_lum, tcd_img.y, haut, larg, compression_zone_tcd.y);
    map_bloc_plan(selection_zone_bloc, &taille_zone_chrom, tcd_img.z, haut, larg, compression_zone_tcd.z);

    //Quantification du plan de luminance avec une matrice de quantification
    map_bloc_plan(copie_bloc, NULL, tf_img.x, haut, larg, compression_matrice_tf.x);
    map_bloc_plan(quantification_bloc, Q, tf_img.y, haut, larg, compression_matrice_tf.y);
    map_bloc_plan(copie_bloc, NULL, tf_img.z, haut, larg, compression_matrice_tf.z);
    
    map_bloc_plan(copie_bloc, NULL, tcd_img.x, haut, larg, compression_matrice_tcd.x);
    map_bloc_plan(quantification_bloc, Q, tcd_img.y, haut, larg, compression_matrice_tcd.y);
    map_bloc_plan(copie_bloc, NULL, tcd_img.z, haut, larg, compression_matrice_tcd.z);

    //Enregistrement des images
    image_vers_fichier_compresse(tf_comp_seuil, compression_seuil_tf);
    image_vers_fichier_compresse_reel(tcd_comp_seuil, compression_seuil_tcd);
    
    image_vers_fichier(tf_comp_zone, compression_zone_tf);
    image_vers_fichier_compresse_reel(tcd_comp_zone, compression_zone_tcd);

    image_vers_fichier_compresse(tf_comp_matrice, compression_matrice_tf);
    image_vers_fichier_compresse_reel(tcd_comp_matrice, compression_matrice_tcd);

    //enregistrement des résultats
    FILE* fresultat = fopen(resultat, "w");

    fprintf(fresultat, "Qualité de la compression par seuil :\n");
    fprintf(fresultat, "EQM pour la TF : %f \n", EQM(tf_img, compression_seuil_tf));
    fprintf(fresultat, "EQM pour la TCD : %f \n", EQM(tcd_img, compression_seuil_tcd));
    fprintf(fresultat, "\n");

    fprintf(fresultat, "Qualité de la compression par zone :\n");
    fprintf(fresultat, "EQM pour la TF : %f \n", EQM(tf_img, compression_zone_tf));
    fprintf(fresultat, "EQM pour la TCD : %f \n", EQM(tcd_img, compression_zone_tcd));
    fprintf(fresultat, "\n");

    fprintf(fresultat, "Qualité de la compression par matrice de quantification :\n");
    fprintf(fresultat, "EQM pour la TF : %f \n", EQM(tf_img, compression_matrice_tf));
    fprintf(fresultat, "EQM pour la TCD : %f \n", EQM(tcd_img, compression_matrice_tcd));
    fprintf(fresultat, "\n");

    fclose(fresultat);

    //Décompression
    //Dequantification du plan de luminance
    //On écrase les images car on n'en a plus besoin (la dequantificaption se fait pixel par pixel donc pas de probleme)
    map_bloc_plan(dequantification_bloc, Q, compression_matrice_tf.y, haut, larg, compression_matrice_tf.y);
    map_bloc_plan(dequantification_bloc, Q, compression_matrice_tcd.y, haut, larg, compression_matrice_tcd.y);


    image itf_seuil = itf_image(compression_seuil_tf);
    image itf_zone = itf_image(compression_zone_tf);
    image itf_matrice = itf_image(compression_matrice_tf);
    image itf_non_compressee = itf_image(tf_img);
    image itcd_seuil = itcd_image(compression_seuil_tcd);
    image itcd_zone = itcd_image(compression_zone_tcd);
    image itcd_matrice = itcd_image(compression_matrice_tcd);
    image itcd_non_compressee = itcd_image(tcd_img);
    libere_image(tf_img);
    libere_image(compression_seuil_tf);
    libere_image(compression_zone_tf);
    libere_image(compression_matrice_tf);
    libere_image(tcd_img);
    libere_image(compression_seuil_tcd);
    libere_image(compression_zone_tcd);
    libere_image(compression_matrice_tcd);


    //On repasse en rgb
    image itf_seuil_rgb = ycbcr_vers_rgb(itf_seuil);
    image itf_zone_rgb = ycbcr_vers_rgb(itf_zone);
    image itf_matrice_rgb = ycbcr_vers_rgb(itf_matrice);
    image itf_non_compressee_rgb = ycbcr_vers_rgb(itf_non_compressee);
    image itcd_seuil_rgb = ycbcr_vers_rgb(itcd_seuil);
    image itcd_zone_rgb = ycbcr_vers_rgb(itcd_zone);
    image itcd_matrice_rgb = ycbcr_vers_rgb(itcd_matrice);
    image itcd_non_compressee_rgb = ycbcr_vers_rgb(itcd_non_compressee);
    libere_image(itf_seuil);
    libere_image(itf_zone);
    libere_image(itf_matrice);
    libere_image(itf_non_compressee);
    libere_image(itcd_seuil);
    libere_image(itcd_zone);
    libere_image(itcd_matrice);
    libere_image(itcd_non_compressee);

    //On reajuste les images à leur taille initiale
    image compression_seuil_tf_finale = decoupe(itf_seuil_rgb, haut_orig, larg_orig);
    image compression_zone_tf_finale = decoupe(itf_zone_rgb, haut_orig, larg_orig);
    image compression_matrice_tf_finale = decoupe(itf_matrice_rgb, haut_orig, larg_orig);
    image tf_finale = decoupe(itf_non_compressee_rgb, haut_orig, larg_orig);
    image compression_seuil_tcd_finale = decoupe(itcd_seuil_rgb, haut_orig, larg_orig);
    image compression_zone_tcd_finale = decoupe(itcd_zone_rgb, haut_orig, larg_orig);
    image compression_matrice_tcd_finale = decoupe(itcd_matrice_rgb, haut_orig, larg_orig);
    image tcd_finale = decoupe(itcd_non_compressee_rgb, haut_orig, larg_orig);
    libere_image(itf_seuil_rgb);
    libere_image(itf_zone_rgb);
    libere_image(itf_matrice_rgb);
    libere_image(itf_non_compressee_rgb);
    libere_image(itcd_seuil_rgb);
    libere_image(itcd_zone_rgb);
    libere_image(itcd_matrice_rgb);
    libere_image(itcd_non_compressee_rgb);

    //enregistrement des images
    image_vers_fichier(tf_comp_seuil_finale, compression_seuil_tf_finale);
    image_vers_fichier(tf_comp_zone_finale, compression_zone_tf_finale);
    image_vers_fichier(tf_comp_matrice_finale, compression_matrice_tf_finale);
    image_vers_fichier(tf_id_finale, tf_finale);
    image_vers_fichier(tcd_comp_seuil_finale, compression_seuil_tcd_finale);
    image_vers_fichier(tcd_comp_zone_finale, compression_zone_tcd_finale);
    image_vers_fichier(tcd_comp_matrice_finale, compression_matrice_tcd_finale);
    image_vers_fichier(tcd_id_finale, tcd_finale);

    libere_image(img);
    libere_image(compression_seuil_tf_finale);
    libere_image(compression_zone_tf_finale);
    libere_image(compression_matrice_tf_finale);
    libere_image(tf_finale);
    libere_image(compression_seuil_tcd_finale);
    libere_image(compression_zone_tcd_finale);
    libere_image(compression_matrice_tcd_finale);
    libere_image(tcd_finale);

    free(dir);
    free(im_source); 
    free(resultat);
    free(im_tf);
    free(im_tcd);
    free(tf_comp_seuil);
    free(tf_comp_zone);
    free(tf_comp_matrice);
    free(tcd_comp_seuil);
    free(tcd_comp_zone);
    free(tcd_comp_matrice);
    free(tf_comp_seuil_finale);
    free(tf_comp_zone_finale);
    free(tf_comp_matrice_finale);
    free(tcd_comp_seuil_finale);
    free(tcd_comp_zone_finale);
    free(tcd_comp_matrice_finale);
    free(tf_id_finale);
    free(tcd_id_finale);
}