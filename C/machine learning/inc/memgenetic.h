#ifndef H_MEMGENETIC
#define H_MEMGENETIC

#include "struct.h"

//algorithme de tri, pour le tableau de score
void quicksort(float** number,int first,int last);
stage** initialisepopfusee();
void freepopfusee(stage** pop);
gene** initialisepopgenes();
void freepopgenes(gene** genespop);

//pour le cross-over
void recopiestage(genestage* colle, genestage* copie);
void recopiegene(gene** colle, gene** copie);

#endif