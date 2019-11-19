#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *func_thread(void *);

int main(){
	int status;
	pthread_t thread_id;
	status = pthread_create(&thread_id, NULL, func_thread, NULL);
	if(status !=0){
		printf("[ERROR]pthread_create() Failed\n");
		exit(0);
	}
	printf("thread [%x] is created.\n", thread_id);
	pthread_join(thread_id, (void **)&status);
	printf("main fuction exit.\n");
	return 0;
}

void *func_thread(void *arg){
	int i=0;

	while(i<10){
		sleep(1);
		i++;
		printf("thread %dth executing...\n",i);
	}
}
