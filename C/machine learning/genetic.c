#include "genetic.h"

gene* initialisegene(fueltank* listft, engine* listeng){
	gene* g=malloc(sizeof(*g));
	for(int i=0; i<100; i++){
		g->s1.ft[i]=listft[rand()%40];
	}
	g->s1.e=listeng[rand()%23];
	return g;
}

stage* genetic(fueltank* listft, engine* listeng, float moddeltav, float modcost, float modtwr){

	//création d'une population de 100 fusees
	stage* pop[100];
	for(int i=0; i<100; i++){
		pop[i]=initialisefusee();
	}

	//initialisation des genes
	gene* genespop[100];
	for(int i=0; i<100; i++){
		genespop[i]=initialisegene(listft, listeng);
	}
}