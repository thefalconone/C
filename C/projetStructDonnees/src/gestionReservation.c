#include "emploiDuTemps.h"
#include "reservationSalle.h"

//fonction utilisee seulement dans gestionReservation.c pour simplifier le code
//et definie en bas de gestionReservation.c
char tryAdd(EmploiDuTemps e, Reservation* rs, Reservation r, int nbRes, int dh, int dm, int diffM, float min, float max, char opti);

Reservation InitialiseReservation(){
	Reservation r=malloc(sizeof(struct reservation));
	r->indexSalle=-1;
	r->type=-1;
	r->classe=NULL;
	r->cours=NULL;
	r->horaire=NULL;
	return r;
}

//Ajoute la reservation passee en parametre dans une salle ou l'horaire de la reservation est disponible, si une telle salle existe
int Reserver(EmploiDuTemps e,Reservation r){
	char trouve=0;
	int i=0;
	while(!trouve && i<e->nbSalle){
		if(disponible(e->salles[i],r->horaire, r->type)){
			if(disponibleClasse(e, r->classe, r->horaire)){
				trouve=1;
			}
		}
		if(!trouve)i++;
	}
	if(trouve){
		ajouterReservationSalle(e,i,r);
		return 0;
	}
	//aucune salle n'est disponible
	return 1;
}

//Ajoute une reservation le plus proche d'une autre reservation ou le plus proche de 13h si la classe de la reservation r n'a aucune reservation
//Le but de cette methode est d'optimiser l'emploi du temps de la classe stockee dans la reservation
//en minimisant la difference de temps entre le debut du premier cours de la journee et la fin du dernier cours de la journee
//tout en respectant les contraintes habituelles (debut : 7h45, fin : 20h, pause midi : 12h-13h)
int ReserverOpti(EmploiDuTemps e, Reservation r, int dureeHeure, int dureeMinute){
	Reservation* reservationClasse = ReservationsClasse(e,r->classe);
	int nbRes=0;
	while(reservationClasse[nbRes]!=NULL){nbRes++;}
	float min=24,max=0; //bornes de la journee d'une classe
	for(int i=0;i<nbRes;i++){
		float d=reservationClasse[i]->horaire->debutHeure+(float)reservationClasse[i]->horaire->debutMinute/60;
		float f=reservationClasse[i]->horaire->finHeure+(float)reservationClasse[i]->horaire->finMinute/60;
		if(d<min){min=d;}
		if(f>max){max=f;}
	}
	char ajoute=0;
	if(nbRes==0){
		//si la classe n'a aucune reservation
		int i=0;
		Horaire h=malloc(sizeof(struct horaire));
		while(!ajoute && i<8*60/2){
			//teste les horaires les plus proches de 13h
			//s'eloigne de 13h de 5 minute en 5 minutes dans les 2 direction
			//suite alternee 0 -5 5 -10 10 ...
			int suite=5*(i/2);
			if(i%2==0){suite*=-1;}
			h->debutHeure=13;
			h->debutMinute=suite;
			while(h->debutMinute>=60){h->debutMinute-=60;h->debutHeure+=1;}
			while(h->debutMinute<0){h->debutMinute+=60;h->debutHeure-=1;}
			h->finHeure=h->debutHeure+dureeHeure;
			h->finMinute=h->debutMinute+dureeMinute;
			while(h->finMinute>=60){h->finMinute-=60;h->finHeure+=1;}
			int j=0;
			//parcours toutes les salles pour et teste la valititee de l'horaire defini ci dessus
			while(!ajoute && j<e->nbSalle){
				if(disponible(e->salles[j],h, r->type)){
					if(disponibleClasse(e, r->classe, h)){
						if(r->horaire!=NULL){free(r->horaire);}
						r->horaire=malloc(sizeof(struct horaire));
						r->horaire=h;
						ajouterReservationSalle(e,j,r);
						ajoute=1;
					}
				}
				j++;
			}
			i++;
		}
	}else{
		int i=0;
		int max=60*(HORAIRE_MAX-HORAIRE_MIN);
		//recherche opti (emplacement qui n'est pas en bord de journee de l'emploi du temps de la classe)
		while(!ajoute && i<max){
			if(tryAdd(e, reservationClasse, r, nbRes, dureeHeure, dureeMinute, i, min, max, 1)){ //dernier parametre = 1 ---> opti
				ajoute=1;
			}
			i+=5; //la recherche se fait a 5 minutes pres
		}
		if(!ajoute){
			i=0;
			//recherche non opti
			while(!ajoute && i<60*(HORAIRE_MAX-HORAIRE_MIN)){
				if(tryAdd(e, reservationClasse, r, nbRes, dureeHeure, dureeMinute, i, min, max, 0)){ //dernier parametre = 0 ---> pas opti
					ajoute=1;
				}
				i+=5;
			}
		}
	}
	if(ajoute)return 0;
	//Pas d'emplacement disponible
	return 1;
}

int AnnuleReservation(EmploiDuTemps e, Reservation r){
	char annule=0;
	if(e->salles[r->indexSalle]!=NULL){
		if(findReservationSalle(e->salles[r->indexSalle],r)){ //verifie que la reservation est bien dans la salle
			enleverReservationSalle(e->salles[r->indexSalle],r);
			annule=1;
		}
	}
	if(annule)return 0;
	//Sinon la reservation n'a pas ete annule
	return 1;
}

//remplace la reservation old par la reservation new
int ModifieReservation(EmploiDuTemps e, Reservation old, Reservation new){
	char erreur=AnnuleReservation(e, old);
	if(!erreur){
		return Reserver(e, new);
	}
	return 1;
}

//fonction utilisee dans les 3 suivantes fonctions qui retournent des liste de reservations trie
//ajoute la reservation r dans la liste de reservation rs en gardant la liste de reservation rs triee par heure (+minute) de debut de cours
void ajouteResParHoraire(Reservation* rs, Reservation r, int nbRes){
	int i=nbRes-1;
	char ajoute=0;
	int h=r->horaire->debutHeure*60+r->horaire->debutMinute;
	//boucle tant que l'horaire de debut de la nouvelle reservation est inférieur a celui de la reservation rs[i]
	//commence par la fin de la liste
	while(!ajoute && i>=0){
		int hi=rs[i]->horaire->debutHeure*60+rs[i]->horaire->debutMinute;
		if(h>hi){
			rs[i+1]=r;
			ajoute=1;	
		}else{
			rs[i+1]=rs[i];
		}
		i--;
	}
	if(!ajoute){
		rs[0]=r;
	}
	rs[nbRes+1]=NULL;
}

//retourne la liste de toutes les reservations du batiment (trie par horaire de debut)
Reservation* ReservationsBat(EmploiDuTemps e){
	Reservation* r=malloc(e->nbSalle*(MAX_COURS+1)*sizeof(struct reservation));
	r[0]=NULL;
	int i=0;
	for(int j=0;j<e->nbSalle;j++){
		if(e->salles[j]!=NULL){
			ChaineReservation* cr=e->salles[j]->cr;
			if(cr!=NULL){			
				while(cr!=NULL && i<e->nbSalle*MAX_COURS){
					ajouteResParHoraire(r,cr->r,i);
					cr=cr->next;
					i++;
				}
			}
		}
	}
	return r;
}
//retourne la liste des reservations de la salle passee en parametre (trie par horaire de debut)
Reservation* ReservationsSalle(Salle salle){
	Reservation* r=malloc(MAX_COURS*sizeof(struct reservation));
	r[0]=NULL;
	ChaineReservation* cr=salle->cr;
	int i=0;
	while(cr!=NULL && i<MAX_COURS){
		ajouteResParHoraire(r,cr->r,i);
		cr=cr->next;
		i++;
	}
	r[i]=NULL;
	return r;
}

//retourne la liste des reservations liees a la classe passee en parametre (trie par horaire de debut)
Reservation* ReservationsClasse(EmploiDuTemps e, char* classe){
	Reservation* r=malloc(MAX_COURS*sizeof(struct reservation));
	r[0]=NULL;
	int i=0;
	for(int j=0;j<e->nbSalle;j++){
		ChaineReservation* cr=e->salles[j]->cr;
		if(cr!=NULL){			
			while(cr!=NULL && i<MAX_COURS){
				if(strcmp(cr->r->classe,classe)==0){
					ajouteResParHoraire(r,cr->r,i);
					i++;
				}
				cr=cr->next;
			}	
		}
	}
	r[i]=NULL;
	return r;
}

//methode utilisée dans ReserveOpti
//essaye d'ajouter la reservation r diffM minutes avant ou apres chaque cours de la classe en balayant toutes les salles
char tryAdd(EmploiDuTemps e, Reservation* rs, Reservation r, int nbRes, int dh, int dm, int diffM, float min, float max, char opti){
	Horaire h = malloc(sizeof(struct horaire));
	int i=0;
	char ajoute=0;
	while(!ajoute && i<nbRes){
		//test diffM minutes avant la reservation d'indice i
		h->debutHeure=rs[i]->horaire->debutHeure-dh;
		h->debutMinute=rs[i]->horaire->debutMinute-dm-diffM;
		while(h->debutMinute<0){h->debutMinute+=60;h->debutHeure-=1;}
		h->finHeure=h->debutHeure+dh;
		h->finMinute=h->debutMinute+dm;
		while(h->finMinute>=60){h->finMinute-=60;h->finHeure+=1;}	
		if(!opti || (h->debutHeure+(float)h->debutMinute/60 > min && h->finHeure+(float)h->finMinute/60 < max)){
			int j=0;
			while(!ajoute && j<e->nbSalle){
				if(disponible(e->salles[j], h, r->type)){
					if(disponibleClasse(e, r->classe, h)){
						if(r->horaire!=NULL){free(r->horaire);}
						r->horaire=malloc(sizeof(struct horaire));
						r->horaire=h;
						ajouterReservationSalle(e,j,r);
						ajoute=1;
					}
				}
				j++;
			}
		}
		if(!ajoute){
			//test diffM minutes apres la reservation d'indice i
			h->debutHeure=rs[i]->horaire->finHeure;
			h->debutMinute=rs[i]->horaire->finMinute+diffM;
			while(h->debutMinute>=60){h->debutMinute-=60;h->debutHeure+=1;}
			h->finHeure=h->debutHeure+dh;
			h->finMinute=h->debutMinute+dm;
			while(h->finMinute>=60){h->finMinute-=60;h->finHeure+=1;}	
			if(!opti || (h->debutHeure+(float)h->debutMinute/60 > min && h->finHeure+(float)h->finMinute/60 < max)){
				int j=0;
				while(!ajoute && j<e->nbSalle){
					if(disponible(e->salles[j], h, r->type)){
						if(disponibleClasse(e, r->classe, h)){
							if(r->horaire!=NULL){free(r->horaire);}
							r->horaire=malloc(sizeof(struct horaire));
							r->horaire=h;
							ajouterReservationSalle(e,j,r);
							ajoute=1;
						}
					}
					j++;
				}
			}
		}
		i++;
	}
	return ajoute;
}