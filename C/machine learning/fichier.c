#include "main.h"

void strcpynb(char* coller, char* copier, int nb){
	int i=nb;
	while(copier[i]!='\n'){
		coller[i-nb]=copier[i];
		i++;
	}
}

engine* lire_eng(FILE* engines){
	int taillemax=50;
	char ligne[taillemax];

	fgets(ligne,taillemax,engines);
	int nbeng=atoi(ligne);

	engine* listeng=malloc(sizeof(struct engine)*nbeng);

	for(int i=0; i<nbeng; i++){
		//name
		fgets(ligne, taillemax, engines);
		listeng[i].name=malloc(sizeof(char)*strlen(ligne));
		//elimination de "name = "
		strcpynb(listeng[i].name,ligne,7);

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

		//amount si srb, isp sinon
		fgets(ligne, taillemax, engines);
		
		listeng[i].typecarb=rien;

		if(ligne[0]=='a'){//soit srb soit tank
			listeng[i].typecarb=solidfuel;
			//elimination de "amount = "
			strcpynb(ligne,ligne,9);
			listeng[i].sf=atoi(ligne);
			fgets(ligne, taillemax, engines);//lit l'isp si srb, le 2e amount sinon

			if(ligne[0]=='a'){//lfox
				listeng[i].typecarb=lfox;
				listeng[i].lf=listeng[i].sf;
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
		//elimination de "name = "
		strcpynb(listft[i].name,ligne,7);

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
				fgets(ligne, taillemax, fueltanks);
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