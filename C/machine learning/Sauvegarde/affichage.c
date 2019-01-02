#include "main.h"

extern int nbpop;

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
		while(s->under!=NULL){
			afficherstage(s);
			s=s->under;
		}
		afficherstage(s);
	}
}

void afficherlistft(fueltank* listft, int l){
	for(int i=0; i<l; i++)
		afficherft(listft[i]);
}

void afficherlisteng(engine* listeng, int l){
	for(int i=0; i<l; i++)
		affichereng(listeng[i]);
}

void affichagegenbest(stage** pop, float** scores, int usercontinue){
	
	//calcul de la moyenne
	float scoremoy;
	for(int i=0; i<nbpop; i++)
		scoremoy+=scores[i][1]; 
	scoremoy/=nbpop;

	if(!usercontinue){//si le compteur est à 0
		//on affiche la meilleure fusee
		int best=(int)scores[nbpop-1][0];
		afficherfusee(pop[best]);

		printf("%.0fΔv	%d$	minTWR:%.3f\n", deltav(pop[best]), costfusee(pop[best]), mintwr(pop[best]) );
	}
	//on affiche ca à  chaque génération
	printf("meilleur: %.2e		moyenne: %.2e\n",scores[nbpop-1][1], scoremoy);

}