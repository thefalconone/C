#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleeps
#include <sys/sem.h>

union semun {
	int val; /* valeur pour SETVAL */
	struct semid_ds *buf; /* tampon pour IPC STAT, IPC SET */
	unsigned short int *array; /* tableau pour GETALL, SETALL */
	struct seminfo *buff; /* tampon pour IPC INFO */
};

int main(){
	union senum init;
	init.val=1;

	//	 					clé		nb sémaph	droits
	int semaphore = semget((key_t) 1,	1,	0666 | IPC_CREAT);

	semctl(semaphore, 0, SETVAL, init);

	struct sembuf buf;
	buf.sem_num=0;
	buf.sem_op=-1;
	buf.sem_flg=0;
	semop(semaphore, &buf, 1);

	//------------fork--------------

	int cid = fork();//cid est l'id du fils

	if(cid == -1){
		printf("erreur fork\n");
		exit(0);
	}
	for(int i=0; i<2; i++){

	}
/*
	if(cid == 0){//---------fils

	}

	else{//----------------père

	}*/
}
