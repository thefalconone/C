#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct engine{
	char* name;
	float ratiolf, ratioox, ratiomo, mass;
	int thrust, isp, cost;
}engine;

//totalmass = dry + 5*(somme des carbus)/1000
typedef struct fueltank{
	char* name;
	int cost, lf, ox, mo;
	float drymass;
}fueltank;

typedef struct stage{
	fueltank* ft;
	engine eng;
	struct stage* under;
}stage;

engine* lire_eng(FILE* engines){
	int taillemax=50;
	char ligne[taillemax];

	fgets(ligne,taillemax,engines);
	int nbeng=atoi(ligne);

	engine* listeng=malloc(sizeof(struct engine)*nbeng);

	for(int i=0; i<nbeng; i++){
		//name
		fscanf(engines, "name = %s", ligne);
		listeng->name=malloc(sizeof(char)*strlen(ligne));
		strcat(listeng->name,ligne);
	}

	return listeng;
}

fueltank* lire_ft(FILE* fueltanks){
	int taillemax=50;
	char ligne[taillemax];

	fgets(ligne,taillemax,fueltanks);
	int nbft=atoi(ligne);

	fueltank* listft=malloc(sizeof(struct fueltank)*nbft);

	for(int i=0; i<nbft; i++){
		//name
		fscanf(fueltanks, "name = %s", ligne);
		listft->name=malloc(sizeof(char)*strlen(ligne));
		strcat(listft->name,ligne);
	}

	return listft;
}

void affichereng(engine e){
	printf("%s",e.name);
}

void afficherft(fueltank ft){
	printf("%s",ft.name);
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

		affichereng(listeng[1]);
		afficherft(listft[1]);
	}
	else{
		printf("fueltank.txt et/ou engine.txt n'existe pas, création des fichiers...\n");
		int erreng=system("sh createengine.sh");
		int errft=system("sh createfueltank.sh");
		if(erreng==-1){ printf("Erreur sur le script createengine.sh\n"); }
		if(errft==-1){ printf("Erreur sur le script createfueltank.sh\n"); }
		else{ printf("Succès, veuillez relancer le programme\n");}
	}
	fclose(fueltanks);
	fclose(engines);
	return 0;
}
//pour calculer la consommation on doit prendre les ressources et les diviser par le bon ratio