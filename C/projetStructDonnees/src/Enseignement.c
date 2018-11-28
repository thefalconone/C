#include "emploiDuTemps.h"

Enseignement InitialiseEnseignement(){
	Enseignement e;
	e=malloc(sizeof(struct enseignement));
	e->cours=malloc(TAILLE_ENSEIGNEMENT*sizeof(struct cours));//cours est une adresse de char*
	e->nbCours=0;
	return e;
}

void AjouterEnseignement(Enseignement e,char* cours){
	e->cours[e->nbCours]=malloc(sizeof(struct cours));//cours est une adresse de char*
	e->cours[e->nbCours]->nom=malloc(strlen(cours)*sizeof(char));//nom est un char*
	strcpy(e->cours[e->nbCours]->nom,cours);
	e->nbCours++;
}

void ModifierEnseignement(EmploiDuTemps edt, Enseignement e,int index,char* newcours){
	SupprimerEnseignement(edt,e,index);
	AjouterEnseignement(e,newcours);
}

void SupprimerEnseignement(EmploiDuTemps edt, Enseignement e,int index){
	Reservation* res=ReservationsBat(edt);//on récupère toutes les reservations
	int i=0;
	while(res[i]!=NULL){//on supprime toutes les reservations de l'enseignement à supprimer
		if(strcmp(res[i]->cours->nom,e->cours[index]->nom)==0){
			AnnuleReservation(edt,res[i]);
		}
		i++;
	}

	free(e->cours[index]->nom);//on free l'enseignement
	e->cours[index]->nom=malloc(strlen(e->cours[e->nbCours-1]->nom)*sizeof(char));//on lui mets le dernier enseignement pour remplir le trou
	strcpy(e->cours[index]->nom,e->cours[e->nbCours-1]->nom);
	free(e->cours[e->nbCours-1]->nom);//on free le dernier (sinon il est en double)
	e->nbCours--;
	}

void AfficherEnseignement(Enseignement e){
	for (int i=0;i<e->nbCours;i++){
		printf("%d) %s\n",i+1,e->cours[i]->nom);//i+1 pour l'utilisateur.
	}
}