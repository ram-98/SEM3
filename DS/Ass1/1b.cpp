#include <iostream>
#include<math.h>
#include<malloc.h>
using namespace std;

void selectionsort(int *array, int size);

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
	selectionsort(array,size);
	cout<<"Using Selection sort The sorted array is "<<endl;
	for (int i = 0; i < size; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
	return 0;
}

void selectionsort(int *array, int size){
	int min,index,loop;
	for (int i = 0; i < size; i++)
	{
		min =array[i];
		index=i;
		for ( loop = i+1; loop < size; loop++)
		{
			if (min>array[loop])
			{
				min=array[loop];
				index=loop;
			}
		}
		array[index]=array[i];
		array[i]=min;

	}
		
}