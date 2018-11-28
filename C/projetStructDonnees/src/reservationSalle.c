#include "emploiDuTemps.h"
#include "reservationSalle.h"

//ajoute une reservation dans la salle e->salles[indexSalle]
void ajouterReservationSalle(EmploiDuTemps e, int indexSalle, Reservation r){
	r->indexSalle=indexSalle;
	Salle salle=e->salles[indexSalle];
	if(salle->cr==NULL){//si la salle n'a pas de reservation
		salle->cr=malloc(sizeof(ChaineReservation));
		salle->cr->r=malloc(sizeof(struct reservation));
		salle->cr->r=r;
		salle->cr->next=NULL;
	}else{//on ajoute le nouvel element au debut de la chaine
		ChaineReservation* cr=malloc(sizeof(ChaineReservation));
		cr->r=r;
		cr->next=salle->cr;
		salle->cr=cr;
	}
}

void enleverReservationSalle(Salle salle, Reservation r){
	char trouve=0;
	ChaineReservation* cr=salle->cr;
	ChaineReservation* old=NULL;
	//parcours la chaine de reservation jusqu'a trouver la reservation passee en parametre
	while(cr!=NULL && !trouve){
		if(cr->r==r){
			trouve=1;
		}else{
			old=cr;
			cr=cr->next;
		}
	}
	if(cr==NULL){
		printf("Tentative de retrait d'un enseignement non existant\n");
	}else{
		//enleve la reservation		
		if(old==NULL){
			salle->cr=cr->next;
		}else{
			old->next=cr->next;
		}
		free(cr->r->classe);
		free(cr->r->cours->nom);
		free(cr->r->cours);
		free(cr->r->horaire);
		free(cr->r);
	}
}
//retourne un boolean qui vaut 1 si l'horaire est disponible pour la salle passee en parametre
//et que le type de la reservation et de la salle sont coherents, 0 sinon 
char disponible(Salle salle, Horaire horaire, typeSalle type){
	if(salle->type!=type){
		return 0;
	}	
	char dispo=1;
	ChaineReservation* cr=salle->cr;
	float debut=horaire->debutHeure+(float)horaire->debutMinute/60;
	float fin=horaire->finHeure+(float)horaire->finMinute/60;

	if(debut<HORAIRE_MIN || fin>HORAIRE_MAX){ //limites d'une journée 7h45 - 20h
		return 0;
	}
	if(debut>=fin){
		return 0;
	}
	//parcours la chaine de reservation et verifie que les horaires sont compabtibles
	while(dispo && cr!=NULL){
		float rDebut=cr->r->horaire->debutHeure+(float)cr->r->horaire->debutMinute/60-INTERCOURS;
		float rFin=cr->r->horaire->finHeure+(float)cr->r->horaire->finMinute/60+INTERCOURS;
		if((debut>=rDebut && debut<rFin)
		|| (fin>rDebut && fin<=rFin)
		|| (rDebut>debut && rDebut<fin)
		|| (rFin>debut && rFin<fin)){
			dispo=0;
		}
		//condition suivante a mettre en parametre pour autoriser des reservations entre 12h et 13h
		if((debut>=12 && debut<13) || (fin>12 && fin<=13)){
			dispo=0;
		}
		cr=cr->next;
	}
	return dispo;
}

//retourne un boolean qui vaut 1 si l'horaire est disponible pour la classe passee en parametre, 0 sinon 
char disponibleClasse(EmploiDuTemps e, char* classe, Horaire horaire){
	char dispo=1;
	float debut=horaire->debutHeure+(float)horaire->debutMinute/60;
	float fin=horaire->finHeure+(float)horaire->finMinute/60;
	if(debut<HORAIRE_MIN || fin>HORAIRE_MAX){ //limites d'une journée 7h45 - 20h
		dispo=0;
	}
	Reservation* r=ReservationsClasse(e,classe);
	int i=0;
	//parcours les reservations et verifie que les horaires sont compatibles
	while(dispo && r[i]!=NULL){
		float rDebut=r[i]->horaire->debutHeure+(float)r[i]->horaire->debutMinute/60-INTERCOURS;
		float rFin=r[i]->horaire->finHeure+(float)r[i]->horaire->finMinute/60+INTERCOURS;
		if((debut>=rDebut && debut<rFin)
		|| (fin>rDebut && fin<=rFin)
		|| (rDebut>debut && rDebut<fin)
		|| (rFin>debut && rFin<fin)){
			dispo=0;
		}
		//condition suivante a mettre en parametre pour autoriser des reservations entre 12h et 13h
		if((debut>=12 && debut<13) || (fin>12 && fin<=13)){
			dispo=0;
		}					
		i++;
	}
	return dispo;
}

//retourne 1 si la salle contient la reservation passee en parametre, 0 sinon
char findReservationSalle(Salle salle, Reservation r){
	char trouve=0;
	ChaineReservation* cr=salle->cr;
	while(cr!=NULL && !trouve){
		if(cr->r==r){
			trouve=1;
		}else{
			cr=cr->next;
		}
	}
	return trouve;
}