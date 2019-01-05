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
float minfuseetwr(stage* s);
float maxfuseetwr(stage* s);

//fichier.c
fueltank* lirefttxt();
engine* lireengtxt();
void readsettings();
void savesettings();

//genetic.c
void genetic(fueltank* listft, engine* listeng);

//affichage.c
void afficherlistft(fueltank* listft, int l);
void afficherlisteng(engine* listeng, int l);
void afficherfuseehtml(stage* s);