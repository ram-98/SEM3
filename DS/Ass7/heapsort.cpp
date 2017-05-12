#include <iostream>
using namespace std;

int length,heapsize;

void maxheapify(int *arr, int i);
void displayheap(int *arr);
void buildmaxheap(int *arr);
void displayheap(int *arr);

int main(){
	int arr[1000];
	
	cout<<"Heap sort is performed .Enter initial no of elements"<<endl;
	cin>>length;
	heapsize=length;
	if (length<=0)
	{
		cout<<"enter atleast one element\n";
		exit(0);
	}
	else{
		cout<<"Enter elements one by one \n";
		for (int i = 0; i < length; ++i)
		{
			cin>>arr[i];
			cout<<endl;
		}
		buildmaxheap(arr);
		displayheap(arr);
		while(1)
		{
			int i;
			cout<<"\nEnter 1 -Insertion 2-Retrieve and delete 3-Display after heap sort and exit\n";
			cin>>i;
			int first;
			switch(i)
			{
				case 1:
					cout<<"Enter the number to be  inserted\n";   //adds an element to the end of the array
					cin>>arr[length];
					length=length+1;
					heapsize=length;
					buildmaxheap(arr);   	
					displayheap(arr);						 
					break;
					
				case 2:
																//if there is no element present in the heap
					if(length<1)   
					{ 
						cout<<"No element to delete \n";
					}
					else         								//swap the 1st element with tha last element and delete the last element
					{
						first=arr[0];
						arr[0]=arr[length-1];
						arr[length-1]=first;
						length=length-1;
						heapsize=length;
						maxheapify(arr,0);  					  //heap is buid to rearrange the new heap
						cout<<"The  maxmimum element deleted is "<<first<<"\n";
						 if ( length >0){
						 	displayheap(arr);
					       }
				        else {
				        	cout<<"\n Heap is Empty\n";
				        }
					}
					break;
				case 3:
					cout<<" The sorted elements after Heap Sort is \n";
					length=heapsize;
					for (int i = heapsize-1; i >=0 ; --i)
					{
						int temp=arr[i];
						arr[i]=arr[0];
						arr[0]=temp;
						heapsize=i;
						maxheapify(arr,0);
					}
					for (int i = 0; i < length; ++i)
					{
						cout<<arr[i]<<" ";
					}
					cout<<endl;
					exit(0);

					break;
					
				default :
					cout<<"Invalid input ! \n";
			}

	}
	}
	return 0;
}

void buildmaxheap(int *arr){

		for (int i = (length/2)-1; i >=0 ; i--)
		{
			maxheapify(arr,i);
		}
	}

void maxheapify(int *arr, int i){
		int left=2*i+1;
		int right=2*i+2;
		int largest;
		if (left<=heapsize-1 && arr[left]>arr[i])
		{
			largest=left;
		}
		else
			largest=i;
		if (right<=heapsize-1 && arr[right]>arr[largest])	
		{
			largest=right;
		}
		if (largest!=i)
		{
			int temp=arr[i];
			arr[i]=arr[largest];
			arr[largest]=temp;
			maxheapify(arr,largest);
		}
}
void displayheap(int *arr){
	int i;
	cout<<"Heap is"<<endl;
	for (int i = 0; i <heapsize ; ++i)
	{
		cout<<arr[i]<<", ";
	}
	}
