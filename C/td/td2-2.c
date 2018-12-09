#define TAILLE 10
#include <stdlib.h>

int main(void){
	char *chaine;
	chaine=malloc(sizeof(char)*TAILLE);
	int *tab;
	tab=malloc(sizeof(int)*TAILLE);
	int i;
	for(i=0;i<TAILLE-1;i++){
		tab[i]=i+1;
		chaine[i]=(char)(i+65);
	}
	chaine[TAILLE-1]=0;
	return 0;
}