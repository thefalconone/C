#include "emploiDuTemps.h"

EmploiDuTemps InitialiseEmploiDuTemps(){
	EmploiDuTemps e;
	e=malloc(sizeof(struct emploiDuTemps));
	e->salles=malloc(1000*sizeof(struct salle));
	e->nbSalle=0;
	return e;
}

Salle InitialiseSalle(int numero, typeSalle type){
	Salle s=malloc(sizeof(struct salle));
	s->cr=NULL;
	s->numero=numero;	
	s->type=type;
	return s;
}

void AjouterSalle(EmploiDuTemps e,int numero, typeSalle type){
	Salle s;
	s=InitialiseSalle(numero, type);
	int i=0;
	while(i<e->nbSalle && numero>e->salles[i]->numero){//on trouve le bon index i pour ajouter la salle
		i++;
	}
	for(int j=e->nbSalle;j>=i;j--){//on décale toutes les salles
		e->salles[j+1]=e->salles[j];
	}
	e->salles[i]=s;//on ajoute la salle
	e->nbSalle++;
}

void SupprimerSalle(EmploiDuTemps e,int index){
	e->nbSalle--;
	for(int i=index;i<e->nbSalle;i++){//on décale les salles
		e->salles[i]=e->salles[i+1];
	}
	Reservation* res=ReservationsSalle(e->salles[e->nbSalle]);//on recupere les reservations de cette salle
	int i=0;
	while(res[i]!=NULL){//on les supprime
		AnnuleReservation(e,res[i]);
	}
}

void ModifierSalle(EmploiDuTemps e, int index, typeSalle newType, int newNumero){
	SupprimerSalle(e,index);
	AjouterSalle(e,newNumero,newType);
}

int AfficherSalles(EmploiDuTemps e,int etage){
	int nbsalles=0;//donne le bon index pour les entrées utilisateur
	for (int i=0;i<e->nbSalle;i++){
		if(e->salles[i]->numero/100 == etage){//la division entre 2 int en C est un quotient
			char* str;
			switch (e->salles[i]->type){
				case 0:
					str="Amphi";
					break;
				case 1:
					str="TD";
					break;
				case 2:
					str="TP";
					break;
			}
			printf("%d) %s n° %d\n",nbsalles,str,e->salles[i]->numero);
			nbsalles++;
		}
	}
	printf("\n");
	return nbsalles;
}