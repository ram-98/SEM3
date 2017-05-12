#include <stdio.h>
//main is at line 52
int n;	//size of input array

void swap (int *a, int *b) {	//swap
	int temp = *a;
	*a = *b;
	*b = temp;
}

void horder (int arr[], int count, int root) {	//heapify-sub function...to heapify the tree when its subtrees are heapified
    int j;
    while ((2*root + 1) <= count) {		//shift the value down until we encounter a value <= the current value
      j = 2*root + 1;
      if (j+1 <= count) {
        if (arr[j] < arr[j+1])
          j++;
        if (arr[j] <= arr[root])
          break;
        swap (&arr[root], &arr[j]);		//swap if par < max (child)..to maintain max heap property
        root = j;
      }
      else {
        if (arr[root] < arr[j]) {
          swap (&arr[root], &arr[j]);
        }
        break;
      }
    }
}

void heapify (int ar[]) {		//heapify the given input array ar[]
	int subroot = (n-2)/2;		//starting from the parent of last node..until we reach the first node
	//call heapify on each node
	while (subroot >= 0) {
		horder (ar, n-1, subroot);
		subroot--;
	}
}

void heap_sort (int ar[]) {		//using Max Heap to get the array sorted in ascending order
	int temp, count = n-1;
	heapify (ar);
	while (count > 0) {
		swap(&ar[0],&ar[count]);	//the popped value is placed at the current end of heap
		//hence making the array sorted in ascending order
    count--;
    horder(ar, count, 0);		//horder at first node (root) fixes the Max heap property - when popped
	}
}

int main() {	//main function
	printf("\nHeap Sort (Max Heap) >>>>>>");
	printf("\nenter the no. of values to be sorted:\n");
	scanf("%d",&n);		//size of input
	int arr[n];
	printf("\nenter the values to be sorted:\n");
	for (int i=0;i<n;i++)
		scanf("%d", &arr[i]);
	heap_sort(arr);		//heapsort
	printf("\nValues in sorted (ascending) order are:\n");
	for (int i=0;i<n;i++)
		printf("%d ",arr[i]);		//print
	printf("\n");
	return 0;
}
