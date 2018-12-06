#include "secondary.h"
#include <time.h>

#define nbmaxft 5
#define nbmaxstages 5
//nbpop tjrs pair (à cause du cross-over)
#define nbpop 100

#define moddeltav 4
#define modcost 0.5
#define modtwr 2

void quicksort(float** number,int first,int last){
	int i, j, pivot;
	float* temp;

	if(first<last){
		pivot=first;
		i=first;
		j=last;

		while(i<j){
			while(number[i][1]<=number[pivot][1] && i<last)
			i++;
			while(number[j][1]>number[pivot][1])
			j--;
			if(i<j){
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}

		temp=number[pivot];
		number[pivot]=number[j];
		number[j]=temp;
		quicksort(number,first,j-1);
		quicksort(number,j+1,last);

	}
}

//il y a 41 fuel tanks et 24 engines
genestage* initialisegenestage(){

	genestage* s=malloc(sizeof(*s));

	s->ft=malloc(sizeof(&s->ft)*nbmaxft);
	for(int i=0; i<nbmaxft; i++){

		if(!(rand()%3)){//0 1 ou 2 donc 2chances/3
			s->ft[i]=rand()%40;
		}
		else{
			s->ft[i]=-1;//no ft
		}

	}
	s->e=rand()%23;
	return s;
}

gene* initialisegene(){
	gene* g=malloc(sizeof(*g));//malloc car*

	g->s=malloc(sizeof(&g->s)*nbmaxstages);

	for(int i=0; i<nbmaxstages; i++){
		g->s[i]=initialisegenestage();
	}

	return g;
}

stage** initialisepopfusee(){
	stage** pop=malloc(sizeof(*pop)*nbpop);
	for(int i=0; i<nbpop; i++){
		pop[i]=initialisefusee();
	}
	return pop;
}

gene** initialisepopgenes(){
	gene** genespop=malloc(sizeof(*genespop)*nbpop);
	for(int i=0; i<nbpop; i++){
		genespop[i]=initialisegene();
	}
	return genespop;
}

void construire(fueltank* listft, engine* listeng, stage** pop, gene** genespop){
	for(int i=0; i<nbpop; i++){//i=individu
		pop[i]=initialisefusee();
		for(int j=0; j<nbmaxstages; j++){//j=un stage

			//creation du ft d'un individu
			fueltank* geneft=malloc(sizeof(*geneft)*nbmaxft);
			int nbftgene=0;

			for(int k=0; k<nbmaxft; k++){//k=un fueltank
				//si il y a un fuel tank et pas rien
				if(genespop[i]->s[j]->ft[k]!=-1){
					geneft[nbftgene] = listft[ genespop[i]->s[j]->ft[k] ] ;
					nbftgene++;
				}
			}
			addstage(pop[i], nbftgene, geneft, listeng[ genespop[i]->s[j]->e ] );
		}
	}
}

void affichage(stage** pop, float** scores, int usercontinue){
	//calcul de la moyenne
	float scoremoy;
	for(int i=0; i<nbpop; i++){
		scoremoy+=scores[i][1];
	}
	scoremoy/=nbpop;

	if(!usercontinue){
		afficherfusee(pop[nbpop-1]);
		printf("La fusée gagne avec un score de %.0f\n%.0fΔv	%d$	minTWR:%.3f\n", scores[nbpop-1][1], deltav(pop[nbpop-1]), costfusee(pop[nbpop-1]), mintwr(pop[nbpop-1]));
	}
	printf("meilleur: %.0f		moyenne: %.0f\n",scores[nbpop-1][1], scoremoy);
}

float** remplirscores(stage** pop){
	float** scores=malloc(sizeof(*scores)*nbpop);
	for(int i=0; i<nbpop; i++){
		scores[i]=malloc(sizeof(*scores[i])*2);//pour indice et score correspondant
		scores[i][0]=i;
		scores[i][1]=scorefusee(pop[i], moddeltav, modcost, modtwr);
	}
	return scores;
}

int* appareillage(){
	int* appareilles=malloc(sizeof(*appareilles)*nbpop/4);
	for(int i=0; i<nbpop/4; i++){
		appareilles[i]=-1;
	}
	//on crée un tableau qui va associer les nbpop/4 premiers (random) avec les nbpop/4 (restants dans l'ordre) car on a tué la moitié
	for(int i=nbpop/4; i>0; i--){
		//je me déplace un nb random (entre 0 et iterations-1)de fois dans le tableau
		int deplac=rand()%i, decal=0;
		for(int j=0; j<=deplac; j++){
			if(appareilles[j+decal]!=-1){
				decal++;
			}
		}
		while(appareilles[deplac+decal]!=-1){
			decal++;
		}
		appareilles[deplac+decal]=i-1;
	}
	return appareilles;
}

void reproduire(gene** genespop, stage** pop, int usercontinue){

	//SELECTION
	float** scores=remplirscores(pop);
	quicksort(scores,0,nbpop-1);
	affichage(pop, scores, usercontinue);

	//les pires 5 sont remplacés par les meilleurs 5
	int* vivants=malloc(sizeof(*vivants)*nbpop/2);
	int nbtues=0;
	while(nbtues<50){
		int indice=rand()%nbpop;//entre 0 et 99
		char existe=0;
		for(int i=0; i<nbtues; i++){
			if(vivants[i]==indice){ existe=1; }
		}
		if(!existe){
			//0=nul=0% chance de vivre
			//99=meilleur=99% chance de vivre
			if(rand()%nbpop < indice){//plus l'indice est grand, plus c'est dur de le tuer
				vivants[nbtues]=indice;
				nbtues++;
			}
		}
	}

	//MUTATION
	for(int i=0; i<5; i++){//seul 5 fusées mutent
		int indice=vivants[rand()%(nbpop/2)];
		for(int j=0; j<nbmaxstages; j++){

			for(int k=0; k<nbmaxft; k++){
				if(!(rand()%11)){
					genespop[indice]->s[j]->ft[k]=rand()%40;
				}
				else if((!rand()%41)){
					genespop[indice]->s[j]->ft[k]=-1;
				}
			}
			
			if(!(rand()%11)){
				genespop[indice]->s[j]->e=rand()%23;
			}

		}
	}

	//CROSS-OVER
	//creation d'un tableau de nbpop/2 randoms
	int* appareilles=appareillage();
	gene** newgenespop=initialisepopgenes();

	for(int e=0; e<4; e++){
		for(int i=0; i<nbpop/4; i++){
			int coupe=rand()%nbmaxstages;//on sépare le génome en 2
			//première partie
			for(int j=0; j<coupe; j++){
				newgenespop[i+e*nbpop/4]->s[j]=genespop[i]->s[j];
			}
			for(int j=coupe; j<nbmaxstages; j++){
				newgenespop[i+e*nbpop/4]->s[j]=genespop[appareilles[i]]->s[j];
			}
		}
	}
	genespop=newgenespop;
}

void genetic(fueltank* listft, engine* listeng){

	time_t t;
	srand((unsigned) time(&t));

	stage** pop=initialisepopfusee();
	gene** genespop=initialisepopgenes();

	int usercontinue=1;//nb de genrations à calculer avant d'afficher le resultat
	while(usercontinue!=0){//pour avancer d'une génération à la fois
		usercontinue--;

		//construire la nouvelle génération et reset la precedente
		construire(listft, listeng, pop, genespop);

		//evaluer la génération
		//la faire reproduire
		//le meilleur partage ses gènes par bloc de stage
		reproduire(genespop, pop, usercontinue);

		if(!usercontinue){//tant qu'il est pas égal à 0
			printf("Continuer combien de fois?\n");
			fpurge(stdin);
			scanf("%d",&usercontinue);
			system("clear");
		}
	}
}

/*

	if(!usercontinue){
		afficherfusee(pop[indicebest]);
		printf("La fusée %d gagne avec un score de %.0f\n%.0fΔv	%d$	minTWR:%.3f\nLa moyenne est de %.0f\n", indicebest, bestscore, deltav(pop[indicebest]), costfusee(pop[indicebest]), mintwr(pop[indicebest]), scoremoy);
	}
	printf("%.0f\n",scoremoy);

*/