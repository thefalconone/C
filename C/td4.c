#include <stdio.h>
#include <stdlib.h>

typedef struct cell{
	int v;
	struct cell *suiv;
}*cell;

typedef struct file{
	struct cell *debut;
	struct cell *fin;
}*file;

file Initialise(){
	file f=malloc(sizeof(struct file));
	f->debut=NULL;
	f->fin=NULL;
	return f;
}

void Ajoute(file f, int a){
	if(f->debut==NULL){//si y'a rien dans la file
		cell c=malloc(sizeof(struct cell));
		c->v=a;
		c->suiv=NULL;
		f->debut=c;
		f->fin=c;
	}
	else{
		cell c=malloc(sizeof(struct cell));
		c->v=a;
		c->suiv=NULL;
		f->fin->suiv=c;
		f->fin=c;
	}
}

void Retire(file f){
	cell retire=malloc(sizeof(struct cell));
	retire=f->debut;
	f->debut=f->debut->suiv;
	free(retire);
}

void Affiche(file f){
	printf("file :");

	cell c=malloc(sizeof(struct cell));
	c=f->debut;
	printf(" %d",c->v);

	while(c->suiv!=NULL){
		c=c->suiv;
		printf(" %d",c->v);
	}

	printf("\n");
}

int Taille(file f){
	int rep=0;

	if(f->debut!=NULL){
		cell c=malloc(sizeof(struct cell));
		c=f->debut;
		rep++;
		while(c->suiv!=NULL){
			rep++;
			c=c->suiv;
		}
	}
	return rep;
}

/*
int isEmpty(cell f){
	return f->suiv==NULL;
}
*/

int main(void){
	file f=Initialise();
	printf("%d\n", Taille(f));

	Ajoute(f,3);
	Affiche(f);
	printf("%d\n", Taille(f));

	Ajoute(f,5);
	Affiche(f);
	printf("%d\n", Taille(f));

	Retire(f);
	Affiche(f);
	printf("%d\n", Taille(f));

	return 0;
}