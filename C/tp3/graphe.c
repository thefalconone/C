#include "graphe.h"

graphe* creer_graphe(int nb){
	printf("debut creergraphe\n");
	graphe* g=malloc(sizeof(*g));
	g->nbs=nb;
	g->adj=malloc(sizeof(*(g->adj))*nb);
	for(int i=0; i<nb; i++){
		g->adj[i]=NULL;
	}
	printf("fin creer\n");
	return g;
}

void ajouter_arc(graphe* g, char etiq, int debut, int fin){
	afficher(g);
	arc* a=malloc(sizeof(struct arc));
	a->etiq=etiq;
	a->voisin=fin;
	a->suiv=g->adj[debut];
	g->adj[debut]=a;
	//printf("%d %c\n", g->adj[debut]->voisin, g->adj[debut]->etiq);
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
	arc* a=g->adj[debut];
	while(a!=NULL){
		if(a->etiq==l){
			rep=a->voisin;
		}
		a=a->suiv;
	}
	return rep;
}

void afficher(graphe* g){
	printf("graphe: g->nbs:%d\n",g->nbs);
	char s[1000];
	scanf("%s",s);
	int i;
	for(i=0; i<g->nbs; i++){
		printf("%d -> ", i);
		arc* a=g->adj[i];
		while(a!=NULL || printf("j")){
			printf("%d:%c ", a->voisin, a->etiq);
			a=a->suiv;
		}
		printf("\n");
	}
	printf("fin affichage");
}
