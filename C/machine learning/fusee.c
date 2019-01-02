#include "secondary.h"

stage* initialisefusee(){
	stage* s=malloc(sizeof(*s));
	s->drymass= 0.02*2 + 0.01 + 0.04;//2 solar panels + 1 battery bank + 1 probodobodyne OKTO2
	//s->drymass=2.72 + 1.3 + 0.3;//MK3 capsule + heatshield + parachute
	//s->drymass=36;//Rockomax Jumbo-64 Fuel Tank
	s->totalmass=s->drymass;
	s->ft=NULL;
	s->under=NULL;
	return s;
}

void freefusee(stage* s){
	while(s->under!=NULL){
		stage* under=s->under;
		free(s->ft);
		free(s);
		s=under;
	}
	free(s->ft);
	free(s);
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

	//consomme tout sauf mo et ox
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

void addstage(stage* s, int nbmaxft, int* indiceft, fueltank* listft, engine e){
	//on descends au dernier étage
	while(s->under!=NULL)
		s=s->under;

	//on est au dernier stage : s->under=NULL
	stage* under=malloc(sizeof(*under));

	//calcul du nombre de fueltank, si le nombre est -1, il n'y en a pas
	int nbft=0;
	for(int i=0; i<nbmaxft; i++)
		if(indiceft[i]!=-1)
			nbft++;

	//ajout des fueltank
	under->ft=malloc(sizeof(*under->ft)*nbft);
	under->nbft=nbft;
	nbft=0;
	for (int i=0; i<nbmaxft; i++){
		if(indiceft[i]!=-1){
			under->ft[nbft]=listft[indiceft[i]];
			nbft++;
		}
	}
	under->e=e;
	under->under=NULL;
	under->totalmass=s->totalmass+stagetotalmass(under);
	under->drymass=s->totalmass+stagedrymass(under);
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
	float rep=8;
	while(s->under!=NULL){
		s=s->under;
		if(s->totalmass==s->drymass)
			rep=0;
		float stagetwr= s->e.thrust / (s->totalmass*9.81);
		if(stagetwr<rep)
			rep=stagetwr;
	}
	return rep;
}

float scoretwr(stage* s){
	//tout ce qu'est au dessus du softmax n'est pas pénalisant mais n'est pas récompensé non plu
	//tout ce qu'est au dessus du hardmax est pénalisé
	float softmax=1, hardmax=5;
	float twr=mintwr(s);
	if(twr>hardmax)
		twr=0;
	else if(twr>softmax)
		twr=softmax;
	return twr;
}

float scorefusee(stage* s, float moddeltav, float modcost, float modtwr){
	int cost=costfusee(s);
	float score=0;
	if(cost)//si le coût est nul, le score l'est aussi, on évite une division par 0
		score= pow(deltav(s), moddeltav) * pow(10000*scoretwr(s), modtwr) / pow(cost, modcost);
	return score;
}