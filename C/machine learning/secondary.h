#include "main.h"

#include <string.h>
#include <math.h>//pour le ln et le pow


//fusee.c
stage* initialisefusee();
void freefusee(stage* s);
void addstage(stage* s, int* indiceft, fueltank* listft, engine e);
void afficherfusee(stage* s);
float scorefusee(stage* s);


//genetic.c
typedef struct genestage{
	int* ft;
	int e;
}genestage;

typedef struct gene{
	genestage** s;
}gene;

void affichereng(engine e);
void afficherft(fueltank ft);
void afficherstage(stage* s);
void afficherfusee(stage* s);

//megenetic.c
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