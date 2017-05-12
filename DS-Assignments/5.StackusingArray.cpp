#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX 5
struct StackArray {
   int s[MAX];
   int top;
} stack;

void push(int item) 
{
	
   stack.top++;
   stack.s[stack.top] = item;
}


int  pop() {
   int item;
   item = stack.s[stack.top];
   stack.top--;
   return (item) ;
}

void display() {
   int i;
   if (stack.top == -1)
      printf("\nStack Is Empty!");
   else {
      for (i = stack.top; i >= 0; i--)
         printf("\n%d", stack.s[i]);
   }
}

int main() {
   int item, ch;
   stack.top = -1;

   
   do {
      printf("\nSelect Any one");
      printf("\n1.Push");
      printf("\n2.Pop");
      printf("\n3.Exit");
      printf("\nEnter Your Choice");
      scanf("%d", &ch);
      switch (ch) {
      case 1:
         printf("\nEnter The item to be pushed");
         scanf("%d", &item);
         if (stack.top >= MAX - 1)
            printf("\n The Stack is Full! \n PUSH operation is not possible");
         else
            push(item);
            printf("\nThe element is pushed into the Stack \nThe existing stack is :");
            display();
         break;
      case 2:
         if (stack.top == -1)
            printf("\nThe stack is empty,Under flow condition (Can't perform POP operation')");
         else {
            item =   pop();
            printf("\nThe popped element is %d", item);
            printf("\nAfter popping out, the existing stack is :");
            display();
         }
         break;
      
      case 3:
         exit(0);
         default :
         	 
 	        printf("Wrong input");
      }
      
   } while (ch!=3);

return 0;
}
