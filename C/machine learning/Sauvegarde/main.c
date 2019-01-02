#include "main.h"

int nbpop=1000, nbmut=300, nbmaxft=3, nbmaxstages=5;
//strictement entre 0 et 1
//0.25 = on tue 25% de la pop
//ratiokill ne fonctionne bien qu'avec la valeur 0.5
float ratiokill=0.5, moddeltav=3, modcost=1, modtwr=1;

int main(int argc, char* argv[]){
	//initialisation de la fonction rand()
	time_t t;
	srand((unsigned) time(&t));

	//lecture des fichiers engine.txt et fueltank.txt
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();
	genetic(listft, listeng, 1);/*
	int nbgenerations=100, nbtry=atoi(argv[1]);
	float score[nbtry], moyenne=0;
	if(listeng!=NULL && listft!=NULL){//si les fichiers ont bien étés ouverts
		//on lance une génération
		//genetic(listft, listeng,1);
		for(int i=0; i<nbtry; i++){
			score[i]=genetic(listft, listeng, nbgenerations);
			moyenne+=score[i]/nbtry;
		}
	}
	printf("%.2e\n", moyenne);*/

/*
	for(int j=0; j<nbtry; j++)
		printf("%.0f\n",score[j]);

	int count[10]={0};
	for(int i=0; i<10; i++)
		for(int j=0; j<nbtry; j++)
			if(i*5000000<score[j] && score[j]<(i+1)*5000000)
				count[i]++;

	for(int i=0; i<10; i++)
		printf("%d:	%d\n",i*5000000, count[i]);
	//printf("%s\n%f\n", argv[0], moyenne);*/
	return 0;
}