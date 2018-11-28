#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 30

int EcritFichier(FILE* fich_lect, char* nom_fich_ecrit, int nb_lignes){
	int erreur_f=0;
	FILE* f_creer=NULL;
	f_creer=fopen(nom_fich_ecrit,"w+");//créé le fichier et supprime si il existe déjà

	if(f_creer==NULL){
		printf("Impossible de créér temp.txt\n");
		erreur_f=2;
	}
	else{
		char chaine[TAILLE_MAX]="";
		char* err=malloc(sizeof(char)*10);

		for(int i=0; i<nb_lignes && err!=NULL; i++){

			err=fgets(chaine, TAILLE_MAX, fich_lect);
			fputs(chaine, f_creer);
		}

		if(err==NULL){
			printf("Impossible de lire l.txt\n");
			erreur_f=1;
		}
	}
	return erreur_f;
}

int main(int argc, char* argv[]){
	if(argc==3){

		FILE* f=NULL;
		f=fopen(argv[1],"r");

		if(f==NULL){
			printf("Impossible d'ouvrir l.txt\n");
		}
		else{
			printf("code erreur:%d\n", EcritFichier(f,argv[2],5));
		}

		fclose(f);
	}
	else{
		printf("il n'y a pas les 2 paramètres\n");
	}

	return 0;
}