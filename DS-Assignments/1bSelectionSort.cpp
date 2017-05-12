#include<stdio.h>
int main ()
{
	int A[20],i,j,p,n,k;
	printf("No.of elements to be sorted=");
	scanf("%d",&n);
	if (n<=0)
	{
		printf("Wrong input.Please give a positive integer");
		printf("\n");
		main();
	
	}
	// when the input is a positive integr
	else
	{
	
	printf("Enter the elements ");
	for (i=0;i<n;i++)
	
	scanf("%d",&A[i]);
	
	for(j=0;j<n;j+=1)
    for(i=j+1;i<n;i+=1)
    {
    	// smallest element is swapped with leftmost element
    	if (A[j]>A[i])
    	{
    		p=A[j];
    		A[j]=A[i];
    		A[i]=p;
    	}
    }
    printf("Elements after sorting: ");
    for(k=0;k<n;k+=1)
         printf("%d  ",A[k]);
    return 0;
}
}
