#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

typedef struct node   //struct which stores the information of all the vertices
{
	int v1;
	int v2;
	int weight;
}node;
 
int parent[10];    //array to maintain the leader of each vertix


void minheapify(node *A,int heapsize,int i)          
{
    node temp;
    int left = 2*i+1;
    int right = 2*(i+1);
    int smallest;
    if((left<heapsize) && (A[i].weight>A[left].weight))
    {
        smallest=left;
    }
    else
        smallest=i;

    if((right<heapsize) && (A[smallest].weight>A[right].weight))
    {
        smallest=right;
    }

    if(smallest!=i)
    {
        temp=A[smallest];
        A[smallest] = A[i];
        A[i]=temp;
        minheapify(A,heapsize,smallest);
    }
}

void buildminheap(node *A, int heapsize)
{
    int i;
    for(i=(heapsize-1)/2;i>=0;i--)
    {
        minheapify(A,heapsize,i);
    }
}

node extractmin(node *A,int heapsize)
{
    node u;
    int a;
    u=A[0];
    if(heapsize!=1)
    {
        A[0]=A[(heapsize-1)];
        A[(heapsize-1)]=u;
        heapsize=heapsize-1;
        minheapify(A,heapsize,1);
    }
    return u;
}

void heapdecreasekey(node *A,int w,int i)
{
    int j;
    node t;
    j = (i-1)/2;
    A[i].weight=w;
    while((i>0) && A[(i-1)/2].weight>A[i].weight)
    {
        t=A[i];
        A[i]=A[(i-1)/2];
        A[(i-1)/2] = t;
        i= (i-1)/2;
    }
}

int find(int i)      // find function to find the parent of vertix
{
	while(parent[i])
	i=parent[i];
	return i;
}
int uni(int i,int j)    //union function to check if the parents are same or not
{
	if(i!=j)
	{
		parent[j]=i;
		return 1;
	}
	return 0;
}

int main()
{
	int n,k,edge=1,heapsize;
	cout<<"Enter the number of vertices \n";
	cin>>k;
	if(k<0)
	{
		cout<<"Number of vertices cannot be less than 1\n";
		return 0;
	}
	else
	{
		cout<<"Enter the number of edges \n";
		cin>>n;
		if(n<0)
		{
			cout<<"Number of edges cannot be less than 1\n";
			return 0;
		}
		else
		{
			node *list;
			list=(node*)malloc(n*sizeof(node));
			for(int i=0;i<n;i++)
			{
				cout<<"Enter the edge between 1 to "<<k<<" vertices (Enter v1 and v2)\n";
				cin>>list[i].v1;
				cin>>list[i].v2;
				cout<<"Enter the weight of the edge \n";
				cin>>list[i].weight;
			}
			node u;
			int x,y;
			heapsize=n;
			int total_minweight=0;
			cout<<"Edges in the final minimum spannig tree are \n";
			while(edge<=n)
			{
				buildminheap(list,heapsize);
				u=extractmin(list,heapsize);
				heapsize--;
				x=find(u.v1);
				y=find(u.v2);
				if(uni(x,y))
				{
					cout<<edge<<"<"<<x<<","<<y<<">"<<"="<<u.weight<<"\n";
					total_minweight=total_minweight + u.weight;
				}
				edge++;
			}
			cout<<"Total cost of the minimum spanning tree is : "<<total_minweight<<"\n";
			}
		}
		
}
