#include "main.h"

int main(int argc, char* argv[]){
	time_t t;
	srand((unsigned) time(&t));

	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();

	//int nbgenerations=100, nbtry=atoi(argv[1]);
	//float score[nbtry];
	if(listeng!=NULL && listft!=NULL)//si les fichiers ont bien étés ouverts
		genetic(listft, listeng,1);
		//for(int i=0; i<nbtry; i++)
			//score[i]=genetic(listft, listeng, nbgenerations);

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