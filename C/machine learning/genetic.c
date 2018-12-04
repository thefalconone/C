#include "secondary.h"
#include <time.h>

#define nbmaxft 5
#define nbmaxstages 5
//nbpop tjrs pair (à cause du cross-over)
#define nbpop 100

#define moddeltav 4
#define modcost 0.5
#define modtwr 2

void quicksort(int* number,int first,int last){
	int i, j, pivot, temp;

	if(first<last){
		pivot=first;
		i=first;
		j=last;

		while(i<j){
			while(number[i]<=number[pivot]&&i<last)
			i++;
			while(number[j]>number[pivot])
			j--;
			if(i<j){
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}

		temp=number[pivot];
		number[pivot]=number[j];
		number[j]=temp;
		quicksort(number,first,j-1);
		quicksort(number,j+1,last);

	}
}

//il y a 41 fuel tanks et 24 engines
genestage* initialisegenestage(){

	genestage* s=malloc(sizeof(*s));

	s->ft=malloc(sizeof(&s->ft)*nbmaxft);
	for(int i=0; i<nbmaxft; i++){

		if(!(rand()%3)){//0 1 ou 2 donc 2chances/3
			s->ft[i]=rand()%40;
		}
		else{
			s->ft[i]=-1;//no ft
		}

	}
	s->e=rand()%23;
	return s;
}

gene* initialisegene(){
	gene* g=malloc(sizeof(*g));//malloc car*

	g->s=malloc(sizeof(&g->s)*nbmaxstages);

	for(int i=0; i<nbmaxstages; i++){
		g->s[i]=initialisegenestage();
	}

	return g;
}

stage** initialisepopfusee(){
	stage** pop=malloc(sizeof(*pop)*nbpop);
	for(int i=0; i<nbpop; i++){
		pop[i]=initialisefusee();
	}
	return pop;
}

gene** initialisepopgenes(){
	gene** genespop=malloc(sizeof(*genespop)*nbpop);
	for(int i=0; i<nbpop; i++){
		genespop[i]=initialisegene();
	}
	return genespop;
}

void construire(fueltank* listft, engine* listeng, stage** pop, gene** genespop){
	for(int i=0; i<nbpop; i++){//i=individu
		pop[i]=initialisefusee();
		for(int j=0; j<nbmaxstages; j++){//j=un stage

			//creation du ft d'un individu
			fueltank* geneft=malloc(sizeof(*geneft)*nbmaxft);
			int nbftgene=0;

			for(int k=0; k<nbmaxft; k++){//k=un fueltank
				//si il y a un fuel tank et pas rien
				if(genespop[i]->s[j]->ft[k]!=-1){
					geneft[nbftgene] = listft[ genespop[i]->s[j]->ft[k] ] ;
					nbftgene++;
				}
			}
			addstage(pop[i], nbftgene, geneft, listeng[ genespop[i]->s[j]->e ] );
		}
	}
}

int* best5percent(int* scores){
	int* best5=malloc(sizeof(*best5));
	for(int i=0; i<5; i++){
		best5[i]=scores[nbpop-i-1];
	}

	return indicebest;
}

int* worst5percent(int* scores){

}

void reproduire(gene** genespop, stage** pop){

	//SELECTION
	float* scores=malloc(sizeof(*score)*nbpop);
	for(int i=0; i<nbpop; i++){
		float scores[i]=scorefusee(pop[i], moddeltav, modcost, modtwr);
	}
	quicksort(scores,0,nbpop-1);

	for(int i=0; i<nbpop; i++){
		printf("%d\n",scores[i]);
	}
	int* indicebest=best5percent(scores);

	//MUTATION
	for(int i=0; i<nbpop; i++){
		for(int j=0; j<nbmaxstages; j++){
			//il y a 1% de chances qu'une mutation random remplace un ft par un autre
			//et 0.25% de chance qu'une mutation random remplace un ft par rien
			if(!(rand()%11)){
				for(int k=0; k<nbmaxft; k++){
					if(!(rand()%11)){
						genespop[i]->s[j]->ft[k]=rand()%40;
					}
					else if((!rand()%41)){
						genespop[i]->s[j]->ft[k]=-1;
					}
				}
				//1% de chance de mutation random d'un engine
				if(!(rand()%11)){
					genespop[i]->s[j]->e=rand()%23;
				}
			}

		}
	}

	//CROSS-OVER
	int appareilles[nbpop/2];
	for(int i=0; i<nbpop/2; i++){
		appareilles[i]=-1;
	}
	//on crée un tableau qui va associer les nbpop/2 premiers (random) avec les nbpop/2 (restants dans l'ordre)
	for(int i=nbpop/2; i>0; i--){
		//je me déplace un nb random (entre 0 et iterations-1)de fois dans le tableau
		int deplac=rand()%i, decal=0;
		for(int j=0; j<=deplac; j++){
			if(appareilles[j+decal]!=-1){
				decal++;
			}
		}
		while(appareilles[deplac+decal]!=-1){
			decal++;
		}
		appareilles[deplac+decal]=i-1;
	}


	for(int i=0; i<nbpop/2; i++){
		for(int j=0; j<nbmaxstages/2; j++){
			genespop[i]->s[j]=genespop[appareilles[i]]->s[j];
		}
	}
	for(int i=0; i<nbpop/2; i++){
		for(int j=nbmaxstages/2; j<nbmaxstages; j++){
			genespop[appareilles[i]]->s[j]=genespop[i]->s[j];
		}
	}
}

void genetic(fueltank* listft, engine* listeng){

	time_t t;
	srand((unsigned) time(&t));

	stage** pop=initialisepopfusee();
	gene** genespop=initialisepopgenes();

	int usercontinue=1;//nb de genrations à calculer avant d'afficher le resultat
	while(usercontinue!=0){//pour avancer d'une génération à la fois
		usercontinue--;
		//system("clear");

		//construire la nouvelle génération et reset la precedente
		construire(listft, listeng, pop, genespop);

		//evaluer la génération
		//la faire reproduire
		//le meilleur partage ses gènes par bloc de stage
		reproduire(genespop,pop);

		//à implementer: un compteur (nb de generations à skip) avec un print par génération pour montrer l'avancement
		if(!usercontinue){//tant qu'il est pas égal à 0
			printf("Continuer combien de fois?\n");
			fpurge(stdin);
			scanf("%d",&usercontinue);
		}
	}
}

/*

	if(!usercontinue){
		afficherfusee(pop[indicebest]);
		printf("La fusée %d gagne avec un score de %.0f\n%.0fΔv	%d$	minTWR:%.3f\nLa moyenne est de %.0f\n", indicebest, bestscore, deltav(pop[indicebest]), costfusee(pop[indicebest]), mintwr(pop[indicebest]), scoremoy);
	}
	printf("%.0f\n",scoremoy);

*/