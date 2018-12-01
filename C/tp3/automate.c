#include "automate.h"

automate* creer_automate(graphe* g, char* alphabet, int etat_init, int etat_final){
	automate* a=malloc(sizeof(*a));
	a->g=g;
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
	printf("Mots acceptés largeur:\n");
	file* f=Initialise();
	Ajoute(f,a->etat_init, "", 0);

	while(Taille(f)){//tant que la file n'est pas vide
		cell* c=Retire(f);

		if(c->sommet==a->etat_final){//affichage des mots acceptés
			printf("\"%s\"\n", c->chemin);
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
		free(c);
	}
}

void profondeur_recursif(automate* a, pile* p, int max){
	cell* c=Retirep(p);

	if(c->sommet==a->etat_final){//affichage des mots acceptés
		printf("\"%s\"\n", c->chemin);
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
	free(c);
}

void profondeur(automate* a, int max){
	pile* p=Initialisep();
	Ajoutep(p,a->etat_init, "", 0);
	printf("Mots acceptés profondeur:\n");
	profondeur_recursif(a,p,max);
}

automate* lire_automate(FILE* fich){
	int taillemax=1000;
	char ligne[taillemax];

	graphe* g=lire_graphe(fich);

	char alphabet[taillemax];
	fgets(alphabet,taillemax,fich);
	alphabet[strlen(alphabet)-1]='\0';

	fgets(ligne,taillemax,fich);
	int etat_init=atoi(ligne);
	fgets(ligne,taillemax,fich);
	int etat_final=atoi(ligne);

	automate* a=creer_automate(g,alphabet,etat_init,etat_final);
	return a;
}

void ecrire_automate(automate* a, FILE* fich){
	int taillemax=1000;

	ecrire_graphe(a->g,fich);

	fputs(a->alphabet,fich);
	fputc('\n',fich);

	char etat_init[taillemax];
	sprintf(etat_init,"%d",a->etat_init);
	fputs(etat_init,fich);
	fputc('\n',fich);

	char etat_final[taillemax];
	sprintf(etat_final,"%d",a->etat_final);
	fputs(etat_final,fich);
}

void afficher_automate(automate* a){
	printf("automate:\nalphabet=%s\nétat initial=%d\nétat final=%d\n\n",a->alphabet,a->etat_init,a->etat_final);
	afficher(a->g);
	printf("\n");
}

int main(int argc, char* argv[]){
	if(argc==2){

		FILE* lect=NULL;
		lect=fopen(argv[1],"r");

		if(lect!=NULL){//si le fichier existe
			automate* a=lire_automate(lect);
			fclose(lect);

			menu(a);

			printf("Emplacement et nom du fichier de sauvegarde :");
			char s[100];
			fpurge(stdin);
			scanf("%s",s);
			FILE* ecr;
			ecr=fopen(s,"w+");
			ecrire_automate(a,ecr);
			fclose(ecr);
		}
		else{ printf("Le fichier n'existe pas\n"); }
	}
	else{
		printf("Usage: %s <fichier de l'automate>",argv[0]);
	}
	
	return 0;
}