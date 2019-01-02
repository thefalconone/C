#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum typecarb{ liquid, solid, monoprop, nuclear }typecarb;

typedef struct engine{
	char* name;
	typecarb type;
	float mass;
	int thrust, isp, cost, typecarb, lf, ox, sf;
}engine;

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

//fusee.c
float deltav(stage* s);
int costfusee(stage* s);
float mintwr(stage* s);

//fichier.c
fueltank* lirefttxt();
engine* lireengtxt();

//genetic.c
float genetic(fueltank* listft, engine* listeng, int nbgenerations);

//affichage.c
void affichereng(engine e);
void afficherft(fueltank ft);
void afficherstage(stage* s);
void afficherfusee(stage* s);
void afficherlistft(fueltank* listft, int l);
void afficherlisteng(engine* listeng, int l);
void affichagegenbest(stage** pop, float** scores, int usercontinue);