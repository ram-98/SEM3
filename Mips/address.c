#include<stdio.h>
int main ()
{
	char a='s';
	char *x=&a;
	int *ip=NULL;
	printf("%p\n",(void*)x);
	printf("%ld\n",sizeof(int));
	printf(“ %p\n”, sizeof((void *)x));
	
	return 0;
}
