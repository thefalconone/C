#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum typecarb{ rien=0, solidfuel=1, lfox=2 }typecarb;

typedef struct engine{
	char* name;
	float mass;
	typecarb type;
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
	fueltank* ft;
	engine e;
	struct stage* under;
}stage;

//fichier.c
engine* lire_eng(FILE* engines);
fueltank* lire_ft(FILE* fueltanks);

//fusee.c
stage* initialisefusee();
void addstage(stage* f, fueltank* ft, engine e);