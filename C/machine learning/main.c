#include "main.h"

//strictement entre 0 et 1
//0.25 = on tue 25% de la pop
//ratiokill ne fonctionne bien qu'avec la valeur 0.5
float ratiokill=0.5, moddeltav=6, modcost=1, modtwr=1, minusertwr=1, maxusertwr=5, payload=2.72 + 1.3 + 0.3;//poids d'une capsule
int nbpop=1000, nbmut=300, nbmaxft=3, nbmaxstages=5, nbgen=100, mindv=0, maxdv=-1, mincost=0, maxcost=-1;

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

void genetique(){
	printf("1) Taille de la population\n2) Nombre de mutants\n3) Portion de population tuée par gen\n4) Nombre de générations\n:");
	int rep=scanint();
	system("clear");

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

		default:
			break;
	}
}

void chargement(){
	float satellite = 0.02*2 + 0.01 + 0.04, capsule = 2.72 + 1.3 + 0.3, reservoir = 36.0;
	printf("Actuel: ");

	if(payload==satellite)//2 solar panels + 1 battery bank + 1 probodobodyne OKTO2
		printf("petit satellite de %.2f tonne\n", payload);
	else if(payload==capsule)
		printf("capsule de %.2f tonnes\n", payload);//MK3 capsule + heatshield + parachute
	else if(payload==reservoir)
		printf("grand réservoir de %.2f tonnes\n", payload);//Rockomax Jumbo-64 Fuel Tank
	else
		printf("chargement custom de %.2f tonnes\n", payload);

	printf("Choix du chargement\n1) petit satellite\n2) capsule\n3) grand réservoir\n4) custom\n:");
	int rep=scanint();
	system("clear");

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
		default:
			break;
	}
}

void fusee(){
	printf("1) Nombre max de fuel tanks\n2) Nombre max d'étages\n3) Modifier le chargement\n:");
	int rep=scanint();
	system("clear");

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
			chargement();
			break;

		default:
			break;
	}
}

void menudv(){
	printf("1) Importance\n2) Minimum\n3) Maximum\n:");
	int rep=scanint();
	system("clear");
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
			mindv=scanint();
			break;

		default:
			break;
	}
}

void menucost(){
	printf("1) Importance\n2) Minimum\n3) Maximum\n:");
	int rep=scanint();
	system("clear");
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
			mincost=scanint();
			break;

		default:
			break;
	}
}

void menutwr(){
	printf("1) Importance\n2) Minimum\n3) Maximum\n:");
	int rep=scanint();
	system("clear");
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
			minusertwr=scanfloat();
			break;

		default:
			break;
	}
}

void score(){
	printf("1) deltaV\n2) coût\n3) TWR\n:");
	int rep=scanint();
	system("clear");

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

		default:
			break;
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
			break;
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
				genetic(listft, listeng);
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