#include<iostream>
#include <stdlib.h>

using namespace std;

struct skiplistNode{
         	int value;
			struct skiplistNode *left, *right,*up, *down=NULL;
		}; 

skiplistNode* head, *tail;
int n,height,flag;
void CreateEmptyLayer(){
			skiplistNode* a=new skiplistNode();
			skiplistNode* b=new skiplistNode();
			a->value=-9999;
			b->value=9999;
			a->right = b;
			   a->down  = head;
			   b->left = a;
			   b->down = tail;
			   head->up = a;
			   tail->up = b;
			   height=height+1;
			   head=a;
			   tail=b;
}
void CreateEmptySkipList(){
			skiplistNode* a=new skiplistNode();
			skiplistNode* b=new skiplistNode();
			a->value=-9999;
			b->value=9999;
			a->right = b;
			b->left = a;
			head=a;
			tail=b;
			n=height=0;
}
skiplistNode * SLsearch(int value){
		skiplistNode *travel=new skiplistNode;
		travel=head;
		while(1){
			while(travel->right->value!=9999 && travel->right->value < value ){
					travel=travel->right;
			}
			if (travel->down!=NULL){
				travel=travel->down;
			}
			else
				break;
		}
		if(travel->right->value==value)
			travel=travel->right;	
		return travel;
}
void SLinsert(int value){
	skiplistNode* x= SLsearch(value);
	skiplistNode* y=new skiplistNode();
	skiplistNode* z=new skiplistNode();;

	int level=0;
	if(value==x->value){
		cout<<"Value already present enter different value\n";
	}
	else{
		y->value=value;				//y q  //x p// z e
		y->left = x;

	     y->right = x->right;
	     x->right->left = y;
	     x->right = y;
	     srand( time(NULL));
	     while(((rand()%10)+1)%2){
	     if(level==height){
	     	CreateEmptyLayer();
	     }
	     while(x->up==NULL){
	     	x=x->left;
	     }
	     x=x->up;
	     z=new skiplistNode();
	     z->left=x;
	     z->value=value;
	     z->right=x->right;
	     z->down=y;
	     x->right->left = z;
   		 x->right = z;
  		y->up = z;
		 y = z; 
		 level=level+1;
		}
	}
	n=n+1;
	return;
}
void SLDisplay(){
	cout<<"\nThe values in skip list are\n\n";
	skiplistNode *vertical ,*horizantal;
	vertical=head;
	while(vertical->down!=NULL)
		vertical=vertical->down;
	if(vertical->right->value==9999)
		cout<<"Empty skiplist\n";
	else{
		vertical=vertical->right;
		horizantal=vertical;
		while(horizantal->right!=NULL){
			vertical=horizantal;
			cout<<vertical->value<<"****";
			while(vertical->up!=NULL){
				cout<<vertical->value<<"****";
				vertical=vertical->up;
			}
			cout<<endl;
			horizantal=horizantal->right;
		}
	}
	cout<<endl;
}
void SLDelete(skiplistNode * temp){
	while(temp->up!=NULL){
		temp->left->right=temp->right;
		temp->right->left = temp->left;
		temp=temp->up;
	}
	temp->left->right=temp->right;
	temp->right->left = temp->left;
	return;
}
int main(){
			int option,value,data;
			skiplistNode* temp;
			CreateEmptySkipList();
			while(1){ 	
	        	cout<<"SKIPList is running - Enter your optiion \n1:Insert \n 2:Delete \n 3:displaySkiplist \n4:Search  \n5:Exit\n";
	        	cin>>option;
			switch(option){
			       case 1:
			       		cout<<"Enter the integer you want to add \n";
					  	cin>>value;
			       		SLinsert(value);
			       		break;
			       case 2:
			       		cout<<"Enter the integer you want to delete \n";
			       		cin>>value;
			       		temp= SLsearch(value);
			       		if(temp->value==value){
			       			SLDelete(temp);
			       			cout<<"VAlue sucessfully deleted\n";
			       		}
			       		else
			       			cout<<"value not found\n";
			       		break;
			       case 3:
			       		SLDisplay();
			       		break;
			       	case 4:
			       		cout<<"Enter the integer you want to search \n";
					  	cin>>value;
					  	temp= SLsearch(value);
			       		if(temp->value==value)
			       			cout<<"value is found in skplist\n";
			       		else
			       			cout<<"value not found\n";
			       		break;
			       case 5:
			       		exit(0);
			       		break;

			       }
			   }

			return 0;
			}
