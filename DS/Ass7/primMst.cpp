#include <iostream>
#include<malloc.h>
#include<cstdlib>
#include<climits>

using namespace std;
int length,heapsize;
int vertex_count,Edge_count,mst_weight,cut_weight;
int *parents;
int k=0;

struct list{
		int secondVertex,weight;
		list * next;
};
struct heads{
		list * head=NULL;
};
heads * adjacencylist;
list * GetNewNode(int secondvertex,int weight){
			list * node =new list();
			node->secondVertex=secondvertex;
			node->weight=weight;
			return node;
}
void createAjacencylist();

struct PQnode{
		int vertex;
		int weight;
};
PQnode* heap_arr;

struct finalMST{
		int v1=0, v2=0, weight=0;
};
finalMST* array;
int *positions;
int *smallest_weight;
bool* contains;

void minheapify( int i){
		int left=2*i+1;
		int right=2*i+2;
		int smallest;
		if (left<=heapsize-1 && heap_arr[left].weight<heap_arr[i].weight)
		{
			smallest=left;
		}
		else
			smallest=i;
		if (right<=heapsize-1 && heap_arr[right].weight<heap_arr[smallest].weight)	
		{
			smallest=right;
		}
		if (smallest!=i)
		{
			PQnode temp=heap_arr[i];
			positions[heap_arr[smallest].vertex] = i;
			positions[heap_arr[i].vertex] = smallest;
			heap_arr[i]=heap_arr[smallest];
			heap_arr[smallest]=temp;
			minheapify(smallest);
		}
}
int extractmin(){
			// Store the root node
			
			int minvertex = heap_arr[0].vertex;
			array[k].v2=heap_arr[0].vertex;
			array[k].weight=heap_arr[0].weight;
			array[k].v1=parents[heap_arr[0].vertex];
			// Replace root node with last node
			heap_arr[0] = heap_arr[heapsize- 1];
			// Update position of last node
			positions[minvertex] = heapsize-1;
			positions[heap_arr[0].vertex] = 0;
			k++;
			// Reduce heap size and heapify root
			heapsize=heapsize-1;
			minheapify(0);

			return minvertex;
}
void decrease_key(int v,int key){
			// Get the index of v in heap array
			int i = positions[v];
			// Get the node and update its key value
			heap_arr[i].weight = key;
			// Travel up while the complete tree is not hepified.
			// This is a O(Logn) loop
			while (i>=0 && heap_arr[i].weight < heap_arr[(i - 1) / 2].weight){
				// Swap this node with its parent
				positions[heap_arr[i].vertex] = (i-1)/2;
				positions[heap_arr[(i-1)/2].vertex] = i;
				PQnode swap=heap_arr[i];
				heap_arr[i]=heap_arr[(i - 1) / 2];
				heap_arr[(i - 1) / 2]=swap;
				// move to parent index
				i = (i - 1) / 2;
			}

}
void Mst_Prim(int r){
				for (int i = 0; i < vertex_count; ++i)
				{
					heap_arr[i].weight=INT_MAX;
				}
				heap_arr[r].weight=0;
				heapsize=vertex_count;
				for (int i = (vertex_count/2)-1; i >=0 ; i--)
				{
					minheapify(i);
				}
				while (heapsize){
							int minvertex=extractmin();
							contains[minvertex]=false;
							int v;
							 list* transverse = adjacencylist[minvertex].head;
							 while (transverse != NULL){
									 v = transverse->secondVertex;
									// If v is not yet included in MST and weight of u-v is
									// less than key value of v, then update key value and
									// parent of v
									if (contains[v] && transverse->weight < smallest_weight[v]){
										parents[v]=minvertex;
										smallest_weight[v] = transverse->weight;
										decrease_key( v, smallest_weight[v]);
									}
									transverse = transverse->next;
								}
							}
				return;
		}
int main()
{
	int r;
	cout<< "Prims MST is running.Enter no of vertices\n" << endl;
	cin>>vertex_count;
	if(vertex_count <=1){ 
		cout<<"Number of vertices cannot be less than 1\n";
		main();
	}
	else{
		 adjacencylist=new heads[vertex_count];
		cout<<"Enter the number of edges \n";
		cin>>Edge_count;
		if(Edge_count<vertex_count-1){
			cout<<"Number of edges cannot be less than (V-1)\n";
			main();
		}
		else{
				array=new finalMST[vertex_count];
				parents=new int[vertex_count];
				positions=new int[vertex_count];
				smallest_weight=new int[vertex_count];
				contains=new bool[vertex_count];

				for (int i = 0; i < Edge_count; i++){
					createAjacencylist();
				} 
				cout<< "The adjacency list is \n" << endl;
				for (int i = 0; i < vertex_count; ++i)
				{
					cout<< i << "\t";
					list * a=adjacencylist[i].head;
					while(a!=NULL){
						cout<<  a->secondVertex<<"--"<<a->weight<<"\t";
						a=a->next;
					}
					cout<< "\n" << endl;
				}
				cout<< "Enter the vertex number you want to start MST from (Start from 0 to V-1)\n" << endl;
				cin>>r;
				 heap_arr=new PQnode[vertex_count];
				for (int i = 0; i < vertex_count; i++){
					contains[i]=true;
					positions[i]=i;
					smallest_weight[i]=INT_MAX;
					heap_arr[i].vertex=i;
					heap_arr[i].weight=INT_MAX;
				}
				Mst_Prim(r);
				for (int i = 1; i < vertex_count; i++)
				{
					cout<<"v1 :"<< array[i].v1<<"-- v2: "<<array[i].v2<<"---weight --" <<array[i].weight<< endl;
					mst_weight=mst_weight+array[i].weight;
				}
				cout<< "the final mst weight is--- "<<mst_weight << endl;
		}
	}
	return 0;
}
void createAjacencylist(){
		int temp1,temp2,temp3;
		list * temp;
		cout<<"Enter v1 v2 and weight assocaited with it (from 0 to v-1) \n";
		cin>>temp1>>temp2>>temp3;
		temp=adjacencylist[temp1].head;
		adjacencylist[temp1].head=GetNewNode(temp2,temp3);
		adjacencylist[temp1].head->next=temp;
		temp=adjacencylist[temp2].head;
		adjacencylist[temp2].head=GetNewNode(temp1,temp3);
		adjacencylist[temp2].head->next=temp;
	}

