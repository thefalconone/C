#ifndef H_FUSEE
#define H_FUSEE

#include "struct.h"

//calcul du deltav d'une fusée
float deltav(stage* s);

//calcul du cout d'une fusée
int costfusee(stage* s);

//calcul du twr minimum sur tous les étages d'une fusée
float minfuseetwr(stage* s);

//calcul du twr maximum sur tous les étages d'une fusée
float maxfuseetwr(stage* s);

//alloue la mémoire d'une fusée et mets en place certaines variables
stage* initialisefusee();

//libère la mémoire allouée à une fusée
void freefusee(stage* s);

//ajoute un étage en bas de la fusée
void addstage(stage* s, int* indiceft, fueltank* listft, engine e);

//retourne le score d'une fusée par rappot aux paramètres
float scorefusee(stage* s);

#endif