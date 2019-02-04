#ifndef H_STRUCT
#define H_STRUCT

//carburant consommé par un engine
typedef enum typecarb{ liquid, solid, monoprop, nuclear }typecarb;

//un moteur fusée
typedef struct engine{
	char* name;
	typecarb type;
	float mass;
	int thrust, isp, cost, typecarb, lf, ox, sf;
}engine;

//un réservoir de carburant
typedef struct fueltank{
	char* name;
	int cost, lf, ox, mo;
	float drymass;
}fueltank;

//un étage de fusée composé de plusieurs réservoirs et d'un moteur
typedef struct stage{
	float drymass, totalmass;
	int nbft;
	fueltank* ft;
	engine e;
	struct stage* under;
}stage;

//representation d'un étage avec les indices des moteurs et reservoirs lues dans les fichiers
typedef struct genestage{
	int* ft;
	int e;
}genestage;

//représente un seul individu/une seule fusée
typedef struct gene{
	genestage** s;
}gene;

#endif