#include "secondary.h"

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
		listeng[i].name=malloc(sizeof(char)*strlen(ligne));
		//elimination de " "
		strcpynb(listeng[i].name,ligne,1);

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
		//name
		fgets(ligne, taillemax, fueltanks);
		listft[i].name=malloc(sizeof(char)*strlen(ligne));
		//elimination de " "
		strcpynb(listft[i].name,ligne,1);

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
	fueltanks=fopen("fueltank.txt","r");
	fueltank* listft;

	//si le fichier s'ouvre correctement
	if (fueltanks!=NULL){
		listft=lire_ft(fueltanks);
	}
	else{
		printf("fueltank.txt n'existe pas, création des fichiers...\n");
		int errft=system("sh createfueltank.sh");
		if(errft==-1){ printf("Erreur sur le script createfueltank.sh\n"); }
		else{ printf("Succès, veuillez relancer le programme\n");}
		listft=NULL;
	}
	fclose(fueltanks);
	return listft;
}

engine* lireengtxt(){
	FILE* engines;
	engines=fopen("engine.txt","r");
	engine* listeng;

	//si le fichier s'ouvre correctement
	if (engines!=NULL){
		listeng=lire_eng(engines);
	}
	else{
		printf("engine.txt n'existe pas, création des fichiers...\n");
		int erreng=system("sh createengine.sh");
		if(erreng==-1){ printf("Erreur sur le script createengine.sh\n"); }
		else{ printf("Succès, veuillez relancer le programme\n");}
		listeng=NULL;
	}
	fclose(engines);
	return listeng;
}