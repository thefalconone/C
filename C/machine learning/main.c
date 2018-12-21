#include "main.h"

int main(int argc, char* argv[]){
	//initialisation de la fonction rand()
	time_t t;
	srand((unsigned) time(&t));

	//lecture des fichiers engine.txt et fueltank.txt
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();

	//int nbgenerations=100, nbtry=atoi(argv[1]);
	//float score[nbtry];
	if(listeng!=NULL && listft!=NULL){//si les fichiers ont bien étés ouverts
		//on lance une génération
		genetic(listft, listeng,1);
		//for(int i=0; i<nbtry; i++)
			//score[i]=genetic(listft, listeng, nbgenerations);
	}

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