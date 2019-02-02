#include "../inc/genetic.h"
#include "../inc/affichage.h"
#include "../inc/menu.h"
#include <stdlib.h>
#include <stdio.h>

extern float ratiokill, moddeltav, modcost, modtwr, minusertwr, maxusertwr, payload;
extern int nbpop, nbmut, nbmaxft, nbmaxstages, nbgen, mindv, maxdv, mincost, maxcost;

//efface tout le texte affiché dans le terminal
void clear(){
	system("clear");//pour Linux
	//system("cls");//pour Windows
}

//récupère un entier à l'entrée stdin
int scanint(){
	char s[1000];
	fpurge(stdin);
	scanf("%s",s);
	return atoi(s);
}

//récupère un float à l'entrée stdin
float scanfloat(){
	char s[1000];
	fpurge(stdin);
	scanf("%s",s);
	return atof(s);
}

void afficherpieces(fueltank* listft, engine* listeng){
	printf("1) Fuel tanks\n2) Engines\n:");
	int rep=scanint();
	clear();
	if(rep==1)
		afficherlistft(listft, 41);
	else
		afficherlisteng(listeng, 24);
	printf("Appuyez sur une touche puis entrée pour continuer\n:");
	rep=scanint();
}

void genetique(){
	printf("1) Taille de la population\n2) Nombre de mutants\n3) Portion de population tuée par gen\n4) Nombre de générations\n5) Retour\n:");
	int rep=scanint();
	clear();

	switch (rep){
		case 1:
			printf("Actuel: %d\n",nbpop);
			printf("Entrez un nombre entre 0 et 10000\n:");
			nbpop=scanint();
			break;

		case 2:
			printf("Actuel: %d\n",nbmut);
			printf("Entrez un nombre entre 0 et la taille de la population\n:");
			nbmut=scanint();
			break;

		case 3:
			printf("Actuel: %f\n",ratiokill);
			printf("Entrez un nombre strictement entre 0 et 1\n:");
			ratiokill=scanfloat();
			break;

		case 4:
			printf("Actuel: %d\n",nbgen);
			printf("Entrez un nombre entre 0 et 10000\n:");
			nbgen=scanint();
			break;

		case 5:
			break;

		default:
			break;
	}
}

void menuchargement(){
	float satellite = 0.02*2 + 0.01 + 0.04, capsule = 2.72 + 1.3 + 0.3, reservoir = 36.0;
	printf("Actuel: ");

	if(payload==satellite)//2 solar panels + 1 battery bank + 1 probodobodyne OKTO2
		printf("petit satellite de %.2f tonnes\n", payload);
	else if(payload==capsule)
		printf("capsule de %.2f tonnes\n", payload);//MK3 capsule + heatshield + parachute
	else if(payload==reservoir)
		printf("grand réservoir de %.2f tonnes\n", payload);//Rockomax Jumbo-64 Fuel Tank
	else
		printf("chargement custom de %.2f tonnes\n", payload);

	printf("Choix du chargement\n1) petit satellite\n2) capsule\n3) grand réservoir\n4) custom\n5) Retour\n:");
	int rep=scanint();
	clear();

	switch (rep){
		case 1:
			payload = satellite;
			break;

		case 2:
			payload = capsule;
			break;

		case 3:
			payload = reservoir;
			break;

		case 4:
			printf("Entrez un nombre entre entre 0 et 100\n:");
			payload = scanfloat();
			break;

		case 5:
			break;

		default:
			break;
	}
}

void fusee(){
	printf("1) Nombre max de fuel tanks\n2) Nombre max d'étages\n3) Modifier le chargement\n4) Retour\n:");
	int rep=scanint();
	clear();

	switch (rep){
		case 1:
			printf("Actuel: %d\n",nbmaxft);
			printf("Entrez un nombre entre 0 et 10\n:");
			nbmaxft=scanint();
			break;

		case 2:
			printf("Actuel: %d\n",nbmaxstages);
			printf("Entrez un nombre entre 0 et 10\n:");
			nbmaxstages=scanint();
			break;

		case 3:
			menuchargement();
			break;

		case 4:
			break;

		default:
			break;
	}
}

void menudv(){
	printf("1) Importance\n2) Minimum\n3) Maximum\n4) Retour\n:");
	int rep=scanint();
	clear();

	switch (rep){
		case 1:
			printf("Actuel: %f\n",moddeltav);
			printf("Entrez un nombre entre 0 et 3\n:");
			moddeltav=scanfloat();
			break;

		case 2:
			printf("Actuel: %d\n",mindv);
			printf("Entrez un nombre\n:");
			mindv=scanint();
			break;

		case 3:
			printf("Actuel: %d\n",maxdv);
			printf("Entrez un nombre\n:");
			maxdv=scanint();
			break;

		case 4:
			break;

		default:
			break;
	}
}

void menucost(){
	printf("1) Importance\n2) Minimum\n3) Maximum\n4) Retour\n:");
	int rep=scanint();
	clear();

	switch (rep){
		case 1:
			printf("Actuel: %f\n",modcost);
			printf("Entrez un nombre entre 0 et 3\n:");
			modcost=scanfloat();
			break;

		case 2:
			printf("Actuel: %d\n",mincost);
			printf("Entrez un nombre\n:");
			mincost=scanint();
			break;

		case 3:
			printf("Actuel: %d\n",maxcost);
			printf("Entrez un nombre\n:");
			maxcost=scanint();
			break;

		case 4:
			break;

		default:
			break;
	}
}

void menutwr(){
	printf("1) Importance\n2) Minimum\n3) Maximum\n4) Retour\n:");
	int rep=scanint();
	clear();

	switch (rep){
		case 1:
			printf("Actuel: %f\n",modtwr);
			printf("Entrez un nombre entre 0 et 3\n:");
			modtwr=scanfloat();
			break;

		case 2:
			printf("Actuel: %f\n",minusertwr);
			printf("Entrez un nombre\n:");
			minusertwr=scanfloat();
			break;

		case 3:
			printf("Actuel: %f\n",maxusertwr);
			printf("Entrez un nombre\n:");
			maxusertwr=scanfloat();
			break;

		case 4:
			break;

		default:
			break;
	}
}

void score(){
	int rep=0;

	while(rep!=4){

		clear();
		printf("1) deltaV\n2) coût\n3) TWR\n4) Retour\n:");
		rep=scanint();
		clear();

		switch (rep){
			case 1:
				menudv();
				break;

			case 2:
				menucost();
				break;

			case 3:
				menutwr();
				break;

			case 4:
				rep=4;
				break;

			default:
				rep=0;
		}
	}
}

void parametres(){
	int rep=0;

	while(rep!=4){

		clear();
		printf("1) Génétique\n2) Fusée\n3) Score\n4) Retour\n:");
		rep=scanint();
		clear();

		switch (rep){
			case 1:
				genetique();
				break;

			case 2:
				fusee();
				break;

			case 3:
				score();
				break;

			case 4:
				rep=4;
				break;

			default:
				rep=0;
		}
	}
}

void menu(engine* listeng, fueltank* listft){
	clear();
	int rep=0;
	while(rep!=4){

		printf("1) Afficher les pièces\n2) Générer une fusée\n3) Modifier les paramètres\n4) Quitter\n:");
		rep=scanint();
		clear();

		switch (rep){
			case 1:
				afficherpieces(listft, listeng);
				break;

			case 2:
				genetic(listft, listeng);
				printf("fusee.html générée\n");
				break;

			case 3:
				parametres();
				break;

			case 4:
				rep=4;
				break;

			default:
				rep=0;
		}
		clear();
	}
}
