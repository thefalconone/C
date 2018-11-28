#include "tp1-2.h"

void Affiche(char* mot){
	printf("%s\n", mot);
}

int Fact(int n){
	int res=1;
	for(int i=1; i<n; i++){
		res*=i;
	}
	return res;
}