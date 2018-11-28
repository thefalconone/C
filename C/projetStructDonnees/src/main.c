#include "emploiDuTemps.h"

int main(int argc, char* argv[]) {
	EmploiDuTemps e=InitialiseEmploiDuTemps();
	Enseignement c=InitialiseEnseignement();
	loadJSON(e,c);
	Menus(e,c);
	saveJSON(e,c);
}