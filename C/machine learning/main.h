#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>//pour le ln et le pow
#include <time.h>

typedef enum typecarb{ liquid, solid, monoprop, nuclear }typecarb;

typedef struct engine{
	char* name;
	typecarb type;
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
fueltank* lirefttxt();
engine* lireengtxt();

//fusee.c
stage* initialisefusee();
void addstage(stage* s, int nbft, fueltank* ft, engine e);
void afficherfusee(stage* s);
float deltav(stage* s);
void affichereng(engine e);
void afficherft(fueltank ft);
int costfusee(stage* s);
float mintwr(stage* s);

stage* genetic(fueltank* listft, engine* listeng, float moddeltav, float modcost, float modtwr);