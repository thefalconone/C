#include "main.h"

void affichereng(engine e){
	printf("\nengine:\nnom: %s\nmass: %.3f thrust: %d isp: %d cost: %d\n",e.name, e.mass, e.thrust, e.isp, e.cost);
	if(e.typecarb==solidfuel){ printf("sf: %d\n", e.sf); }
	if(e.typecarb==lfox){ printf("lf: %d ox: %d\n", e.lf, e.ox); }
}

void afficherft(fueltank ft){
	printf("\nfuel tank:\nnom: %s\nmass: %.3f cost: %d lf: %d ox: %d mo: %d\n",ft.name, ft.drymass, ft.cost, ft.lf, ft.ox, ft.mo);
}

int main(){
	FILE* fueltanks;
	FILE* engines;
	fueltanks=fopen("fueltank.txt","r");
	engines=fopen("engine.txt","r");

	//si les fichiers s'ouvrent correctement
	if (fueltanks!=NULL && engines!=NULL){

		engine* listeng=lire_eng(engines);
		fueltank* listft=lire_ft(fueltanks);

		for(int i=0; i<3; i++){
			affichereng(listeng[i]);
			afficherft(listft[i]);
		}

		stage* fusee=initialisefusee();
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