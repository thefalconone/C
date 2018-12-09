#include <stdio.h>
#include <stdlib.h>

void Alloue(int*** m, int x, int y){
	*m=malloc(sizeof(int*)*x);
	for(int i=0; i<x; i++){
		(*m)[i]=malloc(sizeof(int*)*y);
	}
}

void Saisie(int** m, int x, int y){
	printf("Saisir une matrice de %dx%d\n", x, y);
	for(int i=0; i<x; i++){
		for(int j=0; j<y; j++){
			scanf("%d", &m[i][j]);
		}
	}
}

void Affiche(int** m, int x, int y){
	for(int i=0; i<x; i++){
		for(int j=0; j<y; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]){
	if(argc!=3){
		printf("La taille de la matrice n'a pas été donnée en paramètre\n");
	}
	else{
		int x=atoi(argv[1]);
		int y=atoi(argv[2]);

		int** m;
		Alloue(&m,x,y);
		Saisie(m,x,y);
		Affiche(m,x,y);
	}
	return 0;
}