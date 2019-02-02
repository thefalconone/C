#ifndef H_FUSEE
#define H_FUSEE

#include "struct.h"
float deltav(stage* s);
int costfusee(stage* s);
float minfuseetwr(stage* s);
float maxfuseetwr(stage* s);
stage* initialisefusee();
void freefusee(stage* s);
void addstage(stage* s, int* indiceft, fueltank* listft, engine e);
void afficherfusee(stage* s);
float scorefusee(stage* s);

#endif