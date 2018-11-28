#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc==3){
		printf("%s %s %s\n",argv[0],argv[1],argv[2]);
	}
	else{
		printf("il n'y a pas 3 paramètres\n");
	}
	return 0;
}