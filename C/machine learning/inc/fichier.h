#ifndef H_FICHIER
#define H_FICHIER

#include "struct.h"

//récupère les données dans data/fueltank.txt et retourne une liste de fueltanks
fueltank* lirefttxt();

//récupère les données dans data/engine.txt et retourne une liste d'engines
engine* lireengtxt();

//lecture de data/settings.txt et affectation des variables globales
void readsettings();

//sauvegarde des variables globales dans data/settings.txt
void savesettings();

#endif