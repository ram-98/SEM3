#include<stdio.h>
#include<conio.h>
int main(void)
{
	int A[10],i,j,p,n;
	
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
	
	scanf("%d",&A[i]);
		
	for (i=0;i<=n-1;i++)
	{ p=A[i];
	
	for(j=i-1;j>=0 and p<A[j];j--)
	
	A[j+1]=A[j];
	
	A[j+1]=p;
	
	}
	printf("Sorted Elements are");
	
	for (i=0;i<n;i++)
	printf(" %d",A[i]);

return 0;
}}
}
