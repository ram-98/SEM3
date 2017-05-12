#include <stdio.h>
#include <stdlib.h>   //for malloc
//main is at line 96

int n=0;    //No. of vertices
int e=0;    //No. of edges
int count;  //used for heap datastructure (present size of heap)
int *pos;   //used to get the index of given vertex in the heap

typedef struct {    //heap node
  int key;
  int vertex;
  int source;
} heapnode;

typedef struct edge{    //adjacency list node
  int v2;
  int weight;
  struct edge * next;
} Edge;

Edge **tail;

int insert(Edge ** ar) {    //add an edge to the adjacency list - to both vertices of edge
  int a1, a2, a3;
  printf("\nenter edge details as \"v1(num) v2(num) weight(num)\":\n");
  scanf("%d %d %d",&a1,&a2,&a3);    //get edge attributes
  Edge * temp = (Edge *) malloc(sizeof(Edge)*1);
  Edge * temp2 = (Edge *) malloc(sizeof(Edge)*1);
  temp->weight = a3;
  temp->v2 = a2;
  temp->next = NULL;
  *temp2 = *temp;
  if (ar[a1] != NULL)
    tail[a1]->next = temp;  //add at the end
  else
    ar[a1] = temp;
  tail[a1] = temp;

  temp2->v2 = a1;
  if (ar[a2] != NULL)
    tail[a2]->next = temp2;  //add at the end
  else
    ar[a2] = temp2;
  tail[a2] = temp2;
}

void swap (heapnode *a, heapnode *b) {  //swap heapnodes
	heapnode temp = *a;
	*a = *b;
	*b = temp;
}

void shift_up(heapnode arr[], int indx) {   //shift the value up the heap
    int par, i = indx;
    while (i > 0) {
      par = (i - 1)/2;
      if (arr[par].key > arr[i].key) {
        swap (&arr[par], &arr[i]);
        pos[arr[par].vertex] = par;
        pos[arr[i].vertex] = i;
        i = par;
      }
      else
        break;
    }
}

void pop_heap(heapnode arr[]) {   //pop the min value out of heap
    arr[0] = arr[count];    //put last node at first maintaining structural property
    count--;
    int j, i=0;
    while ((2*i + 1) <= count) {  //fix heap property, by shifting down
      j = 2*i + 1;
      if (j+1 <= count) {
        if (arr[j].key > arr[j+1].key)
          j++;
        if (arr[j].key >= arr[i].key)
          break;
        swap (&arr[i], &arr[j]);    //if (parent > min(child)) then swap
        pos[arr[j].vertex] = j;
        pos[arr[i].vertex] = i;
        i = j;
      }
      else {
        if (arr[i].key > arr[j].key) {
          swap (&arr[i], &arr[j]);
          pos[arr[j].vertex] = j;
          pos[arr[i].vertex] = i;
        }
        break;
      }
    }
}

int main() {    //main function
  printf("\n-----Prim's Algorithm-----\n");
  rechoice:
    printf("\nNo. of Vertices, Edges: ");
    scanf("%d %d",&n,&e);
    if ((n<2)||(e<(n-1))) {
      printf("\nInvalid Graph or No possible Spanning Tree");
      goto rechoice;
    }
  count = n-1;
  Edge * vert[n];   //initialize adj list
  tail = (Edge **) malloc(sizeof(Edge *)*n);

  int sum = 0;    //total cost
  int spanning_tree[n][3];  //final result
  for (int i=0;i<n;i++) {
    vert[i] = NULL;
  }
  for (int i=0;i<e;i++) {   //adding edges
    insert(vert);
  }
  heapnode heap[n];
  pos = (int *) malloc (sizeof(int)*n);
  for (int i=0;i<n;i++) {   //initialize heap
    heap[i].key = 999;
    heap[i].vertex = i;
    heap[i].source = -1;
    pos[i] = i;
  }
  heapnode temp;
  Edge *temp2;
  int indx;
  heap[0].key = 0;
  for (int i=0; i<n;i++) {
    temp = heap[0];   //min weight node
    if (temp.key == 999)
    {
      printf("\nNo possible Spanning Tree\n");
      return 1;
    }
    spanning_tree[i][0] = temp.vertex;
    spanning_tree[i][1] = temp.source;
    spanning_tree[i][2] = temp.key;
    sum += spanning_tree[i][2];
    pos[temp.vertex] = -1;
    pop_heap(heap);   //pop min and adjust heap property
    temp2 = vert[temp.vertex];
    while(temp2!= NULL) {   //traverse through adjlist of newly added (into MST) vertex to find new min weights corr. non-MST vertices (in heap)
      indx = pos[temp2->v2];
      if ((indx != -1) && (heap[indx].key > temp2->weight)) {    //if new min found
        heap[indx].key = temp2->weight;
        heap[indx].source = temp.vertex;
        shift_up(heap, indx);   //no need to look down..as the changed weight is less than prev weight
      }
      temp2 = temp2->next;
    }
  }
  printf("\nEdges : Min Spanning Tree:\n");   //Min Spanning Tree
  for (int i=1;i<n;i++) {
    printf("( %d , %d ) - %d\n", spanning_tree[i][0], spanning_tree[i][1], spanning_tree[i][2]);
  }
  printf("\nTotal Weight : %d\n", sum);   //total cost (or weight)
  return 0;
}
