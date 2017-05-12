#include <stdio.h>
#include <stdlib.h>
// main is at line 352

typedef struct node{
	int key;
	char *color;  //Black, BlackLeaf or Red
	struct node *left;
	struct node *right;
	struct node *par;
} RbNode;

RbNode *root = NULL;		//root node
int count = 0;		//total no. of values present

//search node by value
//if found, return corr node
//else return potential parent, if g is gonna be inserted
RbNode * search(int g) {
	RbNode *temp = root;
	if (root->color == "BlackLeaf")
		return temp;
	while (g!= temp->key) {
		if (g > temp->key ) {
			if ((temp->right)->color == "BlackLeaf")
				return temp->right;
			temp = temp->right;
		}
		else {
			if ((temp->left)->color == "BlackLeaf")
				return temp->left;
			temp = temp->left;
		}
	}
	return temp;
}

//rotate left -> meaning that "anticlockwise rot", t goes to left, and t->right replaces old pos of t
void leftrotate(RbNode *t) {
	RbNode *branchshift = (t->right)->left;
	RbNode *parent = t->par;
	(t->right)->par = parent;
	(t->right)->left = t;
	t->par = t->right;
	t->right = branchshift;
	branchshift->par = t;
	if (parent == NULL)
		root = t->par;
	else if (parent->left == t)
		parent->left = t->par;
	else parent->right = t->par;
}

//rotate right ->meaning that "rotating clockwise", t goes right
//and t->left replaces the old position of t
void rightrotate(RbNode	 *t) {
	RbNode *branchshift = (t->left)->right;
	RbNode *parent = t->par;
	(t->left)->par = parent;
	(t->left)->right = t;
	t->par = t->left;
	t->left = branchshift;
	branchshift->par = t;
	if (parent == NULL)
		root = t->par;
	else if (parent->left == t)
		parent->left = t->par;
	else parent->right = t->par;
}

void insertRb(int val) {		//Insert a value
	//here bst insert
	RbNode *temp = search(val);
	RbNode *leaf1 = (RbNode *) malloc(sizeof(RbNode));
	RbNode *leaf2 = (RbNode *) malloc(sizeof(RbNode));
	leaf1->color = "BlackLeaf";
	leaf2->color = "BlackLeaf";
	leaf1->left = NULL;
	leaf2->left = NULL;

	if (temp->color != "BlackLeaf") {
		printf("\nAlready exists..");
		return;
	}
	else {		//If value is not present in the tree, then insert the value and add two black leaves to it
		temp->key = val;
		temp->left = leaf1;
		temp->right = leaf2;
		leaf1->par = temp;
		leaf2->par = temp;
	}
	printf("\n%d is inserted", val);
	count++;

	//Now fix the colors
	temp->color = "Red";

	RbNode *parent;
	RbNode *uncle;
	RbNode *gparent;
	while (1) {
		if (temp == root) {		//must be black
			temp->color = "Black";
			return;
		}
		parent = temp->par;
		if (parent->color == "Red") {		//consecutive Reds not allowed
			gparent = parent->par;
			if (gparent->left == parent)
				uncle = gparent->right;
			else uncle = gparent->left;
			if (uncle->color == "Red") {		//case 1: If uncle is Red
				parent->color = "Black";
				uncle->color = "Black";
				gparent->color = "Red";
				temp = gparent;
			}
			else {		//case 2: If uncle is Black
				if ((gparent->left == parent)&&(parent->left == temp)) {		// case 2 a) left - left
					rightrotate(gparent);
					parent->color = "Black";
				}
				else if ((gparent->left == parent)&&(parent->right == temp)) {	//case 2 b) left - right
					leftrotate(parent);		//after this the case turns into left - left
					rightrotate(gparent);
					temp->color = "Black";
				}
				else if ((gparent->right == parent)&&(parent->right == temp)) {		//case 2 c) right - right
					leftrotate(gparent);
					parent->color = "Black";
				}
				else {		//case 2 d) right - left
					rightrotate(parent);		// after this , case turns into right - right
					leftrotate(gparent);
					temp->color = "Black";
				}
				gparent->color = "Red";
				return;
			}
		}
		else return;	//Parent is black i.e., No consecutive Reds
	}
}

void deleteRb(int val) {		//delete a given value
	//std BST deletion
	if (root->color != "BlackLeaf") {
		RbNode *del = search(val);
		if (del->color != "BlackLeaf") {
			printf("\n%d is deleted from RbTree", val);

			RbNode *tmp = del->left;
      while (tmp->color != "BlackLeaf") {
      	tmp = tmp->right;
      }
			RbNode *del1 = tmp->par;

			int s;
			s = del1->key;
			del1->key = del->key;
			del->key = s;
			//case 1
			if (count == 1) {		//If there is only one element and is to be deleted
				root = del1->right;
				free(del1->left);
				free(del1);
				root->par = NULL;
				count = 0;
			}
			//if the node or any of its children is Red -> No need to implement DoubleBlack
			else if ((del1->color == "Red") || ((del1->left)->color == "Red") || ((del1->right)->color == "Red")) {
				if ((del1->right)->color == "Red") {
					tmp = del1->right;
					free(del1->left);
				}
				else {
					free(del1->right);
					tmp = del1->left;
				}
				tmp->par = del1->par;
				if (del1->par == NULL) {
					root = tmp;
					free(del1);
				}
				else if (del1 == (del1->par)->left) {
					(del1->par)->left = tmp;
					free(del1);
				}
				else {
					(del1->par)->right = tmp;
					free(del1);
				}
				count--;
				if (tmp->left == NULL) tmp->color = "BlackLeaf";
				else tmp->color = "Black";
			}
			else {		//if the node and its children are Black
				RbNode *sib;
				tmp->par = del1->par;
				if (del1 == (del1->par)->left) (del1->par)->left = tmp;
				else	(del1->par)->right = tmp;

				if (tmp == del1->right) free(del1->left);
				else free(del1->right);
				free(del1);
				count--;

				tmp->color = "DoubleBlack";		//After deleting the node, make one one of its children as double black
				//Double Black -> means the node is treated as two blacks...to maintain equal no. of black nodes in all the branches
				RbNode *parent;
				RbNode *child;

				while((tmp->color == "DoubleBlack")&&(tmp!= root)) {	//root can be made Black from DoubleBlack..does not violate equality
					//initialize parent, child, sib
					parent = tmp->par;
					if (tmp == parent->right) {
						sib = parent->left;
						if ((sib->left)->color == "Red") child = sib->left;		//sib and its child on same side is preferrable..since easy to solve
						else child = sib->right;
					}
					if (tmp == parent->left) {
						sib = parent->right;
						if ((sib->right)->color == "Red") child = sib->right;  //same here
						else child = sib->left;
					}
					//all cases
					//***Case 1***If sibling is black, and atleast one child of it is Red
					if ((sib->color == "Black")&&(((sib->right)->color == "Red") || ((sib->left)->color == "Red"))) {
						//** a)left - left
						if ((parent->left == sib)&&(sib->left == child)) {
							rightrotate(parent);
							sib->color = parent->color;
							child->color = "Black";
						}
						//** b)left - right
						else if ((parent->left == sib)&&(sib->right == child)) {
							leftrotate(sib);
							sib->color = "Red";
							child->color = "Black";
							rightrotate(parent);
							child->color = parent->color;
							sib->color = "Black";
						}
						//** c)right - right
						else if ((parent->right == sib)&&(sib->right == child)) {
							leftrotate(parent);
							sib->color = parent->color;
							child->color = "Black";
						}
						//** d) right - left
						else {
							rightrotate(sib);
							sib->color = "Red";
							child->color = "Black";
							leftrotate(parent);
							child->color = parent->color;
							sib->color = "Black";
						}
						//These two steps are common to all the above sub cases
						parent->color = "Black";
						if (tmp->left == NULL) tmp->color = "BlackLeaf";
						else tmp->color = "Black";
						return;
					}
					//***Case 2*** If Sibling is black, also its children
					else if (sib->color == "Black") {
						sib->color = "Red";
						if ((sib->par)->color == "Black") {		// ***a) If parent is Black, then make it DoubleBlack
							if (tmp->left == NULL) tmp->color = "BlackLeaf";
							else tmp->color = "Black";
							tmp = sib->par;
							tmp->color = "DoubleBlack";
						}
						else {		//***b) If parent is Red, Then make it Black and stop
							if (tmp->left == NULL) tmp->color = "BlackLeaf";
							else tmp->color = "Black";
							(sib->par)->color = "Black";
							return;
						}
					}
					//***Case 3:::***
					else {		// If sibling is Red
						if (parent->right == sib)	leftrotate(parent);
						else rightrotate(parent);
						parent->color = "Red";
						sib->color = "Black";
					}
				}
				if (tmp == root) {		//Root Case
					if (tmp->left == NULL) tmp->color = "BlackLeaf";
					else tmp->color = "Black";
					return;
				}
			}
		}
		else {
			printf("\nNot found");
		}
	}
	else {
		printf("\nBST is empty");
	}

}

void inorder(RbNode *t) {		//In Order traversal
  if(t->color != "BlackLeaf"){
    inorder(t->left);
    printf("%d ",t->key);
    inorder(t->right);
  }
}

int findheight (RbNode *t) {		// To find height of the tree recursively
	if (t->color == "BlackLeaf")
		return 0;
	else {
		int lheight = findheight(t->left);		//left subtree height
		int rheight = findheight(t->right);		//right subtree height
		if (lheight>rheight)
			return lheight + 1;
		else
			return rheight + 1;
	}
}

void printlevel(RbNode *t, int level) {		//print particular level of tree
	if (t->color == "BlackLeaf")
		return;
	if (level == 1) {
		printf("%d(%c", t->key, t->color[0]);
		if (t->par!=NULL) {
			printf(",%d",(t->par)->key);
		}
		printf(")  ");
	}
	else {
		printlevel(t->left, level-1);
		printlevel(t->right, level-1);
	}
}

void levelorder() {		// print all levels -->Level Order
	int height = findheight(root);
	for (int i=1;i<=height;i++) {
		printf("\nlevel-%d:\n",i);
		printlevel(root, i);
	}
}


int main() {	// main function
	int choice, v;
	root = (RbNode *) malloc(sizeof(RbNode));
	root->par = NULL;
	root->left = NULL;
	root->color = "BlackLeaf";
	printf("\nRB-TREE...........");
	while(1) {		// prompt loop
		printf("\n1-insert a node into RbTree,2-delete a node by value,3-display,4-Search,5-exit");
		printf("\nenter the choice:");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				printf("\nenter the value to be inserted:");
				scanf("%d", &v);
				insertRb(v);	//insert
				break;
			case 2:
				printf("\nenter the value to be deleted:");
				scanf("%d", &v);
				deleteRb(v);	//delete
				break;
			case 3:
				printf("\ndisplay-inorder:\n");
				inorder(root);	//display - inorder
				printf("\n\ndisplay-levelorder:\n");
				levelorder();		//display - level order
				break;
			case 4:		//search
				printf("\nEnter the value to be searched for : ");
				scanf("%d", &v);
				if (root->color != "BlackLeaf") {
					if (search(v)->color == "BlackLeaf") printf("\nNot Found");
					else printf("\nFound");
				}
				else printf("\nRBTree is empty");
				break;
			case 5:
				printf("\nprogram terminated");		//exit
				return 0;
			default :
				printf("\nInvalid choice");
		}
		printf("\n-----------------------------------------");
	}
}
