#include<stdio.h>
//main is at line 73

int count = -1;		//index of last valid element
int arr[15];		//queue with size 15

void swap (int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void push_Pqueue() {		//Push a value into queue
  if (count < 14) {		//count == 14 => queue is full
    count++;
    printf("\nenter the priority value (low priority value is more priorized): ");
    scanf("%d",&arr[count]);
    int par, i = count;
    while (i > 0) {		//bubble the new value based on priorities in the current branch
      par = (i - 1)/2;
      if (arr[par]> arr[i]) {
        swap (&arr[par], &arr[i]);
        i = par;
      }
      else
        break;
    }
    printf("\n%d is added to the Pqueue", arr[count]);
  }
  else
    printf("\nPQueue is full");
}

void pop_Pqueue() {		//Pop min value out of PriorityQueue
  if (count == -1)
    printf("\nPQueue is empty");
  else {
    printf("%d is popped", arr[0]);
    arr[0] = arr[count];		//put the last value at the top maintaining structural property
    count--;
    int j, i=0;
    while ((2*i + 1) <= count) {		//shift down the top value based on priority to maintain heap property
      j = 2*i + 1;
      if (j+1 <= count) {
        if (arr[j] > arr[j+1])
          j++;
        if (arr[j] >= arr[i])
          break;
        swap (&arr[i], &arr[j]);		//if (parent > min(child)) then swap
        i = j;
      }
      else {
        if (arr[i] > arr[j]) {
          swap (&arr[i], &arr[j]);
        }
        break;
      }
    }
  }
}

void show() {		// display in the order of index
  if (count == -1)
    printf("\nPriorityQueue is empty");
  else {
    printf("\nlevel order::\n");
    for (int i=0;i<=count;i++) {
      printf("%d ", arr[i]);
    }
  }
}

int main() {		//main function
  int choice;
	printf("\nPriority Queue (Min Heap) >>>>>>");
  while(1) {		//prompt loop
    printf("\n\nChoose\n1-Push a new element into the Pqueue (int)\n2-Pop an element (top priority)\n3-Show\n4-exit\n");
    scanf("%d",&choice);
    switch (choice) {
      case 1:
	      push_Pqueue();		//Push
	      break;
      case 2:
	      pop_Pqueue();		//Pop
	      break;
      case 3:
	      show();		//display
	      break;
      case 4:
	      printf("\nprogram exited\n");		//exit
	      return 0;
      default:
	      printf("\ninvalid response");
    }
    printf("\n------------------------------------------");
  }
}
