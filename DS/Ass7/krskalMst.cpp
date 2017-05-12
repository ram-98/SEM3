#include <iostream>
#include<malloc.h>
#include<cstdlib>

using namespace std;
	int vertex_count,Edge_count,heapsize;

struct list{
		int secondVertex,weight;
		list * next;
};
struct edgeinfo
{
	int u,v,weight;
};
edgeinfo **e;
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
void createAjacencylist(int);
void minheapify( int i);
void buildminheap();

struct disjointset
{
	int vertex_value;
	int rank=0;
	disjointset* parent;
};
disjointset**  array;	
void Makeset(int v){
		disjointset *	x=new disjointset;
		x->vertex_value=v;
		x->parent=x;
		x->rank=0;
		array[v]=x;
}
disjointset* findset(int u);
void unionuv(int u,int v);
void link(int x,int y);
struct edgeinfo* extractmin()
{
    edgeinfo *edge=e[0];
    if(heapsize!=1)
    {
        e[0]=e[(heapsize-1)];
        e[(heapsize-1)]=edge;
        heapsize=heapsize-1;
        minheapify(0);
    }
    return edge;
}
int main()
{
	int totalweight=0;
	cout<<"\nKRUSKALS MST is running\nEnter the number of vertices\n";
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
				e=(edgeinfo **)malloc(sizeof(edgeinfo)*Edge_count);
				for (int i = 0; i < Edge_count; i++){
					createAjacencylist(i);
				}
				cout<< "The adjacency list is \n" << endl;
				for (int i = 0; i < vertex_count; ++i){
					cout<< i << "\t";
					list * a=adjacencylist[i].head;
					while(a!=NULL){
						cout<<  a->secondVertex<<"--"<<a->weight<<"\t";
						a=a->next;
					}
					cout<< "\n" << endl;
				}
				array=(disjointset **)malloc(sizeof(disjointset)*vertex_count);
				for (int i = 0; i < vertex_count; ++i){
					Makeset(i);
				}
				heapsize=Edge_count;
				buildminheap();
				for (int i = 0; i < Edge_count; i++)
				{
					edgeinfo * edge= extractmin();
					if (findset(edge->u)!=findset(edge->v)){
						cout<<"v1:--"<< edge->u<<"v2:--" <<edge->v<<"----weight:--"<< edge->weight << endl;
						unionuv(edge->u,edge->v);
						totalweight=totalweight+edge->weight;
					}
				}
				cout<< "the totalweight is:" <<totalweight<< endl;
			}
	}
	return 0;
}

disjointset* findset(int u){
	if(array[u]!=array[u]->parent)
		array[u]->parent=findset(array[u]->parent->vertex_value);
	return array[u]->parent;
}
void unionuv(int u,int v){

		link(findset(u)->vertex_value,findset(v)->vertex_value);
}
void link(int x,int y){
	if (array[x]->rank>array[y]->rank){
		array[y]->parent=array[x];
	}
	else{
		array[x]->parent=array[y];
			if(array[x]->rank==array[y]->rank)
					array[y]->rank=array[y]->rank+1;
	}
}

void buildminheap(){
				cout<< "In buildminheap" << endl;
				for (int i = (heapsize/2)-1; i >=0 ; i--){
					minheapify(i);
				}
			}
void minheapify( int i){
		int left=2*i+1;
		int right=2*i+2;
		int smallest;
		if (left<=heapsize-1 && e[left]->weight<e[i]->weight)
		{
			smallest=left;
		}
		else
			smallest=i;
		if (right<=heapsize-1 && e[right]->weight<e[smallest]->weight)	
		{
			smallest=right;
		}
		if (smallest!=i)
		{
			edgeinfo * temp=e[i];
			e[i]=e[smallest];
			e[smallest]=temp;
			minheapify(smallest);
		}
}
void createAjacencylist(int i){
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
		edgeinfo * x=new edgeinfo;
		x->u=temp1;
		x->v=temp2;
		x->weight=temp3;
		e[i]=x;
		return;
}

