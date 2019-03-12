#include <stdio.h>
#include <unistd.h>//pour le sleep
#include <pthread.h>

void * courroux(void *n){
	for(int i=0; i<*(int*)n; i++){
		printf("et mon courroux\n");
		sleep(1);
	}
	pthread_exit(NULL);
}

int main(){

	int m,n;
	scanf("%d",&m);
	scanf("%d",&n);
	
	pthread_t tid;
	pthread_create(&tid, NULL, (void*)*courroux, (void *)&n);
	
	for(int i=0; i<m; i++){
		printf("coucou\n");
		sleep(1);
	}
	
	pthread_cancel(tid);
	
	return 0;
}

