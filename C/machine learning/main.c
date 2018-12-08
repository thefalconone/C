#include "main.h"

int main(int argc, char* argv[]){
	printf("%s  	", argv[0]);
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();
	float scoremoy=0;
	if(listeng!=NULL && listft!=NULL){//si les fichiers ont bien étés ouverts
		for(int i=0; i<10; i++)
			scoremoy+=genetic(listft,listeng);
	}
	printf("score:%.0f\n", scoremoy/10);
	return 0;
}