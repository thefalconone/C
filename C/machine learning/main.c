#include "main.h"
#include <time.h>

int main(){
	FILE* fueltanks;
	FILE* engines;
	fueltanks=fopen("fueltank.txt","r");
	engines=fopen("engine.txt","r");

	//si les fichiers s'ouvrent correctement
	if (fueltanks!=NULL && engines!=NULL){

		engine* listeng=lire_eng(engines);
		fueltank* listft=lire_ft(fueltanks);

		stage* fusee=initialisefusee();
		//il y a 42 fuel tanks et 24 engines
		time_t t;
		srand((unsigned) time(&t));
		addstage(fusee, 1, &listft[rand()%43], listeng[rand()%25]);
		addstage(fusee, 1, &listft[rand()%43], listeng[rand()%25]);
		addstage(fusee, 1, &listft[rand()%43], listeng[rand()%25]);
		afficherfusee(fusee);
	}
	else{
		printf("fueltank.txt et/ou engine.txt n'existe pas, création des fichiers...\n");
		int erreng=system("sh createengine.sh");
		int errft=system("sh createfueltank.sh");
		if(erreng==-1){ printf("Erreur sur le script createengine.sh\n"); }
		if(errft==-1){ printf("Erreur sur le script createfueltank.sh\n"); }
		else{ printf("Succès, supprimez de la ligne 202 à 206 inclus dans fueltank.txt, puis veuillez relancer le programme\n");}
	}
	fclose(fueltanks);
	fclose(engines);
	return 0;
}
//pour calculer la consommation on doit prendre les ressources et les diviser par le bon ratio