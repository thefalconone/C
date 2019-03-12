#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>

//TOUJOURS TESTER LES VALEURS DE RETOUR


struct sembuf buf[2];
int semaphore;

union semun {
	int val; /* valeur pour SETVAL */
	struct semid_ds *buf; /* tampon pour IPC STAT, IPC SET
	*/
	unsigned short int *array; /* tableau pour GETALL,
	SETALL */
	struct seminfo *buff; /* tampon pour IPC INFO */
};

void lock(int i){
	buf[i].sem_op = -1; //-1 met en attente(lock), +1 reveil (unlock)
	if(semop(semaphore, &buf[i], 1) == -1){
		perror("semop lock");
		exit(EXIT_FAILURE);
	}
}

void unlock(int i){
	buf[i].sem_op = 1; //-1 met en attente(lock), +1 reveil (unlock)
	if(semop(semaphore, &buf[i], 1) == -1){
		perror("semop unlock");
		exit(EXIT_FAILURE);
	}
}

int main(){
	int shm;
	int* adresse;

	if((semaphore = semget((key_t)10,2,0666 | IPC_CREAT)) == -1){ //création sémaphore
		perror("semget");
		exit(EXIT_FAILURE);		
	}
	if((shm = shmget((key_t)1,sizeof(int),0666 | IPC_CREAT)) == -1){
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	
	if ((adresse = (int*)(shmat(shm, 0, 0))) == (int*)-1){
		perror("shmat");
		exit(EXIT_FAILURE);		
	}
	union semun arg;
	arg.val=1;

	buf[0].sem_num = 0;
	buf[0].sem_flg = 0;
	buf[1].sem_num = 1;
	buf[1].sem_flg = 0;

	*adresse = 0;

	int pid = fork();
	switch(pid){
		case -1: 
			printf("erreur du fork\n");
			break;
		case 0: //fils

			printf("bonjour, je suis ton fils\n");
			while(*adresse < 1000){
				//attente sémaphore
				lock(0);

				//lecture
				printf("fils - %d\n", *adresse);
				//ecriture
				*adresse += 1;

				unlock(1);

			}
			exit(EXIT_SUCCESS);
			break;
		default: //père

			if(semctl(semaphore, 0, SETVAL, arg) == -1){ // initialisation sémaphore bloqué
				perror("semctl");
				exit(EXIT_FAILURE);				
			}
			if(semctl(semaphore, 1, SETVAL, arg) == -1){ // initialisation sémaphore bloqué
				perror("semctl");
				exit(EXIT_FAILURE);				
			}
			lock(0);
			lock(1);

			struct timeval stop,start;
			gettimeofday(&start,NULL);

			while(*adresse < 1000){

				//ecriture
				*adresse += 1;

				//attente sémaphore
				unlock(0);

				lock(1);

				//lecture
				printf("pere - %d\n", *adresse);
			}

			gettimeofday(&stop,NULL);
			unsigned long sec = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
			printf("Débit = %.3lf ko/s\n", (double)1000*4*(*adresse)/(double)sec);

			exit(EXIT_SUCCESS);
			break;

	}
}