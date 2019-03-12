#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>

void sigHandler(int sig){
	if(sig == SIGUSR1){
		printf("SIGUSR1 reçu sur le programme %d\n", getpid());
		exit(0);
	}
	if(sig == SIGCHLD){
		printf("SIGCHLD reçu sur le programme %d\n", getpid());
	}
	else{
		printf("signal inconnu reçu sur le programme %d\n", getpid());
	}
}

int main(){

	sigset_t mask;
	//on bloque tous les signaux
	sigfillset(&mask);
	//on débloque SIGUSR1, le ctrl-c et le SIGCHLD
	sigdelset(&mask, SIGUSR1);
	sigdelset(&mask, SIGINT);
	sigdelset(&mask, SIGCHLD);
	//enregistrement des masks
	sigprocmask(SIG_SETMASK, &mask, NULL);

	//le père est le fils sont sensibles au signal SIGUSR1
	signal(SIGUSR1, sigHandler);

	int cid = fork();//cid est l'id du fils

	if(cid == -1){
		printf("erreur fork\n");
		exit(0);
	}

	if(cid == 0){
		printf("pid fils: %d\n", getpid());
		while(1);
	}

	else{
		printf("pid père: %d\n", getpid());
		//le père est attentif à la mort du fils
		signal(SIGCHLD, sigHandler);
		sleep(1);
		//on tue le fils
		kill(cid, SIGUSR1);
		while(1);
	}
}
