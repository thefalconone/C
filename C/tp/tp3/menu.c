#include "automate.h"

int scanint(){
	char s[1000];
	fpurge(stdin);
	scanf("%s",s);
	return atoi(s);
}

void modifier_graphe(automate* a){
	printf("1) Ajouter arc\n2) Retirer arc\n:");
	int rep=scanint();
	system("clear");

	char etiq;
	int debut,fin;
	afficher(a->g);
	printf("<etiquette> <départ> <arrivée> :");
	fpurge(stdin);
	//A CHANGER
	scanf("%c %d %d", &etiq, &debut, &fin);
	system("clear");

	if(rep==1){ ajouter_arc(a->g, etiq, debut, fin); }
	if(rep==2){ retirer_arc(a->g, etiq, debut, fin); }
}

void modifier_automate(automate* a){
	printf("1) Modifier l'état initial\n2) Modifier l'état final\n3) Modifier l'alphabet\n:");
	int rep=scanint();
	system("clear");

	if(rep==1){
		printf("<état initial> :");
		int etat_init=scanint();
		a->etat_init=etat_init;
	}
	if(rep==2){
		printf("<état final> :");
		int etat_final=scanint();
		a->etat_final=etat_final;
	}
	if(rep==3){
		fpurge(stdin);
		char alphabet[1000];
		printf("<alphabet> :");
		scanf("%s",alphabet);
		a->alphabet=malloc(strlen(alphabet)*sizeof(char));
		strcpy(a->alphabet,alphabet);
	}
	system("clear");
}

void explorer(automate* a){
	printf("1) Exploration en largeur\n2) Exploration en profondeur\n:");
	int rep=scanint();
	system("clear");

	printf("Taille max des mots :");
	int max=scanint();
	system("clear");

	if(rep==1){ largeur(a,max); }
	if(rep==2){ profondeur(a,max); }
	printf("Appuyez sur une touche puis entrée pour continuer\n");
	rep=scanint();
	system("clear");
}

void reconnaitre(automate* a){
	printf("Entrez votre mot :");
	fpurge(stdin);
	char s[1000];
	scanf("%s",s);
	system("clear");
	if(accepte(a,s)){ printf("Accepté\n");}
	else{printf("Refusé\n");}
	printf("Appuyez sur une touche puis entrée pour continuer\n");
	scanf("%s",s);
	system("clear");
}

void menu(automate* a){
	system("clear");
	int rep=0;
	while(rep!=5){

		afficher_automate(a);
		printf("1) Modifier le graphe\n2) Modifier l'automate\n3) Afficher les mots reconnus\n4) Reconnaitre un mot\n5) Enregistrer et quitter\n:");
		rep=scanint();
		system("clear");

		switch (rep){
			case 1:
				modifier_graphe(a);
				break;

			case 2:
				modifier_automate(a);
				break;
			
			case 3:
				explorer(a);
				break;
			
			case 4:
				reconnaitre(a);
				break;

			case 5:
				rep=5;
				break;

			default:
				rep=0;
		}
	}
}