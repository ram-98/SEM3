
                            //FIBONOCCI SEQUENCE USING MULTI-PROCESS PROGRAM

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include<stdlib.h>
#include<time.h>
#include <sys/mman.h>



using namespace std;

void function(int x);                                               /* child call this function */

volatile int *fibo;                                                 /* this data is shared by the thread(s) and store the fibo output */


int main(int argc, char *argv[]){

            int a=0,b=1,var=1;
    
            clock_t  begin=clock();                                        //Begins clock     

             if (argc != 2) {

                fprintf(stderr,"usage: a.out <integer value>\n");
                return -1;
            }
            if (atoi(argv[1]) < 0) {

                fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
                return -1;
            }
 
            fibo = (int *)mmap(0, atoi(argv[1])*sizeof(int), PROT_READ|PROT_WRITE,       // Map space for shared array
                            MAP_SHARED | MAP_ANONYMOUS, -1, 0);                          // and Dynamically creating array 
             if (!fibo) {

                    perror("mmap failed");
                    exit(1);
                }
            int status=0;
            pid_t wpid;
            for (int i = 0 ; i < 5; i++ ) {                                              //Main  generating first five numbers 
                        fibo[i]=var;
                        var=a+b;
                        a=b;
                        b=var;
	        }

            for (int i = 0; i <atoi(argv[1])-5 ; i++){  
                                                                         /* fork a child process */
                    pid_t pid = fork();
                    if (pid < 0) {  
                                                                           /* error occurred */
                            fprintf(stderr, "Fork Failed");
                             return 1;
                     }
                     else if (pid == 0) {  
                                                                            /* child process */
                                function(i);
                        }
                }
    
                while ((wpid = wait(&status)) > 0){}                        /*wait for all the child process  to exit */

                 printf("The fibonocci series is\n");                        //Printing result
                for (int j = 0; j <atoi(argv[1]) ; j++){

                        printf("  %d\n",fibo[j]);
                 }
                 clock_t end=clock();                                         //Ending clock

                printf("Time taken :- %f \n",(double)(end-begin)/CLOCKS_PER_SEC);
                return 0;

        }
                                                                             // Each child process will begin control in this function
                                                                            //and each child generates one number
void function(int x){
    
            x=x+5;
            while(fibo[x-1]==0){}
            fibo[x]=fibo[x-1]+fibo[x-2]; 
            exit(0);
}