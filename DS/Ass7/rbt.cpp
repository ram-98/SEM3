#include<iostream>
#include <stdlib.h>
#include<climits>

using namespace std;

struct rbtNode{
         	int key;
			char color;
			struct rbtNode *left, *right,*parent;
		};    

struct rbtNode* root = NULL;
int flag=0;

rbtNode* GetNewNode(int value) {
    rbtNode* newNode = new rbtNode();
    newNode->key =value ;
    newNode->color='r';
    newNode->left = newNode->right = NULL;
	return newNode;
}
rbtNode* GetNilNode() {
    rbtNode* NilNode = new rbtNode();
    NilNode->key = INT_MAX;
    NilNode->color='b';
    NilNode->left = NilNode->right = NULL;
    return NilNode;
}

void displayinorder(rbtNode * root);
void leftRotate(struct rbtNode* x);
void rightRotate(struct rbtNode* y);
void rbinsert(rbtNode* z);
void rbinsertfixup(rbtNode* z);
void  insert(int value);

rbtNode* search(rbtNode* root,int value) {
    if((root->key)==INT_MAX) {
        return root;
    }
    else if(root->key == value) {
    	flag=1;
    	cout<<root->key<<"the searching finished\n";
        return root;
    }
    else if(value <= root->key) {
        return search(root->left,value);
    }
    else {
        return search(root->right,value);
    }
}
void rbtransplant(rbtNode * u,rbtNode *v){
	if(u->parent->key==INT_MAX)
		root=v;
	else if(u==u->parent->left)
		u->parent->left=v;
	else
		u->parent->right=v;
	v->parent=u->parent;
	return;
}
rbtNode * treemin(rbtNode * x){
	while(x->left->key!=INT_MAX)
		x=x->left;
	cout<<x->key<<"  "<<x->color<<"the min on rightsubtree\n";
	return x;
}
void rbtdeletefixup(rbtNode *x){
	rbtNode* w;
	while(x!=root && x->color=='b'){
		if(x==x->parent->left){
			w=x->parent->right;
				if(w->color=='r'){
					w->color='b';
					x->parent->color='r';
					leftRotate(x->parent);
					w=x->parent->right;
				}
				if(w->left->color=='b' && w->right->color=='b'){
					w->color='r';
					x=x->parent;
				}
				else {
					if(w->right->color=='b'){
					w->left->color='b';
					w->color='r';
					rightRotate(w);
					w=x->parent->right;
					}
					w->color=x->parent->color;
					x->parent->color='b';
					w->right->color='b';
					leftRotate(x->parent);
					x=root;
			}
		}
		else{
			w=x->parent->left;
				if(w->color=='r'){
					w->color='b';
					x->parent->color='r';
					rightRotate(x->parent);
					w=x->parent->left;
				}
				if(w->right->color=='b' && w->left->color=='b'){
					w->color='r';
					x=x->parent;
				}
				else {
					if(w->left->color=='b'){
					w->right->color='b';
					w->color='b';
					leftRotate(w);
					w=x->parent->left;
					}
					w->color=x->parent->color;
					x->parent->color='b';
					w->left->color='b';
					rightRotate(x->parent);
					x=root;
			}
		}
	}
	x->color='b';
}
void rbtdelete(rbtNode* z,int value){
	rbtNode *y=z;
	rbtNode *x=NULL;
	char y_oricolor=y->color;

	if (z->left->key==INT_MAX){
		x=z->right;
		rbtransplant(z,z->right);
	}
	else if (z->right->key==INT_MAX){
		x=z->left;
		rbtransplant(z,z->left);
	}
	else{
		y=treemin(z->right);
		y_oricolor=y->color;
		x=y->right;
		if (y->parent==z){
			x->parent=y;
		}
		else{
			rbtransplant(y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		rbtransplant(z,y);
		y->left=z->left;
		y->left->parent=y;
		y->color=z->color;
	}
	if(y_oricolor=='b')
		rbtdeletefixup(x);
	return;
}

int main(){
			int option,value,data;
			rbtNode* z;
			while(1){ 	
	        	cout<<"RBT is running - Enter your optiion :1:Insert  2:Delete  3:Traversal Inorder  4:Exit\n";
	        	cin>>option;
			switch(option){
			       case 1:
			          	cout<<"Enter the integer you want to add \n";
					  	cin>>value;
						insert(value);
						break;
				   case 2:
				   		cout<<"Enter the integer you want to delete \n ";
						cin>>value;
						 z= search(root,value);
						 if(z==root && z->left->key==INT_MAX && z->right->key==INT_MAX){
						 		root=NULL;
						 		cout<<"element successfully deleted\n";
						 }
						else if (flag)
						{
							rbtdelete(z,value);
							cout<<"element successfully deleted\n";
							flag=0;
						}
						else	
							cout<<"Entered element is not in Rbtree\n";
						
						break;
				   case 3:
				   		if (root==NULL)
				   		{
				   			cout<<"Tree is empty\n";
				   		}
				   		else{
							displayinorder(root);
							cout<<"Root is "<<root->key<<" Root color is "<<root->color<<endl;
				   		}
						break;
					case 4:
						exit(0);
					default:
						cout<<"Invalid optiion\n";
				}
			}
			return 0;
			}
void leftRotate(struct rbtNode* x){
          struct rbtNode *y;
		  y = x->right; 
		  x->right = y->left;
		  if( y->left ->key !=INT_MAX){
			          y->left->parent = x;
			      }
		  y->parent = x->parent;
		  if( x->parent->key == INT_MAX){
		            root = y;
				}
		  else if( x == x->parent->left){
		            x->parent->left = y;
		        }
		  else 
		  		x->parent->right = y;
		  y->left = x; 
		  x->parent = y;
		}

void rightRotate(struct rbtNode* y){
            struct rbtNode *x;
			x = y->left; y->left = x->right;
			if ( x->right ->key != INT_MAX){         
			 		x->right->parent = y;
			}
			x->parent = y->parent;
			if( y->parent->key == INT_MAX){
			          root = x;
			}
			else if( y== y->parent->left){         
			 y->parent->left = x;
			}
			else{
				y->parent->right = x;
			}
			x->right = y;
		    y->parent = x;
		}

void rbinsert(rbtNode* z){
		 rbtNode * y=NULL;
		 rbtNode * x=root;
		 while(x->key!=INT_MAX){
		 	y=x;
		 	if (z->key<x->key)
		 		x=x->left;
		 	else
		 		x=x->right;
		 }
		 z->parent=y;
		 if (z->key<y->key)
		 {
		 	y->left=z;
		 }
		 else
		 	y->right=z;
		 return;
}
void rbinsertfixup(rbtNode* z){
		rbtNode *y=NULL;
		while(z->parent->color=='r'){
				if (z->parent==z->parent->parent->left){
					y=z->parent->parent->right;
					if(y->color=='r'){
						z->parent->color='b';
						y->color='b';
						z->parent->parent->color='r';
						z=z->parent->parent;
					}
					else {
						if(z==z->parent->right){
						z=z->parent;
						leftRotate(z);
						}
						z->parent->color='b';
						z->parent->parent->color='r';
						rightRotate( z->parent->parent);
				}
			}
				else{
					y=z->parent->parent->left;
					if(y->color=='r'){
						z->parent->color='b';
						y->color='b';
						z->parent->parent->color='r';
						z=z->parent->parent;
					}
					else {
						if(z==z->parent->left){
						z=z->parent;
						rightRotate(z);
						}
						z->parent->color='b';
						z->parent->parent->color='r';
						leftRotate( z->parent->parent);
				}
				}
		}
		root->color='b';
}
void  insert(int value){
	if (root==NULL)
	{
		root = GetNewNode(value);
		root->parent=GetNilNode();
		root->parent->parent=NULL;
		root->left=root->right =GetNilNode();
		root->color='b';
	}
	else{
		rbtNode* z=GetNewNode(value);
		z->left=z->right=GetNilNode();
		rbinsert(z);
		rbinsertfixup(z);
	}
		 
}

void displayinorder(rbtNode * root){
    if((root->key)==INT_MAX )
        return;
    displayinorder(root->left);
    cout<<root->key<<"-----"<<"("<<root->color<<")"<<endl;
    displayinorder(root->right);
}