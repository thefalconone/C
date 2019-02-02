#include "../inc/fichier.h"
#include "../inc/menu.h"
#include <stdlib.h>
#include <time.h>

//paramètres globaux modifiables que dans le menu et par readsettings();
float ratiokill, moddeltav, modcost, modtwr, minusertwr, maxusertwr, payload;
int nbpop, nbmut, nbmaxft, nbmaxstages, nbgen, mindv, maxdv, mincost, maxcost;


int main(int argc, char* argv[]){

	//initialisation de la fonction rand()
	time_t t;
	srand((unsigned) time(&t));

	//lecture des fichiers engine.txt et fueltank.txt
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();

	//affectation des variables globales dans data/settings.txt
	readsettings();

	//affichage du menu
	menu(listeng, listft);

	//sauvegarde des variables globales dans data/settings.txt
	savesettings();
	return 0;
}