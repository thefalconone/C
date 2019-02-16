#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>
#include <sys/types.h>

pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

void unlock(){
	pthread_mutex_unlock(&mut);
}

void* thread(void* arg){
	int max=*(int*)arg;

	pthread_cleanup_push(unlock(), NULL);
	pthread_mutex_lock(&mut);
	printf("j'ai le mutex\n");

	for(int i=0; i<max; i++){
		printf("thread:   %lu\n", pthread_self());
		sleep(0.1);
	}

	pthread_cleanup_pop(1);
	pthread_exit(NULL);
}

int main(){
	int max=6;

	for(int i=0; i<2; i++){

		pthread_t tid;
		pthread_create(&tid, NULL, thread, (void*)&max);

		for(int j=0; j<max/2; j++){
			printf("main tid: %lu\n",(unsigned long)tid);
			sleep(0.1);
		}
		pthread_cancel(tid);
		sleep(0.1);
	}

	return 0;
}
