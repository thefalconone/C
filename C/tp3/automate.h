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

void menu(automate* a);
//return 1 si le mot est accepté, 0 sinon
int accepte(automate* a, char* mot);
void largeur(automate* a, int max);
void profondeur(automate* a, int max);

typedef struct file{
	struct cell* debut;
	struct cell* fin;
}file;

typedef struct pile{
	struct cell* debut;
}pile;

file* Initialise();
pile* Initialisep();
void Ajoute(file* f, int sommet, char* chemin, int profondeur);
void Ajoutep(pile* p, int sommet, char* chemin, int profondeur);
cell* Retire(file* f);
cell* Retirep(pile* p);
void Affiche(file* f);
int Taille(file* f);
int Taillep(pile* p);