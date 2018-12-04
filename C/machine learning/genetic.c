#include "genetic.h"

gene* initialisegene(fueltank* listft, engine* listeng){
	gene* g=malloc(sizeof(*g));

	g->s1=malloc(sizeof(g->s1));
	g->s1->ft=malloc(sizeof(g->s1->ft)*3);
	for(int i=0; i<100; i++){
		if(rand()%2){//0 1 ou 2 donc 2chances/3
			g->s1->ft[i]=listft[rand()%40];
		}
		else{
			g->s1->ft[i]=NULL;
		}
	}

	return g;
}

stage* genetic(fueltank* listft, engine* listeng, float moddeltav, float modcost, float modtwr){

	//création d'une population de 100 fusees
	stage** pop=malloc(sizeof(*pop)*100);
	for(int i=0; i<100; i++){
		pop[i]=initialisefusee();
	}

	//initialisation des genes
	gene** genespop=malloc(sizeof(*genespop)*100);
	for(int i=0; i<100; i++){
		genespop[i]=initialisegene(listft, listeng);
	}

	char usercontinue=1;
	while(usercontinue){//pour avancer d'une génération à la fois

		//construire la génération
		for(int i=0; i<100; i++){
			//premier stage
			addstage(pop[i], 3, genespop[i]->s1->ft, genespop[i]->s1->e);
		}

		//evaluer la génération

		//la faire reproduire
		printf("Voulez vous continuer? (0=non,1=oui)\n");
		fpurge(stdin);
		scanf("%c",&usercontinue);
	}
}