#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleeps
#include <sys/time.h>

int main(){
	int nb_msg=10000, taille_msg=1;
	char jeton[taille_msg];
	int size = sizeof(jeton);

	//------creation du pipe----------

	//0 = lecture, 1 = ecriture
	//ptoc = parent to child
	int pipeptoc[2], pipectop[2];

	if(pipe(pipeptoc) == -1){
		printf("échec création pipeptoc\n");
		exit(0);
	}
	if(pipe(pipectop) == -1){
		printf("échec création pipectop\n");
		exit(0);
	}

	//------------fork--------------

	int cid = fork();//cid est l'id du fils

	if(cid == -1){
		printf("erreur fork\n");
		exit(0);
	}

	if(cid == 0){//---------fils

		//fermeture de la lecture
		close(pipectop[0]);
		//fermeture de l'ecriture
		close(pipeptoc[1]);

		for(int i=0; i<nb_msg; i++){
			read(pipeptoc[0], &jeton, size);//4 = sizeof(int)
			write(pipectop[1], &jeton, size);
		}

		//fermeture de la lecture
		close(pipeptoc[0]);
		//fermeture de l'ecriture
		close(pipectop[1]);
	}

	else{//----------------père

		//fermeture de la lecture
		close(pipeptoc[0]);
		//fermeture de l'ecriture
		close(pipectop[1]);


		//calcul du temps
		struct timeval stop, start;
		gettimeofday(&start, NULL);

		for(int i=0; i<nb_msg; i++){
			write(pipeptoc[1], &jeton, size);//4 = sizeof(int)
			read(pipectop[0], &jeton, size);
		}

		//arrêt du timer
		gettimeofday(&stop, NULL);
		unsigned long microsec = stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec)/1000000.0;
		printf("débit pour des msg de %d octets:  	%.3lfMo/s\n", taille_msg, nb_msg*size*2/(double)microsec);

		//fermeture de la lecture
		close(pipectop[0]);
		//fermeture de l'ecriture
		close(pipeptoc[1]);
	}
}
