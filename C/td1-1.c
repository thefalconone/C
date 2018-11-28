#include <stdio.h>

void affiche(int tab[10]){
	printf("{ ");
	for(int i=0;i<10;i++){
		printf("%d ",tab[i]);
	}
	printf("}\n");
}

int main(void){
	int tab[10]={8,4,5,6,3,4,9,8,6,2};
	affiche(tab);
	
	int trie=0;//faux
	int fin=10;
	while(!trie){
		trie=1;//vrai
		fin--;
		for(int i=0;i<fin;i++){//on est sur que le tableau est trié jusqu'a fin à chaque iteration
			if(tab[i+1]<tab[i]){
				int echange=tab[i];
				tab[i]=tab[i+1];
				tab[i+1]=echange;
				trie=0;//faux
			}
		}
	}

	affiche(tab);
	return 0;
}