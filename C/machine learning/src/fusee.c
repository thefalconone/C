#include "../inc/fusee.h"
#include <stdlib.h>
#include <math.h>

extern int nbmaxft, mindv, maxdv, mincost, maxcost;
extern float moddeltav, modcost, modtwr, payload, minusertwr, maxusertwr;

stage* initialisefusee(){
	stage* s=malloc(sizeof(*s));
	s->drymass=payload;
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

void addstage(stage* s, int* indiceft, fueltank* listft, engine e){
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

	//affectation de divers paramètres
	under->e=e;
	under->under=NULL;
	under->totalmass=s->totalmass+stagetotalmass(under);
	under->drymass=s->totalmass+stagedrymass(under);
	s->under=under;
}

float deltav(stage* s){//s=toute le fusee
	float deltav=0;

	//au cas ou la fusee soit vide
	if(s->under!=NULL){
		//pour eviter le premier étage c'est à dire le payload
		s=s->under;
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

//calcul du twr minimum sur tous les étages d'une fusée
float minfuseetwr(stage* s){
	float rep=10000;
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

//calcul du twr maximum sur tous les étages d'une fusée
float maxfuseetwr(stage* s){
	float rep=0;
	while(s->under!=NULL){
		s=s->under;
		if(s->totalmass!=s->drymass){
			float stagetwr= s->e.thrust / (s->drymass*9.81);
			if(stagetwr>rep)
				rep=stagetwr;
		}
	}
	return rep;
}

float scorefusee(stage* s){
	int cost=costfusee(s);
	float dv=deltav(s), minftwr=minfuseetwr(s);
	float score=0;

	if(cost)//si le coût est nul, le score l'est aussi, on évite une division par 0
		score= pow(dv, moddeltav) * pow(10000*minftwr, modtwr) / pow(cost, modcost);

	if(dv){
		if(dv<mindv)
			score *= 0.1*dv/mindv;
		if(maxdv!=-1 && dv>maxdv)//on a dépassé le max
			score *= 0.1*maxdv/dv;
	}

	float maxftwr=maxfuseetwr(s);
	if(minftwr!=0 && minftwr<minusertwr)
		score *= 0.1*minftwr/minusertwr;
	if(maxftwr!=0 && maxusertwr!=-1 && maxftwr>maxusertwr)
		score *= 0.1*maxusertwr/maxftwr;

	if(cost<mincost)
		score *= 0.1*cost/mincost;
	if(maxcost!=-1 && cost>maxcost)
		score *= 0.1*maxcost/cost;

	return score;
}