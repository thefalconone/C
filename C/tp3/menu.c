#include "automate.h"

void menu(automate* a){
	int rep=0;
	do{

		afficher(a->g);
		printf("1) Modifier le graphe\n2) Modifier l'automate\n3) Afficher les mots reconnus\n4) Reconnaitre un mot\n5) Enregistrer et quitter\n:");
		char s[100];
		scanf("%s",s);
		int rep=atoi(s);

		switch (rep){
			case 1:
				printf("1) Ajouter arc\n2) Retirer arc\n:");
				scanf("%s",s);
				rep=atoi(s);
				char etiq;
				int debut,fin;
				printf("<etiquette> <sommet de départ> <sommet d'arrivée> :");
				scanf("%c %d %d", &etiq, &debut, &fin);
				if(rep==1){ ajouter_arc(a->g, etiq, debut, fin); }
				if(rep==2){ retirer_arc(a->g, etiq, debut, fin); }
				rep=0;
				break;

			case 2:
				printf("1) Modifier l'état initial\n2) Modifier l'état final\n3) Modifier l'alphabet\n:");
				scanf("%s",s);
				rep=atoi(s);
				if(rep==1){
					int etat_init;
					scanf("%d",&etat_init);
					a->etat_init=etat_init;
				}
				if(rep==2){
					int etat_final;
					scanf("%d",&etat_final);
					a->etat_final=etat_final;
				}
				if(rep==3){
					char alphabet[1000];
					scanf("%s",alphabet);
					a->alphabet=alphabet;
				}
				rep=0;
				break;
			
			case 3:
				printf("1) Exploration en largeur\n2) Exploration en profondeur\n:");
				scanf("%s",s);
				rep=atoi(s);
				int max;
				printf("Taille max des mots :");
				scanf("%d",&max);
				if(rep==1){ largeur(a,max); }
				if(rep==2){ profondeur(a,max); }
				rep=0;
				break;
			
			case 4:
				printf("Entrez votre mot\n:");
				scanf("%s",s);
				if(accepte(a,s)){ printf("Accepté\n");}
				else{printf("Refusé\n");}
				rep=0;
				break;
			
			case 5:
				rep=-1;
				break;
			
			default:
				rep=0;
		}

	}while(rep!=-1);
}