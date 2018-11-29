#include "graphe.h"

void remplir(graphe* g){
	ajouter_arc(g,'b',0,0);
	ajouter_arc(g,'a',0,1);
	ajouter_arc(g,'a',1,1);
	ajouter_arc(g,'b',1,2);
	ajouter_arc(g,'a',2,1);
	ajouter_arc(g,'b',2,3);
	ajouter_arc(g,'a',3,1);
	ajouter_arc(g,'b',3,0);
}

graphe* creer_graphe(int nb){
	graphe* g=malloc(sizeof(*g));
	g->nbs=nb;
	g->adj=malloc(sizeof(*(g->adj))*nb);
	for(int i=0; i<nb; i++){
		g->adj[i]=NULL;
	}
	return g;
}

void ajouter_arc(graphe* g, char etiq, int debut, int fin){
	arc* a=malloc(sizeof(*a));
	a->etiq=etiq;
	a->voisin=fin;
	a->suiv=g->adj[debut];
	g->adj[debut]=a;
}

void retirer_arc(graphe* g, char l, int debut, int fin){
	int done=0;
	arc* a=g->adj[debut];
	while(a->suiv!=NULL && !done){
		if(a->suiv->etiq==l && a->suiv->voisin==fin){
			arc* temp=a->suiv;
			a->suiv=a->suiv->suiv;
			free(temp);
			done=1;
		}
		a=a->suiv;
	}
}

int arc_existe(graphe* g, char l, int debut, int fin){
	int rep=0;
	arc* a=g->adj[debut];
	while(a!=NULL){
		if(a->etiq==l && a->voisin==fin){
			rep=1;
		}
		a=a->suiv;
	}
	return rep;
}

int transiter(graphe* g, char l, int debut){
	int rep=-1;

	if(g->adj[debut]!=NULL){

		arc* a=g->adj[debut];

		while(a->suiv!=NULL){
			if(a->etiq==l){
				rep=a->voisin;
			}
			a=a->suiv;
		}

		if(a->etiq==l){
			rep=a->voisin;
		}
	}
	return rep;
}

void afficher(graphe* g){
	printf("graphe: \n");
	for(int i=0; i<g->nbs; i++){
		printf("%d -> ", i);
		if(g->adj[i]!=NULL){
			arc* a=g->adj[i];
			while(a->suiv!=NULL){
				printf("%d:%c ", a->voisin, a->etiq);
				a=a->suiv;
			}
			printf("%d:%c ", a->voisin, a->etiq);
		}
		printf("\n");
	}
}