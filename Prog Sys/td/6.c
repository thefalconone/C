#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

sigset_t masque1;
sigset_t masque2;

void handler(int sig){
	if(sig==SIGUSR1)
		printf("SIGUSR1 recu\n");

}

void* thread(void* arg){
	int mainid=*(int*)arg;

	sigfillset(&masque1);
	sigdelset(&masque1, SIGUSR1);
	sigprocmask(SIG_SETMASK, &masque1, NULL);

	struct sigaction action;
	action.sa_handler = handler;
	action.sa_flags=0;
	sigaction(SIGUSR1, &action, NULL);
	printf("thread: masque créé\n");

	pthread_exit(NULL);
}

int main(){

	sigfillset(&masque2);
	sigdelset(&masque2, SIGUSR1);
	sigprocmask(SIG_SETMASK, &masque2, NULL);

	struct sigaction action;
	action.sa_handler = handler;
	action.sa_flags=0;
	sigaction(SIGUSR2, &action, NULL);
	printf("main: masque2 créé\n");

	pthread_t tid;
	pthread_t mainid = pthread_self();
	pthread_create(&tid, NULL, thread, (void*)&mainid);

	pthread_cancel(tid);

	return 0;
}
