#include <stdio.h>

void permute(int *a, int *b){
	int echange=*a;
	echange=*a;
	*a=*b;
	*b=echange;
}

int main(void){
	int a=5,b=2;
	printf("%d,%d\n",a,b);
	permute(&a,&b);
	printf("%d,%d\n",a,b);
	return 0;
}