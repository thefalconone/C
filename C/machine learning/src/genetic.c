#include "secondary.h"

extern int nbpop, nbmut, nbgen, nbmaxft, nbmaxstages;
extern float ratiokill;

//rempli la pop grâce aux gènes
void construire(fueltank* listft, engine* listeng, stage** pop, gene** genespop){
	for(int i=0; i<nbpop; i++){
		for(int j=0; j<nbmaxstages; j++){
			if(genespop[i]->s[j]->e!=-1){//engine=-1 -> stage vide
				addstage(pop[i], genespop[i]->s[j]->ft, listft, listeng[ genespop[i]->s[j]->e ] );
			}
		}
	}
}

//renvoie un tableau de scores à coté de leur indices
/*
	i=0     scores[i][0]=22 scores[i][1]=-37115
	i=1     scores[i][0]=42 scores[i][1]=-37049
	i=2     scores[i][0]=54 scores[i][1]=-36625
	i=3     scores[i][0]=32 scores[i][1]=-28772
	...		...
	i=96    scores[i][0]=18 scores[i][1]=25985
	i=97    scores[i][0]=70 scores[i][1]=26223
	i=98    scores[i][0]=82 scores[i][1]=28323
	i=99    scores[i][0]=16 scores[i][1]=36693
*/
float** remplirscorestries(stage** pop){
	float** scores=malloc(sizeof(*scores)*nbpop);
	for(int i=0; i<nbpop; i++){
		scores[i]=malloc(sizeof(*scores[i])*2);//pour indice et score correspondant
		scores[i][0]=i;
		scores[i][1]=scorefusee(pop[i]);
	}
	quicksort(scores,0,nbpop-1);
	return scores;
}

void freescores(float** scores){
	for(int i=0; i<nbpop; i++)
		free(scores[i]);
	free(scores);
}

//return un tableau de nb entiers compris entre 0 et nb-1 randomisés
int* appareillage(int nb){
	int* appareilles=malloc(sizeof(*appareilles)*nb);
	for(int i=0; i<nb; i++)
		appareilles[i]=-1; 
	//on crée un tableau qui va associer les nb (en random) avec les nb (dans l'ordre) car on a tué la moitié
	for(int i=nb; i>0; i--){
		//je me déplace un nb random (entre 0 et iterations-1)de fois dans le tableau
		int deplac=rand()%i, decal=0;
		for(int j=0; j<=deplac; j++)
			if(appareilles[j+decal]!=-1)
				decal++;

		while(appareilles[deplac+decal]!=-1)
			decal++;

		appareilles[deplac+decal]=i-1;
	}
	return appareilles;
}

//renvoie un tableau de nbpop-nbtokill avecles meilleurs indices qui ont une meilleure chance de survie
int* tue(float** scores, int nbtokill){
	int* vivants=malloc( sizeof(*vivants)*(nbpop-nbtokill) );
	int nbtues=0;
	while(nbtues<nbtokill){
		int indice=rand()%nbpop;//entre 0 et nbpop-1
		char existe=0;
		//recherche de l'existance de l'indice dans le tableau
		for(int i=0; i<nbtues; i++)
			if(vivants[i]==indice)
				existe=1;
		if(!existe){
			//0=nul=0% chance de vivre
			//99=meilleur=99% chance de vivre
			if(scores[rand()%nbpop][1] <= scores[indice][1]){//plus le score est grand, plus c'est dur de le tuer
				vivants[nbtues]=scores[indice][0];
				nbtues++;
			}
		}
	}
	return vivants;
}

void reproduire(gene** genespop, stage** pop, int usercontinue){
	//si usercontinue=0, c'est la dernière generation

	//SELECTION
	float** scores=remplirscorestries(pop);
	
	//affichage de la meilleure fusée de la dernière génération
	if(!usercontinue)
		afficherfuseehtml(pop[ (int)scores[nbpop-1][0] ]);

	//on tue nbpop*ratiokill de la population
	int nbtue=(int)(nbpop*ratiokill);
	int nbvivants=nbpop-nbtue;
	int* vivants=tue(scores, nbtue);
	freescores(scores);
	//dorenavant in travaille sur les fusées d'indice vivants[xx];

	//MUTATION
	for(int i=0; i<nbmut; i++){//seul nbmut fusées mutent
		int indice=vivants[rand()% nbvivants];
		for(int j=0; j<nbmaxstages; j++){

			if(!(rand()%11))// 1/10
				genespop[indice]->s[j]->ft[rand()%nbmaxft]=rand()%40;

			else if((!rand()%41))// 1/40
				genespop[indice]->s[j]->ft[rand()%nbmaxft]=-1;

			if(!(rand()%11))// 1/10
				genespop[indice]->s[j]->e=rand()%23;

			else if((!rand()%41))// 1/40
				genespop[indice]->s[j]->e=rand()%-1;

		}
	}

	//CROSS-OVER
	gene** newgenespop=initialisepopgenes();

	//printf("nbvivants=%d nbtue=%d\n",nbvivants,nbtue);
	int nbenfants=0;
	while(nbenfants<nbpop-1){

		//creation d'un tableau qui relie 2 vivants entre eux (appareillage[i] et i)
		int* appareilles=appareillage(nbvivants);

		for(int i=0; i<nbvivants && nbenfants<nbpop; i++){
			//printf("%d\n",nbenfants);

			for(int j=0; j<nbmaxstages; j++){
				//on prends un génome du père ou de la mère au hasard
				if(rand()%2)
					recopiestage(newgenespop[nbenfants]->s[j], genespop[ vivants[i] ]->s[j]);
				else
					recopiestage(newgenespop[nbenfants]->s[j], genespop[ vivants[ appareilles[i] ] ]->s[j]);
			}
			nbenfants++;
		}

		free(appareilles);
	}

	recopiegene(genespop,newgenespop);
	free(vivants);
	freepopgenes(newgenespop);
}

void genetic(fueltank* listft, engine* listeng){

	gene** genespop=initialisepopgenes();

	int usercontinue=nbgen;//nb de genrations à calculer avant d'afficher le resultat
	while(usercontinue!=0){//pour avancer d'une génération à la fois
		usercontinue--;

		//construire la nouvelle génération et reset la precedente
		stage** pop=initialisepopfusee();
		construire(listft, listeng, pop, genespop);

		//evaluer la génération et la faire reproduire
		//les meilleurs partagent leurs gènes par bloc de stage
		reproduire(genespop, pop, usercontinue);
		freepopfusee(pop);
	}
}