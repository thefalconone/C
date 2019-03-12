#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>


//TOUJOURS TESTER LES VALEURS DE RETOUR


union semun {
	int val; /* valeur pour SETVAL */
	struct semid_ds *buf; /* tampon pour IPC STAT, IPC SET
	*/
	unsigned short int *array; /* tableau pour GETALL,
	SETALL */
	struct seminfo *buff; /* tampon pour IPC INFO */
};

int main(){
	char chaine[200];
	int semaphore = semget((key_t)10,1,0666 | IPC_CREAT); //création sémaphore
	union semun arg;
	arg.val=1;

	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_flg = 0;

	int pid = fork();
	switch(pid){
		case -1: 
			printf("erreur du fork\n");
			break;
		case 0: //fils

			printf("bonjour, je suis ton fils\n");
			while(1){
				//attente sémaphore
				buf.sem_op = -1; //-1 met en attente(lock), +1 reveil (unlock)
				semop(semaphore, &buf, 1);

				printf("Fils - Ecrit une chaine de caractères\n");
				scanf("%s", chaine);

				buf.sem_op = 1; //-1 met en attente(lock), +1 reveil (unlock)
				semop(semaphore, &buf, 1);
			}
			exit(0);
			break;
		default: //père

			semctl(semaphore, 0, SETVAL, arg); // initialisation sémaphore
			
			while(1){
				//attente sémaphore
				buf.sem_op = -1; //-1 met en attente(lock), +1 reveil (unlock)
				semop(semaphore, &buf, 1);

				printf("Père - Ecrit une chaine de caractères\n");
				scanf("%s", chaine);

				buf.sem_op = 1; //-1 met en attente(lock), +1 reveil (unlock)
				semop(semaphore, &buf, 1);
			}

			exit(EXIT_SUCCESS);
			break;

	}
}