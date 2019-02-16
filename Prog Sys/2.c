#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>

pthread_mutex_t mutx=PTHREAD_MUTEX_INITIALIZER, muty=PTHREAD_MUTEX_INITIALIZER;
int *px=NULL, *py=NULL;

void* thread1(void* max){

	for(int i=0; i< *(int*)max; i++){
		pthread_mutex_lock(&mutx);
		printf("thread1: %d\n", *px);
		pthread_mutex_unlock(&mutx);
	}
	pthread_exit(NULL);
}

void* thread2(void* max){

	for(int i=0; i< *(int*)max; i++){
		pthread_mutex_lock(&muty);
		printf("thread2: %d\n", *py);
		pthread_mutex_unlock(&muty);
	}
	pthread_exit(NULL);
}

int main(){
	int x=1, y=2, max=10;
	px=&x;
	py=&y;

	pthread_t tid1;
	pthread_create(&tid1, NULL, thread1, (void*)&max);
	pthread_t tid2;
	pthread_create(&tid2, NULL, thread2, (void*)&max);
	
	int i=0;
	while (i<10){

		if(pthread_mutex_trylock(&mutx)==0){
			if(pthread_mutex_trylock(&muty)==0){
				px=NULL;
				py=NULL;
				printf("main: %d\n", i++);
				px=&x;
				py=px;
				pthread_mutex_unlock(&muty);
			}
			pthread_mutex_unlock(&mutx);
		}
	}
	
	pthread_cancel(tid1);
	pthread_cancel(tid2);
	
	return 0;
}
