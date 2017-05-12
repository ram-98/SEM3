#include<stdio.h>
#include<stdlib.h>	//for malloc, rand functions
//main is at line 116

typedef struct node {		//SkipList Node
	int key;
	struct node *right;
	struct node *left;
	struct node *down;
	struct node *up;
} SLNode;

SLNode *head = NULL;	//starting point of top linked list
SLNode *tail = NULL;	//ending point of top linked list

SLNode *SearchSList(int val) {	//search for the node by value
	SLNode *temp = head;
	while(temp->key != val) {
		if ((temp->right->key <= val)&&(temp->right->key != 9999)) temp = temp->right;
		else if (temp->down != NULL) temp = temp->down;
		else return temp;		//if not found...returns prev of possible insertion point
	}
	if ((temp->key == val)&&(temp->key != -9999)) return temp;
	else return temp->right;
}

void promote(SLNode *t) {		//promote after insertion based on toss (rand()%2)
	SLNode *begin = head;
	SLNode *traverse,*new;
	SLNode *end = tail;
	while(begin->down != NULL) begin = begin->down;	//Now begin is start of bottom ll
	while(end->down != NULL) end = end->down;		//Now end is end of bottom ll
	while (rand() % 2) {  //promotion step
		if (begin == head) {		//If promotion needs another ll to be initialized at the top
			new = (SLNode *) malloc(sizeof(SLNode));
			begin->up = new;
			new = (SLNode *) malloc(sizeof(SLNode));
			end->up = new;
			begin->up->key = -9999;
			end->up->key = 9999;
			head = begin->up;
			tail = end->up;
			head->down = begin;
			tail->down = end;
			head->right = tail;
			tail->left = head;
		}

		new = (SLNode *) malloc(sizeof(SLNode));	//new node
		new->key = t->key;
		new->down = t;
		t->up = new;

		begin = begin->up;
		end = end->up;
		traverse = begin;
		while(traverse->right->key < new->key) traverse = traverse->right;	//placing the node at right place
		new->right = traverse->right;
		traverse->right->left = new;
		new->left = traverse;
		traverse->right = new;

		t = new;
	}
	t->up = NULL;
}

void InsertSList(int val) {		//insert nodes by value (should be distinct from prev values)
	SLNode *In = SearchSList(val);
	SLNode *temp;
	if ((val<=-9999)||(val>=9999)) printf("\nPlease insert a value between -9999 and 9999 (excluding)");
	else if (In->key == val) printf("\nAlready Exists...");
	else {		//placing at the right place, in bottom ll and call promote
		printf("\n%d is inserted into skiplist", val);
		temp = (SLNode *) malloc(sizeof(SLNode));
		temp->key = val;
		temp->right = In->right;
		temp->right->left = temp;
		temp->down = NULL;
		temp->left = In;
		In->right = temp;
		promote(temp);
	}
}

void DeleteSList(int val) {		//delete nodes by value
	SLNode *dl = SearchSList(val);
	SLNode *temp;
	if (dl->key == val) {		// if data exists
		while(dl->up != NULL) dl = dl->up;
		while(dl != NULL) {
			temp = dl->down;
			dl->left->right = dl->right;
			dl->right->left = dl->left;
			if ((dl->left == head)&&(dl->right == tail)&&(dl->down != NULL)) {	//if this node is the only one in that row
				head = head->down;
				tail = tail->down;
				free(dl->left);
				free(dl->right);
			}
			free(dl);
			dl = temp;
		}
		printf("\n%d is deleted from skiplist", val);
	}
	else printf("\nNot Found");
}

void DisplaySList() {		//display SkipList
	for (SLNode *tdown = head, *tend = tail; tdown != NULL; (tdown = tdown->down) && (tend = tend->down) ) {
		printf("\n");
		for (SLNode *t = tdown->right; t!= tend; t = t->right) printf("%d -->",t->key);
	}
}

int main() {		//main function
	int choice,val;
	head = (SLNode *) malloc(sizeof(SLNode));		//first linked list initialization
	head->key = -9999;
	tail = (SLNode *) malloc(sizeof(SLNode));
	tail->key = 9999;
	head->right = tail;
	head->down = NULL;
	tail->down = NULL;
	tail->left = head;
	printf("\nSkipList>>>>>");
	while(1) {		//prompt loop (inf)
		printf("\n\n1-Insert a node, 2-Delete a node, 3-Search fora node, 4-Display, 5-exit");
		printf("\nEnter choice: ");
		scanf("\n%d",&choice);
		switch(choice) {
			case 1:
				printf("\nEnter the value to be inserted: ");
				scanf("%d",&val);
				InsertSList(val);		//Insert
				break;
			case 2:
				printf("\nEnter the value to be deleted: ");
				scanf("%d",&val);
				DeleteSList(val);		//delete
				break;
			case 3:
				printf("\nEnter the value to be searched for: ");
				scanf("%d",&val);
				if (SearchSList(val)->key == val) printf("\nFound");		//search
				else printf("\nNot Found");
				break;
			case 4:
				DisplaySList();		//display
				break;
			case 5:
				printf("\nProgram exited");
				return 0;		//exit
			default :
				printf("\nenter a valid choice");
		}
		printf("\n.........................................");
	}
}
