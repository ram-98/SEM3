#include<stdio.h>
#define MAX 5

int cq[MAX],end=-1,front=-1,p=0;


void insert()
{
	printf("Enter the value to be inserted\n");
scanf("%d",&p);

{
if(front == end+1 || (front==0 && end == MAX-1))
{printf("The queue is full and insertion is not possible(Over flow))");

}
else if ( front !=0 && end== -1) 
{
 front = 0;
 end =0;
 cq[end]=p;}
else if ( end == MAX-1 && front !=0)
 {end = 0;
 cq[end]=p;
 }
else {
 	end ++ ;
 	cq[end]=p;
 }}
 

printf("Element Successfully Inserted\n");
return;}





void dele()
{
if((front == -1) ||  (front==end+1))
 
{
  printf("The circular queue is empty can't delete");
  return;
}
   p = cq[front];

 if(front == end)
 {
 front = -1;
 end = -1;
 }
 else if(front == MAX-1)
 front = 0;
 else
 front++;
 printf("Element is Deleted Successfully\n");
 }
 
 
 
 
 void display()
{
 if((front == -1) ||  (front==end+1))
 
{
  printf("The circular queue is empty");
} 
else 
{
        printf("The Elements in the Queue are\n");
	if(front == 0 && end ==0)
		printf("\t %d ",cq[0]);
 	else if (front<end)
	 {
	 	for (p=front;p<=end ; p++)
	 	 printf("\t %d ",cq[p]);
	 }
	 else {
	 	for (p=front;p<MAX;p++)
	 	printf("\t %d ",cq[p]);
	 	for(p=0;p<=end;p++)
	 	printf("\t %d ",cq[p]);
	 }
 }
 }
 
 


int main ()  
{  
int ch;
 do
 {
 printf("\n 1. Insert \n");
 printf("\n 2. Delete \n");
 printf("\n 3. Display \n");
 printf("\n 4. Exit \n");
 printf("\n Select any one: ");
 scanf("%d", &ch);
 switch(ch)
 {
 case 1:
 insert();
 break;
 case 2:
 dele();
break;
 case 3:
 display();
 break;
 case 4:
 return 1; 
  
 
 default :
 	printf("Wrong input");
}
}while(ch!=4);


return 0;}

