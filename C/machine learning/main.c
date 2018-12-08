#include "main.h"

int main(){
	engine* listeng=lireengtxt();
	fueltank* listft=lirefttxt();

	if(listeng!=NULL && listft!=NULL)//si les fichiers ont bien étés ouverts
		genetic(listft,listeng);
	return 0;
}