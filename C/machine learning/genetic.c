
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
//rempli le génome de gènes random
genestage* initialisegenestage(){

	genestage* s=malloc(sizeof(*s));

	s->ft=malloc(sizeof(&s->ft)*nbmaxft);
	for(int i=0; i<nbmaxft; i++){

		//2 chances sur 3
		if(!(rand()%3))
			s->ft[i]=rand()%40;
		else
			s->ft[i]=-1;//no ft

	}
	s->e=rand()%23;
	return s;
}

gene* initialisegene(){
	gene* g=malloc(sizeof(*g));
	g->s=malloc(sizeof(&g->s)*nbmaxstages);

	for(int i=0; i<nbmaxstages; i++)
		g->s[i]=initialisegenestage();

	return g;
}

//mets des satellites dans toutes les fusées mais rien d'autre
stage** initialisepopfusee(){
	stage** pop=malloc(sizeof(*pop)*nbpop);
	for(int i=0; i<nbpop; i++)
		pop[i]=initialisefusee();
	return pop;
}

gene** initialisepopgenes(){
	gene** genespop=malloc(sizeof(*genespop)*nbpop);
	for(int i=0; i<nbpop; i++)
		genespop[i]=initialisegene();
	return genespop;
}

//rempli la pop grâce aux gènes
void construire(fueltank* listft, engine* listeng, stage** pop, gene** genespop){
	//free(pop);
	//pop=initialisepopfusee();
	for(int i=0; i<nbpop; i++){
		pop[i]=initialisefusee();
		for(int j=0; j<nbmaxstages; j++)
			addstage(pop[i], nbmaxstages, genespop[i]->s[j]->ft, listft, listeng[ genespop[i]->s[j]->e ] );
	}
}

void affichage(stage** pop, float** scores, int usercontinue){
	//calcul de la moyenne
	float scoremoy;
	for(int i=0; i<nbpop; i++)
		scoremoy+=scores[i][1]; 
	scoremoy/=nbpop;

	if(!usercontinue){
		int best=(int)scores[nbpop-1][0];
		afficherfusee(pop[best]);
		printf("%.0fΔv	%d$	minTWR:%.3f\n", deltav(pop[best]), costfusee(pop[best]), mintwr(pop[best]) );
	}
	printf("meilleur: %.0f		moyenne: %.0f\n",scores[nbpop-1][1], scoremoy);
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
		scores[i][1]=scorefusee(pop[i], moddeltav, modcost, modtwr);
	}
	quicksort(scores,0,nbpop-1);
	return scores;
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
		int indice=rand()%nbpop;//entre 0 et 99
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
	}/*
	for(int i=0; i<nbpop-nbtokill; i++)
		vivants[i]=(int)scores[nbpop-i][0];*/
	return vivants;
}

void recopiestage(genestage* colle, genestage* copie){
	for(int i=0; i<nbmaxft; i++)
		colle->ft[i]=copie->ft[i];
	colle->e=copie->e;
}

void recopiegene(gene** colle, gene** copie){
	for(int i=0; i<nbpop; i++)
		for(int j=0; j<nbmaxstages; j++)
			recopiestage(colle[i]->s[j],copie[i]->s[j]);
}

void reproduire(gene** genespop, stage** pop, int usercontinue){

	//SELECTION
	float** scores=remplirscorestries(pop);
	//affichage(pop, scores, usercontinue);

	//on tue nbpop/2 de la population
	int* vivants=tue(scores, nbpop/2);
	free(scores);
	//dorenavant in travaille sur les fusées d'indice vivants[xx];

	//MUTATION
	for(int i=0; i<nbmut; i++){//seul 5 fusées mutent
		int indice=vivants[rand()%(nbpop/2)];
		for(int j=0; j<nbmaxstages; j++){

			for(int k=0; k<nbmaxft; k++){
				if(!(rand()%11))
					genespop[indice]->s[j]->ft[k]=rand()%40;

				else if((!rand()%41))
					genespop[indice]->s[j]->ft[k]=-1;
			}

			if(!(rand()%11))
				genespop[indice]->s[j]->e=rand()%23;

		}
	}

	//CROSS-OVER
	gene** newgenespop=initialisepopgenes();

	for(int e=0; e<2; e++){//nbpop/2 papas et mamans en même temps donc les couples font 2 enfants

		//creation d'un tableau de nbpop/2 randoms
		int* appareilles=appareillage(nbpop/2);

		for(int i=0; i<nbpop/2; i++){

			for(int j=0; j<nbmaxstages; j++){
				if(rand()%2)
					recopiestage(newgenespop[i+e*nbpop/2]->s[j], genespop[vivants[i]]->s[j]);
				else
					recopiestage(newgenespop[i+e*nbpop/2]->s[j], genespop[ vivants[ appareilles[i] ] ]->s[j]);
			}
		}
		free(appareilles);
	}
	recopiegene(genespop,newgenespop);
	free(vivants);
	free(newgenespop);
}

float genetic(fueltank* listft, engine* listeng){

	time_t t;
	srand((unsigned) time(&t));

	stage** pop=initialisepopfusee();
	gene** genespop=initialisepopgenes();

	int usercontinue=100;//nb de genrations à calculer avant d'afficher le resultat
	while(usercontinue!=0){//pour avancer d'une génération à la fois
		usercontinue--;

		//construire la nouvelle génération et reset la precedente
		construire(listft, listeng, pop, genespop);

		//evaluer la génération et la faire reproduire
		//le meilleur partage ses gènes par bloc de stage
		reproduire(genespop, pop, usercontinue);
		/*
		if(!usercontinue){//tant qu'il est pas égal à 0
			printf("Continuer combien de fois?\n");
			fpurge(stdin);
			scanf("%d",&usercontinue);
			//system("clear");
		}
		*/
	}
	float** scores=remplirscorestries(pop);
	return scores[nbpop-1][1];
}