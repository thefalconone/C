#include "main.h"

//strictement entre 0 et 1
//0.25 = on tue 25% de la pop
//ratiokill ne fonctionne bien qu'avec la valeur 0.5
float ratiokill=0.5, moddeltav=3, modcost=1, modtwr=1;
int nbpop=1000, nbmut=300, nbmaxft=3, nbmaxstages=5, nbgen=60;

int scanint(){
	char s[1000];
	fpurge(stdin);
	scanf("%s",s);
	return atoi(s);
}

float scanfloat(){
	char s[1000];
	fpurge(stdin);
	scanf("%s",s);
	return atof(s);
}

void afficherpieces(fueltank* listft, engine* listeng){
	printf("1) Fuel tanks\n2) Engines\n:");
	int rep=scanint();
	system("clear");
	if(rep==1)
		afficherlistft(listft, 41);
	else
		afficherlisteng(listeng, 24);
	printf("Appuyez sur une touche puis entrée pour continuer\n::");
	rep=scanint();
}

void generer(fueltank* listft, engine* listeng){
	genetic(listft, listeng);
	printf("Appuyez sur une touche puis entrée pour continuer\n:");
	scanint();
}

void genetique(){
	printf("1) Taille de la population\n2) Nombre de mutants\n3) Portion de population tuée par gen\n4) Nombre de générations\n:");
	int rep=scanint();
	system("clear");
	printf("Entrez un nombre ");

	switch (rep){
		case 1:
			printf("Actuel: %d\n",nbpop);
			printf("entre 0 et 10000\n:");
			nbpop=scanint();
			break;

		case 2:
			printf("Actuel: %d\n",nbmut);
			printf("entre 0 et la taille de la population\n:");
			nbmut=scanint();
			break;

		case 3:
			printf("Actuel: %f\n",ratiokill);
			printf("strictement entre 0 et 1\n:");
			ratiokill=scanfloat();
			break;

		case 4:
			printf("Actuel: %d\n",nbgen);
			printf("entre 0 et 10000\n:");
			nbgen=scanint();
			break;

		default:
			rep=0;
	}
}

void fusee(){
	printf("1) Nombre max de fuel tanks\n2) Nombre max d'étages\n:");
	int rep=scanint();
	system("clear");
	printf("Entrez un nombre ");

	switch (rep){
		case 1:
			printf("Actuel: %d\n",nbmaxft);
			printf("entre 0 et 10\n:");
			nbmaxft=scanint();
			break;

		case 2:
			printf("Actuel: %d\n",nbmaxstages);
			printf("entre 0 et 10\n:");
			nbmaxstages=scanint();
			break;

		default:
			rep=0;
	}
}

void score(){
	printf("Importance du:\n1) deltaV\n2) coût\n3) TWR\n:");
	int rep=scanint();
	system("clear");
	printf("Entrez un nombre entre 0 et 3\n:");

	switch (rep){
		case 1:
			printf("Actuel: %f\n",moddeltav);
			moddeltav=scanfloat();
			break;

		case 2:
			printf("Actuel: %f\n",modcost);
			modcost=scanfloat();
			break;

		case 3:
			printf("Actuel: %f\n",modtwr);
			modtwr=scanfloat();
			break;

		default:
			rep=0;
	}
}

void parametres(){
	printf("1) Génétique\n2) Fusée\n3) Score\n");
	int rep=scanint();
	system("clear");

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

		default:
			rep=0;
	}
}

int main(int argc, char* argv[]){

	//initialisation de la fonction rand()
	time_t t;
	srand((unsigned) time(&t));

	//lecture des fichiers engine.txt et fueltank.txt
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();

	system("clear");
	int rep=0;
	while(rep!=4){

		printf("1) Afficher les pièces\n2) Générer une fusée\n3) Modifier les paramètres\n4) Quitter\n:");
		rep=scanint();
		system("clear");

		switch (rep){
			case 1:
				afficherpieces(listft, listeng);
				break;

			case 2:
				generer(listft, listeng);
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
		system("clear");
	}
	return 0;
}