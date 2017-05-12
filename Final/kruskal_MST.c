#include<stdio.h>
#include<stdlib.h>
//main is at line 51

typedef struct edge {   //adjacency list node
  int v2;
  int weight;
  struct edge * next;
} Edge;

int findleader(int a[][2], int V) {   //find head of this array-tree
  if (a[V][0] == V)
    return V;
  else
    return findleader(a, a[V][0]);
}

void move (int source[][3], int dest[][3], int s_a, int d_b) {  //move contents from source[s_a] to dest[d_b]
  for (int i=0; i<3; i++)
    dest[d_b][i] = source[s_a][i];
}

void Merge(int arr[][3], int l, int m)    //Merge function of Merge Sort ..to merge two sorted arrays
{
  int mid = (l+m)/2;
  int array1[m-l+1][3];
  int i = l, j = mid + 1, k=0;
  while ((i<=mid)||(j<=m)) {
    if ((i<=mid)&&((j>m)||(arr[i][2] <= arr[j][2]))) {
      move(arr, array1, i, k);
      i++;
    }
    else if (j<=m) {
      move(arr, array1, j, k);
      j++;
    }
    k++;
  }
  for (k=0;k<(m-l+1);k++) {
    move(array1, arr, k, k+l);
  }
}

void MergeSort (int array[][3], int S, int E) {   //To sort the edges based on weights
  int mid = (S+E)/2;
  if (mid > S) MergeSort(array, S, mid);
  if (E > (mid+1)) MergeSort(array, mid+1, E);
  Merge(array, S, E);
}

int main() {    //main function
  printf("\n-----Kruskal's Algorithm-----\n");
  int n,e,count = 0;    //No. of vertices - n, No. of edges - e, count - Present no of vertices in MST
  rechoice:
    printf("\nNo. of Vertices, Edges:");
    scanf("%d %d",&n,&e);
    if ((e < (n-1))||(n<2)) {
      printf("\nInvalid Graph or No possible Spanning Tree");
      goto rechoice;
    }
  Edge * vert[n];   //initialize adjacency list
  Edge * tail[n];
  for (int i=0;i<n;i++) {
    vert[i] = NULL;
    tail[i] = NULL;
  }
  int a[e][3];  //another storage of edges
  int spanning_tree[n-1];
  printf("\nedge = (v1,v2)");
  printf("\nenter edge details as \"v1(num) v2(num) weight(num)\":\n");
  for(int i=0;i<e;i++) {
    Edge * temp = (Edge *) malloc(sizeof(Edge)*1);
    scanf("%d %d %d",&a[i][0],&a[i][1],&a[i][2]);
    temp->weight = a[i][2];
    temp->v2 = a[i][1];
    temp->next = NULL;
    if (vert[a[i][0]] != NULL) {
      tail[a[i][0]]->next = temp;   //add edge to the end of list
    }
    else {
      vert[a[i][0]] = temp;
    }
    tail[a[i][0]] = temp;
    if (i != e-1) printf("Next Edge :\n");
  }
  MergeSort (a, 0, e-1);
  int array[n][2];    //array indicating the trees ->>> each tree indicates that, In MST, there exists
  //a path between any two vertices which are taken from the same tree
  //and not If they belong to different trees

  for (int i=0;i<n;i++) {
    array[i][0] = i;    //parent
    array[i][1] = 0;    //depth of tree from this node
  }

  int temp1, temp2;
  int sum = 0;    //total cost
  for (int i=0;i<e;i++) {
    temp1 = findleader(array,a[i][0]);    //head of this tree
    temp2 = findleader(array,a[i][1]);    //head of this tree
    if (temp1 != temp2) {   //meaning that both trees are different and the edge can be included in MST
      // Trees are merged based on their heights....TREE BALANCING ...to ensure finding leader takes O(logn)
      if (array[temp1][1] >= array[temp2][1]) {
        array[temp2][0] = array[temp1][0];
        if (array[temp1][1] == array[temp2][1])
          array[temp1][1] += 1;
      }
      else
        array[temp1][0] = array[temp2][0];
      sum += a[i][2];
      spanning_tree[count] = i;   //newly added to MST
      count += 1;
    }
    if (count == n-1)
      break;
  }
  if (count == n-1) {
    printf("\nEdges - MST ::");
    for (int i=0;i<n-1;i++) {
      printf("\n( %d , %d ) - %d",a[spanning_tree[i]][0],a[spanning_tree[i]][1],a[spanning_tree[i]][2]);
    }
    printf("\n\nTotal Weight : %d\n",sum);  //total cost (or weight)
  }
  else printf("\nNo possible Spanning Tree\n");

  return 0;
}
