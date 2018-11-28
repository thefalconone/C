#include "automate.h"

graphe* remplir(){
	printf("debut remplir graphe\n");
	graphe* g=creer_graphe(4);;
	afficher(g);
	printf("graphe crée\n");
	ajouter_arc(g,'b',0,0);
	ajouter_arc(g,'a',0,1);
	ajouter_arc(g,'a',1,1);
	ajouter_arc(g,'b',1,2);
	ajouter_arc(g,'a',2,1);
	ajouter_arc(g,'b',2,3);
	ajouter_arc(g,'a',3,1);
	ajouter_arc(g,'b',3,0);
	putc('a', stdout);
	//printf("afficher");
	//afficher(g);
	printf("return");
	return g;
}

automate* creer_automate(char* alphabet, int etat_init, int etat_final){
	automate* a=malloc(sizeof(*a));
	a->g=remplir();
	printf("malloc alpha");
	a->alphabet=malloc(sizeof(strlen(alphabet)));
	printf("strcpy");
	strcpy(a->alphabet,alphabet);
	a->etat_init=etat_init;
	a->etat_final=etat_final;
	return a;
}

int accepte(automate* a, char* mot){
	int l=strlen(mot);
	int etat=a->etat_init;
	for(int i=0; i<l; i++){
		etat=transiter(a->g,mot[i],etat);
		if(etat==-1){
			return 0;
		}
	}
	if(etat!=a->etat_final){
		return 0;
	}
	return 1;
}

void l(automate* a, int max){
	printf("initialise");
	file* f=Initialise();
	printf("ajoute debut");
	Ajoute(f,a->etat_init, "", 0);
	printf("while taille");
	while(Taille(f)){//tant que la file n'est pas vide
		printf("retire");
		cell* c=Retire(f);
		printf("avant");
		if(c->sommet==a->etat_final){
			printf("%s", c->chemin);
		}
		if(c->profondeur<max){
			for(int i=0; i<strlen(a->alphabet); i++){//tout l'alphabet
				char lettre[2];
				lettre[0]=a->alphabet[i];
				lettre[1]='\0';
				int potentielvoisin=transiter(a->g,lettre[0],c->sommet);
				if(potentielvoisin!=-1){
					Ajoute(f,potentielvoisin, strcat(c->chemin,lettre), c->profondeur+1);
				}
			}
		}
	}
}

/*	affiche si un mot est accepté
		automate* a=creer_automate(0,3);
		printf("mot accepte : %d\n", accepte(a,argv[1]));
*/

int main(int argc, char* argv[]){
	if(argc==2){
		automate* a=creer_automate(argv[1],0,3);
		printf("avant appel");
		l(a,4);
	}
	else{ printf("il n'y a pas le mot en paramètre\n"); }
	
	return 0;
}
