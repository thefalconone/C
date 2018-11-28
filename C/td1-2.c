#include <stdio.h>

void multipliedeux(int *a){
	*a=*a << 1;
}

unsigned int ae(unsigned int a, unsigned int b){
	//F=vrai et 0=faux
	a=a & 0xFFFF0000;//on vire les octets faibles
	a=a >> 16;//2 octets vers la droite (de fort vers faible)
	b=~b;
	b=b & 0x0000FFFF;
	b=b << 16;//2 octets vers la droite (de fort vers faible)
	return a | b;
}

int bitdiff(int a, int b){
	return !(a%1024 ^ b%1024);
}

int bitcount(int a){
	int c=0;
	for(int i=0;i<sizeof(int)*8;i++){
		c+=a%2;
		a=a>>1;
	}
	return c;
}

int main(void){
	int x=45;
	multipliedeux(&x);
	printf("45x2=%d\n",x);

	unsigned int a=10;
	printf("%x\n",a);
	unsigned int b=30;
	printf("%x\n",b);
	unsigned int c=ae(a,b);
	printf("%x\n",c);

	a=1024;
	b=1023;
	printf("%x,%x\n",a,b);
	printf("faux:%d vrai:%d\n",bitdiff(a,b),bitdiff(a,a));
	printf("bitcount:%d\n",bitcount(1024));
}