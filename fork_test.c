#include <stdio.h>
int main(){
	int a = 10;
	int b = 100;
	int pid;

	a = a + 10;
	sleep(10);
	pid = fork();
	if(pid==0){
		printf("CHILD\n");
		b = b + 10;
		printf("[CHILD] a = %d, b = %d\n",a,b);
		sleep(20);
	}else if(pid>0){
		printf("PARENT\n");
		a = a + 10;
		printf("[PARENT] a = %d, b = %d\n",a,b);
		sleep(20);
	}else
		printf("fork() unexcuted\n");
	return 0;
}
