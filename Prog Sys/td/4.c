#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>
#include <sys/types.h>

pthread_key_t key;

int incrementation(){
	int *i=pthread_getspecific(key);
	(*i)++;
	return *i;
}

void* thread(void* arg){
	int max=*(int*)arg;

	int *i = malloc(sizeof(int));
	pthread_setspecific(key, i);

	for(int j=0; j<max; j++){
		printf("thread: %lu inc: %d\n", pthread_self(), incrementation());
		sleep(0.1);
	}

	pthread_exit(NULL);
}

int main(){
	int max=3;
	pthread_key_create(&key, NULL);


	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread, (void*)&max);
	pthread_create(&tid2, NULL, thread, (void*)&max);

	int *i = malloc(sizeof(int));
	pthread_setspecific(key, i);

	for(int j=0; j<max; j++){
		printf("main: %lu inc: %d\n", pthread_self(), incrementation());
		sleep(0.1);
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
