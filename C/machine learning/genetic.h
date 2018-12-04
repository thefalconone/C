#include "main.h"


typedef struct genestage{
	int* ft;
	int e;
}genestage;

//3 stages, contenant chacun 3 ft et 1 eng
typedef struct gene{
	genestage* s1;
	genestage* s2;
	genestage* s3;
}gene;

stage* genetic(fueltank* listft, engine* listeng, float moddeltav, float modcost, float modtwr);