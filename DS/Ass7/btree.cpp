#include<iostream>
#include<malloc.h>
#include<cstdlib>

using namespace std;

struct btreenode         //structure for each node
{
    int n;
    int keys[5];
    struct btreenode* child[6];
    bool leaf;
    struct btreenode *parent;
};
struct btreenode *root=NULL;
int flag,flag1=0;
void displayinorder(struct btreenode*root) ;
btreenode*  search(btreenode *x, int k);

void splitchild(btreenode *x, int i){
	if(x==root){
			
			btreenode *r=root;
			btreenode *temp=new btreenode();
			btreenode * s=new btreenode();
		root=s;
		flag=flag+1;
		s->leaf=false;
		s->n=1;
		s->child[0]=r;
		s->child[1]=temp;
		s->child[1]->n=2;
		s->child[0]->n=2;
		s->keys[0]=r->keys[2];
		s->child[1]->keys[0]=s->child[0]->keys[3];
		s->child[1]->keys[1]=s->child[0]->keys[4];
		s->child[1]->parent=root;
		s->child[0]->parent=root;
		if(flag==1){
		s->child[1]->leaf=s->child[0]->leaf=true;
		}
		else
			s->child[1]->leaf=s->child[0]->leaf=false;
		if (!(s->child[0]->leaf))
		{
			s->child[1]->child[0]=s->child[0]->child[3];
			s->child[1]->child[1]=s->child[0]->child[4];
			s->child[1]->child[2]=s->child[0]->child[5];
			}
		return;
	}
	else{
		btreenode *z=new btreenode();
		btreenode *y=x;
		z->n=2;
		x=x->parent;
		z->leaf=y->leaf;
		z->keys[0]=y->keys[3];
		z->keys[1]=y->keys[4];
		//cout<<"\nim in first 	loop\n ";
		if (!(y->leaf))
		{
			z->child[0]=y->child[3];
			z->child[1]=y->child[4];
			z->child[2]=y->child[5];
			}
		y->n=2;
		y->parent=x;
		z->parent=x;
		for (int j = x->n; j >=i+1 ; j--)
		{
			x->child[j+1]=x->child[j];
		}
		x->child[i+1]=z;
		for (int j = x->n-1; j >=i ; j--)
		{
			
			x->keys[j+1]=x->keys[j];
		}
		//cout<<"im out of loop\n";
		x->keys[i]=y->keys[2];
		x->n=x->n+1;

		if(x!=root){
		for (int j = 0;  j< (x->parent->n)+1; j++)
		{
			if (x==x->parent->child[j]){
				i=j;
				break;
			}
		}
		}
		if(x->n==5)
			splitchild(x,i);
	}
}
void InsertNonfull(btreenode *x,int k){
	int i=x->n -1;
	
	if(x->leaf){
		if(i!=-1){
				while(i>=0 && k<x->keys[i]){
			x->keys[i+1]=x->keys[i];
			i=i-1;
		}
		}
		x->keys[i+1]=k;
		x->n=x->n+1;	 
		if(x->n==5){
			if(x!=root){
			for (int j = 0;  j< (x->parent->n)+1; j++)
				{
					if (x==x->parent->child[j]){
						i=j;
						break;
					}
				}
			}
			splitchild(x,i);
		}
	}
	else{
		if(i!=-1){
		while(i>=0 && k<x->keys[i]){
			i=i-1;
		}
			}
		i=i+1;
		InsertNonfull(x->child[i],k);
	}
	return;
}

void insert(int k){
	btreenode *r=root;	
	InsertNonfull(r,k);
	return;
}
void   del_leaf(int value, btreenode*x)     //function to delete element from the leaf btreenode
{
    struct btreenode*temp;
    int k,t,p;
    for(int i=0;i<x->n;i++)
    {
    	if(x->keys[i]==value)
    	{
    		p=i;
    		break;
    	}
    }
    if(x->parent==NULL||x->n>2)           //Leaf has more than 2 values
    {	
        for(int i=p;i<x->n;i++)
        {
            x->keys[i]=x->keys[i+1];
            x->child[i+1]=x->child[i+2];
        }
        x->n=x->n-1;
    }
    else                                       //"Leaf has 2 values
    {	
        for(int i=0;i<=x->parent->n;i++)
        {
            if(x->parent->child[i]==x)
            {
                k=i;
                break;
            }
            
        }
        if(x->keys[1]==value)
        	t=1;
        else
        	t=0;
        if(k!=0 && ((x->parent)->child[k-1])->n>2)       //Left shift
        {	
            if(t==1)
            {
                x->keys[t]=x->keys[0];
               x->keys[0]=x->parent->keys[k-1];
               x->parent->keys[k-1]=x->parent->child[k-1]->keys[x->parent->child[k-1]->n-1];
               x->parent->child[k-1]->n=x->parent->child[k-1]->n -1;
            }
            if(t==0)
            {
                x->keys[0]=x->parent->keys[k-1];
                x->parent->keys[k-1]=x->parent->child[k-1]->keys[x->parent->child[k-1]->n-1];
               x->parent->child[k-1]->n=x->parent->child[k-1]->n -1;
            }
        }
        else
        {	
            if(((k!=0 && ((x->parent)->child[k-1])->n==2)|| k==0) && (x->parent)->child[k+1]!=NULL && ((x->parent)->child[k+1])->n>2)      //Right shift
            {	
                if(t==1)
                {
                    x->keys[p]=x->parent->keys[k];
                    x->parent->keys[k]=x->parent->child[k+1]->keys[0];
                }
                if(t==0)
                {
                    x->keys[0]=x->keys[1];
                    x->keys[1]=x->parent->keys[k];
                    x->parent->keys[k]=x->parent->child[k+1]->keys[0];
                }
                for(int i=0;i<(((x->parent)->child[k+1])->n);i++)
                {
                    x->parent->child[k+1]->keys[i]=x->parent->child[k+1]->keys[i+1];
                }
                x->parent->child[k+1]->n=x->parent->child[k+1]->n -1;
            }
            else          																		 //mergecase
            {	
                if(k!=0 && x->parent->child[k-1]->n==2 && ((x->parent->child[k+1]!=NULL && x->parent->child[k+1]->n==2) || x->parent->child[k+1]==NULL))
                {	       																		 //left merge 
                    x->parent->child[k-1]->keys[2]=x->parent->keys[k-1];
                    if(t==1)
                    {
                    	x->parent->child[k-1]->keys[3]=x->keys[0];
                    }
                    else
                    {
                    	x->parent->child[k-1]->keys[3]=x->keys[1];
                    }
                    x->parent->child[k-1]->n=x->parent->child[k-1]->n +2;
                    for(int i=k-1;i<x->parent->n-1;i++)
                    {
                        x->parent->keys[i]=x->parent->keys[i+1];
                        x->parent->child[i+1]=x->parent->child[i+2];
                    }
                    x->parent->n=x->parent->n-1;
                    if(x->parent->n==0)
					{
                    	root=x->parent->child[0];
                    	x->parent->child[0]->parent=NULL;
                    }
                }        												
                else       												//right merge 
                {	
                    if(k==0)
                    {
                        x->parent->child[k+1]->keys[3]=x->parent->child[k+1]->keys[1];
                        x->parent->child[k+1]->keys[2]=x->parent->child[k+1]->keys[0];
                        x->parent->child[k+1]->keys[1]=x->parent->keys[k];
                        if(t==1)
                        {
                        	x->parent->child[k+1]->keys[0]=x->keys[0];
                        }
                        else
                        {
                        	x->parent->child[k+1]->keys[0]=x->keys[1];
                        }
                        x->parent->child[k+1]->n=x->parent->child[k+1]->n+2;
                        for(int i=0;i<x->parent->n-1;i++)
                        {
                            x->parent->keys[i]=x->parent->keys[i+1];
                        }
                        for(int i=0;i<x->parent->n;i++)
                        {
                            x->parent->child[i]=x->parent->child[i+1];
                        }
                        x->parent->n=x->parent->n-1;
                        if(x->parent->n==0)
						{
                    	root=x->parent->child[0];
                    	x->parent->child[0]->parent=NULL;
                    	}
                        free(x);        					
                    }
                }
            }
        }
    }
}
void deletevalue(int value,struct btreenode*x)
{	
	int y;
    struct btreenode*temp=NULL;
	    if(x==NULL)
    {
        cout<<"No element present to delete"<<endl;
        return ;
    }
    else
    {	
        for(int i=0;i<x->n;i++)
        {
            if(x->keys[i]==value && x->child[i]==NULL)     //leaf case
            {
                del_leaf(value,x);
                return ;
            }
            for(int i=0;i<x->n;i++)                   //deletion of non leaf node value by swapping the element with predecessor element in the leaf
        {
            if(x->keys[i]==value)
            {
                  if(x->child[i]!=NULL)
                 {
                         temp=x->child[i];
                        while(temp->child[temp->n]!=NULL)
                        {
                            temp=temp->child[temp->n];
                        }
                        y=x->keys[i];
                        x->keys[i]=temp->keys[temp->n-1];
                        temp->keys[temp->n-1]=y;
                        del_leaf(value,temp);
                        return ;
                 }  
            }
        }
        }
    }
}
int main(){
			int option,value,data;
			btreenode*srch;
			while(1){ 	

	        	cout<<"\nBtree with n=5 is running - Enter your optiion :1:Insert  2:Delete  3:Traversal Inorder  4:Exit 5:Search\n";
	        	cin>>option;
			switch(option){
			       case 1:
			          	cout<<"Enter the integer you want to add \n";
					  	cin>>value;
					  	if (root==NULL)
					  	{
					  		 root= new btreenode();
							root->leaf=true;
							root->n=1;
							root->keys[0]=value;
					  	}
					  	else
							insert(value);
						break;
				   case 2:
				   		cout<<"Enter the integer you want to delete \n ";
						cin>>value;
						srch=search(root,value);
						if(flag1==1){
						deletevalue(value,srch);
						cout<< "Deletion successfull" << endl;
						}
						else
							cout<< "Element not found" << endl;

						break;
				   case 3:
				   		cout<<"the elements in root are\n\t";

				   		for (int i = 0; i < root->n; ++i)
				   		{
				   			cout<<root->keys[i]<<" ";
				   		}
				   		cout<<"\n";
						displayinorder(root);
						break;
					case 4:
						exit(0);
					case 5:
						cout<<"enter element to search\n";
						cin>>value;
					    srch=	search(root,value);
						break;
					default:
						cout<<"Invalid \n";
				}
			}
			return 0;
			}
void displayinorder(struct btreenode*root)    //display function to print the tree
{  
	int i;
    if (root!=NULL)
    {
        for ( i=0;i<root->n;i++)
        {
            displayinorder(root->child[i]);
            cout<<"->"<<root->keys[i]<<" ";
        }
      displayinorder(root->child[i]);
    }
}
btreenode* search(btreenode *x, int k){
		int i=0;
		while(i<x->n && k>x->keys[i])
			i=i+1;
		if(i<x->n && k==x->keys[i]){
			cout<<"Key is found\n";
			flag1=1;
			return x;
		}
		else if (x->leaf)
		{
			cout<<"Key is not found\n";	
			flag1=0;	
			return x;
		}
		else
			return search(x->child[i],k);

}
