#include <stdio.h>
#include <pthread.h>

int ncount = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *do_sum2(void *data){
	int i;
	int n = *((int*)data);
	for(i=0; i<n; i++){
		pthread_mutex_lock(&mutex);
		ncount++;
		printf("[%x] sum : %d\n",pthread_self(), ncount);
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	pthread_t thread_id[3];
	int status;
	int thr_id;
	int num[3] = {5,10,20};
	int i;
	for(i=0; i<3; i++){
		thr_id = pthread_create(&thread_id[i], NULL, do_sum2, (void *)&num[i]);
		pthread_join(thread_id[i], (void **)&status);
		sleep(1);
	}
	status = pthread_mutex_destroy(&mutex);
	printf("THREAD END.\n");
	return 0;
}
