#include "secondary.h"

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
	for(int i=0; i<s->nbft; i++)
		rep+= s->ft[i].drymass + 0.005*(s->ft[i].lf+s->ft[i].ox) + 0.004*s->ft[i].mo;
	return rep;
}

//calcul de la consommation de carburant
float stagedrymass(stage* s){
	float rep= s->e.mass;//engine drymass

	//consomme tout sauf mo
	if(s->e.type==liquid)
		for(int i=0; i<s->nbft; i++)
			rep+= s->ft[i].drymass + 0.004*s->ft[i].mo;

	//consomme rien
	else if(s->e.type==solid)
		for(int i=0; i<s->nbft; i++)
			rep+= s->ft[i].drymass + 0.005*(s->ft[i].lf+s->ft[i].ox) + 0.004*s->ft[i].mo;

	//consomme tout sauf mo, ox
	else if(s->e.type==nuclear)
		for(int i=0; i<s->nbft; i++)
			rep+= s->ft[i].drymass + 0.005*s->ft[i].ox + 0.004*s->ft[i].mo;

	//monoprop, consomme tout sauf monoprop
	else
		for(int i=0; i<s->nbft; i++)
			rep+= s->ft[i].drymass + 0.005*(s->ft[i].lf+s->ft[i].ox);

	return rep;
}

int stagecost(stage* s){
	int rep= s->e.cost;
	for(int i=0; i<s->nbft; i++)
		rep+= s->ft[i].cost;
	return rep;
}

int stagelf(stage* s){
	int rep=s->e.lf;
	for(int i=0; i<s->nbft; i++)
		rep+=s->ft[i].lf;
	return rep;
}

int stageox(stage* s){
	int rep=s->e.ox;
	for(int i=0; i<s->nbft; i++)
		rep+=s->ft[i].ox;
	return rep;
}

int stagemo(stage* s){
	int rep=0;
	for(int i=0; i<s->nbft; i++)
		rep+=s->ft[i].mo;
	return rep;
}

int stagesf(stage* s){
	int rep=s->e.sf;
	return rep;
}

void affichereng(engine e){
	printf("engine: %s\n", e.name);
	if(e.type==liquid)
		printf("Liquid");
	else if(e.type==solid)
		printf("Solid");
	else if(e.type==monoprop)
		printf("Monop");
	else
		printf("Nuclear");

	printf("	%.3ft	%dkN	%ds	%d$", e.mass, e.thrust, e.isp, e.cost);
	if(e.lf)
		printf("	%dlf", e.lf); 
	if(e.sf)
		printf("	%dsf", e.sf); 
	if(e.ox)
		printf("	%dox", e.ox); 
	printf("\n");
}

void afficherft(fueltank ft){
	printf("fuel tank: %s\n%.3ft	%dlf	%dox	%dmo	%d$\n",ft.name, ft.drymass, ft.lf, ft.ox, ft.mo, ft.cost);
}

void afficherstage(stage* s){
	for(int i=0; i<s->nbft; i++)
		afficherft(s->ft[i]);
	affichereng(s->e);
	printf("\n");
}

void afficherfusee(stage* s){
	if(s->under!=NULL){//au cas ou la fusee soit vide
		printf("\nfusee:\n\n");
		s=s->under;
		afficherstage(s);
		while(s->under!=NULL){
			s=s->under;
			afficherstage(s);
		}
	}
}

void addstage(stage* s, int nbmaxstages, int* indiceft, fueltank* listft, engine e){
	float totalmass=0;
	totalmass += s->totalmass;
	while(s->under!=NULL){
		totalmass += s->totalmass;
		s=s->under;
	}
	//on est au dernier stage : s->under=NULL
	stage* under=malloc(sizeof(*under));

	int vraift=0;
	for(int i=0; i<nbmaxstages; i++)
		if(indiceft[i]!=-1)
			vraift++;
	under->ft=malloc(sizeof(*under->ft)*vraift);
	under->nbft=vraift;
	vraift=0;
	for (int i=0; i<nbmaxstages; i++){
		if(indiceft[i]!=-1){
			under->ft[vraift]=listft[indiceft[i]];
			vraift++;
		}
	}
	under->e=e;
	under->under=NULL;
	under->totalmass=s->totalmass+stagetotalmass(under);
	under->drymass=s->totalmass+stagedrymass(under);
	s->under=malloc(sizeof(stage*));
	s->under=under;
}

float deltav(stage* s){//s=toute le fusee
	float deltav=0;
	if(s->under!=NULL){//au cas ou la fusee soit vide
		s=s->under;//pour eviter le command pod
		deltav= log(s->totalmass/s->drymass) * s->e.isp * 9.81;
		while(s->under!=NULL){
			s=s->under;
			deltav+= log(s->totalmass/s->drymass) * s->e.isp * 9.81;
		}
	}
	return deltav;
}

int costfusee(stage* s){
	int rep=0;//le satellite est gratuit
	while(s->under!=NULL){
		s=s->under;
		rep+=stagecost(s);
	}
	return rep;
}

float mintwr(stage* s){
	float rep=5;//tout ce qu'est au dessus de 5 n'est pas necessaire
	while(s->under!=NULL){
		s=s->under;
		float stagetwr= s->e.thrust / (s->totalmass*9.81);
		if(stagetwr<rep)
			rep=stagetwr;
	}
	//au dela de 5 on perds
	if(rep==5) rep=0;
	return rep;
}

float scorefusee(stage* s, float moddeltav, float modcost, float modtwr){
	//return moddeltav*deltav(s) - modcost*costfusee(s) + 1000*modtwr*mintwr(s);
	return 1000*mintwr(s)*deltav(s)/costfusee(s);
	//return pow(moddeltav*deltav(s), 2) - pow(modcost*costfusee(s), 2) - pow(1000*modtwr-1000*modtwr*mintwr(s), 2);
}