#include<iostream>

using namespace std;

void satisfyheap(float a[], int i, int heapsize)    
{
  int l, r,large; 
  float  temp;
  l = 2*i;
  r = 2*i + 1;
  if(l <= heapsize && a[l] > a[i])
  {
  	
    large = l;
  }
  else
  {
  	
    large = i;
  }
  if( r <= heapsize )
  {
  	if (a[r] > a[large])
  	{
  	
    large = r;
    }
  }
  
  if(large != i)
  {
    temp = a[i];
    
    a[i] = a[large];
    a[large] = temp;
    
    satisfyheap(a, large, heapsize);
  }
}

void buildheap(float a[], int length)
{
  int heapsize;
  heapsize = length-1;
  for(int i=(length/2); i >=0; i--)
  {
    satisfyheap(a, i, heapsize);
  } 
}

void heapsort(float a[], int length)
{
  buildheap(a, length);
  int heapsize, i;
  float temp;
  heapsize = length-1;
  for( i=heapsize; i >=0; i--)    
  {
    temp = a[0];
    a[0] = a[heapsize];
    a[heapsize] = temp;
    heapsize--;
    satisfyheap(a, 0, heapsize);
  }
  
}

int main()
{
  int length;
  float a[100];
  cout << "\nInitially create a heap  with n elements. Enter the value of n: \n";  
  cout<<"\n(To start with an empty heap give length as 0) \n n=" ;
  cin >> length;
  cout<<"\n";
	if(length<0)
	{
		cout<<"Invalid input,enter a positive number.\n";
		main();
	}
	else
	{
		for(int i=0;i<length;i++)
		{
			cout<<"Enter the element at position "<<i<< ":  ";
			cin>>a[i];
			cout<<"\n";
		}
		heapsort(a, length);
		buildheap(a,length);
		while(1)
		{
			int i;
			float n;
			cout<<"\nOPERATIONS ON HEAP : \n";
			cout<<"\n 1.Insert an element \n";
			cout<<" 2.Delete the maximum element \n";
			cin>>i;
			switch(i)
			{
				case 1:
					cout<<"Enter the number to be  inserted\n";   //adds an element to the end of the array
					cin>>a[length];
					length++; 
					cout<<"\nElement is inserted \n";
					    cout<<"\nThe existing heap is: \n";
					for(int i=0;i<length;i++)
						
					{
					
						cout<<a[i]<<"\t";
					}
					
					buildheap(a,length);   //heap is build along with the new element  
					break;
					
				case 2:
					//if there is no element present in the heap
					if(length<1)   
					{ 
						cout<<"No element to delete \n";
					}
					else         //swap the 1st element with tha last element and delete the last element
					{
						n=a[0];
						a[0]=a[length-1];
						a[length-1]=n;
						length--;
						buildheap(a,length);    //heap is buid to rearrange the new heap
						cout<<"The maximum element "<<n<<" is deleted \n";
						 cout<<"\nThe existing heap is: \n";
						 if ( length >0){
						 
					       for(int i=0;i<length;i++)
						
					        {
					
						        cout<<a[i]<<"\t";
				            }
				        }
				        else {
				        	cout<<"\nEmpty";
				        }
					}
					break;
					
				default :
					cout<<"Wrong input \n";
			}
		}
	}
}
