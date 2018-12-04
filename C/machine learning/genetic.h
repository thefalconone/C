#include "main.h"


typedef struct genestage{
	fueltank ft[3];
	engine e;
}genestage;

//3 stages, contenant chacun 3 ft et 1 eng
typedef struct gene{
	genestage s1;
	genestage s2;
	genestage s3;
}gene;