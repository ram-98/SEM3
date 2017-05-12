#include<stdio.h>
#include<stdlib.h>
//main is at line 130
//BST - parent > nodes on left ; parent < nodes on right

struct node {		//BST node
	int k;
	struct node *left;
	struct node *right;
};

struct childpar {		//struct of two BST nodes. used in some functions for ease of writing code
  struct node *child;
  struct node *par;
};

struct node *root = NULL;

//search by value, returns a childpar-
//if g exists then child - has g, and par is its parent
//else child is the potential parent of new node , if g is gonna be inserted
struct childpar search(int g) {
  struct childpar temp;
  temp.child = root;
  temp.par = NULL;
	while ((temp.child)->k != g) {
		if ((temp.child)->k < g) {
      if ((temp.child)->right != NULL) {
        temp.par = temp.child;
        temp.child = (temp.child)->right;
      }
      else
        return temp;
    }
		else {
      if ((temp.child)->left != NULL) {
        temp.par = temp.child;
        temp.child = (temp.child)->left;
      }
      else
        return temp;
    }
	}
  return temp;
}

//Insert => add a new node to the tree, if it is distinct from the values already there in binary tree
void insert(int s) {
	struct node *temp = (struct node *) malloc(sizeof(struct node));
	temp->k = s;
	temp->left = NULL;
	temp->right = NULL;
	if (root == NULL) {
		printf("\ninserted at root");
		root = temp;
	}
	else {
		struct childpar tmp = search(temp->k);
    if ((tmp.child)->k != temp->k) {
      if (temp->k > (tmp.child)->k)
				(tmp.child)->right = temp;
			else
				(tmp.child)->left = temp;
			printf("\n%d is inserted into BST",temp->k);
    }
		else {
      printf("\nentry already exists!");
    }
	}
}

// delete => deletes a node by value from BST
void del(int s) {
	struct childpar tmp = search(s);
	if ((tmp.child)->k == s) {
		printf("\n%d is deleted from BST", s);
    struct childpar t;
    t.child = (tmp.child)->left;
    t.par = tmp.child;
    while (t.child != NULL) {
    	if ((t.child)->right == NULL) {
        break;
    	}
      t.par = t.child;
      t.child = (t.child)->right;
    }
    if ((tmp.child)->left == NULL) {		//has no left node...hence we delete the same node
      t.child = tmp.child;
      t.par = tmp.par;
    }
    else {		//has left node...hence exchange the values b/w max on left and this node
			//now max on left is to be deleted
      (tmp.child)->k = (t.child)->k;
      (t.child)->k = s;
    }
    if (t.par == NULL) {	//if del node is root
      root = root->right;
      free(t.child);
    }
    else {
      if (t.par == tmp.child)		//if del node is direct left child of "old node(s)"
        (t.par)->left = (t.child)->left;
      else
        (t.par)->right = (t.child)->left;
      free(t.child);
    }
	}
	else {
		printf("\nNot found");
	}
}

void inorder(struct node *t) {		//inorder traversal of BST, should give ascending numbers
  if(t!=NULL){
    inorder(t->left);
    printf("%d ",t->k);
    inorder(t->right);
  }
}

int main() {		//main function
	int i,f;
	printf("\n\nBinary Search Tree::\n");
	while(1) {	//prompt loop
		printf("\n\n\n1-insert node,2-delete node,3-search node,4-display,5-exit:\n");
		scanf("%d",&i);
		switch (i) {
			case 1:
				printf("\nEnter the value to be inserted : ");
				scanf("%d", &f);
				insert(f);		//insert
				break;
			case 2:
				printf("\nEnter the value to be deleted : ");
				scanf("%d", &f);
				del(f);			//delete
				break;
			case 3:
				if (root != NULL) {
					printf("\nenter search value:");
					scanf("%d",&f);
					if ((search(f).child)->k == f)		//search
						printf("\nFound");
					else
						printf("\nNot Found");
				}
				else {
					printf("\nBST is empty");
				}
				break;
      case 4:
	      printf("\n");
				if (root != NULL) printf("Root : %d\n", root->k);
				else printf("BST is empty\n");
				printf("\nIn Order ::\n");
	      inorder(root);		//display
	      break;
			case 5:
				printf("\nprogram terminated");
				return 0;		//exit
			default:
				printf("\nInvalid response");
		}
		printf("\n------------------------------------------------");
	}
}
