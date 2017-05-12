#include<stdio.h>
#include<stdlib.h>
//main is at line 159

typedef struct node {
  struct node *lmost;   // left most child
  struct node *next;    // sibling (also using the same ptr to connect different binomial trees)
  int order;        // order of binomial tree
  int key;          // value by which the priority is made
} BinHNode;

BinHNode *root = NULL;  //root binomial tree
BinHNode *min = NULL;   //min binomial tree

BinHNode *getmin() {   //get the binomial tree with minimum head -> gives global minimum
  BinHNode *t = root;
  BinHNode *min = NULL;
  while(t->next != NULL) {
    if (min == NULL) {
      if (root->key > t->next->key) min = t;
    }
    else if (min->next->key > t->next->key) min = t;
    t = t->next;
  }
  return min;
}

void unionBinH(BinHNode *H1, BinHNode *H2) { //merging H2 to H1
  BinHNode *Heap1 = H1; // to traverse through H1 - a binomial tree
  BinHNode *Heap2 = H2; //to traverse through H2 - a binomial tree
  BinHNode *temp;
  BinHNode *prev = NULL;
  while((Heap2 != NULL)&&(Heap1 != NULL)) {  //this loop merges H2 to H1 until any one binheap ends
    if (Heap2->order == Heap1->order) {   // same order
      temp = Heap2->next;
      if ((Heap1->next != NULL)&&(Heap1->next->order == Heap1->order)) { //if Heap1->next also has same order
        Heap1 = Heap1->next;
        if (prev != NULL) prev = prev->next;
        else prev = root;
      }
      if (Heap2->key >= Heap1->key) {   //if Heap1 order <= of Heap2, add Heap2 as branch to Heap1
        Heap2->next = Heap1->lmost;
        Heap1->lmost = Heap2;
        Heap1->order += 1;    //new order
        Heap2 = temp;
      }
      else {    //else add Heap1 as branch to Heap2, which adds to BinHeap. Heap2->next becomes new Heap2
        Heap2->next = Heap1->next;
        if (prev == NULL) root = Heap2;
        else prev->next = Heap2;
        Heap1->next = Heap2->lmost;
        Heap2->lmost = Heap1;
        Heap2->order += 1;    //new order
        Heap1 = Heap2;
        Heap2 = temp;
      }
    }
    else if (Heap2->order < Heap1->order) {   // Insert Heap2 before Heap1 in BinHeap
      if (prev == NULL) {
        root = Heap2;
        prev = root;
      }
      else prev = prev->next = Heap2;
      temp = Heap2->next;
      Heap2->next = Heap1;
      Heap2 = temp;
    }
    else {    // if Heap1 order is less, advance Heap1
      Heap1 = Heap1->next;
      if (prev == NULL) prev = root;
      else prev = prev->next;
    }
  }
  // After either Heap2 or Heap1 gets finished
  if (Heap2 != NULL) {    // if Heap1 gets finished - no chances of having same ordered binomial trees
    // hence add whole Binomial heap from Heap2 directly to Main Binomial Heap
    if (prev != NULL) prev->next = Heap2;
    else root = Heap2;
  }
  if (Heap1 != NULL) {    // if Heap2 gets finished - there is chance that Heap1->next and Heap1 having same order..and may continue until end
    while ((Heap1->next != NULL)&&(Heap1->order == Heap1->next->order)) {   // if they have same order..then merge them
      if (Heap1->key > Heap1->next->key) {  // if Heap1->key > Heap2->key
        temp = Heap1->next;
        Heap1->next = Heap1->next->lmost;
        temp->lmost = Heap1;
        Heap1 = temp;
        if (prev == NULL) root = Heap1;
        else prev->next = Heap1;
      }
      else {    // if Heap2->key >= Heap1->key
        temp = Heap1->next->next;
        Heap1->next->next = Heap1->lmost;
        Heap1->lmost = Heap1->next;
        Heap1->next = temp;
      }
      Heap1->order += 1;    // new order
    }
  }
}

void pushBinH(int val) {    // push (or insert) a value into BinHeap
  BinHNode *t = (BinHNode *) malloc(sizeof(BinHNode));
  printf("\n%d is inserted",val);
  t->key = val;
  t->next = NULL;
  t->lmost = NULL;
  t->order = 0;   // only one element
  if (root == NULL) root = t;
  else unionBinH(root, t);    // union t with main BinHeap
}

void popBinH() {    // pop min
  if (root == NULL) printf("\nBinHeap is empty");
  else {
    BinHNode *h,*del = getmin();  // del -node left to the min binomial tree
    if (del == NULL) h = root->lmost;
    else h = del->next->lmost;    //h = min node ->lmost
    BinHNode *t = h;
    BinHNode *temp;
    if (t != NULL) {    //traversing through children of min node (or) siblings of min->lmost
      //to separate and create a new BinHeap from these nodes in reverse order of their next pointers - i.e., correct inc order of "orders"
      t = t->next;
      h->next = NULL;
      while (t != NULL) {
        temp = t->next;
        t->next = h;
        h = t;
        t = temp;
      }
    }
    //deleting the min-node
    if (del == NULL) {
      temp = root;
      root = root->next;
      printf("\n%d is deleted",temp->key);
      free(temp);
    }
    else {
      temp = del->next;
      del->next = del->next->next;
      printf("\n%d is deleted",temp->key);
      free(temp);
    }
    //union newly isolated BinHeap with the main BinHeap
    unionBinH(root, h);
  }
}

void displayBinH() {    //display -> displays --each binomial tree and its lmost node and theirs and so on--------like a layer
  for (BinHNode *temp = root; temp != NULL; temp = temp->next) {
    printf("\nBinomial Tree - %d", temp->order);
    printf("\n");
    for (BinHNode *temp2 = temp; temp2 != NULL; temp2 = temp2->lmost) {
      printf("%d ", temp2->key);
    }
  }
}

int main() {    //main function
  int choice, v;
	BinHNode *t;
	printf("\n..........Binomial Heap...........");
	while(1) {   //prompt loop
		printf("\n1-push a node into Binomial Heap,2-pop min node,3-get min value,4-display,5-Quit");
		printf("\nenter the choice:");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
  			printf("\nenter the value to be inserted: ");
  			scanf("%d", &v);
  			pushBinH(v);   //insert
  			break;
			case 2:
  			popBinH();     //delete min
  			break;
			case 3:
        if (root != NULL) {
          t = getmin();   //getmin
          if (t!= NULL) printf("\nMin is %d",t->next->key);
          else printf("\nMin is %d",root->key);
        }
        else printf("\nBinHeap is empty");
  			break;
      case 4:
        displayBinH();    //display
        break;
			case 5:
  			printf("\nprogram terminated");    //exit
  			return 0;
			default :
  			printf("\nInvalid choice");
		}
		printf("\n-----------------------------------------");
	}
}
