#include "automate.h"

automate* creer_automate(char* alphabet, int etat_init, int etat_final){
	automate* a=malloc(sizeof(*a));
	a->g=creer_graphe(4);
	remplir(a->g);
	a->alphabet=malloc(sizeof(char)*strlen(alphabet));
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

char* concat(char *s1, char *s2){//concatene 2 strings
    char *rep = malloc(strlen(s1) + strlen(s2) + 1);//+1 pour le \0
    strcpy(rep, s1);
    strcat(rep, s2);
    return rep;
}

void largeur(automate* a, int max){
	printf("mots acceptés largeur:\n");
	file* f=Initialise();
	Ajoute(f,a->etat_init, "", a->etat_init);

	while(Taille(f)){//tant que la file n'est pas vide
		cell* c=Retire(f);

		if(c->sommet==a->etat_final){//affichage des mots acceptés
			printf("%s\n", c->chemin);
		}

		if(c->profondeur<max){
			for(int i=0; i<strlen(a->alphabet); i++){//tout l'alphabet

				char lettre[2];
				lettre[0]=a->alphabet[i];
				lettre[1]='\0';

				int potentielvoisin=transiter(a->g,lettre[0],c->sommet);

				if(potentielvoisin!=-1){//si le voisin existe, on l'ajoute à la liste
					Ajoute(f,potentielvoisin, concat(c->chemin,lettre), c->profondeur+1);
				}
			}
		}
	}
}

void profondeur_recursif(automate* a, pile* p, int max){
	cell* c=Retirep(p);

	if(c->sommet==a->etat_final){//affichage des mots acceptés
		printf("%s\n", c->chemin);
	}

	if(c->profondeur<max){
		for(int i=0; i<strlen(a->alphabet); i++){//tout l'alphabet

			char lettre[2];
			lettre[0]=a->alphabet[i];
			lettre[1]='\0';

			int potentielvoisin=transiter(a->g,lettre[0],c->sommet);

			if(potentielvoisin!=-1){//si le voisin existe, on l'ajoute à la liste
				Ajoutep(p,potentielvoisin, concat(c->chemin,lettre), c->profondeur+1);
				profondeur_recursif(a,p,max);
			}
		}
	}
}

void profondeur(automate* a, int max){
	pile* p=Initialisep();
	Ajoutep(p,a->etat_init, "", a->etat_init);
	printf("mots acceptés profondeur:\n");
	profondeur_recursif(a,p,max);
}

/*	affiche si un mot est accepté
		automate* a=creer_automate(0,3);
		printf("mot accepte : %d\n", accepte(a,argv[1]));
*/
int main(int argc, char* argv[]){
	if(argc==3){
		automate* a=creer_automate(argv[1],0,3);
		afficher(a->g);
		largeur(a,atoi(argv[2]));
		profondeur(a,atoi(argv[2]));
	}
	else{ printf("il n'y a pas le mot en paramètre\n"); }
	
	return 0;
}
