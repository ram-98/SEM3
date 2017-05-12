#include<iostream>
#include<malloc.h>
#include<cstdlib>

using namespace std;

struct node         //structure for each node
{
    int count;
    int arr[5];
    struct node*child[6];
    struct node*parent;
};

struct node*root=NULL;
struct node*flag=NULL;
void splittree(struct node*);
void insert(int,struct node*);

void sort(struct node*temp,int n)       //function for sorting the elements while iinserting new element in to the node
{
    int j=temp->count-2,check=-1;
    for(int i=0;i<temp->count-1;i++)
    {
        if(temp->arr[i]>n)
        {
            check=i;
            while(j>=i)
            {
                temp->arr[j+1]=temp->arr[j];
                j--;
            }
            break;
        }
    }
    if(check==-1)             //Element is inserted and greater than all
    {    
        temp->arr[temp->count-1]=n;
    }
    else
    {    
        temp->arr[check]=n;
    }    
}

void splittree(struct node*tree)       //function for splitting the node when the elements in the node are greater than 5
{
    if(tree->parent==NULL)           //Root case
    {   
        struct node*temp1=NULL,*temp2=NULL;
        temp2=(struct node*)malloc(sizeof(struct node));     //memory allocation for creating new node during splitting
        temp1=(struct node*)malloc(sizeof(struct node));
        temp1->arr[0]=tree->arr[2];
        temp1->parent=NULL;                                 //changing the position of pointers and changing the count values during splitting
        root=temp1;
        temp2->arr[0]=tree->arr[3];
        temp2->arr[1]=tree->arr[4];
        temp1->count=1;
        tree->count=2;
        temp2->count=2;
        temp1->child[0]=tree;
        temp1->child[1]=temp2;
        temp1->child[2]=NULL;
        temp1->child[3]=NULL;
        temp1->child[4]=NULL;
        temp1->child[5]=NULL;
        temp2->parent=temp1;
        tree->parent=temp1;
        temp2->child[0]=tree->child[3];
        temp2->child[1]=tree->child[4];
        temp2->child[2]=tree->child[5];
        for(int i=0;i<3;i++)
        {
            if(temp2->child[i]!=NULL)
            {
                temp2->child[i]->parent=temp2;
            }
        }
        temp2->child[3]=NULL;
        temp2->child[4]=NULL;
        temp2->child[5]=NULL;
        tree->child[3]=NULL;
        tree->child[4]=NULL;
        tree->child[5]=NULL;
    }
    else                     //Not root case
    {  
        int p;
        for(int i=0;i<=tree->parent->count;i++)
        {
            if(tree->parent->child[i]==tree)         //to find position
            {   
                p=i;
        		break;
            }
        }
        struct node*temp2=NULL;
        temp2=(struct node*)malloc(sizeof(struct node));     //allocating memory for new node during splitting
        temp2->arr[0]=tree->arr[3];                          //changing the pointers and counts during splitting
        temp2->arr[1]=tree->arr[4];
        tree->count=2;
        temp2->count=2;
        temp2->child[0]=tree->child[3];
        temp2->child[1]=tree->child[4];
        temp2->child[2]=tree->child[5];
        for(int i=0;i<3;i++)
        {
            if(temp2->child[i]!=NULL)
            {
                temp2->child[i]->parent=temp2;
            }
        }
        temp2->child[3]=NULL;
        temp2->child[4]=NULL;
        temp2->child[5]=NULL;
        tree->child[3]=NULL;
        tree->child[4]=NULL;
        tree->child[5]=NULL;
        temp2->parent=tree->parent;
        for(int i=tree->parent->count+1;i>p;i--)
        {
        	tree->parent->child[i]=tree->parent->child[i-1];
        }
        tree->parent->child[p+1]=temp2;
        insert(tree->arr[2],tree->parent);
    }
}

void insert(int n,struct node*tree)                //function to insert the element and check for count property 
{   
    if(tree==NULL)                         //Root case
    {    
        tree=(struct node*)malloc(sizeof(struct node));
        tree->count=1;
        tree->arr[0]=n;
        tree->parent=NULL;
        for(int i=0;i<6;i++)
        {
            tree->child[i]=NULL;
        }
        root=tree;
    }
    else
    {    
        if(tree->count<5)
        {
            tree->count=tree->count +1;
            sort(tree,n);
        }
        if(tree->count==5)
        {
            tree->count=4;
            splittree(tree);
        }        
    }
}

void display(struct node*root)    //display function to print the tree
{  
	int i; 
    if (root!=NULL)
    {
        for (i=0;i<root->count;i++)
        {
            display(root->child[i]);
            cout<<"|->"<<root->arr[i]<<"\t";
        }
        display(root->child[i]);
    }
}
struct node* search_position(int n,struct node*tree)
{     
    if(tree==NULL)
        return tree;
    else
    {
        while(tree!=NULL)
        {                                           //case when the value is greater than all the array elements
            if(tree->arr[(tree->count)-1]<n)
            {   
                if(tree->child[tree->count]==NULL)      //no child
                { 
                    return tree;
                }
                else
                {   
                    tree=tree->child[tree->count];
                }
            }
            else
            {
                for(int i=0;i<tree->count;i++)
                {
                    if(tree->arr[i]>n)
                    {
                        if(tree->child[i]==NULL)
                        {   
                            return tree;
                        }
                        else
                        {    
                            tree=tree->child[i];
                        }
                        break;
                    }
                    else 
                    {
                        if(tree->arr[i]==n)
                       {    cout<<"Element is found"<<endl;
                           flag=(struct node*)malloc(sizeof(struct node));
                           flag->count=-1;
                           return flag;
                       }
                    }
                }
            }
        }
    }
}

struct node*del_search(int n,struct node*tree)     //function to search for the node in which the element to be deleted is found
{    
    if(tree==NULL)
        return tree;
    else                               //Root is not null
    {    
        while(tree!=NULL)
        {
            if(tree->arr[(tree->count)-1]<n)
            {
                if(tree->child[tree->count]==NULL)
                { 
                    flag=(struct node*)malloc(sizeof(struct node));
                    flag->count=-1;
                    return flag;
                }
                else
                {
                    tree=tree->child[tree->count];
                }
            }
            else
            {	
                for(int i=0;i<tree->count;i++)
                {
                    if(tree->arr[i]>n)
                    {
                        if(tree->child[i]==NULL)
                        {
                            flag=(struct node*)malloc(sizeof(struct node));
                            flag->count=-1;
                            return flag;
                        }
                        else
                        {
                            tree=tree->child[i];
                        }
                        break;
                    }
            		if(tree->arr[i]==n)
                    {    //cout<<"Element is found at i="<<i<<endl;
                         return tree;
                    }
                }
            }
        }
    }
}

void del_leaf(int n,struct node*tree)     //function to delete element from the leaf node
{
    struct node*temp;
    int k,t,p;
    for(int i=0;i<tree->count;i++)
    {
    	if(tree->arr[i]==n)
    	{
    		p=i;
    		break;
    	}
    }
    if(tree->parent==NULL||tree->count>2)           //Leaf has more than 2 values
    {	
        for(int i=p;i<tree->count;i++)
        {
            tree->arr[i]=tree->arr[i+1];
            tree->child[i+1]=tree->child[i+2];
        }
        tree->count=tree->count-1;
    }
    else                                       //"Leaf has 2 values
    {	
        for(int i=0;i<=tree->parent->count;i++)
        {
            if(tree->parent->child[i]==tree)
            {
                k=i;
                break;
            }
            
        }
        if(tree->arr[1]==n)
        	t=1;
        else
        	t=0;
        if(k!=0 && ((tree->parent)->child[k-1])->count>2)       //Left shift
        {	
            if(t==1)
            {
                tree->arr[t]=tree->arr[0];
               tree->arr[0]=tree->parent->arr[k-1];
               tree->parent->arr[k-1]=tree->parent->child[k-1]->arr[tree->parent->child[k-1]->count-1];
               tree->parent->child[k-1]->count=tree->parent->child[k-1]->count -1;
            }
            if(t==0)
            {
                tree->arr[0]=tree->parent->arr[k-1];
                tree->parent->arr[k-1]=tree->parent->child[k-1]->arr[tree->parent->child[k-1]->count-1];
               tree->parent->child[k-1]->count=tree->parent->child[k-1]->count -1;
            }
        }
        else
        {	
            if(((k!=0 && ((tree->parent)->child[k-1])->count==2)|| k==0) && (tree->parent)->child[k+1]!=NULL && ((tree->parent)->child[k+1])->count>2)      //Right shift
            {	
                if(t==1)
                {
                    tree->arr[p]=tree->parent->arr[k];
                    tree->parent->arr[k]=tree->parent->child[k+1]->arr[0];
                }
                if(t==0)
                {
                    tree->arr[0]=tree->arr[1];
                    tree->arr[1]=tree->parent->arr[k];
                    tree->parent->arr[k]=tree->parent->child[k+1]->arr[0];
                }
                for(int i=0;i<(((tree->parent)->child[k+1])->count);i++)
                {
                    tree->parent->child[k+1]->arr[i]=tree->parent->child[k+1]->arr[i+1];
                }
                tree->parent->child[k+1]->count=tree->parent->child[k+1]->count -1;
            }
            else           //mergecase
            {	
                if(k!=0 && tree->parent->child[k-1]->count==2 && ((tree->parent->child[k+1]!=NULL && tree->parent->child[k+1]->count==2) || tree->parent->child[k+1]==NULL))
                {	        //left merge case
                    tree->parent->child[k-1]->arr[2]=tree->parent->arr[k-1];
                    if(t==1)
                    {
                    	tree->parent->child[k-1]->arr[3]=tree->arr[0];
                    }
                    else
                    {
                    	tree->parent->child[k-1]->arr[3]=tree->arr[1];
                    }
                    tree->parent->child[k-1]->count=tree->parent->child[k-1]->count +2;
                    for(int i=k-1;i<tree->parent->count-1;i++)
                    {
                        tree->parent->arr[i]=tree->parent->arr[i+1];
                        tree->parent->child[i+1]=tree->parent->child[i+2];
                    }
                    tree->parent->count=tree->parent->count-1;
                    if(tree->parent->count==0)
					{
                    	root=tree->parent->child[0];
                    	tree->parent->child[0]->parent=NULL;
                    }
                }        //left merge completed
                else       //right merge case
                {	
                    if(k==0)
                    {
                        tree->parent->child[k+1]->arr[3]=tree->parent->child[k+1]->arr[1];
                        tree->parent->child[k+1]->arr[2]=tree->parent->child[k+1]->arr[0];
                        tree->parent->child[k+1]->arr[1]=tree->parent->arr[k];
                        if(t==1)
                        {
                        	tree->parent->child[k+1]->arr[0]=tree->arr[0];
                        }
                        else
                        {
                        	tree->parent->child[k+1]->arr[0]=tree->arr[1];
                        }
                        tree->parent->child[k+1]->count=tree->parent->child[k+1]->count+2;
                        for(int i=0;i<tree->parent->count-1;i++)
                        {
                            tree->parent->arr[i]=tree->parent->arr[i+1];
                        }
                        for(int i=0;i<tree->parent->count;i++)
                        {
                            tree->parent->child[i]=tree->parent->child[i+1];
                        }
                        tree->parent->count=tree->parent->count-1;
                        if(tree->parent->count==0)
						{
                    	root=tree->parent->child[0];
                    	tree->parent->child[0]->parent=NULL;
                    	}
                        free(tree);        //right merge completed
                    }
                }
            }
        }
    }
}

void del(int n,struct node*tree)
{	
    struct node*temp=NULL;
    int x;
    if(tree==NULL)
    {
        cout<<"No element present to delete"<<endl;
        return ;
    }
    else
    {	
        for(int i=0;i<tree->count;i++)
        {
            if(tree->arr[i]==n && tree->child[i]==NULL)     //leaf case
            {
                del_leaf(n,tree);
                return ;
            }
        }
        for(int i=0;i<tree->count;i++)                   //deletion of non leaf node value by swapping the element with predecessor element in the leaf
        {
            if(tree->arr[i]==n)
            {
                  if(tree->child[i]!=NULL)
                 {
                         temp=tree->child[i];
                        while(temp->child[temp->count]!=NULL)
                        {
                            temp=temp->child[temp->count];
                        }
                        x=tree->arr[i];
                        tree->arr[i]=temp->arr[temp->count-1];
                        temp->arr[temp->count-1]=x;
                        del_leaf(n,temp);
                        return ;
                 }  
            }
        }       
    }    
}

int main()
{
    struct node*temp;
    temp=(struct node*)malloc(sizeof(struct node));
    int c,n,i=1;
    while(i>0)
    {
        cout<<"Enter 1 to insert a number"<<endl;
        cout<<"Enter 2 to delete a number"<<endl;
        cout<<"Enter 3 to print all the numbers"<<endl;
        cout<<"Enter 4 to exit"<<endl;
        cin>>c;
        switch(c)
        {
            case 1:
                cout<<"Enter the number to be inserted"<<endl;
                cin>>n;
                temp=search_position(n,root); 
                if(temp!=NULL && temp->count==-1)
                    cout<<"Element already exists "<<endl;
                else
                    insert(n,temp);
                break;
                
            case 2:
                cout<<"Enter the element to be deleted"<<endl;
                cin>>n;
                temp=del_search(n,root);
                if(temp!=NULL &&temp->count==-1)
                    cout<<"Element is not present to delete"<<endl;
                else
                    del(n,temp);
                break;
                
            case 3:
            	cout<<"Inorder Printing:"<<endl;
                display(root);
                break;
                
            case 4:
                exit(i);
                
            default:
                cout<<"wrong input...."<<endl;
        }
    }
}
