#include<stdio.h>
int main ()
{
	int Array[20],i,j,bubble,n;
	printf("No.of elements to be sorted=");
	scanf("%d",&n);
	// If the input is not a positive integer
	if (n<=0)
	{
		printf("Wrong input.Please give a positive integer");
		printf("\n");
		main();
	
	}
	// when the input is a positive integr
	else
	{
	
	{
	printf("Enter the elements ");
	// allocating the elements into array
	
	for (i=0;i<n;i++)
	
	scanf("%d",&Array[i]);
	}
	
	for (j=0;j<n-1;++j)
	
	 for(i=0;i<n-1;++i){
	 //checking the adjacent elements and swapping if necessary	
	
	if (Array[i]>Array[i+1])
	{bubble=Array[i];
	Array[i]=Array[i+1];
	Array[i+1]=bubble;
	}
}
printf("After sorting: ");
    for(i=0;i<n;++i)
         printf("%d  ",Array[i]);
    return 0;
}
}
