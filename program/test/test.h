#ifndef _TEST_H_
#define _TEST_H_

#include "../gestion_image/image.h"
#include "../gestion_image/traitement/traitement.h"
#include "../gestion_image/traitement/controle.h"
#include "../gestion_image/traitement/quantification.h"
#include "../transformations/fourier/tf.h"
#include "../transformations/fourier/itf.h"
#include "../transformations/cosinus/tcd.h"
#include "../transformations/cosinus/itcd.h"

#define chemin_source "test/sources_test/"

#define chemin_resultat "test/resultats_test/"

void test_compression(char* image_source, double complex** Q);

#endif