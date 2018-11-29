#include <string.h>
#include "graphe.h"

typedef struct automate{
	graphe* g;
	char* alphabet;
	int etat_init;
	int etat_final;
}automate;

typedef struct cell{
	int sommet;
	char* chemin;
	int profondeur;
	struct cell* suiv;
}cell;

typedef struct file{
	struct cell* debut;
	struct cell* fin;
}file;

file* Initialise(){
	file* f=malloc(sizeof(struct file));
	f->debut=NULL;
	f->fin=NULL;
	return f;
}

void Ajoute(file* f, int sommet, char* chemin, int profondeur){
	if(f->debut==NULL){//si y'a rien dans la file
		cell* c=malloc(sizeof(*c));
		c->sommet=sommet;
		c->chemin=malloc(sizeof(char)*strlen(chemin));
		strcpy(c->chemin, chemin);
		c->profondeur=profondeur;
		c->suiv=NULL;
		f->debut=c;
		f->fin=c;
	}
	else{
		cell* c=malloc(sizeof(*c));
		c->sommet=sommet;
		c->chemin=malloc(sizeof(char)*strlen(chemin));
		strcpy(c->chemin, chemin);
		c->profondeur=profondeur;
		c->suiv=NULL;
		f->fin->suiv=c;
		f->fin=c;
	}
}

cell* Retire(file* f){
	cell* retire=f->debut;
	f->debut=f->debut->suiv;
	//free(retire);
	return retire;
}

void Affiche(file* f){
	printf("file: \n");
	if(f->debut!=NULL){
		cell* c=f->debut;
		while(c->suiv!=NULL){
			printf("sommet:%d chemin:%s profondeur:%d ",c->sommet, c->chemin, c->profondeur);
			c=c->suiv;
		}
		printf("sommet:%d chemin:%s profondeur:%d ",c->sommet, c->chemin, c->profondeur);
	}
	else{printf("vide\n");}
}

int Taille(file* f){
	int rep=0;

	if(f->debut!=NULL){
		cell* c=f->debut;
		rep++;
		while(c->suiv!=NULL){
			rep++;
			c=c->suiv;
		}
	}
	return rep;
}
