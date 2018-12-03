#include "main.h"
#include <time.h>

int main(){
		engine* listeng=lireengtxt();
		fueltank* listft=lirefttxt();
		/*
		for(int i=0; i<41; i++){
			afficherft(listft[i]);
		}
		for(int i=0; i<24; i++){
			affichereng(listeng[i]);
		}
		printf("\n");
		*/
		time_t t;
		srand((unsigned) time(&t));

		//il y a 41 fuel tanks et 24 engines
		stage* fusee=initialisefusee();
		fueltank listft1[2]= { listft[rand()%40], listft[rand()%40] };
		fueltank listft2[1]= { listft[rand()%40] };
		fueltank listft3[3]= { listft[rand()%40], listft[rand()%40], listft[rand()%40] };
		addstage(fusee, 2, listft1, listeng[rand()%23]);
		addstage(fusee, 1, listft2, listeng[rand()%23]);
		addstage(fusee, 3, listft3, listeng[rand()%23]);
		afficherfusee(fusee);
		printf("%.0fΔv	%d$	minTWR:%.3f", deltav(fusee), costfusee(fusee), mintwr(fusee));
	return 0;
}

/*
		for(int i=0; i<41; i++){
			afficherft(listft[i]);
		}
		for(int i=0; i<24; i++){
			affichereng(listeng[i]);
		}
*/

// nbstages		1 gene / part / etage / ftmax et engine