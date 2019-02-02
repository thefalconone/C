#include "../inc/fichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern float ratiokill, moddeltav, modcost, modtwr, minusertwr, maxusertwr, payload;
extern int nbpop, nbmut, nbmaxft, nbmaxstages, nbgen, mindv, maxdv, mincost, maxcost;

//supprime les nb premier char de la variable char* copier et les mets dans le char* coller
void strcpynb(char* coller, char* copier, int nb){
	int i=nb;
	while(copier[i]!='\n'){
		coller[i-nb]=copier[i];
		i++;
	}
}

engine* lire_eng(FILE* engines){
	int taillemax=100;
	char ligne[taillemax];

	fgets(ligne,taillemax,engines);
	int nbeng=atoi(ligne);

	engine* listeng=malloc(sizeof(struct engine)*nbeng);

	for(int i=0; i<nbeng; i++){
		//name
		fgets(ligne, taillemax, engines);
		ligne[strlen(ligne)-1]='\0';
		listeng[i].name=malloc(sizeof(char)*strlen(ligne) + 1);//+1 pour le \0
		strcpy(listeng[i].name,ligne);

		//cost
		fgets(ligne, taillemax, engines);
		//elimination de "cost = "
		strcpynb(ligne,ligne,7);
		listeng[i].cost=atoi(ligne);

		//mass
		fgets(ligne, taillemax, engines);
		//elimination de "mass = "
		strcpynb(ligne,ligne,7);
		listeng[i].mass=atof(ligne);

		//EngineType
		fgets(ligne, taillemax, engines);
		//elimination de "EngineType = "
		if(ligne[13]=='L'){ listeng[i].type=liquid; }
		else if(ligne[13]=='N'){ listeng[i].type=nuclear; }
		else if(ligne[13]=='S'){ listeng[i].type=solid; }
		else{ listeng[i].type=monoprop; }

		//amount si srb ou lfox, isp sinon
		fgets(ligne, taillemax, engines);
		
		listeng[i].sf=0;
		listeng[i].lf=0;
		listeng[i].ox=0;

		if(ligne[0]=='a'){//soit srb soit tank
			//elimination de "amount = "
			strcpynb(ligne,ligne,9);
			listeng[i].sf=atoi(ligne);
			fgets(ligne, taillemax, engines);//lit l'isp si srb, le 2e amount sinon

			if(ligne[0]=='a'){//si 2e amount : c'est obligé lfox
				listeng[i].lf=listeng[i].sf;
				listeng[i].sf=0;
				//elimination de "amount = "
				strcpynb(ligne,ligne,9);
				listeng[i].ox=atoi(ligne);
				fgets(ligne, taillemax, engines);//lit l'isp car tank
			}
		}

		//isp
		//elimination de "key = 0 "
		strcpynb(ligne,ligne,8);
		listeng[i].isp=atoi(ligne);

		//thrust
		fgets(ligne, taillemax, engines);
		//elimination de "maxThrust = "
		strcpynb(ligne,ligne,12);
		listeng[i].thrust=atoi(ligne);
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
		fgets(ligne, taillemax, fueltanks);
		ligne[strlen(ligne)-1]='\0';
		listft[i].name=malloc(sizeof(char)*strlen(ligne) + 1);//+1 pour le \0
		strcpy(listft[i].name,ligne);

		//cost
		fgets(ligne, taillemax, fueltanks);
		//elimination de "cost = "
		strcpynb(ligne,ligne,7);
		listft[i].cost=atoi(ligne);

		//mass
		fgets(ligne, taillemax, fueltanks);
		//elimination de "mass = "
		strcpynb(ligne,ligne,7);
		listft[i].drymass=atof(ligne);

		//soit lf only, soit lf+ox, soit mo only
		fgets(ligne, taillemax, fueltanks);
		if(ligne[7]=='L'){
			listft[i].mo=0;
			fgets(ligne, taillemax, fueltanks);

			if(ligne[7]=='O'){//lf+ox
				//lf
				fgets(ligne, taillemax, fueltanks);
				//elimination de "amount = "
				strcpynb(ligne,ligne,9);
				listft[i].lf=atoi(ligne);
				//ox
				fgets(ligne, taillemax, fueltanks);
				//elimination de "amount = "
				strcpynb(ligne,ligne,9);
				listft[i].ox=atoi(ligne);

			}
			else{//lf only
				listft[i].ox=0;
				//elimination de "amount = "
				strcpynb(ligne,ligne,9);
				listft[i].lf=atoi(ligne);
			}
		}
		else{//mo only
			listft[i].lf=0;
			listft[i].ox=0;
			fgets(ligne, taillemax, fueltanks);
			//elimination de "amount = "
			strcpynb(ligne,ligne,9);
			listft[i].mo=atoi(ligne);
		}
	}

	return listft;
}

fueltank* lirefttxt(){
	FILE* fueltanks;
	fueltanks=fopen("data/fueltank.txt","r");
	fueltank* listft;

	//si le fichier s'ouvre correctement
	if (fueltanks!=NULL){
		listft=lire_ft(fueltanks);
	}
	else{
		printf("fueltank.txt n'existe pas, création des fichiers...\n");
		int errft=system("cd ../data; sh createfueltank.sh");
		if(errft==-1){ printf("Erreur sur le script createfueltank.sh\n"); }
		else{ printf("Succès, veuillez relancer le programme\n");}
		listft=NULL;
	}
	fclose(fueltanks);
	return listft;
}

engine* lireengtxt(){
	FILE* engines;
	engines=fopen("data/engine.txt","r");
	engine* listeng;

	//si le fichier s'ouvre correctement
	if (engines!=NULL){
		listeng=lire_eng(engines);
	}
	else{
		printf("engine.txt n'existe pas, création des fichiers...\n");
		int erreng=system("cd ../data; sh createengine.sh");
		if(erreng==-1){ printf("Erreur sur le script createengine.sh\n"); }
		else{ printf("Succès, veuillez relancer le programme\n");}
		listeng=NULL;
	}
	fclose(engines);
	return listeng;
}

void overwritesettings(){
	FILE* settings;
	settings=fopen("data/settings.txt","w");

	fprintf(settings, "0.5\n1\n1\n1\n1\n5\n4.32\n1000\n300\n3\n5\n100\n0\n-1\n0\n-1\n");
}

void readsettings(){
	FILE* settings;
	settings=fopen("data/settings.txt","r");

	if(settings!=NULL){//si le fichier existe
		int taillemax=50;
		char ligne[taillemax];

		fgets(ligne,taillemax,settings);
		ratiokill=atof(ligne);
		fgets(ligne,taillemax,settings);
		moddeltav=atof(ligne);
		fgets(ligne,taillemax,settings);
		modcost=atof(ligne);
		fgets(ligne,taillemax,settings);
		modtwr=atof(ligne);
		fgets(ligne,taillemax,settings);
		minusertwr=atof(ligne);
		fgets(ligne,taillemax,settings);
		maxusertwr=atof(ligne);
		fgets(ligne,taillemax,settings);
		payload=atof(ligne);
		fgets(ligne,taillemax,settings);
		nbpop=atoi(ligne);
		fgets(ligne,taillemax,settings);
		nbmut=atoi(ligne);
		fgets(ligne,taillemax,settings);
		nbmaxft=atoi(ligne);
		fgets(ligne,taillemax,settings);
		nbmaxstages=atoi(ligne);
		fgets(ligne,taillemax,settings);
		nbgen=atoi(ligne);
		fgets(ligne,taillemax,settings);
		mindv=atoi(ligne);
		fgets(ligne,taillemax,settings);
		maxdv=atoi(ligne);
		fgets(ligne,taillemax,settings);
		mincost=atoi(ligne);
		fgets(ligne,taillemax,settings);
		maxcost=atoi(ligne);
	}
	else{
		printf("Le fichier settings n'existe pas, reconstruction\n");
		overwritesettings();
	}
}

void savesettings(){
	FILE* settings;
	settings=fopen("data/settings.txt","w");

	fprintf(settings, "%f\n%f\n%f\n%f\n%f\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", ratiokill, moddeltav, modcost, modtwr, minusertwr, maxusertwr, payload, nbpop, nbmut, nbmaxft, nbmaxstages, nbgen, mindv, maxdv, mincost, maxcost);
}