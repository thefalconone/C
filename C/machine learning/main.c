#include "main.h"

int main(){
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();

	if(listeng!=NULL && listft!=NULL){//si les fichiers ont bien étés ouverts
		genetic(listft,listeng);
	}
	return 0;
}

/*
		for(int i=0; i<41; i++){
			afficherft(listft[i]);
		}
		for(int i=0; i<24; i++){
			affichereng(listeng[i]);
		}


		fueltank listft1[2]= { listft[rand()%40], listft[rand()%40] };
		fueltank listft2[1]= { listft[rand()%40] };
		fueltank listft3[3]= { listft[rand()%40], listft[rand()%40], listft[rand()%40] };
		addstage(fusee, 2, listft1, listeng[rand()%23]);
		addstage(fusee, 1, listft2, listeng[rand()%23]);
		addstage(fusee, 3, listft3, listeng[rand()%23]);


		stage* best=initialisefusee();
		addstage(best, 1, &listft[0], listeng[0]);
		addstage(best, 1, &listft[0], listeng[0]);
		for(int i=0; i<41; i++){
			for(int j=0; j<24; j++){
				for(int a=0; a<41; a++){
					for(int b=0; b<24; b++){
						stage* fusee=initialisefusee();
						addstage(fusee, 1, &listft[i], listeng[j]);
						addstage(fusee, 1, &listft[a], listeng[b]);
						if( pow(deltav(fusee),2) - pow(costfusee(fusee),2) + pow(3000*mintwr(fusee),2) > pow(deltav(best),2) - pow(costfusee(best),2) + pow(3000*mintwr(best),2)){
							best=fusee;
						}
					}
				}
			}
		}


		stage* best=initialisefusee();
		afficherfusee(best);
		printf("%.0fΔv	%d$	minTWR:%.3f", deltav(best), costfusee(best), mintwr(best));
*/

// 1 gene / part / etage / ftmax et engine