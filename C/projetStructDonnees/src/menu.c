#include "emploiDuTemps.h"

void Clear(){ //fonction qui clear la console a utiliser avent un affichage
	system("clear");
}

int scanchiffre(int min, int max){
	int fini=0;
	int error=0;
	char errorMsg[63];
	char get[10];
	int iget;//le get apres avoir verif que c'est un int
	while (!fini){
		iget=0;
		if (error){//si il y a une erreur on l'affiche et et redemande
			printf("%s\n",errorMsg);
			error =0;
		}
		scanf("%s",get);//prend les stdin dnas un char[10]
		int estnombre=1;
		for(int i=0;i<strlen(get);i++){//verif qu'il n'y ait pas de lettres
			estnombre=estnombre && !(get[i]<58 && get[i]>47);
			iget=iget*10+get[i]-48;
		}
		if (estnombre){//verifie si le caractère est un nombre
			error=1;
			strcpy(errorMsg,"Veuillez taper un chiffre");
		}
		else{
			if(iget>max||iget<min){//verifie que l'integer est dans la range des menus
				error=1;
				sprintf(errorMsg,"Veuillez taper un chiffre entre %d et %d",min,max);
			}
			else{//sinon fini
				fini=1;
			}
		}
	}
	return iget;//retourne l'index de la position dans la liste menus
}

int AfficherMenu(int nbMenu, char** menus,char* str){ // affiche des menus de la liste menu en donnant le nombre de menu a afficher et affiche str avent tout ça retourne le numero du menu tapé par l'utilisateur
	Clear();
	printf("%s\n",str);//afficher le message globale du menu
	for (int i=0;i<nbMenu;i++){//affiche les menus
		printf("%d) %s\n",i+1,menus[i]);	
	}
	int get=scanchiffre(1,nbMenu);
	return get-1;//retourne l'index de la position dans la liste menus
}

//--------------------ENSEIGNEMENT--------------------

void MenuAjouterEnseignement (Enseignement e){ 
	Clear();
	char c[30];
	printf("Tappez le nom de l'enseignement que vous voulez ajouter\n");
	printf("puis appuyez sur entrée\n");
	scanf("%s",c);
	AjouterEnseignement(e,c);
}

void MenuModifierEnseignement (EmploiDuTemps edt, Enseignement e){
	Clear();
	if(!e->nbCours){//si y'a rien à suppr
		printf("Il n'y a aucun enseignement à modifier\n");
		printf("Appuyez sur une touche et entrée pour revenir au menu\n");
		char buffer[30];
		scanf("%s",buffer);
	}else{
		printf("Choisissez un enseignement a modifier parmis la liste\n");
		AfficherEnseignement(e);
		int get=scanchiffre(1,e->nbCours);
		Clear();
		printf("Vous voulez modifier l'enseignement %s\n",e->cours[get-1]->nom);
		printf("Tappez le nouveaux nom de cet enseignement\n");
		char c[30];
		scanf("%s",c);
		ModifierEnseignement(edt, e,get-1,c);
	}
}

void MenuSupprimerEnseignement (EmploiDuTemps edt, Enseignement e){
	Clear();
	if(!e->nbCours){//si y'a rien à suppr
		printf("Il n'y a aucun enseignement à supprimer\n");
		printf("Appuyez sur une touche et entrée pour revenir au menu\n");
		char buffer[30];
		scanf("%s",buffer);
	}else{
		printf("Choisissez un enseignement a supprimer parmis la liste\n");
		AfficherEnseignement(e);
		SupprimerEnseignement(edt, e,scanchiffre(1,e->nbCours)-1);
	}
}

void MenuAfficherEnseignement (Enseignement e){
	Clear();
	if(!e->nbCours){//si y'a rien à suppr
		printf("Il n'y a aucun enseignement\n");
	}else{
		printf("Voici la liste des enseignement\n");
		AfficherEnseignement(e);
	}
	printf("Appuyez sur une touche et entrée pour revenir au menu\n");
	char buffer[30];
	scanf("%s",buffer);
}

//--------------------SALLE--------------------

int indexParEtage(EmploiDuTemps e, int etage, int index){
	int nbSalle=0;//compte jusqu'a index
	for(int i=0;i<e->nbSalle;i++){
		if(e->salles[i]->numero/100 == etage){
			if(nbSalle==index){
				return i;
			}
			nbSalle++;
		}
	}
	return -1;
}

int nbSallesEtage(EmploiDuTemps e, int etage){
	int nbSallesEtage=0;
	for (int i=0;i<e->nbSalle;i++){
		if(e->salles[i]->numero/100 == etage){
			nbSallesEtage++;
		}
	}
	return nbSallesEtage;
}

void MenuAjouterSalle(EmploiDuTemps e){
	Clear();
	char* menu[]={"Amphi","TD","TP"};
	int type=AfficherMenu(3,menu,"Choisissez un type pour votre salle");

	Clear();
	printf("Entrez le numero de la salle que vous voulez ajouter\n");
	printf("Le chiffre des centaine sera l'etage de la salle\n");
	int numero=scanchiffre(0,999);
	AjouterSalle(e,numero,type);
}

void MenuModifierSalle(EmploiDuTemps e){ // montre la liste des salle a l'utilisateur et modifie la salle que l'utilisateur choisis
	Clear();
	printf("Choisissez un etage entre 0 et 10\n");
	int etage=scanchiffre(0,9);
	Clear();
	if(nbSallesEtage(e,etage)==0){
		printf("Il n'y a pas de salle dans cet étage\n");
	}else{
		printf("Choisissez une salle a modifier parmis la liste\n");
		int indexSalle=indexParEtage(e,etage,scanchiffre(0,AfficherSalles(e,etage)-1));
		
		Clear();
		char* menu[]={"Amphi","TD","TP"};
		int newType=AfficherMenu(3,menu,"Choisissez un type pour votre salle");
		printf("Quel est le nouveau numero de la salle que vous voulez modifier\n");
		printf("Le chiffre des centaines sera l'etage de la salle\n");
		int newNumero=scanchiffre(0,999);
		ModifierSalle(e,indexSalle,newType,newNumero);
	}
}
void MenuSupprimerSalle(EmploiDuTemps e){// montre la liste des salles a l'utilisateur et supprime le numero tapé par l'utilisateur
	Clear();
	printf("Choisissez un étage entre 0 et 10\n");
	int etage=scanchiffre(0,9);
	Clear();
	if(nbSallesEtage(e,etage)==0){
		printf("Il n'y a pas de salle dans cet étage\n");
	}else{
		printf("Choisissez une salle à supprimer parmis la liste\n");
		int indexSalle=indexParEtage(e,etage,scanchiffre(0,AfficherSalles(e,etage)-1));
				
		Clear();
		SupprimerSalle(e,indexSalle);
		printf("Salle supprimée!\n");
	}
	printf("Appuyez sur une touche et entrée pour revenir au menu\n");
	char buffer[30];
	scanf("%s",buffer);
}

void MenuAfficherSalles(EmploiDuTemps e){
	Clear();
	printf("Choisissez un étage entre 0 et 10\n");
	int etage=scanchiffre(0,9);
	Clear();
	if(nbSallesEtage(e,etage)==0){
		printf("Il n'y a pas de salle dans cet étage\n");
	}else{
		AfficherSalles(e,etage);
	}
	printf("Appuyez sur une touche et entrée pour revenir au menu\n");
	char buffer[30];
	scanf("%s",buffer);
}

//--------------------RESERVATION--------------------

char* TypeSalleToString(typeSalle t){
	char* str;
	switch (t){
		case 0:
			str="Amphi";
			break;
		case 1:
			str="Salle de TD";
			break;
		case 2:
			str="Salle de TP";
			break;
	}
	return str;
}

void AfficheReservation(EmploiDuTemps e, Reservation res){
	printf("%s n° %d\n",TypeSalleToString(res->type),e->salles[res->indexSalle]->numero);
	printf("Classe %s\n",res->classe);
	printf("Cours %s\n",res->cours->nom);
	printf("de ");
	if(res->horaire->debutHeure<10)printf("0");
	printf("%d:",res->horaire->debutHeure);
	if(res->horaire->debutMinute<10)printf("0");
	printf("%d à ",res->horaire->debutMinute);
	if(res->horaire->finHeure<10)printf("0");
	printf("%d:",res->horaire->finHeure);
	if(res->horaire->finMinute<10)printf("0");
	printf("%d\n\n",res->horaire->finMinute);
}

Reservation AfficheReservationSalleScan(EmploiDuTemps e,Salle s){
	Reservation* r= ReservationsSalle(s);
	int i=0;
	while(r[i]!=NULL){
		printf("%d)\n",i);
		AfficheReservation(e,r[i]);
		i++;
	}//scan l'utilisateur pour la reservation choisie
	int index=scanchiffre(0,i-1);
	return r[index];
}

void MenuModifieReservation(EmploiDuTemps e,Enseignement c){
	Clear();
	printf("Selection de la salle dans laquelle vous voulez modifier votre réservation\n");
	printf("Choisissez l'étage entre 0 et 10\n");
	int etage=scanchiffre(0,9);

	Clear();
	if(nbSallesEtage(e,etage)==0){
		printf("Il n'y a pas de salle dans cet étage\n");
	}else{
		printf("Choisissez une salle a modifier parmis la liste\n");
		int indexSalle=indexParEtage(e,etage,scanchiffre(0,AfficherSalles(e,etage)-1));

		Clear();
		if(e->salles[indexSalle]->cr==NULL){
			printf("Il n'y a pas de réservation dans cette salle\n");
		}else{
			printf("Choisissez la réservation que vous voulez modifier dans la salle numero %d\n",e->salles[indexSalle]->numero);
			Reservation old=AfficheReservationSalleScan(e,e->salles[indexSalle]);//le scan se fait dans AfficheReservationSalleScan
			
			Clear();
			Reservation new=InitialiseReservation();
			new->type=old->type;//comme l'ancien si on le change pas 
			new->classe=malloc(strlen(old->classe)*sizeof(char));
			strcpy(new->classe,old->classe);
			new->cours=malloc(sizeof(struct cours));
			new->cours->nom=malloc(strlen(old->cours->nom)*sizeof(char));
			strcpy(new->cours->nom,old->cours->nom);
			new->horaire=malloc(sizeof(struct horaire));
			new->horaire->debutHeure=old->horaire->debutHeure;
			new->horaire->debutMinute=old->horaire->debutMinute;
			new->horaire->finHeure=old->horaire->finHeure;
			new->horaire->finMinute=old->horaire->finMinute;
			printf("Voulez vous changer de type de salle ? (0=non 1=oui)\n");
			printf("Type actuel : %s\n",TypeSalleToString(old->type));
			int booltype=scanchiffre(0,1);
			if(booltype){
				char* menu[]={"Amphi","TD","TP"};
				int newtype=AfficherMenu(3,menu,"Choisissez un type pour votre salle");
				new->type=newtype;
			}

			Clear();
			printf("Voulez vous changer la classe ? (0=non 1=oui)\n");
			printf("Classe actuelle : %s\n",old->classe);
			int boolclasse=scanchiffre(0,1);
			if(boolclasse){
				printf("Entrez le nouveau nom de la classe\n");
				char nom[20];
				scanf("%s",nom);
				new->classe=malloc(strlen(nom)*sizeof(char));
				strcpy(new->classe,nom);
			}

			Clear();
			printf("Voulez vous changer le nom du cours ? (0=non 1=oui)\n");
			printf("Cours actuel : %s\n",old->cours->nom);
			int boolcours=scanchiffre(0,1);
			if(boolcours){
				if(!c->nbCours){//si les enseignements sont vides
					printf("Il n'y a aucun enseignement\n");
					printf("Appuyez sur une touche et entrée pour ajouter un enseignement\n");
					char buffer[30];
					scanf("%s",buffer);
					MenuAjouterEnseignement(c);
					Clear();
				}
				printf("Voici la liste des enseignement\n");
				AfficherEnseignement(c);
				printf("Choisissez un enseignement pour votre reservation\n");
				int indexCours=scanchiffre(0,c->nbCours)-1;
				strcpy(new->cours->nom,c->cours[indexCours]->nom);
			}

			Clear();
			printf("Voulez vous changer l'horaire de votre réservation ? (0=non 1=oui)\n");
			printf("Horaire actuel : de ");
			if(old->horaire->debutHeure<10)printf("0");
			printf("%d:",old->horaire->debutHeure);
			if(old->horaire->debutMinute<10)printf("0");
			printf("%d à ",old->horaire->debutMinute);
			if(old->horaire->finHeure<10)printf("0");
			printf("%d:",old->horaire->finHeure);
			if(old->horaire->finMinute<10)printf("0");
			printf("%d\n",old->horaire->finMinute);
			int boolhoraire=scanchiffre(0,1);
			if(boolhoraire){
				printf("Entrez l'horaire de debut du nouveau cours\n");
				printf("heure:");
				new->horaire->debutHeure=scanchiffre(7,20);
				printf("minutes:");
				new->horaire->debutMinute=scanchiffre(0,60);
				printf("\nEntrez l'horaire de fin du nouveau cours\n");
				printf("heure:");
				new->horaire->finHeure=scanchiffre(7,20);
				printf("minutes:");
				new->horaire->finMinute=scanchiffre(0,60);
			}

			Clear();
			if(!ModifieReservation(e, old, new)){
				printf("Réservation modifiée!\n");
			}else{
				printf("Impossible de modifier le reservation\n");
			}
		}
	}
	printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
	char buffer[30];
	scanf("%s",buffer);
}

void MenuAnnuleReservation(EmploiDuTemps e){
	Clear();
	printf("Sélection de la salle dans laquelle vous voulez annuler votre reservation\n");
	printf("Choisissez l'etage entre 0 et 10\n");
	int etage=scanchiffre(0,9);

	Clear();
	if(nbSallesEtage(e,etage)==0){
		printf("Il n'y a pas de salle dans cet étage\n");
	}else{
		printf("Choisissez une salle parmis la liste\n");
		int indexSalle=indexParEtage(e,etage,scanchiffre(0,AfficherSalles(e,etage)-1));

		Clear();
		if(e->salles[indexSalle]->cr==NULL){
			printf("Il n'y a pas de réservation dans cette salle\n");
		}else{
			printf("Choisissez la réservation que vous voulez annuler dans la salle numero %d\n",e->salles[indexSalle]->numero);
			Reservation suppr=AfficheReservationSalleScan(e,e->salles[indexSalle]);

			Clear();
			if(!AnnuleReservation(e,suppr)){
				printf("Réservation annulée!\n");
			}else{
				printf("Impossible d'anunler la reservation\n");
			}
			
		}
	}
	printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
	char buffer[30];
	scanf("%s",buffer);
}

void MenuReserver(EmploiDuTemps e,Enseignement c){
	Reservation new=InitialiseReservation();
	new->cours=malloc(sizeof(struct cours));
	new->horaire=malloc(sizeof(struct horaire));

	//choix du type
	Clear();
	char* menu[]={"Amphi","TD","TP"};
	int newtype=AfficherMenu(3,menu,"Choisissez un type pour votre salle");
	new->type=newtype;

	//choix de la classe
	Clear();
	printf("Entrez le nom de la classe\n");
	char nom[20];
	scanf("%s",nom);
	new->classe=malloc(strlen(nom)*sizeof(char));
	strcpy(new->classe,nom);

	//choix de l'enseignement
	Clear();
	if(!c->nbCours){
		printf("Il n'y a aucun enseignement\n");
		printf("Appuyez sur une touche et entrée pour ajouter un enseignement\n");
		char buffer[30];
		scanf("%s",buffer);
		MenuAjouterEnseignement(c);
	}
	printf("Voici la liste des enseignement\n");
	AfficherEnseignement(c);
	printf("Choisissez un enseignement pour votre reservation\n");
	int indexCours=scanchiffre(1,c->nbCours)-1;
	new->cours->nom=malloc(strlen(c->cours[indexCours]->nom)*sizeof(char));
	strcpy(new->cours->nom,c->cours[indexCours]->nom);

	//choix de l'horaire
	Clear();
	printf("Voulez vous donner un horaire precis à la reservation ? (0=non 1=oui)\n");
	int boolhoraire=scanchiffre(0,1);
	char erreur;
	if(boolhoraire){
		printf("Entrez l'horaire de debut du nouveau cours\n");
		printf("heure:");
		new->horaire->debutHeure=scanchiffre(0,23);
		printf("minutes:");
		new->horaire->debutMinute=scanchiffre(0,59);
		printf("\nEntrez l'horaire de fin du nouveau cours\n");
		printf("heure:");
		new->horaire->finHeure=scanchiffre(0,23);
		printf("minutes:");
		new->horaire->finMinute=scanchiffre(0,59);
		erreur=Reserver(e,new);
	}
	else{
		printf("Entrez la durée de votre cours\n");
		printf("heures:");
		int dureeHeure=scanchiffre(0,8);
		printf("minutes:");
		int dureeMinutes=scanchiffre(0,59);
		erreur=ReserverOpti(e,new,dureeHeure,dureeMinutes);
	}

	Clear();
	if(!erreur){
		printf("Vous avez reservé :\n");
		AfficheReservation(e,new);
	}else{
		printf("Impossible de rajouter cette reservation\n");
	}
	printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
	char buffer[30];
	scanf("%s",buffer);
}
void AfficheReservationBat(EmploiDuTemps e){
	Reservation* r=ReservationsBat(e);
	int i=0;
	Clear();
	if(r[0]==NULL){//pas de reservations
		printf("Il n'y a pas de reservation dans le batiment\n");
	}
	while(r[i]!=NULL){
		printf("%d)\n",i);
		AfficheReservation(e,r[i]);
		i++;
	}
	printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
	char buffer[30];
	scanf("%s",buffer);
}

void AfficheReservationSalle(EmploiDuTemps e,Salle s){
	Reservation* r=ReservationsSalle(s);//une liste de reservations se terminant par NULL
	int i=0;
	Clear();
	if(r[0]==NULL){//pas de reservations
		printf("Il n'y a pas de reservation dans cette salle\n");
	}
	while(r[i]!=NULL){
		printf("%d)\n",i);
		AfficheReservation(e,r[i]);
		i++;
	}
	printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
	char buffer[30];
	scanf("%s",buffer);
}

void AfficheReservationClasse(EmploiDuTemps e,char* classe){
	Reservation* r=ReservationsClasse(e,classe);
	int i=0;
	Clear();
	if(r[0]==NULL){//pas de reservations
		printf("Il n'y a pas de reservation pour cette classe\n");
	}
	while(r[i]!=NULL){
		printf("%d)\n",i);
		AfficheReservation(e,r[i]);
		i++;
	}
	printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
	char buffer[30];
	scanf("%s",buffer);
}

void AfficheReservationMenu(EmploiDuTemps e){
	//switch case des 3 fonctions au dessus
	char* menu[]={"Afficher les réservations par classes","Afficher les réservations par salles","Afficher toutes les réservation du bâtiment"};
	int index=AfficherMenu(3,menu,"Choisissez ce que vous voulez afficher");
	Clear();

	switch(index){
		case 0:
			printf("Entrez le nom de la classe\n");
			char nom[20];
			scanf("%s",nom);
			AfficheReservationClasse(e,nom);
			break;

		case 1:
			printf("Sélection de la salle\n");
			printf("Choisissez l'étage entre 0 et 10\n");
			int etage=scanchiffre(0,9);

			Clear();
			if(nbSallesEtage(e,etage)==0){
				printf("Il n'y a pas de salle dans cet étage\n");
				printf("Appuyez sur une touche et entrée pour revenir aux menus\n");
				char buffer[30];
				scanf("%s",buffer);
			}else{
				printf("Choisissez une salle parmis la liste\n");
				AfficherSalles(e,etage);
				int indexSalle=indexParEtage(e,etage,scanchiffre(0,e->nbSalle-1));
				AfficheReservationSalle(e,e->salles[indexSalle]);
			}
			break;

		case 2:
			AfficheReservationBat(e);
			break;
	}
}


//--------------------MENU--------------------


void Menus (EmploiDuTemps e ,Enseignement c){
	int get;
	int fini=0;
	int innerget;
	int innerfini=0;
	// initialitation des menus creer la liste des menu pour affiche menu
	char* MenuPrincipal[]={"Gestion des enseigements","Gestion des salles","Gestion des reservations","Quitter le programe"};
	int nbMenuPrincipal=4;
	
	char* MenuEnseigments[]={"Ajouter un enseigement","Modifier un enseigement","Supprimer un enseigement","Afficher la liste des enseigements","Retourner au menu principal"};
	int nbMenuEnseigments=5;

	char* MenuSalles[]={"Ajouter une Salle","Modifier une salle","Supprimer une salle","Afficher la liste des salles par étage","Retourner au menu principal"};
	int nbMenuSalles=5;

	char* MenuReservation[]={"Réserver une salle pour un enseigement","Annuler une réservation","Modifier une réservaton","Afficher les réservations","Retourner au menu principal"};
	int nbMenuReservation=5;

	char* DefaultStr="Choisissez un menu en tappant un chiffre";
	//demarage des switch
	//c'est un while pas fini et si on quite ça modifie le fini (0->1)
	while (!fini){
		get = AfficherMenu(nbMenuPrincipal,MenuPrincipal,DefaultStr);
		innerfini=0;
		switch(get){
			case 0:
			//Gestion des Enseignements
				while (!innerfini){
					//meme chose que le premier while
					innerget = AfficherMenu (nbMenuEnseigments,MenuEnseigments,DefaultStr);
					switch(innerget){
						case 0:
							MenuAjouterEnseignement(c);//ajjoute un enseignement
							break;
						case 1:
							MenuModifierEnseignement(e,c);//modifie un enseignement
							break;
						case 2:
							MenuSupprimerEnseignement(e,c);//supprime un enseignement
							break;
						case 3:
							MenuAfficherEnseignement(c);//affiche la liste des enseignements par heure
							break;
						case 4:
							innerfini=1;
							break;
					}
				}
				break;
			case 1:
			//Gestion des Salles
				while (!innerfini){
					//meme chose que le premier while
					innerget = AfficherMenu (nbMenuSalles,MenuSalles,DefaultStr);
					switch(innerget){
						case 0:
							MenuAjouterSalle(e);//ajoute une salle au batiment (pousse les murs)
							break;
						case 1:
							MenuModifierSalle(e);//modifie le nom (numero) ou le type d'une salle
							break;
						case 2:
							MenuSupprimerSalle(e);//supprime une salle (tire les nurs)
							break;
						case 3:
							MenuAfficherSalles(e); //affiche l'ensembre des salles ou les salles dans un etage donné par l'utilisateur
							break;
						case 4:
							innerfini=1;
							break;
					}
				}
				break;
			case 2:
			//Gestion des Reservations
				while (!innerfini){
					innerget = AfficherMenu (nbMenuReservation,MenuReservation,DefaultStr);
					switch(innerget){
						case 0:
							MenuReserver(e,c);//reserve une salle pour un enseignement
							break;
						case 1:
							MenuAnnuleReservation(e);//annule une reservation parmis la liste de reservation 
							break;
						case 2:
							MenuModifieReservation(e,c);//modifie une reservation parmis la liste de reservation
							break;
						case 3:
							AfficheReservationMenu(e);// affiche la liste des salles reservées
							break;
						case 4:
							innerfini=1;
							break;
					}
				}
				break;
			case 3:
			//quite programme
				fini =1;
				break;
		}
	}
}
