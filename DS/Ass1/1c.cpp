#include <iostream>
#include<math.h>
#include<malloc.h>
using namespace std;

void bubblesort(int *array, int size);

int main()
{
	cout<<"enter the no of elements in integer array"<<endl;
	int size;
	cin>>size;
	int *array=(int *)malloc(size*4);
	cout<<"enter the elements one by one "<<endl;
	for (int i = 0; i < size; i++)
	{
		cin>>array[i];
	}
	cout<<"The unsorted array is "<<endl;
	for (int i = 0; i < size; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
	bubblesort(array,size);
	cout<<"Using Bubble Sort The sorted array is "<<endl;
	for (int i = 0; i < size; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;

	return 0;
}

void bubblesort(int *array, int size){
		int temp;
		for (int i = 0; i < size-1	; i++)
		{
			for (int j = 0; j < size-1; j++)
			{
				if (array[j]>array[j+1])
				{
					temp=array[j];
					array[j]=array[j+1];
					array[j+1]=temp;
				}
			}
		}
}