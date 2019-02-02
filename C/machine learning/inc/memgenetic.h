#ifndef H_MEMGENETIC
#define H_MEMGENETIC

#include "struct.h"
void quicksort(float** number,int first,int last);
genestage* initialisegenestage();
void freegenestage(genestage* s);
gene* initialisegene();
void freegene(gene* g);
stage** initialisepopfusee();
void freepopfusee(stage** pop);
gene** initialisepopgenes();
void freepopgenes(gene** genespop);
void recopiestage(genestage* colle, genestage* copie);
void recopiegene(gene** colle, gene** copie);

#endif