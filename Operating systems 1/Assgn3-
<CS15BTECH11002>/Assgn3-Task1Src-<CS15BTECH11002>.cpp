                           
                            //FIBONOCCI SEQUENCE USING MULTI-THREADED PROGRAM

#include <pthread.h>
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include <cstdlib>
#include<time.h>


using namespace std;
int *array;                                                 //array to store index postion to be passed
int *fibo=0;    
                                                            /* this data is shared by the thread(s) and store the fibo output */

void *runner(void * param);                                 /* threads call this function */

int main(int argc, char *argv[])
{
        pthread_attr_t attr;                                 /* set of thread attributes */
        int a=0,b=1,var=1;

        if (argc != 2) { 
            fprintf(stderr,"usage: a.out <integer value>\n");
            return -1;
         }
        if (atoi(argv[1]) < 0) {
            fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
            return -1;
        }
        clock_t begin,end;                                       //Begins clock 
        begin=clock();                   
                                                                //Dynamically creating array 
        fibo = (int*) malloc( atoi(argv[1])* sizeof(int));    

        array = (int*) malloc( atoi(argv[1])* sizeof(int));

        for (int i = 0 ; i < 5; i++ ) {                          //Main  generating first five numbers 
                  fibo[i]=var;
                  var=a+b;
                  a=b;
                  b=var;
            }
        for (int i = 0 ; i < atoi(argv[1]); i++ ) {             //Setting the array elements to its position 
                array[i]=i;
	        }

        pthread_t workers[atoi(argv[1])-5];                                 /* the worker threads  */

         for (int i = 5; i <atoi(argv[1]) ; i++){
                                                                           /* get the default attributes */
                 pthread_attr_init(&attr);
                                                                            //Storing the address of ith index
                 int * temp= &array[i];
                                                                            /* create the thread */
                 pthread_create(&workers[i-5],NULL,runner,(void *)temp);

                                                                            
            }
         for (int i = 0; i <atoi(argv[1])-5 ; i++){
                                                                             /*wait for all the threads to exit */
                     pthread_join(workers[i], NULL);
            }


         printf("The fibonocci series is\n");                                  //Printing result

          for (int i = 0; i <atoi(argv[1]) ; i++){

                printf("  %d\n",fibo[i]);
            }

            end=clock();                                                        //Ending clock

            printf("Time taken :- %f \n",(double)(end-begin)/CLOCKS_PER_SEC);      

            return 0;
}
                                                            // The thread will begin control in this function and each thread
                                                            // generates one number
void *runner(void  *param){
            int i = *(int*)param;

            while(fibo[i-1]==0){}

            fibo[i]=fibo[i-1]+fibo[i-2];
        }