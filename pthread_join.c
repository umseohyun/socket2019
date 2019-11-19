#include <stdio.h>
#include <pthread.h>

void *do_sum(void *);

int main(){
	pthread_t thread_id[3];
	int status;
	int thr_id;
	int num[3] = {4,5,6};
	int i;
	for(i=0;i<3;i++){
		thr_id = pthread_create(&thread_id[i], NULL, do_sum, (void*)&num[i]);
		pthread_join(thread_id[i], (void **)&status);
	}
	printf("Main Thread END\n");
}

void *do_sum(void *arg){
	int i;
	int max = *((int *)arg);
	int sum = 0;
	for(i=1; i<=max; i++){
		sum += i ;
		printf("[%d] - ADD %d\n",max, i);
	}
	printf("SUM of '1~%d' : %d\n",max,sum);
}
