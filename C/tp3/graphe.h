#include <stdio.h>
#include <stdlib.h>

typedef struct arc{
	char etiq;
	int voisin;
	struct arc* suiv;
}arc;

typedef struct graphe{
	int nbs;
	struct arc** adj;	
}graphe;

graphe* creer_graphe(int nb);
void remplir(graphe* g);
void ajouter_arc(graphe* g, char etiq, int debut, int fin);
int arc_existe(graphe* g, char l, int debut, int fin);
void retirer_arc(graphe* g, char l, int debut, int fin);
//retourne l'etat atteint à partir d'un état et une etiquette
int transiter(graphe* g, char l, int debut);
void afficher(graphe* g);
