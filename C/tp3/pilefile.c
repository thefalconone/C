#include "automate.h"


file* Initialise(){
	file* f=malloc(sizeof(*f));
	f->debut=NULL;
	f->fin=NULL;
	return f;
}

pile* Initialisep(){
	pile* p=malloc(sizeof(*p));
	p->debut=NULL;
	return p;
}

void Ajoute(file* f, int sommet, char* chemin, int profondeur){
	if(f->debut==NULL){//si y'a rien dans la file
		cell* c=malloc(sizeof(*c));
		c->sommet=sommet;
		c->chemin=malloc(sizeof(char)*strlen(chemin)+1);
		strcpy(c->chemin, chemin);
		c->profondeur=profondeur;
		c->suiv=NULL;
		f->debut=c;
		f->fin=c;
	}
	else{
		cell* c=malloc(sizeof(*c));
		c->sommet=sommet;
		c->chemin=malloc(sizeof(char)*strlen(chemin)+1);
		strcpy(c->chemin, chemin);
		c->profondeur=profondeur;
		c->suiv=NULL;
		f->fin->suiv=c;
		f->fin=c;
	}
}

void Ajoutep(pile* p, int sommet, char* chemin, int profondeur){
	cell* c=malloc(sizeof(*c));
	c->sommet=sommet;
	c->chemin=malloc(sizeof(char)*strlen(chemin)+1);
	strcpy(c->chemin, chemin);
	c->profondeur=profondeur;

	c->suiv=p->debut;
	p->debut=c;
}

cell* Retire(file* f){
	cell* retire=f->debut;
	f->debut=f->debut->suiv;
	//free(retire);
	return retire;
}

cell* Retirep(pile* p){
	cell* retire=p->debut;
	p->debut=p->debut->suiv;
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

int Taillep(pile* p){
	int rep=0;

	if(p->debut!=NULL){
		cell* c=p->debut;
		rep++;
		while(c->suiv!=NULL){
			rep++;
			c=c->suiv;
		}
	}
	return rep;
}