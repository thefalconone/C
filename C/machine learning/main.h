#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct engine{
	char* name;
	float mass;
	int thrust, isp, cost, typecarb, lf, ox, sf;
}engine;

//totalmass = dry + 5*(somme des carbus)/1000
typedef struct fueltank{
	char* name;
	int cost, lf, ox, mo;
	float drymass;
}fueltank;

typedef struct stage{
	float drymass, totalmass;
	int nbft;
	fueltank* ft;
	engine e;
	struct stage* under;
}stage;

//fichier.c
engine* lire_eng(FILE* engines);
fueltank* lire_ft(FILE* fueltanks);

//fusee.c
stage* initialisefusee();
void addstage(stage* s, int nbft, fueltank* ft, engine e);
void afficherfusee(stage* s);
void afficherft(fueltank ft);
void affichereng(engine e);