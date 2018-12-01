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
	if(debut<g->nbs && g->adj[debut]!=NULL){//si il y a au moins un arc
		int done=0;
		arc* a=g->adj[debut];
		if(a->suiv!=NULL){//si il y a au moins 2 arcs
			while(!done && a->suiv->suiv!=NULL){//tant qu'on est pas à l'avant dernier
				if(a->suiv->etiq==l && a->suiv->voisin==fin){//si l'arc suivant est le bon arc
					arc* temp=a->suiv;
					a->suiv=a->suiv->suiv;
					free(temp);
					done=1;
				}
				a=a->suiv;
			}
			//on est à l'avant dernier
			if(a->suiv->etiq==l && a->suiv->voisin==fin){//si le dernier est le bon
				arc* temp=a->suiv;
				a->suiv=NULL;
				free(temp);
				done=1;
			}
			if(g->adj[debut]->etiq==l && g->adj[debut]->voisin==fin){//si le bon arc était le premier
				arc* temp=g->adj[debut];
				g->adj[debut]=g->adj[debut]->suiv;
				free(temp);
			}
		}
		else{//si il n'y a qu'un arc
			if(a->etiq==l && a->voisin==fin){//et que c'est le bon
				g->adj[debut]=NULL;
				free(a);
			}
		}
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

graphe* lire_graphe(FILE* fich){
	int taillemax=1000;
	char ligne[taillemax];

	//première ligne: nb de sommets
	fgets(ligne,taillemax,fich);
	int nbsommets=atoi(ligne);
	graphe* g=creer_graphe(nbsommets);

	for(int i=0; i<nbsommets; i++){//parcours des sommets
		fgets(ligne,taillemax,fich);
		int nbarcs=strlen(ligne);
		for(int j=0; j<nbarcs/2; j++){//parcours des arcs
			ajouter_arc(g, ligne[j*2+1], i, ligne[j*2]-48);
		}
	}
	return g;
}

void ecrire_graphe(graphe* g, FILE* fich){
	//première ligne: nb de sommets
	fputc(g->nbs+48,fich);
	fputc('\n',fich);

	for(int i=0; i<g->nbs; i++){//parcours des arcs
		if(g->adj[i]!=NULL){
			arc* a=g->adj[i];
			while(a->suiv!=NULL){
				fputc(a->voisin+48, fich);
				fputc(a->etiq, fich);
				a=a->suiv;
			}
			fputc(a->voisin+48, fich);
			fputc(a->etiq, fich);
		}
		fputc('\n',fich);
	}
}