#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct S1 {
	int a;
	char *ch;
};

struct S2 {
	int a;
	char ch[40];
};

int main(void){
	struct S1 v11, v12;
	struct S2 v21, v22;
	v11.a=3;
	v21.a=5;
	v11.ch=malloc(40);
	strcpy(v11.ch,"Hulk");
	strcpy(v21.ch,"Gruik");
	
	v12=v11;
	v22=v21;

	printf("v12.a=%d v12.ch=%s\n",v12.a,v12.ch);
	printf("v22.a=%d v22.ch=%s\n\n",v22.a,v22.ch);
	
	v11.a=123;
	v21.a=124;
	strcpy(v11.ch,"Kluh");
	strcpy(v21.ch,"Kiurg");
	
	printf("v12.a=%d v12.ch=%s\n",v12.a,v12.ch);
	printf("v22.a=%d v22.ch=%s\n",v22.a,v22.ch);
	return 0;
}