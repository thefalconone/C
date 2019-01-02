#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int existev(int* vivants, int indice){
	for(int i=0; i<100; i++)
		if(vivants[i]==indice)
			return 1;
	return 0;
}

int* tue(){
	int nbpop=1000, nbtokill=900;
	int* vivants=malloc( sizeof(*vivants)*(nbpop-nbtokill) );
	int nbtues=0;
	while(nbtues<nbtokill){
		int indice=rand()%nbpop;//entre 0 et nbpop-1
		//recherche de l'existance de l'indice dans le tableau
		if( !(existev(vivants,indice)) ){
			//0=nul=0% chance de vivre
			//99=meilleur=99% chance de vivre
			if(rand()%nbpop <= indice){//plus le score est grand, plus c'est dur de le tuer
				vivants[nbtues]=indice;
				nbtues++;
			}
		}
	}
	return vivants;
}

int main(void){
	time_t t;
	srand((unsigned) time(&t));
	int* vivants=tue();
	for(int i=0; i<100; i++){
		for(int j=0; j<10; j++){
			if(existev(vivants, 10*i+j)){
				printf("@");
			}
			else{//mort
				printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}