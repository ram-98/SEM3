#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
//main is at line 251

typedef struct node {
  int key[5];
  int n; //current num keys
  bool isleaf;    //if is a leaf node
  struct node *parent;
  struct node *child[6];
} BNode;

BNode *root = NULL;   //root node

BNode *search(int val) {    //search node by value
  BNode *temp = root;
  int i;
  while(1) {
    for (i=0;i<temp->n;i++) {   //searching the current node
      if (val == temp->key[i])
        return temp;
      if (val < temp->key[i])
        break;
    }
  	if (temp->isleaf == false)   //if not found at this node
  		temp = temp->child[i];
    else
      return temp;
  }
}

void Inorder(BNode *t) {    //Inorder traversal
  for (int i=0;i<=t->n;i++) {
    if (t->isleaf == false)
      Inorder(t->child[i]);
    if (i != t->n) printf("%d ",t->key[i]);
  }
}

void splitup(BNode *split) {    //fix btree (no of keys overflow)
  int i,j,val;
  BNode *t;
  while (split->n == 5) {   //while this node violates Btree property (max no of keys)
    val = split->key[2];

    //separate 4th, 5th keys - and make the new node sibling to this split node
    t = (BNode *) malloc(sizeof(BNode));
    t->parent = split->parent;
    for (int i=0;i<6;i++) {
      t->child[i] = NULL;
    }
    t->n = 2;
    split->n = 2;
    t->isleaf = split->isleaf;
    t->key[0] = split->key[3];
    t->key[1] = split->key[4];
    t->child[0] = split->child[3];
    t->child[1] = split->child[4];
    t->child[2] = split->child[5];
    if (t->isleaf == false) {   //if it is not a leaf node - adjusting parent pointers of the divided children
      t->child[0]->parent = t;
      t->child[1]->parent = t;
      t->child[2]->parent = t;
    }
    split->child[3] = NULL;
    split->child[4] = NULL;
    split->child[5] = NULL;
    if (split->parent == NULL) {    //if there is no node above the present node
      split->parent = (BNode *) malloc(sizeof(BNode));  //create a new one and make it root
      t->parent = split->parent;
      split->parent->parent = NULL;
      for (int i=0;i<6;i++) {
        split->parent->child[i] = NULL;
      }
      split->parent->n = 1;
      split->parent->isleaf = false;
      split->parent->child[0] = split;
      split->parent->child[1] = t;
      split->parent->key[0] = val;

      root = split->parent;
      return;
    }
    j = split->parent->n;
    for(i=0;i<j;i++) {    // place the (old node - middle value) in the parent node..i.e., promoting middle
      if (split->key[0] < split->parent->key[i])
        break;
    }
    split = split->parent;    // check the order of keys and child ptrs in the parent ..and then
    //carry the iteration on parent
    while(j>i) {
      split->child[j+1] = split->child[j];
      split->key[j] = split->key[j-1];
      j--;
    }
    split->child[j+1] = t;
    split->key[j] = val;
    split->n += 1;
  }
}

void insertBtree(int val) {   //Insert a value into Btree
  BNode *temp = search(val);
  int i;
  for (i=0;i<temp->n;i++) {
    if (val == temp->key[i])
      break;
  }
  if (i == temp->n) {   //If the value is not already present
    //insertion main code
    int j = temp->n - 1;
    while(j>=0 && temp->key[j] > val) {   //Inserting at the right place in the node - (keys should be sorted)
      temp->key[j+1] = temp->key[j];
      j--;
    }
    temp->key[j+1] = val;
    temp->n += 1;
    if (temp->n == 5) {   //if no of keys == 5 (max)...split the node then promote the middle value to uppernodes
      splitup(temp);
    }
    else {
      return;
    }
  }
  else {
    printf("\nGiven key exists...Enter a new key");
    return;
  }
}

void Adjust(BNode *A) {   // fix btree (no. of keys underflow)
  if ((A == root)||(A->n>1)) {
    if (root->n == 0) {   // root has no keys also root->child[0] wont be NULL
      BNode *t = root;
      root = root->child[0];
      free(t);
    }
    return;
  }
  BNode *temp = A->parent;
  int i;
  for (i=0;i<temp->n;i++) {
    if (A->key[0] < temp->key[i])
      break;
  }
  if (i < temp->n) {    //if the node has right sibling
    A->key[1] = temp->key[i];
    if (temp->child[i+1]->n > 2) {    //and it has more than 2 keys..then the node can borrow a value from here
      temp->key[i] = temp->child[i+1]->key[0];
      A->n++;
      (temp = temp->child[i+1])->n--;
      A->child[2] = temp->child[0];
      if (A->isleaf == false) A->child[2]->parent = A;
      for(int i=0;i<temp->n;i++) {
        temp->key[i] = temp->key[i+1];
        temp->child[i] = temp->child[i+1];
      }
      temp->child[temp->n] = temp->child[temp->n+1];
    }
    else {    //otherwise , these two nodes can be merged...resulting node will have 4 keys
      A->key[2] = temp->child[i+1]->key[0];
      A->key[3] = temp->child[i+1]->key[1];
      A->child[2] = temp->child[i+1]->child[0];
      A->child[3] = temp->child[i+1]->child[1];
      A->child[4] = temp->child[i+1]->child[2];
      if (A->isleaf == false) {
        A->child[2]->parent = A;
        A->child[3]->parent = A;
        A->child[4]->parent = A;
      }

      free(temp->child[i+1]);
      temp->n--;
      for(int j=i;j<temp->n;j++) {
        temp->key[j] = temp->key[j+1];
        temp->child[j+1] = temp->child[j+2];
      }
      A->n = 4;
      Adjust(temp);   //then the parent looses a key, hence adjust (Parent)
    }
  }
  else {    //if there is no right sibling..There must be left sibling
    if (temp->child[i-1]->n > 2) {  //if it has more than 2 keys..borrow from here
      A->key[1] = A->key[0];
      A->key[0] = temp->key[i-1];
      temp->key[i-1] = temp->child[i-1]->key[temp->child[i-1]->n-1];
      A->n++;
      (temp = temp->child[i-1])->n--;
      A->child[2] = A->child[1];
      A->child[1] = A->child[0];
      A->child[0] = temp->child[temp->n+1];
      if (A->isleaf == false) A->child[0]->parent = A;
    }
    else {    //otherwise , these two nodes can be merged, resulting node will have 4 keys
      temp->child[i-1]->key[2] = temp->key[i-1];
      temp->child[i-1]->key[3] = A->key[0];
      temp->child[i-1]->child[3] = A->child[0];
      temp->child[i-1]->child[4] = A->child[1];
      if (temp->child[i-1]->isleaf == false) {
        temp->child[i-1]->child[3]->parent = temp->child[i-1];
        temp->child[i-1]->child[4]->parent = temp->child[i-1];
      }

      free(A);
      temp->n--;
      temp->child[i-1]->n = 4;
      for(int j=i-1;j<temp->n;j++) {
        temp->key[j] = temp->key[j+1];
        temp->child[j+1] = temp->child[j+2];
      }
      Adjust(temp);   //the parent looses a key, hence Adjust (Parent)
    }
  }

}

void deleteBtree(int val) {   //delete a value
  if (root->n == 0) {
    printf("\nBTree is empty");
    return;
  }
  BNode *del = search(val);
  int i;
  for (i=0;i<del->n;i++) {
    if (val == del->key[i])
      break;
  }
  if (i < del->n) {   //if the value is present
    //main code here
    BNode *del1 = del;
    if (del->isleaf == false) {   //traverse down on left side of value to be deleted till the leaf that has max
      del1 = del->child[i];
      while(del1->isleaf == false) {
        del1 = del1->child[del1->n];
      }
      del->key[i] = del1->key[del1->n - 1];   //then move this value to the place of the value to be deleted
      i=del1->n - 1;
    }
    del1->n--;    //now we can delete this value in the leaf node instead
    for(int j=i;j<del1->n;j++) del1->key[j] = del1->key[j+1];
    if ((del1!= root)&&(del1->n < 2))   //if Btree property is violated (leaf should have - atleast 2 keys)
      Adjust(del1);
  }
  else {
    printf("\nNot found");
  }
}


int main() {    //main function
  int temp,choice,i;
  int val;
  BNode *t;
  printf("\nBtree>>>>>>>>>>>>>>");
  root = (BNode *) malloc(sizeof(BNode));   //initializing the root node
  root->parent = NULL;
  root->isleaf = true;
  for (int i=0;i<6;i++) {
    root->child[i] = NULL;
  }
  root->n = 0;
  while(1) {    //prompt loop
    printf("\n1-add a new key to Btree, 2-delete a key, 3-search for a key, 4-Inorder, 5-exit\n");
    printf("\nenter choice:");
    scanf("%d",&choice);

    switch(choice) {
      case 1:
        printf("\nenter the value to be deleted from BTree>>>");
        scanf("%d", &val);
        insertBtree(val);   //insert
        break;
      case 2:
        printf("\nenter the value to be deleted from BTree>>>");
        scanf("%d", &val);
        deleteBtree(val);   //delete
        break;
      case 3:
        printf("\nenter the key you want to search for:");
        scanf("%d",&temp);
        t = search(temp);   //search
        for (i=0;i<t->n;i++) {
          if (temp == t->key[i])
            break;
        }
        if (i < t->n) printf("\nFound");
        else printf("\nNot Found");
        break;
      case 4:
        if (root->n == 0) printf("\nRoot - NULL");
        else {
          printf("\nRoot - [");
          for (int tem=0;tem<root->n;tem++)
            printf(" %d ,",root->key[tem]);
          printf("]");
        }
        printf("\n\nIn Order ::\n");
        Inorder(root);    //display
        break;
      case 5:
        printf("\nProgram exited\n");
        return 0;   //exit
      default :
        printf("\nenter a valid choice");
    }
    printf("\n--------------------------------");
  }
}
