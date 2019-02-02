#include "../inc/fusee.h"
#include "../inc/memgenetic.h"
#include <stdlib.h>
#include <time.h>

extern int nbpop, nbmut, nbmaxft, nbmaxstages;

void quicksort(float** number,int first,int last){
	int i, j, pivot;
	float* temp;

	if(first<last){
		pivot=first;
		i=first;
		j=last;

		while(i<j){
			while(number[i][1]<=number[pivot][1] && i<last)
			i++;
			while(number[j][1]>number[pivot][1])
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
//rempli le génome de gènes random
genestage* initialisegenestage(){
	genestage* s=malloc(sizeof(*s));

	s->ft=malloc(sizeof(&s->ft)*nbmaxft);
	for(int i=0; i<nbmaxft; i++){

		if(rand()%3)//2 chances sur 3 qu'il y ait un ft
			s->ft[i]=rand()%41;
		else//1 chance sur 3 vide
			s->ft[i]=-1;//no ft
	}

	if(rand()%3)//2 chances sur 3 que le stage soit pas vide
		s->e=rand()%24;
	else//1 chance sur 3 vide
		s->e=-1;

	return s;
}

void freegenestage(genestage* s){
	free(s->ft);
	free(s);
}

gene* initialisegene(){
	gene* g=malloc(sizeof(*g));
	g->s=malloc(sizeof(&g->s)*nbmaxstages);

	for(int i=0; i<nbmaxstages; i++)
		g->s[i]=initialisegenestage();

	return g;
}

void freegene(gene* g){
	for(int i=0; i<nbmaxstages; i++)
		freegenestage(g->s[i]);
	free(g->s);
	free(g);
}

//mets des satellites dans toutes les fusées mais rien d'autre
stage** initialisepopfusee(){
	stage** pop=malloc(sizeof(*pop)*nbpop);
	for(int i=0; i<nbpop; i++)
		pop[i]=initialisefusee();
	return pop;
}

void freepopfusee(stage** pop){
	for(int i=0; i<nbpop; i++)
		freefusee(pop[i]);
	free(pop);
}

gene** initialisepopgenes(){
	gene** genespop=malloc(sizeof(*genespop)*nbpop);
	for(int i=0; i<nbpop; i++)
		genespop[i]=initialisegene();
	return genespop;
}

void freepopgenes(gene** genespop){
	for(int i=0; i<nbpop; i++)
		freegene(genespop[i]);
	free(genespop);
}

void recopiestage(genestage* colle, genestage* copie){
	for(int i=0; i<nbmaxft; i++)
		colle->ft[i]=copie->ft[i];
	colle->e=copie->e;
}

void recopiegene(gene** colle, gene** copie){
	for(int i=0; i<nbpop; i++)
		for(int j=0; j<nbmaxstages; j++)
			recopiestage(colle[i]->s[j],copie[i]->s[j]);
}