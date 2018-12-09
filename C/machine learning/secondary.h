#include "main.h"

#include <string.h>
#include <math.h>//pour le ln et le pow


//fusee.c
stage* initialisefusee();
void freefusee(stage* s);
void addstage(stage* s, int nbft, int* indiceft, fueltank* listft, engine e);
void afficherfusee(stage* s);
float scorefusee(stage* s, float moddeltav, float modcost, float modtwr);


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
float deltav(stage* s);
int costfusee(stage* s);
float mintwr(stage* s);