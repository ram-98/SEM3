#include <stdio.h>
#include <stdlib.h>
 
struct node
{
   
    int item;
    
    struct node *ptr;
    
}*stp,*stp1,*temp;

int count =0 ;


	void push(int element)
{
    if (stp == NULL)
    {
        stp =(struct node *)malloc(1*sizeof(struct node));
        stp->ptr = NULL;
        stp->item = element;
    }
    else
    {
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = stp;
        temp->item = element;
        stp = temp;
    }
    count++;
}

void pop()
{
    stp1 = stp;
 
    if (stp1 == NULL)
    {
        printf("The stack is empty \n POP operation is not possible");
        return;
    }
    else
        stp1 = stp1->ptr;
    printf("\n Value popped out is : %d", stp->item);
    free(stp);
    stp = stp1;
    count--;
}

void display()
{
    stp1 = stp;
 
    if (stp1 == NULL)
    {
        printf("Empty Stack");
        return;
    }
 
    while (stp1 != NULL)
    {
    	
        printf("%d ", stp1->item);
        stp1 = stp1->ptr;
    }
 }


int main()
{
 int number, choice , count;
 
    printf("\n 1 - Push");
    printf("\n 2 - Pop");
    printf("\n 3 - Display");
    printf("\n 4 - Exit");
    
     stp = NULL;
     count=0 ;
 
    while (1)
    
     {
        printf("\n Enter choice : ");
        scanf("%d", &choice);
 
        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &number);
            push(number);
            printf("\n The element has been successfully pushed \nThe Existing stack is");
            display();
            break;
        case 2:
            pop();
            printf("\nThe Existing stack is");
            display();
            break;
        case 3:
        	printf("The existing stack is  : \n ");
           display();
            break;
        case 4:
        	exit(0);
        	break;
        	default :
            printf(" wrong input is given ");
            break;
            
        }
		} return 0;
	}
	

 
   


