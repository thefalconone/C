#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>

pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ressources=4;

void* thread1(void* max){

	//demande 3 ressources
	pthread_mutex_lock(&mut);
	while(ressources<3){
		pthread_cond_wait(&cond, &mut);
	}
	ressources-=3;
	printf("thread 1 prends 3 ressources\n");
	pthread_mutex_unlock(&mut);


	//libère 3 ressources
	pthread_mutex_lock(&mut);
	ressources+=3;
	printf("thread 1 libère 3 ressources\n");
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);

	pthread_exit(NULL);
}

void* thread2(void* max){

	//demande 2 ressources
	pthread_mutex_lock(&mut);
	while(ressources<2){
		pthread_cond_wait(&cond, &mut);
	}
	ressources-=2;
	printf("thread 2 prends 2 ressources\n");
	pthread_mutex_unlock(&mut);


	//libère 2 ressources
	pthread_mutex_lock(&mut);
	ressources+=2;
	printf("thread 2 libère 2 ressources\n");
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);

	pthread_exit(NULL);
}

//thread 3
int main(){
	int max=10;

	pthread_t tid1;
	pthread_create(&tid1, NULL, thread1, (void*)&max);
	pthread_t tid2;
	pthread_create(&tid2, NULL, thread2, (void*)&max);


	//demande 1 ressources
	pthread_mutex_lock(&mut);
	while(ressources<1){
		pthread_cond_wait(&cond, &mut);
	}
	ressources-=1;
	printf("thread 3 prends 1 ressources\n");
	pthread_mutex_unlock(&mut);


	//libère 1 ressources
	pthread_mutex_lock(&mut);
	ressources+=1;
	printf("thread 3 libère 1 ressources\n");
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	return 0;
}
