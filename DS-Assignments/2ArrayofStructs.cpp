#include<stdio.h>
#include <string.h>


struct  students {
	char name[50] ;
	int roll;
	int year;
};
int main ()
{
	int i,j,n,y,temp=0,z;
	char test[20];
	struct students list_[25],x;
	printf("Enter total no.of students(n)\n");
	scanf("%d", &n);
	if (n<=0){
		printf("Wrong input");
		printf("\nEnter another value \n");
		printf("\n");
		main ();
	}
	else
	{
	

	for (i=0;i<n;i++)
	{
        printf ("Enter  name: \t");
        scanf("%s", &list_[i].name);


		printf("Enter the roll number : \n");
		scanf("%d", &list_[i].roll);
		
        printf("Enter year of joining :\n");
		scanf("%d", &list_[i].year);

    }
    printf("\nThe Given Array of Structs is :\n ");
    
    for (i = 0; i<n; i++)
	   {
	   	
       printf("\n%s\t%d\t%d\n",list_[i].name,list_[i].roll,list_[i].year);
       
	    }
		
	    
    printf("The desired Result is \n After sorting based on students name : \n ");
    
   
    for (i = 0; i < n; i++){
    
      for (j = 0; j < n-i-1 ; j++) 
	  {
         if (strcmp(list_[j].name, list_[j + 1].name) > 0) 
		 {
            x = list_[j];
            list_[j] = list_[j + 1];
            list_[j + 1] = x;
         }
      }
  }
      for (i = 0; i < n; i++)
	   {
	   	
       printf("\n%s\t%d\t%d\n",list_[i].name,list_[i].roll,list_[i].year);
       
	    }
	    
	  printf("After sorting based on Roll number \n");
	 
	
  
    
    for (i = 0; i < n; i++){
    
      for (j = 0; j < n-i-1 ; j++) 
    {
    	// smallest element is swapped with leftmost element
    	if (list_[j].roll>list_[j+1].roll)
    	
    	{
            x = list_[j];
            list_[j] = list_[j + 1];
            list_[j + 1] = x;
         }
    }
}
    for (i = 0; i <= n-1; i++)
	   {
	   	
       printf("\n%s\t%d\t%d\n",list_[i].name,list_[i].roll,list_[i].year);
       
	    }
		printf("\n After sorting based on Year of joining");    
	    
    for (i = 0; i < n; i++){
    
      for (j = 0; j < n-i-1 ; j++) 
    {
    	// smallest element is swapped with leftmost element
    	if (list_[j].year>list_[j+1].year)
    	{
            x = list_[j];
            list_[j] = list_[j + 1];
            list_[j + 1] = x;
         }
    	
    }}
    for (i = 0; i <= n-1; i++)
	   {
	   	
       printf("\n%s\t%d\t%d\n",list_[i].name,list_[i].roll,list_[i].year);
       
	    }
		}
	}
