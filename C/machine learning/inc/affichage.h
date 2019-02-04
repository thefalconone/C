#ifndef H_AFFICHAGE
#define H_AFFICHAGE

#include "struct.h"

//affiche tous les fueltanks dans stdin
void afficherlistft(fueltank* listft, int l);

//affiche tous les engines dans stdin
void afficherlisteng(engine* listeng, int l);

//crée le fichier fusee.html et le rempli avec la fusée fourni dans le dossier racine
void creerfuseehtml(stage* s);

#endif