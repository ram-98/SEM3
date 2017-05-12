#include <iostream>
#include<math.h>
#include<malloc.h>
using namespace std;

void insertionsort(int *array, int size);

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
	insertionsort(array,size);
	cout<<endl;
	cout<<"Using insertion sort The sorted array is "<<endl;
	for (int i = 0; i < size; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
	return 0;
}

void insertionsort(int *array,int size){
	int value,hole;
	for (int i = 0; i < size; i++)
	{
		value=array[i];
		hole=i;
		while(hole>0 && array[hole-1]>value){
			array[hole]=array[hole-1];
			hole=hole-1;
		}
		array[hole]=value;
	}
} 
