#include "secondary.h"
#include <time.h>
#define nbmaxft 5
#define nbmaxstages 5
#define nbpop 100

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

int evaluer(stage** pop, float moddeltav, float modcost, float modtwr){
	float bestscore=0, scoremoy=0;
	int indicebest=0;

	for(int i=0; i<nbpop; i++){
		float score=scorefusee(pop[i], moddeltav, modcost, modtwr);
		scoremoy+=score;
		if(score>bestscore){
			bestscore=score;
			indicebest=i;
		}
	}
	scoremoy/=nbpop;
	afficherfusee(pop[indicebest]);
	printf("La fusée %d gagne avec un score de %.0f\n%.0fΔv	%d$	minTWR:%.3f\nLa moyenne est de %.0f", indicebest, bestscore, deltav(pop[indicebest]), costfusee(pop[indicebest]), mintwr(pop[indicebest]), scoremoy);
	return indicebest;
}

void reproduire(gene** genespop, int indicebest){
	for(int i=0; i<nbpop; i++){
		for(int j=0; j<nbmaxstages; j++){

			//SELECTION
			//le meilleur a 1 chance sur 3 de partager son gène de stage
			if(!(rand()%3)){
				genespop[i]->s[j]=genespop[indicebest]->s[j];
			}

			//MUTATION
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
	int appareiles[nbpop/2]={-1};
	//la première moitié de la population va être appareillée avec la seconde moitié en random
	for(int i=0; i<nbpop/2; i++){
		
	}
}

void genetic(fueltank* listft, engine* listeng, float moddeltav, float modcost, float modtwr){

	time_t t;
	srand((unsigned) time(&t));

	//création d'une population de nbpop fusees
	stage** pop=malloc(sizeof(*pop)*nbpop);
	for(int i=0; i<nbpop; i++){
		pop[i]=initialisefusee();
	}

	//initialisation des genes
	gene** genespop=malloc(sizeof(*genespop)*nbpop);
	for(int i=0; i<nbpop; i++){
		genespop[i]=initialisegene();
	}


	char usercontinue=121;
	//n = 110
	//y= 121
	while(usercontinue-110){//pour avancer d'une génération à la fois
		system("clear");

		//construire la nouvelle génération et reset la precedente
		construire(listft, listeng, pop, genespop);

		//evaluer la génération
		//la faire reproduire
		//le meilleur partage ses gènes par bloc de stage
		reproduire(genespop, evaluer(pop, moddeltav, modcost, modtwr));

		//à implementer: un compteur (nb de generations à skip) avec un print par génération pour montrer l'avancement
		printf("Voulez vous continuer? (y=yes,n=no)\n");
		fpurge(stdin);
		scanf("%c",&usercontinue);
	}
}