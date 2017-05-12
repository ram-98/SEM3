#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
void work(){
	for (int i = 0; i < 2; i += 1)
	{
		sleep(rand()%4);
		printf("done passd %d\n",i);
	}
}
int main(){
	printf("i am %d\n",(int)getpid());
	pid_t pid=fork();
	printf("fork returned %d\n",(int)pid);
	if(pid==0){
	printf("i am child with pid %d\n",(int)getpid());
	printf("fork returned %d\n",(int)pid);
	//printf("child waiting.\n");
	//sleep(5);
	//printf("child exeting.\n");
	//printf("child exeting.\n");	
	work();
	exit(42);
	///printf("taek was %d \n",take);
	}
	
	printf("i am parent with pid %d\n",(int)getpid());
	
	printf("fork returned %d\n",(int)pid);
	printf("im parent waitng \n");
	sleep(30);
	int status =0;
		printf("status BEFORE WAIT was %d \n",status);
	pid_t childpid =wait(&status);
	printf("status was %d \n",status);
	printf("paretn knowas child %d finished with status %d \n",(int )childpid,status);
	int childreturnvalue=WEXITSTATUS(status);
	printf("return value was %d \n",childreturnvalue);
		printf("status was %d \n",status);

	printf("im parent ending \n");
    	return 0;
}
