#include "main.h"

stage* initialisefusee(){
	stage* s=malloc(sizeof(*s));
	//2 solar panels + 1 battery bank + 1 probodobodyne OKTO2
	s->drymass= 0.02*2 + 0.01 + 0.04;
	s->totalmass=s->drymass;
	s->ft=NULL;
	s->under=NULL;
	return s;
}

void addstage(stage* s, fueltank* ft, engine e){
	float totalmass=0;
	while(s->under!=NULL){
		totalmass += s->totalmass;
		s=s->under;
	}
	stage* under=malloc(sizeof(*under));


	s->under=under;
}