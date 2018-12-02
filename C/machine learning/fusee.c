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

float stagetotalmass(stage* s){
	float rep= s->e.mass + 0.005*(s->e.lf+s->e.ox) + 0.0075*s->e.sf;
	for(int i=0; i<s->nbft; i++){
		rep+= s->ft[i].drymass + 0.005*(s->ft[i].lf+s->ft[i].ox) + 0.004*s->ft[i].mo;
	}
	return rep;
}

float stagedrymass(stage* s){
	float rep= s->e.mass;
	for(int i=0; i<s->nbft; i++){
		rep+= s->ft[i].drymass;
	}
	return rep;
}

int stagecost(stage* s){
	int rep= s->e.cost;
	for(int i=0; i<s->nbft; i++){
		rep+= s->ft[i].cost;
	}
	return rep;
}

int stagelf(stage* s){
	int rep=s->e.lf;
	for(int i=0; i<s->nbft; i++){
		rep+=s->ft[i].lf;
	}
	return rep;
}

int stageox(stage* s){
	int rep=s->e.ox;
	for(int i=0; i<s->nbft; i++){
		rep+=s->ft[i].ox;
	}
	return rep;
}

int stagemo(stage* s){
	int rep=0;
	for(int i=0; i<s->nbft; i++){
		rep+=s->ft[i].mo;
	}
	return rep;
}

int stagesf(stage* s){
	int rep=s->e.sf;
	return rep;
}

void affichereng(engine e){
	printf("\nengine: nom: %s mass: %.3f thrust: %d isp: %d cost: %d",e.name, e.mass, e.thrust, e.isp, e.cost);
	if(e.lf){ printf(" lf: %d", e.lf); }
	if(e.sf){ printf(" lf: %d", e.sf); }
	if(e.ox){ printf(" lf: %d", e.ox); }
	printf("\n");
}

void afficherft(fueltank ft){
	printf("\nfuel tank: nom: %s mass: %.3f cost: %d lf: %d ox: %d mo: %d\n",ft.name, ft.drymass, ft.cost, ft.lf, ft.ox, ft.mo);
}

void afficherstage(stage* s){
	for(int i=0; i<s->nbft; i++){
		afficherft(s->ft[i]);
	}
	affichereng(s->e);
}

void afficherfusee(stage* s){
	while(s->under!=NULL){
		afficherstage(s);
		s=s->under;
	}
	afficherstage(s);
}

void addstage(stage* s, int nbft, fueltank* ft, engine e){
	float totalmass=0;
	while(s->under!=NULL){
		totalmass += s->totalmass;
		s=s->under;
	}
	//on est au dernier stage : s->under=NULL
	stage* under=malloc(sizeof(*under));
	under->nbft=nbft;
	under->ft=malloc(sizeof(ft)*nbft);
	under->ft=ft;
	under->e=e;
	under->totalmass=s->totalmass+stagetotalmass(under);
	under->drymass=s->drymass+stagedrymass(under);
	s->under=under;
}